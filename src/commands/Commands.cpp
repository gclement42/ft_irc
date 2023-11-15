#include "Commands.hpp"

Commands::Commands(std::map<int, Client> &clients, std::map<std::string, Channel> &channels, Client &client):
    _clients(clients), _channels(channels), _client(client) {

	this->_cmd["JOIN"] = &Commands::join;
	this->_cmd["QUIT"] = &Commands::quit;
	this->_cmd["TOPIC"] = &Commands::topic;
    this->_cmd["PRIVMSG"] = &Commands::privateMsg;
    this->_cmd["OPER"] = &Commands::oper;
	this->_cmd["NICK"] = &Commands::nick;
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
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		for (size_t i = 0; i < allClients.size(); i++)
		{
			if (it->second.getNickname() == allClients[i] && it->second.getNickname() != this->_client.getNickname())
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