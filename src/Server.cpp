/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:31:00 by gclement          #+#    #+#             */
/*   Updated: 2023/11/15 13:16:20 by lboulatr         ###   ########.fr       */
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
}

void Server::acceptClientConnexion() {
	struct sockaddr_in	sockaddrInClient;
	pollfd 				pollClient = {};
	std::string 		buffer;

	socklen_t len = sizeof(sockaddrInClient);
	pollClient.fd = accept(_socketServer, (sockaddr *)(&sockaddrInClient), &len);
	if (pollClient.fd == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return ;
		else {
			std::cout << "errno : " << errno << std::endl;
			//Rajouter gestions des erreurs
			return ;
		}
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
    std::string		buffer;

    if (_clients.find(pollClient.fd) == _clients.end())
	{
        createClient(pollClient.fd);
		pollClient.revents |= POLLOUT;
		return ;
	}
    buffer = this->readInBuffer(pollClient.fd);
    Client &client = _clients.find(pollClient.fd)->second;
    if (buffer != "" && client.getIsConnected())
    {
        Commands        commands(_clients, _channels, client);
        buffer = buffer.substr(0, buffer.find_first_of("\r\n"));
        std::cout << client.getNickname() << " : " << buffer << std::endl;
        commands.parseBuffer(buffer);
		// _clients.find(pollClient.fd)->second = client;
		pollClient.revents |= POLLOUT;
    }
}

void Server::sendMessageToClient(pollfd &pollClient) {
    if (_clients.find(pollClient.fd) == _clients.end())
        return ;
    Client client(_clients.find(pollClient.fd)->second);
    client.sendAllMessageToClient();
	client.setWaitingForSend(false);
	if (!client.getIsConnected())
		disconnectClient(pollClient.fd);
	else
    	_clients.find(pollClient.fd)->second = client;
    pollClient.revents = 0;
}

void Server::checkFdsEvent() {

	int ret;

	ret = poll(_allFds, _nbFds, 0);
	if (ret == -1) {
		//Rajouter gestions des erreurs
		return ;
	} else {
		for (size_t i = 0; i < _nbFds; i++)
		{
			if (checkIfClientIsWaitingForSend(_allFds[i].fd))
				_allFds[i].revents |= POLLOUT;
			if (_allFds[i].revents & POLLIN)
                receiveMessageFromClient(_allFds[i]);
            if (_allFds[i].revents & POLLOUT)
                sendMessageToClient(_allFds[i]);
		}
	}
}

void Server::createClient(int fd) {
    std::string buffer = this->readInBuffer(fd);

    while (buffer.find("USER") == std::string::npos)
        buffer += this->readInBuffer(fd);
    Client client(parseClientData(buffer, fd));
	if (client.checkIfNicknameIsValid(_clients)
		&& client.checkIfPasswordIsValid(client, _password)
		&& client.checkIfUsernameIsValid())
		client.addMessageToSend(RPL_WELCOME(client.getUsername()));
	else
	{
		client.addMessageToSend(RPL_QUIT(std::string("Disconnected")));
		client.setIsConnected(false);
	}
    _clients.insert(std::pair<int, Client>(fd, client));
    std::cout << "New client connected : " << std::endl;
    std::cout << client << std::endl;
}

void Server::disconnectClient(int fd) {
	std::map<int, Client>::iterator it;

	it = _clients.find(fd);
	if (it != _clients.end())
	{
		std::cout << it->second.getNickname() << " disconnected" << std::endl;
		_clients.erase(it);
		eraseFd(_allFds[fd]);
		close(fd);
	}
}

void Server::displayClients() {
	std::map<int, Client>::iterator it;

	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		std::cout << it->second << std::endl;
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

void	Server::eraseFd(pollfd client) {
	pollfd		*tmp;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	tmp = new pollfd[_nbFds - 1];
	while (i < _nbFds)
	{
		if (_allFds[i].fd != client.fd)
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

