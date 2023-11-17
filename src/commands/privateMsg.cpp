/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:01:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/17 11:16:36 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"

static void		sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, std::string client, std::string channel,std::vector<std::string> args);
static void		sendPrivMsgUser(std::map<int, Client> &clients, Client &client, std::vector<std::string> args);

static std::vector<std::string> getAllTargets(std::vector<std::string> args);
static std::string 				getMessage(std::vector<std::string> args);
static int 						clientExist(std::map<int, Client> &clients, std::string client);


void	Commands::privateMsg()
{
	std::string 				channelName = this->_args[1];
	std::vector<std::string> 	allClients = allClientsOnChannel(channelName);
		
	if (channelName.find("#", 0) == 0 || channelName.find("&", 0) == 0)
		sendPrivMsgChannel(this->_clients, allClients, this->_client.getNickname(), channelName, this->_args);
	else
		sendPrivMsgUser(this->_clients, this->_client, this->_args);
}



// ===== STATIC FUNCTIONS =====

static void		sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, \
					std::string client, std::string channel, std::vector<std::string> args)
{
	std::string					rpl_msg;
	
	rpl_msg = RPL_PRIVMSGCHANNEL(client, channel, getMessage(args));
	
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		for (size_t i = 0; i < allClients.size(); i++)
		{
			if (it->second.getNickname() == allClients[i] && it->second.getNickname() != client)
			{
				it->second.addMessageToSend(rpl_msg);
				it->second.setWaitingForSend(true);
			}
		}
	}
}

static void		sendPrivMsgUser(std::map<int, Client> &clients, Client &client, std::vector<std::string> args)
{
	std::vector<std::string> 	target;
	
	target = getAllTargets(args);

	for (size_t i = 0; i < target.size(); i++)
	{
		if (clientExist(clients, target[i]) == SUCCESS)
		{
			for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
			{
				if (it->second.getNickname() == target[i])
				{
					it->second.addMessageToSend(RPL_PRIVMSGUSER(client.getNickname(), target[i], getMessage(args)));
					it->second.setWaitingForSend(true);
				}
			}
		}
		else
		{
			client.addMessageToSend(RPL_NOSUCHNICK(client.getNickname(), target[i]));
			client.setWaitingForSend(true);
		}
	}
}

static std::vector<std::string> getAllTargets(std::vector<std::string> args)
{
	std::vector<std::string> targets;
	
	for (size_t i = 1; i < args.size(); i++)
	{
		if (args[i][0] == ':')
			break;
		else
			targets.push_back(args[i]);
	}
	
	return (targets);
}

static std::string getMessage(std::vector<std::string> args)
{
	std::string msg;

	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i][0] == ':')
		{
			for (size_t j = i; j < args.size(); j++)
			{
				msg += (" " + args[j]);
			}
			msg = msg.substr(2, msg.size());
			break;
		}
	}
	return (msg);
}

static int clientExist(std::map<int, Client> &clients, std::string client)
{
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.getNickname() == client)
			return (SUCCESS);
	}
	return (FAILURE);
}