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

	while (arg[i].find("#") != std::string::npos)
		i++;
	return (cmds->splitByComa(arg[i]));
}

std::vector<Client>	getClientsToBeKicked(Commands *cmds, std::vector<std::string> usersTab)
{
	std::vector<Client> clientsToBeKicked;

	for (size_t i = 0; i < usersTab.size(); i++)
		clientsToBeKicked.push_back(cmds->getClientFromNickname(usersTab[i]));
	return (clientsToBeKicked);
}

void	kickClients(std::vector<Client> clientsToBeKicked)
{
	(void)clientsToBeKicked;
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
	kickClients(getClientsToBeKicked(this, usersTab));
}