/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/15 13:11:03 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"
#include "Channel.hpp"

static int 			checkChannelExist(std::string channelName, std::map<std::string, Channel> channels);
static int 			checkAll(std::string channelName, Client &client, std::map<std::string, Channel> channels);
static int 			checkKey(std::string channelName, std::vector<std::string> keys, std::map<std::string, Channel> channels, int i);

void	Commands::join()
{	
	std::vector<std::string> 	argChannel = this->parseChannelName(_args);
	std::vector<std::string> 	keys = this->parseKey(_args);
	std::string					topic;

	for (size_t i = 0; i < argChannel.size(); i++)
	{
		if (checkChannelExist(argChannel[i], _channels) == FAILURE)
		{
			Channel newChannel(argChannel[i], "", "", "", USER_LIMITS);
			
			newChannel.incrementUserCount();
			_channels.insert(std::pair<std::string, Channel>(argChannel[i], newChannel));
			_client.setIsOperator(true);
			topic = newChannel.getTopic();
		}
		else
		{
			std::map<std::string, Channel>::iterator it;

			it = _channels.find(argChannel[i]);
			it->second.incrementUserCount();
			topic = it->second.getTopic();
		}
		
		if (checkKey(argChannel[i], keys, _channels, i) == SUCCESS && checkAll(argChannel[i], _client, _channels) == SUCCESS)
			allSend(_client, argChannel[i], topic);
		else
			_client.addMessageToSend(ERR_BADCHANNELKEY(argChannel[i]));
	}
}

void	Commands::allSend(Client &client, std::string channel, std::string topic)
{
	std::string		createChannel = RPL_JOIN(client.getNickname(), channel);

	client.addChannel(channel);
	client.addMessageToSend(createChannel);
	addChannelInMap(client.getNickname(), channel);
	this->displayListClientOnChannel(channel);

	if (topic.empty() == false)
		client.addMessageToSend(":irc 332 " + client.getNickname() + " " + channel + " " + topic + "\r\n");
}

// ===== STATIC FUNCTIONS ===== //

static int checkChannelExist(std::string channelName, std::map<std::string, Channel> channels)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);

	if (it != channels.end())
		return (SUCCESS);
	return (FAILURE);
}

static int checkKey(std::string channelName, std::vector<std::string> keys, std::map<std::string, Channel> channels, int i)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);

	if (it->second.getKey().empty() == true)
		return (SUCCESS);
	if (keys.size() != 0 && keys[i].empty() == false)
	{
		if (it->second.getKey() == keys[i])
			return (SUCCESS);
	}
	return (FAILURE);
}

static int checkAll(std::string channelName, Client &client, std::map<std::string, Channel> channels)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);

	if (it->second.getUserCount() >= USER_LIMITS)
	{
		client.addMessageToSend(ERR_CHANNELISFULL(channelName));
		return (FAILURE);
	}
	if (it->second.getInviteMode() == true)
	{
		client.addMessageToSend(ERR_INVITEONLYCHAN(channelName));
		return (FAILURE);
	}
		
	return (SUCCESS);
}
