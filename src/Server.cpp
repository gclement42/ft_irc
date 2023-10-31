/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:31:00 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 10:08:56 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port): _port(port)
{
	_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(_socketServer, F_SETFL, O_NONBLOCK);
}

Server::Server(const Server &src)
{
	*this = src;
}

Server::~Server(void){}

Server	&Server::operator=(const Server &src)
{
	(void)src;
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
	_allClients.insert(client);
	recv(client.fd, buffer, 1024, 0);
	std::cout << "accept : "<< buffer << std::endl;
	//std::cout << "Client.fd : " << client.fd << std::endl;
	std::cout << "NbClient : " << _allClients.getNbClients() << std::endl;
}

void Server::checkClientEvent(void)
{
	char	buffer[1024];
	pollfd	*fds;
	int 	ret;

	fds = _allClients.getFds();
	ret = poll(fds, _allClients.getNbClients(), 0);
	if (ret == -1) {
		//Rajouter gestions des erreurs
		return ;
	} else {
		for (size_t i = 0; i < _allClients.getNbClients(); i++)
		{
			if (fds[i].revents == POLLIN)
			{
				recv(fds[i].fd, buffer, 1024, 0);
				std::cout << "check : "<< buffer << std::endl;
			}
		}
	}
}

Pollfds	&Server::getAllClients(void)
{
	return (_allClients);
}

void Server::joinCommand(void)
{
	return ;
}