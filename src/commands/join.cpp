/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/24 14:13:59 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"
#include "Channel.hpp"

static std::vector<std::string> split(std::string arg);

static bool checkChannelNameIsValid(std::string channelName);
static bool	checkChannelExist(std::string channelName, std::map<std::string, Channel> channels);
static bool	checkAll(std::string channelName, Client &client, std::map<std::string, Channel> &channels);
static bool checkKey(std::string channelName, std::vector<std::string> keys, std::map<std::string, Channel> channels, size_t i);

void	Commands::join()
{	
	std::vector<std::string> 	argChannel;
	std::vector<std::string> 	keys;
	std::string					topic;
	bool						isChannelValid = true;

	if (this->_args.size() < 2)
	{
		std::cout << "ERROR: Not enough parameters" << std::endl;
		return ;
	}
	
	argChannel = split(_args[1]);
	if (_args.size() > 2)
		keys = split(_args[2]);
	
	for (size_t i = 0; i < argChannel.size(); i++)
	{
		if (!checkChannelNameIsValid(argChannel[i]))
		{
			_client.addMessageToSend(ERR_BADCHANMASK(argChannel[i]));
			isChannelValid = false;
		}
		else if (!checkChannelExist(argChannel[i], _channels))
		{
			Channel newChannel(argChannel[i], "", "", "", USER_LIMITS);
			
			newChannel.addOperator(_client.getNickname());
			_channels.insert(std::pair<std::string, Channel>(argChannel[i], newChannel));
			topic = newChannel.getTopic();
		}
		else
		{
			std::map<std::string, Channel>::iterator it;

			it = _channels.find(argChannel[i]);
			topic = it->second.getTopic();
		}
		
		if (isChannelValid && !checkKey(argChannel[i], keys, _channels, i))
			_client.addMessageToSend(ERR_BADCHANNELKEY(argChannel[i]));
		else if (isChannelValid && checkAll(argChannel[i], _client, _channels))
		{
			_channels.find(argChannel[i])->second.incrementUserCount();
			addClientInChannel(argChannel[i], topic);
		}
	}
}

void	Commands::addClientInChannel(std::string channel, std::string topic)
{
	std::string		createChannel = RPL_JOIN(_client.getNickname(), channel);

	_client.addMessageToSend(createChannel);
	addChannelInMap(_client.getNickname(), channel);
	this->displayListClientOnChannel(channel);

	if (!topic.empty())
		_client.addMessageToSend(RPL_TOPIC(_client.getNickname(), channel, topic));
}

// ===== STATIC FUNCTIONS ===== //

static std::vector<std::string> split(std::string arg)
{
	std::vector<std::string> 	targets;
	size_t 						i;

	i = 0;
	while (i < arg.size())
	{
		if (arg[i] == ',')
		{
			targets.push_back(arg.substr(0, i));
			arg = arg.substr(i + 1, arg.size());
			i = 0;
		}
		i++;
	}
	targets.push_back(arg);

	return (targets);
}

static bool checkChannelNameIsValid(std::string channelName)
{
	if (channelName.empty() || channelName.size() <= 1)
		return (false);
	if (channelName[0] != '#' && channelName[0] != '&')
		return (false);
	return (true);
}

static bool checkChannelExist(std::string channelName, std::map<std::string, Channel> channels)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);

	if (it != channels.end())
		return (true);
	return (false);
}

static bool checkKey(std::string channelName, std::vector<std::string> keys, std::map<std::string, Channel> channels, size_t i)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);

	if (it->second.getKey().empty())
		return (true);

	if (keys.size() > i && keys[i] == it->second.getKey())
		return (true);
	return (false);
}

static bool checkAll(std::string channelName, Client &client, std::map<std::string, Channel> &channels)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);
	Channel channel = it->second;
	
	if (channel.getLimitMode() && (channel.getUserCount() >= channel.getUserLimit()))
	{
		client.addMessageToSend(ERR_CHANNELISFULL(channelName));
		return (false);
	}		
	if (channel.getInviteMode() && !channel.checkIfClientIsInvited(client.getNickname()))
	{
		client.addMessageToSend(ERR_INVITEONLYCHAN(channelName));
		return (false);
	}

	return (true);
}