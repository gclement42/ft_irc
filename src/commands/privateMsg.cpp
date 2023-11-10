/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:01:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/10 12:23:29 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

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
	
	for (size_t i = 0; i < allClients.size(); i++)
	{
		finalMsg = ":" + allClients[i] + " " + this->_args[0] + " " + channelName + " :" + msg + "\r\n";
		std::cout << "finalMsg = '" << finalMsg << "'" << std::endl;
		this->_client.addMessageToSend(finalMsg);
	}
	sendMsgToAllClients(allClients, finalMsg);
}



std::vector<std::string> Commands::allClientsOnChannel(std::string channel)
{
	size_t 						i = 0;
	std::vector<std::string> 	allClients;
	
	std::map<int, Client>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		std::vector<std::string> tmpV = it->second.getChannels();
		while (i < tmpV.size())
		{
			if (tmpV[i] == channel)
				allClients.push_back(it->second.getNickname());
			i++;
		}
		i = 0;
		it++;
	}

	return (allClients);
}

void Commands::sendMsgToAllClients(std::vector<std::string> allClients, std::string msg)
{
	size_t 						i = 0;

	std::map<int, Client>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second.getUsername() == allClients[i])
		{
			// send(it->second.getFd(), msg.c_str(), msg.size(), 0);
			it->second.addMessageToSend(msg);
		}
		i++;
		it++;
	}
}