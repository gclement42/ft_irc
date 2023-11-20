/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/20 10:03:08 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"
#include "Channel.hpp"

static std::vector<std::string> 	getAllChannels(std::vector<std::string> args);

static int 			checkArgs(std::vector<std::string> args, Client &client);
static int 			checkChannelExist(std::string channelName, std::map<std::string, Channel> channels);
static int 			checkAll(std::string channelName, Client &client, std::map<std::string, Channel> channels);
static int 			checkKey(std::string channelName, std::vector<std::string> keys, std::map<std::string, Channel> channels, int i);


void	Commands::join()
{	
	std::vector<std::string> 	argChannel = getAllChannels(_args);
	std::vector<std::string> 	keys = this->parseKey(_args);
	std::string					topic;

	if (checkArgs(_args, _client) == FAILURE)
		return ;

	for (size_t i = 0; i < argChannel.size(); i++)
	{
		if (checkChannelExist(argChannel[i], _channels) == FAILURE)
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
		
		if (checkKey(argChannel[i], keys, _channels, i) == SUCCESS && checkAll(argChannel[i], _client, _channels) == SUCCESS)
			allSend(_client, argChannel[i], topic);
		else
			_client.addMessageToSend(ERR_BADCHANNELKEY(argChannel[i]));
	}
}

void	Commands::allSend(Client &client, std::string channel, std::string topic)
{
	std::string		createChannel = RPL_JOIN(client.getNickname(), channel);

	client.addMessageToSend(createChannel);
	addChannelInMap(client.getNickname(), channel);
	this->displayListClientOnChannel(channel);

	if (topic.empty() == false)
		client.addMessageToSend(":irc 332 " + client.getNickname() + " " + channel + " " + topic + "\r\n");
}




// ===== STATIC FUNCTIONS ===== //

static std::vector<std::string> getAllChannels(std::vector<std::string> args)
{
	std::vector<std::string> 	targets;
	std::string 				tmp;
	
	for (size_t i = 1; i < args.size(); i++)
	{
		if (args[i][0] == ':')
			break;
		else
		{
			size_t pos = args[i].find(",");
			if (pos != std::string::npos)
			{
				targets.push_back(args[i].substr(0, pos));
				targets.push_back(args[i].substr(pos + 1, args[i].size()));
			}
			else
				targets.push_back(args[i]);
		}
	}
	
	return (targets);
}

static int checkArgs(std::vector<std::string> args, Client &client)
{
	if (!(args[1][0] == '#' || args[1][0] == '&'))
	{
		client.addMessageToSend(ERR_NOSUCHCHANNEL(client.getNickname(), args[1]));
		return (FAILURE);
	}
	if ((args.size() > 2) && (!(args[2][0] == '#' || args[2][0] == '&')))
	{
		client.addMessageToSend(ERR_NOSUCHCHANNEL(client.getNickname(), args[2]));
		return (FAILURE);
	}
	return (SUCCESS);
}

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

	if (it->second.getUserCount() >= it->second.getUserLimit())
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