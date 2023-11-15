#include "Commands.hpp"

Commands::Commands(std::map<int, Client> &clients, std::map<std::string, Channel> &channels, Client &client):
    _clients(clients), _channels(channels), _client(client) {

	this->_cmd["JOIN"] = &Commands::join;
	this->_cmd["QUIT"] = &Commands::quit;
	this->_cmd["TOPIC"] = &Commands::topic;
    this->_cmd["PRIVMSG"] = &Commands::privateMsg;
    this->_cmd["OPER"] = &Commands::oper;
	this->_cmd["NICK"] = &Commands::nick;
	this->_cmd["INVITE"] = &Commands::invite;
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

