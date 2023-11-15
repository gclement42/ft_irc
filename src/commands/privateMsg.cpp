/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:01:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/15 10:23:10 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"


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
	
	finalMsg = ":" + this->_client.getUsername() + " " + this->_args[0] + " " + channelName + " :" + msg + "\r\n";
	std::cout << "finalMsg = '" << finalMsg << "'" << std::endl;

	sendMsgToAllClients(allClients, finalMsg);
	std::cout << "DEBUG\n";
}

void Commands::sendMsgToAllClients(std::vector<std::string> allClients, std::string msg)
{
	size_t	i = 0;

	std::map<int, Client>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second.getUsername() == allClients[i] && it->second.getNickname() != this->_client.getNickname())
		{
			it->second.addMessageToSend(msg);
			it->second.setWaitingForSend(true);
		}
		i++;
		it++;
	}
}

