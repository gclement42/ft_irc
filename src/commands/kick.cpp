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

std::string					parseReason(Commands *cmds, std::vector<std::string> arg);
std::vector<std::string>	parseComaSeparatedArgs(Commands *cmds, std::vector<std::string> arg);
std::string					checkAllClientsExist(Commands *cmds, std::string channel, std::vector<std::string> usersTab);
std::string					checkAllChannelsExist(Commands *cmds, std::vector<std::string> channelNameTab);
void						kickClients(Commands *cmds, std::string kickerName, std::string channelToBeKickedOut,
										std::vector<std::string> usersTab, std::string reason);
void						checkIrcInArgs(std::vector<std::string> &args);

void	Commands::kick()
{
	std::string errorMessage;
	checkIrcInArgs(this->_args);
	std::vector<std::string> channelNameTab = this->parseChannelName(this->_args);
	if (channelNameTab.empty())
		return (this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "KICK")));
	else if (!(errorMessage = checkAllChannelsExist(this, channelNameTab)).empty())
		return(this->_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), errorMessage)));

	std::vector<std::string> usersTab = parseComaSeparatedArgs(this, this->_args);
	if (usersTab.empty())
		return (this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "KICK")));

	std::map<std::string, Channel>::iterator channel = this->_channels.find(channelNameTab[0]);

	if (!channel->second.checkIfClientIsOperator(this->_client.getNickname()))
		return (this->_client.addMessageToSend(ERR_CHANOPRIVSNEEDED(this->_client.getNickname(), channel->first)));
	if (!(errorMessage = checkAllClientsExist(this, channel->first, usersTab)).empty())
		return (this->_client.addMessageToSend(ERR_USERNOTINCHANNEL(this->_client.getNickname(), errorMessage, channel->first)));

	if (!this->checkIfThisUserIsOnChannel(channel->first))
		return (this->_client.addMessageToSend(ERR_NOTONCHANNEL(this->_client.getNickname(), channel->first)));

	kickClients(this, this->_client.getNickname(), channel->first, usersTab, parseReason(this, this->_args));
	displayListClientOnChannel(channel->first);
}

std::string		parseReason(Commands *cmds, std::vector<std::string> arg)
{
	size_t i = 1;
	std::vector<std::string>	reasonTab;

	while (i < arg.size() && (arg[i].find("#") != std::string::npos || arg[i].find("&") != std::string::npos))
		i++;
	if (++i >= arg.size())
		return std::string();
	while (i < arg.size())
		reasonTab.push_back(arg[i++]);
	return (cmds->concatenate(reasonTab));
}

std::vector<std::string>	parseComaSeparatedArgs(Commands *cmds, std::vector<std::string> arg)
{
	size_t i = 1;

	while (i < arg.size() && (arg[i].find("#") != std::string::npos || arg[i].find("&") != std::string::npos))
		i++;
	if (i == arg.size())
		return std::vector<std::string>();
	return (cmds->splitByComa(arg[i]));
}

void	kickClients(Commands *cmds, std::string kickerName, std::string channelToBeKickedOut, std::vector<std::string> usersTab, std::string reason)
{
	for (size_t i = 0; i < usersTab.size(); i++)
	{
		Client &client = cmds->getClientFromNickname(usersTab[i]);
		std::vector<std::string>::iterator it = std::find(client.getChannels().begin(), client.getChannels().end(), channelToBeKickedOut);
		client.getChannels().erase(it);
		if (reason.empty())
			reason = "No reason was specified.";
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

void	checkIrcInArgs(std::vector<std::string> &args)
{
	std::vector<std::string>::iterator it = args.begin();
	std::string toFind = "irc";

	if (args.size() > 1 && it->find(toFind, 0))
		args.erase(it);
}