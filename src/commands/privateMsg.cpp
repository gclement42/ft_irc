/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:01:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/24 10:17:19 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Commands.hpp"

static bool 					clientIsInChannel(std::vector<std::string> channels, std::string channel);
static bool 					checkDoubleDot(std::vector<std::string> &arg);
static std::string 				getMessage(std::vector<std::string> args);
static bool 					clientExist(std::map<int, Client> &clients, std::string client);
static bool						channelExist(std::map<std::string, Channel> &channels, std::string channel);

void	Commands::privateMsg()
{
	std::vector<std::string> 	targets;

	if (this->_args.size() <= 1)
	{
		_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), ""));
		return ;
	}
	
	targets = splitByComa(this->_args[1]);
	
	if (checkDoubleDot(this->_args) == false)
	{
		_client.addMessageToSend(ERR_NOTEXTTOSEND(_client.getNickname()));
		return ;
	}

	for (size_t i = 0; i < targets.size(); i++)
	{
		if (targets[i].size() > 1 && (targets[i].find("#", 0) == 0 || targets[i].find("&", 0) == 0))
		{
			if (clientIsInChannel(this->_client.getChannels(), targets[i]) == false)
				this->_client.addMessageToSend(ERR_CANNOTSENDTOCHAN(this->_client.getNickname(), targets[i]));
			else if (channelExist(this->_channels, targets[i]))
			{
				std::vector<std::string> 	allClients;

				allClients = allClientsOnChannel(targets[i]);
				sendPrivMsgChannel(this->_clients, allClients, this->_client.getNickname(), targets[i], this->_args);
			}
			else
				_client.addMessageToSend((ERR_NOSUCHNICK(_client.getNickname(), targets[i])));
		}
		else
			sendPrivMsgUser(this->_clients, this->_client, this->_args, targets[i]);
	}
}

void	Commands::sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, \
					std::string client, std::string channel, std::vector<std::string> args)
{
	std::vector<std::string> 	targets;
	
	targets = splitByComa(args[1]);
	
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		for (size_t i = 0; i < allClients.size(); i++)
		{
			if (it->second.getNickname() == allClients[i] && it->second.getNickname() != client)
			{
				it->second.addMessageToSend(RPL_PRIVMSGCHANNEL(client, channel, getMessage(args)));
				it->second.setWaitingForSend(true);	
			}
		}
	}
}

 void	Commands::sendPrivMsgUser(std::map<int, Client> &clients, Client &client, std::vector<std::string> args, std::string target)
{
	if (clientExist(clients, target) == true)
	{
		for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (it->second.getNickname() == target)
			{
				it->second.addMessageToSend(RPL_PRIVMSGUSER(client.getNickname(), target, getMessage(args)));
				it->second.setWaitingForSend(true);
			}
		}
	}
	else
	{
		client.addMessageToSend(ERR_NOSUCHNICK(client.getNickname(), target));
		client.setWaitingForSend(true);
	}
}



// ===== STATIC FUNCTIONS =====

static bool	checkDoubleDot(std::vector<std::string> &arg)
{
	if (arg.size() < 3)
		return (false);
	if (arg[2].find(":", 0) != 0)
		arg[2] = ":" + arg[2];
	return (true);
}

static bool clientIsInChannel(std::vector<std::string> channels, std::string channel)
{
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i] == channel)
			return (true);
	}
	return (false);
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

static bool clientExist(std::map<int, Client> &clients, std::string client)
{
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.getNickname() == client)
			return (true);
	}
	return (false);
}

static bool channelExist(std::map<std::string, Channel> &channels, std::string channel)
{
	for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->second.getName() == channel)
			return (true);
	}
	return (false);
}