/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:31:00 by gclement          #+#    #+#             */
/*   Updated: 2023/12/05 10:21:07 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"


Server::Server(int port, const std::string& password): _port(port), _password(password) {
	_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	int iSetOption = 1;
	setsockopt(_socketServer, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption,
        sizeof(iSetOption));
	_allFds =  NULL;
	_nbFds = 0;
}

Server::Server(const Server &src) {
	*this = src;
}

Server::~Server() {
	std::cout << "Server destructor called" << std::endl;
	for (size_t i = 0; i < _nbFds; i++)
		close(_allFds[i].fd);
	close (_socketServer);
	delete [] _allFds;
}

Server	&Server::operator=(const Server &src) {
	size_t	i;

	i = 0;
	if (&src == this)
		return (*this);
	delete [] _allFds;
	_allFds = new pollfd[src._nbFds];
	while (i < src._nbFds) {
		_allFds[i] = src._allFds[i];
		i++;
	}
	_nbFds = src._nbFds;
	close(_socketServer);
	_socketServer = src._socketServer;
	_port = src._port;
	return (*this);
}

void Server::start() const {
	struct sockaddr_in sockaddr_in;
	sockaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(_port);
	bind(_socketServer, (sockaddr *)(&sockaddr_in), sizeof(sockaddr_in));
	listen(_socketServer, 1);
	fcntl(_socketServer, F_SETFL, O_NONBLOCK);
	std::cout << "Server started on port " << _port << std::endl;
}

void Server::stop() const {
	std::cout << "Server stopped" << std::endl;
	close(_socketServer);
	for (size_t i = 0; i < _nbFds; i++)
		close(_allFds[i].fd);
}

void Server::acceptClientConnexion() {
	struct sockaddr_in	sockaddrInClient;
	pollfd 				pollClient = {};
	std::string 		buffer;

	socklen_t len = sizeof(sockaddrInClient);
	pollClient.fd = accept(_socketServer, (sockaddr *)(&sockaddrInClient), &len);
	if (pollClient.fd == -1) {
			return ;
	}
	pollClient.events = POLLIN;
	pollClient.revents = 0;
	insertFd(pollClient);
}

bool Server::checkIfClientIsWaitingForSend(int fd) {
	if (_clients.find(fd) == _clients.end())
		return (false);
	Client client(_clients.find(fd)->second);
	if (client.getWaitingForSend())
		return (true);
	return (false);
}

void Server::receiveMessageFromClient(pollfd &pollClient) {
    int 			ret;
	Client			*client;

    ret = this->readInBuffer(pollClient.fd);
	if (_clients.find(pollClient.fd) == _clients.end())
	{
		Client tmpClient(pollClient.fd);
		client = &tmpClient;
		_clients.insert(std::pair<int, Client>(pollClient.fd, *client));
	}
    client = &_clients.find(pollClient.fd)->second;
	if (ret == 1 && !client->checkIfAllDataIsFilled())
		fillClientData(*client, _buffer);
    else if (ret == 1 && client->getIsConnected()) {
		Commands commands(_clients, _channels, *client);

		_buffer = _buffer.substr(0, _buffer.find_first_of("\r\n"));
		std::cout << client->getNickname() << " : " << _buffer << std::endl;
		commands.parseBuffer(_buffer);
		pollClient.revents |= POLLOUT;
	}
	else if (ret == 0 && this->_buffer.empty())
		disconnectClient(pollClient.fd);
	this->_buffer.clear();
}

void Server::sendMessageToClient(pollfd &pollClient) {
    if (_clients.find(pollClient.fd) == _clients.end())
        return ;

    Client client(_clients.find(pollClient.fd)->second);

    client.sendAllMessageToClient();
	client.setWaitingForSend(false);
	if (!client.getIsConnected())
		disconnectClient(pollClient.fd);
	else {
    	_clients.find(pollClient.fd)->second = client;
    	pollClient.revents = 0;
	}
}

void Server::checkFdsEvent() {

	int ret;

	ret = poll(_allFds, _nbFds, 0);
	if (ret == -1) {
		return ;
	} else {
		for (size_t i = 0; i < _nbFds; i++)
		{
			if (checkIfClientIsWaitingForSend(_allFds[i].fd))
				_allFds[i].revents |= POLLOUT;
            if (_allFds[i].revents & POLLOUT)
                sendMessageToClient(_allFds[i]);
			else if (_allFds[i].revents & POLLIN)
                receiveMessageFromClient(_allFds[i]);
		}
	}
}

void Server::fillClientData(Client &client, std::string buffer) {
	parseClientData(buffer, client);

	if (client.checkIfAllDataIsFilled())
	{
		if (client.checkIfNicknameIsValid(_clients)
			&& client.checkIfPasswordIsValid(client, _password)
			&& client.checkIfUsernameIsValid())
		{
			client.addMessageToSend(RPL_WELCOME(client.getUsername()));
		}
		else
		{
			std::cout << "Client disconnected : " << std::endl;
			client.addMessageToSend(RPL_QUIT(std::string("Disconnected")));
			client.setIsConnected(false);
		}
		client.setWaitingForSend(true);
		std::cout << "New client connected : " << std::endl;
		std::cout << client << std::endl;
	}
}

void Server::disconnectClient(int fd) {
	std::map<int, Client>::iterator it;
	Commands commands(_clients, _channels, _clients.find(fd)->second);
	std::vector<std::string> clientChannels = _clients.find(fd)->second.getChannels();

	it = _clients.find(fd);
	it->second.setIsConnected(false);
	if (it != _clients.end())
	{
		std::vector<std::string> clientChannels = it->second.getChannels();
		for (size_t i = 0; i < clientChannels.size(); i++)
		{
			commands.displayListClientOnChannel(clientChannels[i]);
		}
		commands.removeOperatorFromChannels();
		std::cout << it->second.getNickname() << " disconnected" << std::endl;
		eraseFd(fd);
		_bufferByFd.erase(fd);
		_clients.erase(it);
		close(fd);
	}
}

void	Server::insertFd(pollfd client) {
	pollfd	*tmp;
	size_t	i;

	i = 0;
	tmp = new pollfd[_nbFds + 1];
	while (i < _nbFds)
	{
		tmp[i] = _allFds[i];
		i++;
	}
	tmp[i] = client;
	delete [] _allFds;
	_allFds = tmp;
	_nbFds++;
}

void	Server::eraseFd(int fd) {
	pollfd		*tmp;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	tmp = new pollfd[_nbFds - 1];
	while (i < _nbFds)
	{
		if (_allFds[i].fd != fd)
		{
			tmp[j] = _allFds[i];
			j++;
		}
		i++;
	}
	delete [] _allFds;
	_allFds = tmp;
	_nbFds--;
}

pollfd *Server::getAllFds() {
	return (_allFds);
}

size_t Server::getNbFd() const {
	return (_nbFds);
}

int Server::getSocketServer() const {
	return (_socketServer);
}

