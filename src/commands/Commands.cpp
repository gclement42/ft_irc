/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:22:14 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/28 12:27:35 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Commands::Commands(std::map<int, Client> &clients, std::map<std::string, Channel> &channels, Client &client):
    _clients(clients), _channels(channels), _client(client) {

	this->_cmd["JOIN"] = &Commands::join;
	this->_cmd["QUIT"] = &Commands::quit;
	this->_cmd["TOPIC"] = &Commands::topic;
    this->_cmd["PRIVMSG"] = &Commands::privateMsg;
	this->_cmd["NICK"] = &Commands::nick;
	this->_cmd["INVITE"] = &Commands::invite;
	this->_cmd["PART"] = &Commands::part;
	this->_cmd["KICK"] = &Commands::kick;
	this->_cmd["MODE"] = &Commands::mode;
    _operPassword = "password";
}

Commands::Commands(const Commands &src):
    _clients(src._clients), _channels(src._channels),
    _client(src._client), _operPassword(src._operPassword) { }

Commands::~Commands() { }

Commands &Commands::operator=(const Commands &src) {
    if (this != &src) {
        this->_clients = src._clients;
        this->_channels = src._channels;
        this->_client = src._client;
    }
    return (*this);
}

std::string	Commands::concatenate(std::vector<std::string> stringTab)
{
	std::string concatString;
	for (std::vector<std::string>::iterator it = stringTab.begin(); it != stringTab.end(); ++it) {
		concatString += *it;
		if (it != stringTab.end())
			concatString += " ";
	}
	return concatString;
}

std::vector<std::string>	Commands::splitByComa(std::string str)
{
	std::string 				word;
	std::stringstream 			ss(str);
	std::vector<std::string> 	result;

	if (str.find(",") != std::string::npos)
	{
		while (std::getline(ss, word, ','))
		{
			if (word[0] == ':')
				word.erase(0, 1);
			result.push_back(word);
		}
	}
	else
	{
		if (str[0] == ':')
			str.erase(0, 1);
		result.push_back(str);
	}
	return (result);
}


std::vector<std::string>		Commands::parseChannelName(std::vector<std::string> arg)
{
	std::vector<std::string> 	channelName;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i][0] == '#' || arg[i][0] == '&')
			channelName.push_back(arg[i]);
	}

	return (channelName);
}

std::vector<std::string>		Commands::parseKey(std::vector<std::string> arg)
{
	std::vector<std::string> 	keys;
	for (size_t i = 1; i < arg.size(); i++)
	{
		if (!(arg[i][0] == '#' || arg[i][0] == '&'))
			keys.push_back(arg[i]);
	}
	return (keys);
}

bool Commands::checkIfChannelExist(std::string channelName) {
	if (_channels.find(channelName) == _channels.end())
		return (false);
	Channel channel = _channels.find(channelName)->second;
	if (channel.getUserCount() < 0)
		return (false);
	return (true);
}

bool Commands::checkIfThisUserIsOnChannel(std::string channelName) {
	std::vector<std::string> clientChannels = _client.getChannels();
	for (size_t i = 0; i < clientChannels.size(); i++) {
		if (clientChannels[i] == channelName)
			return (true);
	}
	return (false);
}

bool Commands::checkIfTargetClientIsOnChannel(std::string channelName, std::string targetClient) {
	std::map<int, Client>::iterator it = _clients.begin();

	while (it != _clients.end()) {
		if (it->second.getNickname() == targetClient) {
			std::vector<std::string> clientChannels = it->second.getChannels();
			for (size_t i = 0; i < clientChannels.size(); i++) {
				if (clientChannels[i] == channelName)
					return (true);
			}
		}
		it++;
	}
	return (false);
}

Client &Commands::getClientFromNickname(std::string nickname) {
	std::map<int, Client>::iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (it->second.getNickname() == nickname)
			return (it->second);
		it++;
	}
	return (this->_client);
}

void Commands::removeOperatorFromChannels(void)
{
	std::map<std::string, Channel>::iterator it = this->_channels.begin();
	
	while (it != this->_channels.end())
	{
		Channel &channel = it->second;
		std::vector<std::string> &operators = channel.getOperators();
		for (size_t i = 0; i < operators.size(); i++)
		{
			if (operators[i] == this->_client.getNickname())
				operators.erase(operators.begin() + i);
		}
		it++;
	}
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

void Commands::sendMsgToAllClientsInChannel(std::vector<std::string> allClients, std::string msg)
{
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		for (size_t i = 0; i < allClients.size(); i++)
		{
			if (it->second.getNickname() == allClients[i])
			{
				it->second.addMessageToSend(msg);
				it->second.setWaitingForSend(true);
			}
		}
	}
}

void	Commands::addChannelInMap(std::string nickname, std::string channelName)
{
	std::map<int, Client>::iterator it = this->_clients.begin();
	
	while (it != this->_clients.end())
	{
		if (it->second.getNickname() == nickname)
			it->second.addChannel(channelName);
		it++;
	}
}

void Commands::displayListClientOnChannel(std::string channelName)
{
	std::vector<std::string>	ClientsInChannel;
	std::string					listNicknames;

	ClientsInChannel = this->allClientsOnChannel(channelName);
	for (size_t i = 0; i < ClientsInChannel.size(); i++)
	{
		Client client = this->getClientFromNickname(ClientsInChannel[i]);

		if (!client.getIsConnected())
			continue ;
		else if (isOperatorInChannel(client.getNickname(), channelName) == SUCCESS)
			listNicknames += "@" + ClientsInChannel[i] + " ";
		else
			listNicknames += ClientsInChannel[i] + " ";
	}
	std::cout << RPL_NAMREPLY(this->_client.getNickname(), channelName, listNicknames) << std::endl;
	this->sendMsgToAllClientsInChannel(ClientsInChannel, RPL_NAMREPLY(this->_client.getNickname(), channelName, listNicknames));
	this->sendMsgToAllClientsInChannel(ClientsInChannel, RPL_ENDOFNAMES(this->_client.getNickname(), channelName));
}

int Commands::isOperatorInChannel(std::string nickname, std::string channel)
{
	std::map<std::string, Channel>::iterator it = this->_channels.begin();

	while (it != this->_channels.end())
	{
		if (it->first == channel)
		{
			std::vector<std::string> operators = it->second.getOperators();
			for (size_t i = 0; i < operators.size(); i++)
			{
				if (operators[i] == nickname)
					return (SUCCESS);
			}
		}
		it++;
	}
	return (FAILURE);
}

std::map<std::string, Channel> &Commands::getChannels(void) const {
	return (this->_channels);
}

std::map<int, Client> &Commands::getClients() const {
	return (this->_clients);
}

Client &Commands::getClient() const {
	return (this->_client);
}

std::vector<std::string> &Commands::getArgs() {
	return (this->_args);
}
