/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:36:33 by gclement          #+#    #+#             */
/*   Updated: 2023/11/15 15:36:33 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

static void parseArgs(std::vector<std::string> args,std::vector<std::string> &channelNames, std::string &reason);

void Commands::part()
{
	std::vector <std::string>	channelNames;
	std::string 				reason;

	if (_args.size() < 2) {
		_client.addMessageToSend(ERR_NEEDMOREPARAMS(_client.getNickname(), _args[0]));
		return ;
	}
	parseArgs(_args, channelNames, reason);
	for (size_t i = 0; i < channelNames.size(); i++) {
		if (!checkIfChannelExist(channelNames[i])) {
			_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), channelNames[i]));
			return ;
		}
		if (!checkIfThisUserIsOnChannel(channelNames[i])) {
			_client.addMessageToSend(ERR_NOTONCHANNEL(_client.getNickname(), channelNames[i]));
			return ;
		}
		std::cout << "delete :" << *_client.getChannels().erase(_client.getChannels().begin() + i) << std::endl;
		_client.addMessageToSend(RPL_PART(_client.getNickname(), channelNames[i], reason));
		_client.getChannels().erase(_client.getChannels().begin() + i);
		displayListClientOnChannel(channelNames[i]);
	}
	return ;
}

static void parseArgs(std::vector<std::string> args, std::vector<std::string> &channelNames, std::string &reason)
{
	for (size_t i = 1; i < args.size(); i++)
	{
		if (args[i][0] == '#' || args[i][0] == '&')
			channelNames.push_back(args[i]);
		else
			reason += args[i] + " ";
	}
}
