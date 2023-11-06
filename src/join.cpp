/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/03 15:07:57 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"
#include "Client.hpp"

static std::string parseChannelName(std::string buffer);
static std::string parseKey(std::string arg);

void	commandJoin(std::string buffer)
{
	std::string		channelName = parseChannelName(buffer);
	std::string		key = parseKey(buffer);
	std::string		joinMessage = "Now talking on " + channelName;
	if (channelName.empty())
	{
		printError("Channel name is empty");
		return ;
	}

	send(4, joinMessage.c_str(), joinMessage.length(), 0);
	// send(client.fd, joinMessage.c_str(), joinMessage.length(), 0);

	std::cout << "Channel name: '" << channelName << "'" << std::endl;
}

static std::string parseChannelName(std::string arg)
{
	int				status = FAILURE;
	
	if (arg.find("#", 0) == 0 || arg.find("&", 0) == 0)
		status = SUCCESS;
	else
	{
		printError("Wrong channel name. Please use `#` or `&` to start a channel name.");
		return ("");
	}

	if (arg.find(" ", 0) < 1024 || arg.find(",", 0) < 1024)
	{
		printError("Wrong channel name. You cannot use a ` ` or a `,` in the channel name.");
		return ("");
	}
	return (arg);
}

static std::string parseKey(std::string arg)
{
	std::string		key;
	size_t			first_space;
	size_t			length;

	first_space = arg.find(" ", 0);
	length = arg.length() - 1;
	key = arg.substr(first_space + 1, length);
	if (key.empty())
	{
		printError("Key is empty");
		return ("");
	}
	std::cout << "Key: '" << key << "'" << std::endl;
	return (key);
}

// static void displayChannelInfos(Client client, Channel channel)
// {
// 	std::string clientMessage = "Client " + client.nickname + " joined channel " + channel.name;
// 	std::string topicMessage = "Topic: " + channel.topic;

// 	if (channel.topic.empty() != true)
// 		send(4, topicMessage.c_str(), topicMessage.length(), 0);
// 	send(4, clientMessage.c_str(), clientMessage.length(), 0);
// }