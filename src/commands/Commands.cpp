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
