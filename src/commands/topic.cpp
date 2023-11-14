/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:34:14 by maujogue          #+#    #+#             */
/*   Updated: 2023/11/14 08:16:44 by lboulatr         ###   ########.fr       */
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

static void		RPL_TOPIC(Client &client, std::map<std::string, Channel>::iterator channel, std::vector<std::string> parseTopicTab)
{
	std::string topicName;

	for(long unsigned int i = 0; i < parseTopicTab.size(); i++)
		topicName += parseTopicTab[i] + " ";
	//check mode
	channel->second.setTopic(topicName);
	std::string topicMessage = ":irc 332 " + client.getNickname() + " " + channel->first + " " + topicName + "\r\n";
	client.addMessageToSend(topicMessage);

	std::time_t currentTime = std::time(0);
	std::stringstream ss;
	ss << currentTime;
	std::string timeString = ss.str();

	std::string topicWhoTimeMessage = ":irc 333" +  client.getNickname() + " " + channel->first + " " + client.getNickname() + " " + timeString + "\r\n";
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
    {
		std::cout << "OK!" << std::endl;
        std::string 	emptyTopicMessage = ":irc 403 " + this->_client.getNickname() + " "  + tempChannelName[0] + " :No such channel\r\n";
        this->_client.addMessageToSend(emptyTopicMessage);
    }
    else if (parseTopicTab.empty())
	{
		std::string 	emptyTopicMessage;
		if (channel->second.getTopic().empty())
        	emptyTopicMessage = ":irc 331 " + this->_client.getNickname() + " "  + channel->first + " :No topic is set\r\n";
		else
			emptyTopicMessage = ":irc 332 " + this->_client.getNickname() + " "  + channel->first + " " + channel->second.getTopic() + "\r\n";
		this->_client.addMessageToSend(emptyTopicMessage);
	}
    else
		RPL_TOPIC(this->_client, channel, parseTopicTab);
}
//  461     ERR_NEEDMOREPARAMS