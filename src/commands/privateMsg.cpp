/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:01:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/15 15:44:11 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"

static void		sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, Client &client, std::string msg);
static void		sendPrivMsgUser(std::map<int, Client> &clients, Client &client, std::string msg, std::string target);

void	Commands::privateMsg()
{
	std::string					msg;
	std::string					finalMsg;
	std::string 				channelName = this->_args[1];
	std::vector<std::string> 	allClients = allClientsOnChannel(channelName);

	for (size_t i = 0; i < this->_args.size(); i++)
		std::cout << "this->_args[" << i << "] = " << this->_args[i] << std::endl;

	for (size_t i = 2; i < this->_args.size(); i++)
	{
		msg += (" " + this->_args[i]);
	}
	msg = msg.substr(2, msg.size());
	

	if (channelName.find("#", 0) == 0 || channelName.find("&", 0) == 0)
	{
		finalMsg = RPL_PRIVMSGCHANNEL(this->_client.getNickname(), channelName, msg);
		sendPrivMsgChannel(this->_clients, allClients, this->_client, finalMsg);
	}
	else
	{
		finalMsg = RPL_PRIVMSGUSER(channelName, msg);
		sendPrivMsgUser(this->_clients, this->_client, finalMsg, channelName);
	}
}

static void		sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, Client &client, std::string msg)
{
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		for (size_t i = 0; i < allClients.size(); i++)
		{
			if (it->second.getNickname() == allClients[i] && it->second.getNickname() != client.getNickname())
			{
				it->second.addMessageToSend(msg);
				it->second.setWaitingForSend(true);
			}
		}
	}
}

static void		sendPrivMsgUser(std::map<int, Client> &clients, Client &client, std::string msg, std::string target)
{
	(void)client;

	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.getNickname() == target)
		{
			it->second.addMessageToSend(msg);
			it->second.setWaitingForSend(true);
		}
	}
}