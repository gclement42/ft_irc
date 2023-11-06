/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:45:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/06 15:07:52 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "main.hpp"

Channel::Channel(std::string name, std::string topic, std::string key, std::string mode, int userLimit):
	_name(name), _topic(topic), _key(key), _mode(mode)
{
	this->_userLimit = userLimit;
	return ;
}

Channel::Channel(const Channel &src)
{
	*this = src;
	return ;
}

Channel::~Channel(void)
{
	return ;
}

Channel		&Channel::operator=(const Channel &src)
{
	(void)src;
	return (*this);
}

int			Channel::getUserLimit(void) const
{
	return (this->_userLimit);
}

std::string	Channel::getName(void) const
{
	return (this->_name);
}

std::string	Channel::getTopic(void) const
{
	return (this->_topic);
}

std::string	Channel::getKey(void) const
{
	return (this->_key);
}

std::string	Channel::getMode(void) const
{
	return (this->_mode);
}

