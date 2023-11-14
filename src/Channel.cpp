/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:45:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/13 10:16:57 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "main.hpp"

Channel::Channel(std::string name, std::string topic, std::string key, std::string mode, int userLimit):
	_name(name), _topic(topic), _key(key), _mode(mode)
{
	this->_userLimit = userLimit;
	this->_userCount = 0;
	this->_inviteMode = false;
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
	if (&src == this)
		return (*this);
	this->_name = src._name;
	this->_topic = src._topic;
	this->_key = src._key;
	this->_mode = src._mode;
	this->_userLimit = src._userLimit;
	this->_userCount = src._userCount;
	this->_inviteMode = src._inviteMode;
	
	return (*this);
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

int			Channel::getUserLimit(void) const
{
	return (this->_userLimit);
}

int			Channel::getUserCount(void) const
{
	return (this->_userCount);
}

bool		Channel::getInviteMode(void) const
{
	return (this->_inviteMode);
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

void	Channel::incrementUserCount(void)
{
	this->_userCount++;
}

std::ostream	&operator<<(std::ostream &o, const Channel &src)
{
	o << "Channel name: " << src.getName() << std::endl;
	o << "Channel topic: " << src.getTopic() << std::endl;
	o << "Channel key: " << src.getKey() << std::endl;
	o << "Channel mode: " << src.getMode() << std::endl;
	o << "Channel user limit: " << src.getUserLimit() << std::endl;
	return (o);
}

