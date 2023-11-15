/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/15 08:37:30 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Channel.hpp"

static std::vector<std::string>		parseChannelName(std::vector<std::string> arg);
static std::vector<std::string>		parseKey(std::vector<std::string> arg);

static int 			checkChannelExist(std::string channelName, std::map<std::string, Channel> channels);
static int 			checkAll(std::string channelName, Client &client, std::map<std::string, Channel> channels);
static int 			checkKey(std::string channelName, std::vector<std::string> keys, std::map<std::string, Channel> channels, int i);
static std::string 	getListUsers(std::string channelName, std::map<int, Client> clients);

void	Commands::join()
{	
	std::vector<std::string> 	argChannel = parseChannelName(_args);
	std::vector<std::string> 	keys = parseKey(_args);
	std::string 				createChannel; 
	std::string					messageDisplayUsers;
	std::string					listUsers;
	std::string					topic;
	std::string 				tmpKey;
	bool		 				isNewChannel;
	bool 						status;

	for (size_t i = 0; i < argChannel.size(); i++)
	{
		isNewChannel = false;
		status = true;

		if (checkChannelExist(argChannel[i], _channels) == FAILURE)
		{
			Channel newChannel(argChannel[i], "topic", "key", "", USER_LIMITS);
			
			isNewChannel = true;
			newChannel.incrementUserCount();
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
		
		if (checkKey(argChannel[i], keys, _channels, i) == FAILURE)
		{
			_client.addMessageToSend(ERR_BADCHANNELKEY(argChannel[i]));
			status = false;
		}
		
		if (status == true && checkAll(argChannel[i], _client, _channels) == SUCCESS)
		{	
			createChannel = ":" + _client.getNickname() + " JOIN " + argChannel[i] + "\r\n";
			listUsers = getListUsers(argChannel[i], _clients);
			if (isNewChannel == true)
				listUsers = listUsers + " @" + _client.getNickname();
			else
				listUsers = listUsers + " " + _client.getNickname();
			std::cout << "\n\nlistUsers: " << listUsers << std::endl;
			messageDisplayUsers = RPL_NAMREPLY(_client.getNickname(), argChannel[i], listUsers);
			
			_client.addChannel(argChannel[i]);
			_client.addMessageToSend(createChannel);
			_client.addMessageToSend(messageDisplayUsers);
			if (topic.empty() == false)
				_client.addMessageToSend(":irc 332 " + _client.getNickname() + " " + argChannel[i] + " " + topic + "\r\n");
		}
	}
}




// ===== STATIC FUNCTIONS ===== //

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

	for (size_t i = 1; i < arg.size(); i++)
	{
		if (!(arg[i][0] == '#' || arg[i][0] == '&'))
			keys.push_back(arg[i]);
	}

	return (keys);
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

static std::string 	getListUsers(std::string channelName, std::map<int, Client> clients)
{
	std::string 	listUsers;
	std::map<int, Client>::iterator it;
	
	for (it = clients.begin(); it != clients.end(); it++)
	{
		for (size_t i = 0; i < it->second.getChannels().size(); i++)
		{
			if (it->second.getChannels()[i] == channelName)
				listUsers += it->second.getNickname() + " ";
		}
	}
	std::cout << "listUsers: " << listUsers << std::endl;
	return (listUsers);
}
