/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:31:00 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 16:01:52 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string password): _port(port), _password(password) {
	_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	_allFds = NULL;
	_nbFds = 0;
}

Server::Server(const Server &src) {
	*this = src;
}

Server::~Server(void) {
	std::cout << "Server destructor called" << std::endl;
	for (size_t i = 0; i < _nbFds; i++)
		close(_allFds[i].fd);
	close (_socketServer);
	if (_allFds)
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

void Server::start(void) {	
	struct sockaddr_in sockaddr_in;
	sockaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(_port);
	bind(_socketServer, (sockaddr *)(&sockaddr_in), sizeof(sockaddr_in));
	listen(_socketServer, 1);
	fcntl(_socketServer, F_SETFL, O_NONBLOCK);
	std::cout << "Server started on port " << _port << std::endl;
}

void Server::stop(void) {
	std::cout << "Server stopped" << std::endl;
	close(_socketServer);
}

void Server::checkIfPasswordIsValid(Client client) {
	if (client.getPassword() == _password) {
		return ;
	} else {
		sendMessageToClient(ERR_PASSWDMISMATCH(client.getUsername()), client.getFd());
		
		return ;
	}
}

void Server::sendMessageToClient(std::string message, int fd) {
	int ret;

	ret = send(fd, message.c_str(), message.size(), 0);
	if (ret == -1) {
		std::cerr << "errno : " << errno << std::endl;
		// throw exception (????)
		return ;
	}
}


void Server::acceptClientConnexion(void) {
	struct sockaddr_in	sockaddr_in_client;
	pollfd 				pollClient;
	std::string 		buffer;

	socklen_t len = sizeof(sockaddr_in_client);
	pollClient.fd = accept(_socketServer, (sockaddr *)(&sockaddr_in_client), &len);
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
	buffer = readInBuffer(pollClient.fd);
	while (buffer.find("USER") == std::string::npos)
		buffer += readInBuffer(pollClient.fd);
	Client client(parseClientData(buffer, pollClient.fd));
	checkIfPasswordIsValid(client);
	_clients.insert(std::pair<int, Client>(pollClient.fd, client));
	std::cout << "New client connected : " << std::endl;
	std::cout << client << std::endl;
	
}

void Server::checkFdsEvent(void) {
	std::string		buffer;
	int				ret;

	ret = poll(_allFds, _nbFds, 0);
	if (ret == -1) {
		//Rajouter gestions des erreurs
		return ;
	} else {
		for (size_t i = 0; i < _nbFds; i++)
		{
			if (_allFds[i].revents == POLLIN)
			{
				Client client(_clients.find(_allFds[i].fd)->second);
				buffer = readInBuffer(_allFds[i].fd);
				buffer = buffer.substr(0, buffer.find_first_of("\r\n"));
				std::cout << client.getUsername() << " : "<< buffer << std::endl;
			}
		}
	}
}

std::string Server::readInBuffer(int fd) {
	char		buffer[1024];
	std::string	concatenateBuffer;
	int			i;
	int			bytes;
	int			lastNewline;

	i = 0;
	while (_allFds[i].fd != fd)
		i++;
	bytes = recv(_allFds[i].fd, buffer, 1024, 0);
	if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		return ("");
	concatenateBuffer = buffer;
	lastNewline = concatenateBuffer.find_last_of("\r\n");
	concatenateBuffer = concatenateBuffer.substr(0, lastNewline + 1);
	if (bytes == -1) {
		if ((errno == EAGAIN || errno == EWOULDBLOCK))
			return (concatenateBuffer);
		std::cerr << "errno : " << errno << std::endl;
		// throw exception (????)
		return ("error");
	}
	return (concatenateBuffer);
}

void Server::displayClients(void) {
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

pollfd *Server::getAllFds(void) {
	return (_allFds);
}

size_t Server::getNbFd(void) const {
	return (_nbFds);
}

int Server::getSocketServer(void) const {
	return (_socketServer);
}

void Server::joinCommand(void) {
	return ;
}