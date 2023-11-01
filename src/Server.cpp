/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:31:00 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 16:58:58 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port): _port(port)
{
	_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(_socketServer, F_SETFL, O_NONBLOCK);
	_allFds = NULL;
	_nbFds = 0;
}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server(void) {
	if (_allFds)
		delete [] _allFds;
}

Server	&Server::operator=(const Server &src)
{
	size_t	i;

	i = 0;
	if (&src == this)
		return (*this);
	delete [] _allFds;
	_allFds = new pollfd[src._nbFds];
	while (i < src._nbFds)
	{
		_allFds[i] = src._allFds[i];
		i++;
	}
	_nbFds = src._nbFds;
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
	std::cout << "Server started on port " << _port << std::endl;
}

void Server::acceptClientConnexion(void)
{
	struct sockaddr_in	sockaddr_in_client;
	pollfd 				client;

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
	client.revents = 0;
	insertFd(client);
	//std::cout << "Client.fd : " << client.fd << std::endl;
	//std::cout << "NbClient : " << _nbFds << std::endl;
}

void Server::checkFdsEvent(void)
{
	char			buffer[1024];
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
				recv(_allFds[i].fd, buffer, 1024, 0);
				std::cout << "Message from client " << _allFds[i].fd << " : " << buffer << std::endl;
			}
		}
	}
}

void	Server::insertFd(pollfd client)
{
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

void	Server::eraseFd(pollfd client)
{
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

pollfd *Server::getAllFds(void)
{
	return (_allFds);
}

size_t Server::getNbFd(void) const
{
	return (_nbFds);
}

void Server::joinCommand(void)
{
	return ;
}