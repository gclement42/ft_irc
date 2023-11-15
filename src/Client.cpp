/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:04:31 by gclement          #+#    #+#             */
/*   Updated: 2023/11/10 14:28:00 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "main.hpp"

Client::Client(std::string nickname, std::string username, std::string realname, int fd, std::string password):
 _fd(fd), _password(password), _nickname(nickname),
  _username(username), _realname(realname),_isConnected(true), _waitingForSend(false), _isOperator(false) {}

Client::Client(const Client &src):
 _fd(src._fd), _password(src._password), _nickname(src._nickname),
 _username(src._username), _realname(src._realname), _isOperator(src._isOperator)
{
    _messagesToSend = src._messagesToSend;
    _isConnected = src._isConnected;
	_channel = src._channel;
	_waitingForSend = src._waitingForSend;
}

Client::~Client() {}

Client	&Client::operator=(const Client &src)
{
	if (&src == this)
		return (*this);
	this->_nickname = src._nickname;
	this->_channel = src._channel;
	this->_messagesToSend = src._messagesToSend;
	this->_isConnected = src._isConnected;
	this->_isOperator = src._isOperator;
	this->_waitingForSend = src._waitingForSend;
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
	if (!checkIfNicknameIsNotEmpty())
		return (false);
	if (!this->checkIfNicknameIsAlreadyUsed(clients))
		return (false);
	if (!this->checkIfNicknameContainsForbiddenCharacters())
		return (false);
    return (true);
}

void	Client::sendAllMessageToClient() {
	ssize_t ret;

	std::cout << _nickname << " send messages" << std::endl;
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

void Client::addChannel(std::string channelName)
{
	_channel.push_back(channelName);
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

std::vector<std::string>	&Client::getChannels()
{
	return (_channel);
}

std::vector<std::string> Client::getMessageToSend() {
    return (_messagesToSend);
}

bool	Client::getWaitingForSend() const
{
	return (_waitingForSend);
}

bool	Client::getIsOperator() const
{
	return (_isOperator);
}

void Client::setIsConnected(bool isConnected){
    this->_isConnected = isConnected;
}

void	Client::setWaitingForSend(bool waitingForSend)
{
	_waitingForSend = waitingForSend;
}

void	Client::setIsOperator(bool isOperator)
{
	_isOperator = isOperator;
}

bool Client::getIsConnected() const {
    return (_isConnected);
}

bool Client::checkIfNicknameIsNotEmpty() {
	if (this->_nickname.empty()) {
		std::string message = "No nickname given";
		this->addMessageToSend(ERR_NONIKNAMEGIVEN());
		return (false);
	}
	return (true);
}

bool Client::checkIfNicknameIsAlreadyUsed(std::map<int, Client> clients) {
	std::map<int, Client>::iterator it;

	for (it = clients.begin(); it != clients.end(); it++) {
		if (it->second.getNickname() == this->_nickname && it->second.getFd() != this->_fd) {
			std::string message = "Nickname already in use";
			this->addMessageToSend(ERR_NICKNAMEINUSE(this->_nickname));
			return (false);
		}
	}
	return (true);
}

bool Client::checkIfNicknameContainsForbiddenCharacters() {
	if (this->_nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") != std::string::npos) {
		this->addMessageToSend(ERR_ERRONEUSNICKNAME(this->_nickname));
		return (false);
	}
	return (true);
}

bool Client::checkIfUsernameIsValid() {
	if (this->_username.empty()) {
		std::string message = "No username given";
		this->addMessageToSend(ERR_NEEDMOREPARAMS(std::string("USER")));
		return (false);
	}
	return (true);
}

void Client::setNickname(std::string nickname) {
	this->_nickname = nickname;
}

std::ostream	&operator<<(std::ostream &o, const Client &src)
{
	o << "Client fd: " << src.getFd() << std::endl;
	o << "Client password: " << src.getPassword() << std::endl;
	o << "Client nickname: " << src.getNickname() << std::endl;
	o << "Client username: " << src.getUsername() << std::endl;
	return (o);
}