/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:17 by maujogue          #+#    #+#             */
/*   Updated: 2023/11/15 15:30:17 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/main.hpp"
#include <sstream>
#include <string>

std::vector<std::string>	parseComaSeparatedArgs(Commands *cmds, std::vector<std::string> arg)
{
	size_t i = 1;

	while (arg[i].find("#") != std::string::npos || arg[i].find("&") != std::string::npos)
		i++;
	return (cmds->splitByComa(arg[i]));
}

std::vector<Client>	getclientsToKick(Commands *cmds, std::vector<std::string> &usersTab)
{
	std::vector<Client> clientsToKick;

	for (size_t i = 0; i < usersTab.size(); i++)
	{
		Client &client = cmds->getClientFromNickname(usersTab[i]);
		clientsToKick.push_back(client);
	}
	return (clientsToKick);
}

void	kickClients(std::string channelToBeKickedOut, std::vector<Client> &clientsToKick)
{
	std::vector<std::string>::iterator it;

	for (size_t i = 0; i < clientsToKick.size(); i++)
	{
		std::vector<std::string> &clientChannels = clientsToKick[i].getChannels();
		it = std::find(clientChannels.begin(), clientChannels.end(), channelToBeKickedOut);
		clientChannels.erase(it);
		std::cout << "TEST : " ;
		for (size_t i = 0; i < clientChannels.size(); i++)
			std::cout << clientChannels[i] << std::endl;
		std::cout << "TEST : " ;
//		std::cout << "TEST : " ;
//		for (size_t i = 0; i < clientsToKick[i].getChannels().size(); i++)
//			std::cout << clientsToKick[i].getChannels()[i] << std::endl;
//		std::cout << "TEST : " ;
	}
}

void	Commands::kick()
{
	std::vector<std::string> channelNameTab = this->parseChannelName(this->_args);
//	for (size_t i = 0; i < channelNameTab.size(); i++)
//		std::cout << channelNameTab[i] << std::endl;
	if (channelNameTab.size() > 2)
		return ;
	else if (channelNameTab.empty())
		this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "KICK"));

	std::vector<std::string> usersTab = parseComaSeparatedArgs(this, this->_args);
	for (size_t i = 0; i < usersTab.size(); i++)
		std::cout << usersTab[i] << std::endl;
	std::map<std::string, Channel>::iterator channel = this->_channels.find(channelNameTab[0]);
	std::cout << channel->first << std::endl;

	if (!checkIfChannelExist(channel->first)) {
		_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), channel->first));
		return ;
	}
	if (!checkIfTargetClientIsOnChannel(channel->first, usersTab[0])) {
		_client.addMessageToSend(ERR_NOTONCHANNEL(usersTab[0], channel->first));
		return ;
	}
	std::vector<Client> clientsToKick = getclientsToKick(this, usersTab);
	kickClients(channel->first, clientsToKick);
	displayListClientOnChannel(channel->first);
	std::cout << "-->" << getClientFromNickname(usersTab[0]).getChannels()[0] << std::endl;
}