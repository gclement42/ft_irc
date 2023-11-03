/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:04:31 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 11:14:15 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "main.hpp"

Client::Client(std::string nickname, std::string username, pollfd data, std::string password):
 _data(data), _password(password), _nickname(nickname), _username(username)
{
	_channel = "default";
}

Client::Client(const Client &src)
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
	_data = src._data;
	_channel = src._channel;
	return (*this);
}

pollfd		Client::getData(void) const
{
	return (_data);
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