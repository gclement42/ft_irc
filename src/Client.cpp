/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:04:31 by gclement          #+#    #+#             */
/*   Updated: 2023/11/06 15:35:08 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "main.hpp"

Client::Client(std::string nickname, std::string username, int fd, std::string password):
 _fd(fd), _password(password), _nickname(nickname), _username(username), _isConnected(true) {}

Client::Client(const Client &src):
 _fd(src._fd), _password(src._password), _nickname(src._nickname),
 _username(src._username)
{
    _messagesToSend = src._messagesToSend;
    _isConnected = src._isConnected;
}

Client::~Client() {}

Client	&Client::operator=(const Client &src)
{
	if (&src == this)
		return (*this);
	_channel = src._channel;
    _messagesToSend = src._messagesToSend;
    _isConnected = src._isConnected;

	return (*this);
}

void Client::checkIfPasswordIsValid(Client client, std::string passwordServer) {
	if (client.getPassword() == passwordServer) {
		return ;
	} else {
		std::string message = " Incorrect password";
        addMessageToSend(ERR_PASSWDMISMATCH(client.getUsername()));
        addMessageToSend(ERROR(message));
		return ;
	}
}

bool Client::checkIfClientIsStillConnected() const {
	std::string buffer = readInBuffer(this->getFd());
	
	if (buffer != "PONG localhost\r\n")
		return (false);
	return (true);
}

void Client::sendAllMessageToClient() {
	ssize_t ret;

    for (std::vector<std::string>::iterator it = _messagesToSend.begin(); it != _messagesToSend.end(); it++)
    {
        ret = send(_fd, (*it).c_str(), (*it).length(), 0);
        if (ret == -1)
        {
            std::cerr << "errno : " << errno << std::endl;
            // throw exception (????)
            return;
        }
    }
    if (!_messagesToSend.empty())
        _messagesToSend.clear();
}

void Client::addMessageToSend(std::string message) {
	_messagesToSend.push_back(message);
}

int		Client::getFd() const
{
	return (_fd);
}

std::string	Client::getPassword() const
{
	return (_password);
}

std::string	Client::getNickname() const
{
	return (_nickname);
}

std::string	Client::getUsername() const
{
	return (_username);
}

std::vector<Channel>	&Client::getChannels()
{
	return (_channel);
}

std::vector<std::string> Client::getMessageToSend() {
    return (_messagesToSend);
}

void Client::setIsConnected() {
    if (_isConnected)
        _isConnected = false;
    else
        _isConnected = true;
}

bool Client::getIsConnected() const {
    return (_isConnected);
}

std::ostream	&operator<<(std::ostream &o, const Client &src)
{
	o << "Client fd: " << src.getFd() << std::endl;
	o << "Client password: " << src.getPassword() << std::endl;
	o << "Client nickname: " << src.getNickname() << std::endl;
	o << "Client username: " << src.getUsername() << std::endl;
	return (o);
}