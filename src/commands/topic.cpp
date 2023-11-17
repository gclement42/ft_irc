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

static std::string	concatenate(std::vector<std::string> stringTab);
static std::string	getTimeString();

void	Commands::topic() {

    std::vector<std::string> channelName = this->parseChannelName(this->_args);
    if (channelName.empty())
	{
		this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "TOPIC"));
		return ;
	}

    std::vector<std::string> topicNameTab = this->parseKey(this->_args);
	std::map<std::string, Channel>::iterator channel = this->_channels.find(channelName[0]);

	if (channel == this->_channels.end())
		this->_client.addMessageToSend(ERR_NOSUCHCHANNEL(this->_client.getNickname(), channelName[0]));
	else if (this->checkIfThisUserIsOnChannel(channel->first) == false)
		this->_client.addMessageToSend(ERR_NOTONCHANNEL(this->_client.getNickname(), channel->first));
    else if (topicNameTab.empty())
	{
		if (channel->second.getTopic().empty())
			this->_client.addMessageToSend(RPL_NOTOPIC(this->_client.getNickname(), channel->first));
		else
			this->_client.addMessageToSend(RPL_TOPIC(this->_client.getNickname(), channel->first, channel->second.getTopic()));
	}
    else
	{
		std::vector<std::string> clientsList = allClientsOnChannel(channel->first);
		std::string topicName = concatenate(topicNameTab);

		channel->second.setTopic(topicName);

		sendMsgToAllClientsInChannel(clientsList, RPL_TOPIC(this->_client.getNickname(), channel->first, topicName));
		sendMsgToAllClientsInChannel(clientsList, RPL_TOPICWHOTIME(this->_client.getNickname(), channel->first, this->_client.getNickname(), getTimeString()));
	}
}

static std::string	concatenate(std::vector<std::string> stringTab)
{
	std::string concatString;
	for (std::vector<std::string>::iterator it = stringTab.begin(); it != stringTab.end(); ++it) {
		concatString += *it + " ";
	}
	return concatString;
}

std::string		getTimeString()
{
	std::time_t currentTime = std::time(0);
	std::stringstream ss;
	ss << currentTime;
	return (ss.str());
}
