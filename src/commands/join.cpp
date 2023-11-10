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
#include "Channel.hpp"

void	Commands::join()
{	
	std::vector<std::string> 	argChannel = parseChannelName(_args);
	std::vector<std::string> 	keys = parseKey(_args);
	std::string 				tmpKey;

	for (size_t i = 0; i < argChannel.size(); i++)
	{
		std::string 	createChannel = ":" + _client.getUsername() + " JOIN " + argChannel[i] + "\r\n";

		Channel newChannel(argChannel[i], "topic", "key", "mode", USER_LIMITS);

		_channels.insert(std::pair<std::string, Channel>(argChannel[i], newChannel));
        _client.addMessageToSend(createChannel);
	}
}

std::vector<std::string>		Commands::parseChannelName(std::vector<std::string> arg)
{
	std::vector<std::string> 	channelName;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i][0] == '#' || arg[i][0] == '&')
			channelName.push_back(arg[i]);
	}

	return (channelName);
}

std::vector<std::string>		Commands::parseKey(std::vector<std::string> arg)
{
	std::vector<std::string> 	keys;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (!(arg[i][0] == '#' || arg[i][0] == '&'))
			keys.push_back(arg[i]);
	}

	return (keys);
}