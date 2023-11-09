/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/08 13:12:00 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

static std::vector<std::string> 	parseChannelName(std::vector<std::string> arg);
static std::vector<std::string> 	parseKey(std::vector<std::string> arg);
// static int							checkChannelNameAlreadyExist(std::vector<Channel> channels, std::string channelName);

void	commandJoin(Client &client, std::vector<std::string> arg)
{	
	std::vector<std::string> 	argChannel = parseChannelName(arg);
	std::vector<std::string> 	keys = parseKey(arg);
	std::string 				tmpKey;

	for (size_t i = 0; i < argChannel.size(); i++)
	{
		std::string 	createChannel = ":" + client.getUsername() + " JOIN " + argChannel[i] + "\r\n";

		Channel newChannel(argChannel[i], "topic", "key", "mode", USER_LIMITS);

		client.getChannels().push_back(newChannel);
        client.addMessageToSend(createChannel);
	}
}

static std::vector<std::string> parseChannelName(std::vector<std::string> arg)
{
	std::vector<std::string> 	channelName;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i][0] == '#' || arg[i][0] == '&')
			channelName.push_back(arg[i]);
	}

	return (channelName);
}

static std::vector<std::string> parseKey(std::vector<std::string> arg)
{
	std::vector<std::string> 	keys;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (!(arg[i][0] == '#' || arg[i][0] == '&'))
			keys.push_back(arg[i]);
	}

	return (keys);
}

// static int	checkChannelNameAlreadyExist(std::vector<Channel> channels, std::string channelName)
// {
// 	for (size_t i = 0; i < channels.size(); i++)
// 	{
// 		if (channels[i].getName() == channelName)
// 			return (SUCCESS);
// 	}
// 	return (FAILURE);
// }