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
	this->_messagesToSend = src._messagesToSend;
	this->_isConnected = src._isConnected;
}

Client::~Client() {}

Client	&Client::operator=(const Client &src)
{
	if (&src == this)
		return (*this);
	this->_channel = src._channel;
	this->_messagesToSend = src._messagesToSend;
	this->_isConnected = src._isConnected;

	return (*this);
}

bool	Client::checkIfPasswordIsValid(Client client, std::string passwordServer) {
	if (client.getPassword() == passwordServer) {
		return (true);
	} else {
		std::string message = " Incorrect password";
		this->addMessageToSend(ERR_PASSWDMISMATCH(client.getUsername()));
		this->addMessageToSend(ERROR(message));
		return (false);
	}
}

bool	Client::checkIfClientIsStillConnected() const {
	std::string buffer = readInBuffer(this->getFd());
	
	if (buffer != "PONG localhost\r\n")
		return (false);
	return (true);
}

bool	Client::checkIfNicknameIsValid(std::map<int, Client> clients) {
    std::map<int, Client>::iterator it;

	if (this->_nickname.empty()) {
		std::cout << "Nickname is empty" << std::endl;
		this->addMessageToSend(ERR_NONIKNAMEGIVEN());
		this->addMessageToSend(RPL_QUIT(std::string("No nickname given")));
		this->setIsConnected(false);
		return (false);
	}
    for (it = clients.begin(); it != clients.end(); it++) {
        if (it->second.getNickname() == this->_nickname && it->second.getFd() != this->_fd) {
            std::string message = "Nickname already in use";
			this->addMessageToSend(ERR_NICKNAMEINUSE(this->_nickname));
			this->addMessageToSend(RPL_QUIT(std::string("Nickname already in use")));
            this->setIsConnected(false);
            return (false);
        }
    }
    return (true);
}

void	Client::sendAllMessageToClient() {
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

void	Client::addMessageToSend(std::string message) {
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

void Client::setIsConnected(bool isConnected){
    this->_isConnected = isConnected;
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