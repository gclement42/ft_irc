/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:34:14 by maujogue          #+#    #+#             */
/*   Updated: 2023/11/07 15:43:41 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include <ctime>
#include <sstream>

static std::vector<std::string>		parseChannelName(std::vector<std::string> arg)
{
    std::vector<std::string> 	channelName;

    for (size_t i = 0; i < arg.size(); i++)
    {
        if (arg[i][0] == '#' || arg[i][0] == '&')
            channelName.push_back(arg[i]);
    }

    return (channelName);
}

static std::vector<std::string>		parseKey(std::vector<std::string> arg)
{
    std::vector<std::string> 	keys;
//    std::cout << "[";
    for (size_t i = 1; i < arg.size(); i++)
    {
        if (!(arg[i][0] == '#' || arg[i][0] == '&'))
            keys.push_back(arg[i]);
//        std::cout << arg[i] << "-";
    }
//    std::cout << "]" << std::endl;
    return (keys);
}

static void		setTopic(Client &client, std::map<std::string, Channel>::iterator &channel, std::vector<std::string> parseTopicTab)
{
	std::string topicName;

	for(long unsigned int i = 0; i < parseTopicTab.size(); i++)
		topicName += parseTopicTab[i] + " ";
	//check mode
	channel->second.setTopic(topicName);
	std::string topicMessage = RPL_TOPIC(client.getNickname(), channel->first, topicName);
	client.addMessageToSend(topicMessage);

	std::time_t currentTime = std::time(0);
	std::stringstream ss;
	ss << currentTime;
	std::string timeString = ss.str();

	std::string topicWhoTimeMessage = RPL_TOPICWHOTIME(client.getNickname(), channel->first,client.getNickname(), timeString);
	client.addMessageToSend(topicWhoTimeMessage);
}

void	Commands::topic()
{
    std::map<std::string, Channel>::iterator channel;
    std::vector<std::string> parseTopicTab;
    std::vector<std::string> tempChannelName;

    tempChannelName = parseChannelName(this->_args);
    if (tempChannelName.empty())
		return ;
    parseTopicTab = parseKey(this->_args);
    channel = this->_channels.find(tempChannelName[0]);
    if (channel == this->_channels.end())
		this->_client.addMessageToSend(ERR_NOSUCHCHANNEL(this->_client.getNickname(), tempChannelName[0]));
    else if (parseTopicTab.empty())
	{
		if (channel->second.getTopic().empty())
			this->_client.addMessageToSend(RPL_NOTOPIC(this->_client.getNickname(), channel->first));
		else
			this->_client.addMessageToSend(RPL_TOPIC(this->_client.getNickname(), channel->first, channel->second.getTopic()));
	}
    else
		setTopic(this->_client, channel, parseTopicTab);
}
//  461     ERR_NEEDMOREPARAMS