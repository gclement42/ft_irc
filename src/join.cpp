/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:20:34 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/08 11:04:43 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

static std::vector<std::string> 	parseChannelName(std::vector<std::string> arg);
static std::vector<std::string> 	parseKey(std::vector<std::string> arg);

void	commandJoin(Client &client, std::vector<std::string> arg, std::map<std::string, Channel> &channels)
{	
	std::vector<std::string> 	argChannel = parseChannelName(arg);
	std::vector<std::string> 	keys = parseKey(arg);
	std::string 				tmpKey;

	for (size_t i = 0; i < argChannel.size(); i++)
	{
		std::string 	createChannel = ":" + client.getUsername() + " JOIN " + argChannel[i] + "\r\n";

		Channel newChannel(argChannel[i], "topic", "key", "mode", USER_LIMITS);

		channels.insert(std::pair<std::string, Channel>(argChannel[i], newChannel));
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