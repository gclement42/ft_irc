/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:01:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/20 08:44:17 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"

static void		sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, std::string client , std::vector<std::string> args);
static void		sendPrivMsgUser(std::map<int, Client> &clients, Client &client, std::vector<std::string> args);

static void 					checkDoubleDot(std::vector<std::string> &arg);
static std::vector<std::string> getAllTargets(std::vector<std::string> args);
static std::string 				getMessage(std::vector<std::string> args);
static int 						clientExist(std::map<int, Client> &clients, std::string client);
static int						channelExist(std::map<std::string, Channel> &channels, std::string channel);


void	Commands::privateMsg()
{	
	std::vector<std::string> 	targets;
	std::vector<std::string> 	allClientsFirstChannel;
	std::vector<std::string> 	allClientsSecondChannel;

	if (this->_args[1].find("#", 0) == 0 || this->_args[1].find("&", 0) == 0)
	{
		targets = getAllTargets(this->_args);
		allClientsFirstChannel = allClientsOnChannel(targets[0]);
		if (channelExist(this->_channels, targets[0]) == SUCCESS)
			sendPrivMsgChannel(this->_clients, allClientsFirstChannel, this->_client.getNickname(), this->_args);
		else	
			_client.addMessageToSend((ERR_NOSUCHNICK(_client.getNickname(), targets[0])));

		if (targets.size() > 1)
		{
			allClientsSecondChannel = allClientsOnChannel(targets[1]);
			if (channelExist(this->_channels, targets[0]) == SUCCESS)
				sendPrivMsgChannel(this->_clients, allClientsSecondChannel, this->_client.getNickname(), this->_args);
			else	
				_client.addMessageToSend((ERR_NOSUCHNICK(_client.getNickname(), targets[1])));
		}
	}
	else
		sendPrivMsgUser(this->_clients, this->_client, this->_args);
}



// ===== STATIC FUNCTIONS =====

static void		sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, \
					std::string client, std::vector<std::string> args)
{
	std::vector<std::string> 	target;
	
	target = getAllTargets(args);
	
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		for (size_t i = 0; i < allClients.size(); i++)
		{
			if (it->second.getNickname() == allClients[i] && it->second.getNickname() != client)
			{
				for (size_t i = 0; i < target.size(); i++)
				{
					it->second.addMessageToSend(RPL_PRIVMSGCHANNEL(client, target[i], getMessage(args)));
					it->second.setWaitingForSend(true);	
				}
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
			client.addMessageToSend(ERR_NOSUCHNICK(client.getNickname(), target[i]));
			client.setWaitingForSend(true);
		}
	}
}

static void 	checkDoubleDot(std::vector<std::string> &arg)
{
	if (arg[2].find(":", 0) == 0)
		return ;
	else
	{
		arg[2] = ":" + arg[2];
		std::cout << arg[2] << std::endl;
	}
}

static std::vector<std::string> getAllTargets(std::vector<std::string> args)
{
	std::vector<std::string> 	targets;
	std::string 				tmp;
	
	for (size_t i = 1; i < args.size(); i++)
	{
		if (args[i][0] == ':')
			break;
		else
		{
			size_t pos = args[i].find(",");
			if (pos != std::string::npos)
			{
				targets.push_back(args[i].substr(0, pos));
				targets.push_back(args[i].substr(pos + 1, args[i].size()));
			}
			else
				targets.push_back(args[i]);
		}
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

static int channelExist(std::map<std::string, Channel> &channels, std::string channel)
{
	for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->second.getName() == channel)
			return (SUCCESS);
	}
	return (FAILURE);
}