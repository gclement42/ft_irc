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

std::vector<Client>	getChannelClients(std::string channelName, std::map<int, Client> clientTab)
{
	std::vector<Client> clients;

	for (std::map<int, Client>::iterator it = clientTab.begin(); it != clientTab.end(); it++)
	{
		if (std::find(it->second.getChannels().begin(), it->second.getChannels().end(), channelName) != it->second.getChannels().end())
		{
			clients.push_back(it->second);
			std::cout << it->second << std::endl;
		}
	}
	return clients;
}

static void		setTopic(std::map<std::string, Channel>::iterator &channel, std::vector<std::string> parseTopicTab, std::vector<Client> clientsList) {
	std::string topicName;

	for (long unsigned int i = 0; i < parseTopicTab.size(); i++)
		topicName += parseTopicTab[i] + " ";
	//check mode
	channel->second.setTopic(topicName);
//	std::cout << "-->[" ;
	for (size_t i = 0; i < clientsList.size(); i++)
	{
		std::string topicMessage = RPL_TOPIC(clientsList[i].getNickname(), channel->first, topicName);
//		std::cout << clientsList[i] << ",";
		clientsList[i].addMessageToSend(topicMessage);
		clientsList[i].setWaitingForSend(true);
		std::time_t currentTime = std::time(0);
		std::stringstream ss;
		ss << currentTime;
		std::string timeString = ss.str();

		std::string topicWhoTimeMessage = RPL_TOPICWHOTIME(clientsList[i].getNickname(), channel->first, channel->second.getTopic(), timeString);
		clientsList[i].addMessageToSend(topicWhoTimeMessage);
	}
//	std::cout << "]" << std::endl ;
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
	{
		std::vector<Client> clientsList = getChannelClients(channel->first, this->_clients);
		setTopic(channel, parseTopicTab, clientsList);
	}
}
//  461     ERR_NEEDMOREPARAMS