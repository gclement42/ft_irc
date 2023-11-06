/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/06 14:21:42 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

static std::string parseChannelName(std::string buffer);
static std::string parseKey(std::string arg);

void	commandJoin(Client client, std::string buffer)
{	
	std::string		channelName = parseChannelName(buffer);
	std::string		key 		= parseKey(buffer);
	std::string		joinMessage = "Now talking on " + channelName + "\r\n";
	
	if (channelName.empty())
		return ;
	
	std::string 	clientMessage = "Client " + client.getNickname() + " joined channel " + channelName + "\r\n";

	send(client.getFd(), clientMessage.c_str(), clientMessage.length(), 0);
	send(client.getFd(), joinMessage.c_str(), joinMessage.length(), 0);

	std::string 	createChannel = ":" + client.getUsername() + " JOIN " + channelName + "\r\n";
	send(client.getFd(), createChannel.c_str(), createChannel.length(), 0);
}

static std::string parseChannelName(std::string arg)
{
	int		status = FAILURE;
	size_t	first_space;
	
	if (arg.find("#", 0) == 0 || arg.find("&", 0) == 0)
		status = SUCCESS;
	else
	{
		printError("Wrong channel name. Please use `#` or `&` to start a channel name.");
		return ("");
	}

	first_space = arg.find(" ", 0);
	if (first_space == std::string::npos)
		return (arg);
	else
		arg = arg.substr(0, first_space);
	return (arg);
}

static std::string parseKey(std::string arg)
{
	std::string		key;
	size_t			first_space;
	size_t			length;

	first_space = arg.find(" ", 0);
	if (first_space == std::string::npos)
		return ("");
	length = arg.length();
	key = arg.substr(first_space + 1, length);
	if (key.empty())
	{
		printError("Key is empty");
		return ("");
	}
	return (key);
}