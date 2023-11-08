/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:04:31 by gclement          #+#    #+#             */
/*   Updated: 2023/11/08 11:11:30 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "main.hpp"

Client::Client(std::string nickname, std::string username, int fd, std::string password):
 _fd(fd), _password(password), _nickname(nickname), _username(username)
{
	return ;
}

Client::Client(const Client &src):
 _fd(src._fd), _password(src._password), _nickname(src._nickname), _username(src._username)
{
	*this = src;
}

Client::~Client(void)
{
	return ;
}

Client	&Client::operator=(const Client &src)
{
	if (&src == this)
		return (*this);
	_channel = src._channel;
	return (*this);
}

void Client::checkIfPasswordIsValid(Client client, std::string passwordServer) {
	if (client.getPassword() == passwordServer) {
		return ;
	} else {
		std::string message = " Incorrect password";
		sendMessageToClient(ERR_PASSWDMISMATCH(client.getUsername()), client.getFd());
		sendMessageToClient(ERROR(message), client.getFd());
		return ;
	}
}

bool Client::checkIfClientIsStillConnected(void) {
	std::string buffer = readInBuffer(this->getFd());
	
	if (buffer != "PONG localhost\r\n")
		return (false);
	return (true);
}

void Client::sendMessageToClient(std::string message, int fd) {
	int ret;

	ret = send(fd, message.c_str(), message.size(), 0);
	if (ret == -1) {
		std::cerr << "errno : " << errno << std::endl;
		// throw exception (????)
		return ;
	}
}

int		Client::getFd(void) const
{
	return (_fd);
}

std::string	Client::getPassword(void) const
{
	return (_password);
}

std::string	Client::getNickname(void) const
{
	return (_nickname);
}

std::string	Client::getUsername(void) const
{
	return (_username);
}

std::vector<Channel>	&Client::getChannels(void)
{
	return (_channel);
}

std::ostream	&operator<<(std::ostream &o, const Client &src)
{
	o << "Client fd: " << src.getFd() << std::endl;
	o << "Client password: " << src.getPassword() << std::endl;
	o << "Client nickname: " << src.getNickname() << std::endl;
	o << "Client username: " << src.getUsername() << std::endl;
	return (o);
}