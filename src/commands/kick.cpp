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
#include <string>

std::vector<std::string>	parseComaSeparatedArgs(Commands *cmds, std::vector<std::string> arg)
{
	size_t i = 1;

	while (i < arg.size() && (arg[i].find("#") != std::string::npos || arg[i].find("&") != std::string::npos))
		i++;
	if (i == arg.size())
		return std::vector<std::string>();
	return (cmds->splitByComa(arg[i]));
}

void	kickClients(Commands *cmds, std::string kickerName, std::string channelToBeKickedOut, std::vector<std::string> usersTab)
{
	for (size_t i = 0; i < usersTab.size(); i++)
	{
		Client &client = cmds->getClientFromNickname(usersTab[i]);
		std::vector<std::string>::iterator it = std::find(client.getChannels().begin(), client.getChannels().end(), channelToBeKickedOut);
		client.getChannels().erase(it);
		std::string reason = "Kick";
		std::string message = ":" + kickerName + " KICK " + channelToBeKickedOut+ " " + client.getNickname() + " " + reason + "\r\n";
		client.addMessageToSend(message);
		client.setWaitingForSend(true);
	}
}

std::string		checkAllChannelsExist(Commands *cmds, std::vector<std::string> channelNameTab)
{
	for (size_t i = 0; i < channelNameTab.size(); i++)
	{
		if (cmds->checkIfChannelExist(channelNameTab[i]) == false)
			return (channelNameTab[i]);
	}
	return (std::string());
}

std::string		checkAllClientsExist(Commands *cmds, std::string channel, std::vector<std::string> usersTab)
{
	for (size_t i = 0; i < usersTab.size(); i++)
	{
		if (cmds->checkIfTargetClientIsOnChannel(channel, usersTab[i]) == false)
			return (usersTab[i]);
	}
	return (std::string());
}


void	Commands::kick()
{
	std::string errorMessage="salut";
	std::vector<std::string> channelNameTab = this->parseChannelName(this->_args);
	if (channelNameTab.empty())
		return (this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "KICK")));
	else if (!(errorMessage = checkAllChannelsExist(this, channelNameTab)).empty())
		return(this->_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), errorMessage)));

	std::vector<std::string> usersTab = parseComaSeparatedArgs(this, this->_args);
	if (usersTab.empty())
		return (this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "KICK")));

	std::map<std::string, Channel>::iterator channel = this->_channels.find(channelNameTab[0]);

	if (!(errorMessage = checkAllClientsExist(this, channel->first, usersTab)).empty())
		return (this->_client.addMessageToSend(ERR_NOTONCHANNEL(errorMessage, channel->first)));

	kickClients(this, this->_client.getNickname(), channel->first, usersTab);
	displayListClientOnChannel(channel->first);
}