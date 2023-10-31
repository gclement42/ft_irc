/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:31:00 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 10:45:58 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port): _port(port)
{
	_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(_socketServer, F_SETFL, O_NONBLOCK);
	_allClients = NULL;
	_nbClients = 0;
}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server(void) {
	if (_allClients)
		delete [] _allClients;
}

Server	&Server::operator=(const Server &src)
{
	size_t	i;

	i = 0;
	if (&src == this)
		return (*this);
	delete [] _allClients;
	_allClients = new pollfd[src._nbClients];
	while (i < src._nbClients)
	{
		_allClients[i] = src._allClients[i];
		i++;
	}
	_nbClients = src._nbClients;
	_socketServer = src._socketServer;
	_port = src._port;
	return (*this);
}

void Server::start(void)
{	
	struct sockaddr_in sockaddr_in;
	sockaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(_port);
	bind(_socketServer, (sockaddr *)(&sockaddr_in), sizeof(sockaddr_in));
	listen(_socketServer, 1);
}

void Server::acceptClientConnexion(void)
{
	struct sockaddr_in	sockaddr_in_client;
	pollfd 				client;
	char 				buffer[1024];

	socklen_t len = sizeof(sockaddr_in_client);
	client.fd = accept(_socketServer, (sockaddr *)(&sockaddr_in_client), &len);
	if (client.fd == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return ;
		else
		{
			//Rajouter gestions des erreurs
			return ;
		}
	}
	client.events = POLLIN;
	insertClient(client);
	recv(client.fd, buffer, 1024, 0);
	std::cout << "accept : "<< buffer << std::endl;
	//std::cout << "Client.fd : " << client.fd << std::endl;
	std::cout << "NbClient : " << _nbClients << std::endl;
}

void Server::checkClientEvent(void)
{
	char	buffer[1024];
	int 	ret;

	ret = poll(_allClients, _nbClients, 0);
	if (ret == -1) {
		//Rajouter gestions des erreurs
		return ;
	} else {
		for (size_t i = 0; i < _nbClients; i++)
		{
			if (_allClients[i].revents == POLLIN)
			{
				recv(_allClients[i].fd, buffer, 1024, 0);
				std::cout << "check : "<< buffer << std::endl;
			}
		}
	}
}

void	Server::insertClient(pollfd client)
{
	pollfd	*tmp;
	size_t	i;

	i = 0;
	tmp = new pollfd[_nbClients + 1];
	while (i < _nbClients)
	{
		tmp[i] = _allClients[i];
		i++;
	}
	tmp[i] = client;
	delete [] _allClients;
	_allClients = tmp;
	_nbClients++;
}

void	Server::eraseClient(pollfd client)
{
	pollfd		*tmp;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	tmp = new pollfd[_nbClients - 1];
	while (i < _nbClients)
	{
		if (_allClients[i].fd != client.fd)
		{
			tmp[j] = _allClients[i];
			j++;
		}
		i++;
	}
	delete [] _allClients;
	_allClients = tmp;
	_nbClients--;
}

pollfd *Server::getAllClients(void)
{
	return (_allClients);
}

size_t Server::getNbClients(void) const
{
	return (_nbClients);
}

void Server::joinCommand(void)
{
	return ;
}