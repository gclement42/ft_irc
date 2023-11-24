/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:03:42 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/23 14:14:18 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

static void 	createBotChannel(int socket);

Bot::Bot(int port, std::string serverPassword)
{
	this->_port = port;
	
	this->_serverPassword = serverPassword;
	this->_botPassword = "PASS " + serverPassword + "\r\n";
	this->_nickName = "NICK alfredo\r\n";
	this->_userName = "USER alfredo\r\n";

	this->_responses = createResponsesMap();
}

Bot::~Bot(void)
{
	return ;
}

int Bot::startBot(void)
{
	int status = 0;

	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket < 0)
		return (FAILURE);

	this->_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(this->_port);

	status = 1;
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &(status), sizeof(int)) == -1) 
        return (FAILURE);
	
	if (connect(this->_socket, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) < 0)
		return (FAILURE);
	
	send(_socket, this->_botPassword.c_str(), this->_botPassword.size(), 0);
	send(_socket, this->_nickName.c_str(), this->_nickName.size(), 0);
	send(_socket, this->_userName.c_str(), this->_userName.size(), 0);
	
	std::cout << "Bot Alfredo is now connected on the server." << std::endl;
	return (SUCCESS);
}

void Bot::closeBot(void)
{
	close(this->_socket);
}

void Bot::runBot(void)
{
	std::string		buffer;

	createBotChannel(this->_socket);
	
	while (1)
	{
		if (send(this->_socket, "PING\r\n", 6, 0) == -1)
			break ;
		buffer = readInBuffer(this->_socket);
		botResponse(buffer, this->_socket);
	}
	
}

std::string Bot::readInBuffer(int socket) {
	char			buffer[1024];
	std::string		concatenateBuffer;
	ssize_t 		bytes;
	int				lastNewline;

	bytes = recv(socket, buffer, 1024, 0);
	if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		std::cout << "EAGAIN" << std::endl;
		return ("");
	}
	concatenateBuffer = buffer;
	lastNewline = concatenateBuffer.find_last_of("\r\n");
	concatenateBuffer = concatenateBuffer.substr(0, lastNewline + 1);
	if (bytes == -1) {
		if ((errno == EAGAIN || errno == EWOULDBLOCK))
		{
			std::cout << "EAGAIN after while" << std::endl;
			return (concatenateBuffer);
		}
		return ("");
	}
	return (concatenateBuffer);
}

void Bot::botResponse(std::string buffer, int socket)
{	
	if (buffer.find("353") != std::string::npos)
		newUserInChannel(socket);
	if (buffer.find("PRIVMSG") != std::string::npos)
		privateMsgResponse(buffer, socket);
}

void Bot::newUserInChannel(int socket)
{
	std::string 	newUserInChannel;
	
	newUserInChannel = "PRIVMSG #BOT :Enchanté, je suis Alfredo !\r\n";
	send(socket, newUserInChannel.c_str(), newUserInChannel.size(), 0);
}

void Bot::privateMsgResponse(std::string buffer, int socket)
{
	std::string 	privateMsgResponse;
	std::string 	userMsg;

	userMsg = buffer.substr(buffer.find_last_of(":") + 1);

	std::map<std::string, std::string>::iterator it = this->_responses.begin();
	while (it != this->_responses.end())
	{
		if (userMsg.find(it->first) != std::string::npos)
		{
			send(socket, it->second.c_str(), it->second.size(), 0);
			return ;
		}
		it++;
	}
}

std::map<std::string, std::string> Bot::createResponsesMap(void)
{
	std::map<std::string, std::string>		responses;
	std::string								format;

	format = "PRIVMSG #BOT :";

	responses["salut"] = format + "Salut !\r\n";
	responses["bonjour"] = format + "Bonjour !\r\n";
	responses["ca va ?"] = format + "Je vais bien et vous ?\r\n";
	responses["tranquille"] = format + "Excellente nouvelle !\r\n";
	responses["quelle heure"] = format + "Je n'en ai aucune idée !\r\n";
	responses["alfredo"] = format + "Oui ?\r\n";
	responses["merci"] = format + "Avec plaisir !\r\n";
	responses["IRC"] = format + "J'adore IRC ! Ce sigle signifie Internet Relay Chat.\r\n";
	responses["commandes"] = format + "Vous pouvez utiliser /join #channel pour rejoindre un channel ou /msg `utilisateur` `message` pour envoyer un message privé.\r\n";
	
	responses["con"] = format + "Pas de ca ici ! C'est un serveur friendly.\r\n";
	responses["connard"] = format + "Pas de ca ici ! C'est un serveur friendly.\r\n";
	responses["putain"] = format + "Pas de ca ici ! C'est un serveur friendly.\r\n";
	
	return (responses);
}

// ===== STATIC FUNCTIONS =====

static void createBotChannel(int socket)
{
	std::string 	createChannelMsg;

	createChannelMsg = "JOIN #BOT\r\n";
	send(socket, createChannelMsg.c_str(), createChannelMsg.size(), 0);
}