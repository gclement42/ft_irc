/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:04:31 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 15:36:37 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "main.hpp"

Client::Client(std::string nickname, std::string username, int fd, std::string password):
 _fd(fd), _password(password), _nickname(nickname), _username(username)
{
	_channel = "default";
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

std::string	Client::getChannel(void) const
{
	return (_channel);
}

std::ostream	&operator<<(std::ostream &o, const Client &src)
{
	o << "Client fd: " << src.getFd() << std::endl;
	o << "Client password: " << src.getPassword() << std::endl;
	o << "Client nickname: " << src.getNickname() << std::endl;
	o << "Client username: " << src.getUsername() << std::endl;
	o << "Client channel: " << src.getChannel() << std::endl;
	return (o);
}