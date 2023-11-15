/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:01:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/15 13:41:04 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"

static void		sendPrivMsg(std::map<int, Client> &clients, std::vector<std::string> allClients, Client &client, std::string msg);

void	Commands::privateMsg()
{
	std::string					msg;
	std::string					finalMsg;
	std::string 				channelName = this->_args[1];
	std::vector<std::string> 	allClients = allClientsOnChannel(channelName);

	for (size_t i = 2; i < this->_args.size(); i++)
	{
		msg += (" " + this->_args[i]);
	}
	msg = msg.substr(2, msg.size());
	
	finalMsg = RPL_PRIVMSG(this->_client.getNickname(), channelName, msg);

	sendPrivMsg(this->_clients, allClients, this->_client, finalMsg);
}

static void		sendPrivMsg(std::map<int, Client> &clients, std::vector<std::string> allClients, Client &client, std::string msg)
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