/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/20 15:12:07 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"
#include "Channel.hpp"

static std::vector<std::string> 	getAllChannels(std::string args);
static std::string 					getKeyString(std::vector<std::string> args);

static bool	checkArgs(std::vector<std::string> args, Client &client);
static bool	checkChannelExist(std::string channelName, std::map<std::string, Channel> channels);
static bool	checkAll(std::string channelName, Client &client, std::map<std::string, Channel> channels);
static bool	checkKey(std::string channelName, std::string keys, std::map<std::string, Channel> channels, int i);


void	Commands::join()
{	
	std::vector<std::string> 	argChannel = getAllChannels(_args[1]);
	std::string					keys = getKeyString(_args);
	std::string					topic;

	if (!checkArgs(_args, _client))
		return ;

	for (size_t i = 0; i < argChannel.size(); i++)
	{
		if (!checkChannelExist(argChannel[i], _channels))
		{
			Channel newChannel(argChannel[i], "", "", "", USER_LIMITS);
			
			newChannel.incrementUserCount();
			newChannel.addOperator(_client.getNickname());
			_channels.insert(std::pair<std::string, Channel>(argChannel[i], newChannel));
			topic = newChannel.getTopic();
		}
		else
		{
			std::map<std::string, Channel>::iterator it;

			it = _channels.find(argChannel[i]);
			it->second.incrementUserCount();
			topic = it->second.getTopic();
		}
		if (!checkKey(argChannel[i], keys, _channels, i))
			_client.addMessageToSend(ERR_BADCHANNELKEY(argChannel[i]));
		else if (checkAll(argChannel[i], _client, _channels))
			addClientInChannel(argChannel[i], topic);
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

static std::vector<std::string> getAllChannels(std::string arg)
{
	std::vector<std::string> 	targets;
	size_t 						pos;
	
	pos = arg.find(",");
	if (pos != std::string::npos)
	{
		targets.push_back(arg.substr(0, pos));
		targets.push_back(arg.substr(pos + 1, arg.size()));
	}
	else
		targets.push_back(arg);

	return (targets);
}

static std::string getKeyString(std::vector<std::string> args)
{
	std::string key;

	if (args.size() == 3 && args[2].empty() != true)
		key = args[2];
	else
		key = "";
	return (key);
}

static bool checkArgs(std::vector<std::string> args, Client &client)
{
	if (!(args[1][0] == '#' || args[1][0] == '&'))
	{
		client.addMessageToSend(ERR_NOSUCHCHANNEL(client.getNickname(), args[1]));
		return (false);
	}
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

static bool checkKey(std::string channelName, std::string keys, std::map<std::string, Channel> channels, int i)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);
	size_t 				pos;

	if (it->second.getKey().empty() == true)
		return (true);
	if (keys.empty() == true)
		return (false);
	
	pos = keys.find(",");
	if (pos != std::string::npos)
	{
		if (i == 0)
		{
			if (keys.substr(0, pos) == it->second.getKey())
				return (true);	
		}
		else if (i == 1)
		{
			if (keys.substr(pos + 1, keys.size()) == it->second.getKey())
				return (true);
		}
	}
	else
	{
		if (keys == it->second.getKey() && i == 0)
			return (true);
	}
	return (false);
}

static bool checkAll(std::string channelName, Client &client, std::map<std::string, Channel> channels)
{
	std::map<std::string, Channel>::iterator it;
	it = channels.find(channelName);
	Channel channel = it->second;

	std::cout << "getlimitmode :" << channel.getLimitMode() << std::endl;
	if (channel.getLimitMode() && channel.getUserCount() >= channel.getUserLimit())
	{
		client.addMessageToSend(ERR_CHANNELISFULL(channelName));
		return (false);
	}
	if (channel.getInviteMode() == true)
	{
		client.addMessageToSend(ERR_INVITEONLYCHAN(channelName));
		return (false);
	}
	return (true);
}