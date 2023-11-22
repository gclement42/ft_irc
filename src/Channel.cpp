/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:45:54 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/20 09:30:52 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "main.hpp"
#include <cstdarg>

Channel::Channel(std::string name, std::string topic, std::string key, std::string mode, int userLimit):
	_name(name), _topic(topic), _key(key), _mode(mode)
{
	this->_userLimit = userLimit;
	this->_userCount = 0;
	this->_inviteMode = false;
	this->_keyMode = false;
	this->_limitMode = false;
	this->_topicMode = false;
}

Channel::Channel(const Channel &src)
{
	*this = src;
}

Channel::~Channel(void) { }

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
	this->_keyMode = src._keyMode;
	this->_limitMode = src._limitMode;
	this->_topicMode = src._topicMode;
	this->_operators = src._operators;
	this->_invites = src._invites;
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

int	Channel::getUserLimit(void) const
{
	return (this->_userLimit);
}

int	Channel::getUserCount(void) const
{
	return (this->_userCount);
}

bool	Channel::getInviteMode(void) const
{
	return (this->_inviteMode);
}

std::vector<std::string>	&Channel::getOperators(void)
{
	return (this->_operators);
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

void	Channel::incrementUserCount(void)
{
	this->_userCount++;
}

void	Channel::addOperator(std::string nickname)
{
	this->_operators.push_back(nickname);
}

void Channel::addMode(char mode, ...)
{
	std::cout << "addmode : " << mode << std::endl;
	va_list args;
	va_start(args, mode);

	if (mode == 'k')
		this->setKey(va_arg(args, char *));
	if (mode == 'l')
		this->setUserLimit(va_arg(args, char *));
	if (mode == 'i')
		this->_inviteMode = true;
	if (mode == 't')
		this->_topicMode = true;
	if (this->_mode.find(mode) != std::string::npos)
		return ;
	this->_mode += mode;
	va_end(args);
}

void Channel::removeMode(char mode)
{
	if (this->_mode.find(mode) == std::string::npos)
		return ;
	this->_mode.erase(this->_mode.find(mode), 1);
	if (mode == 'k')
	{
		this->_key = "";
		this->_keyMode = false;
	}
	if (mode == 'l')
	{
		this->_userLimit = -1;
		this->_limitMode = false;
	}
	if (mode == 'i')
		this->_inviteMode = false;
	if (mode == 't')
		this->_topicMode = false;

}

void Channel::setKey(char *key)
{
	std::string keyString(key);
	this->_key = keyString;
	this->_keyMode = true;
}

void Channel::setUserLimit(char *userLimit)
{
	int userLimitInt = atoi(userLimit);
	this->_userLimit = userLimitInt;
	this->_limitMode = true;
}

bool Channel::getKeyMode(void) const {
	return (this->_keyMode);
}

bool Channel::getLimitMode(void) const {
	return (this->_limitMode);
}

bool Channel::getTopicMode(void) const {
	return (this->_topicMode);
}

bool Channel::checkIfClientIsOperator(std::string nickname) {
	for (size_t i = 0; i < this->_operators.size(); i++)
	{
		std::cout << "operators : " << this->_operators[i] << std::endl;
		if (this->_operators[i] == nickname)
			return (true);
	}
	return (false);
}

void Channel::addInvite(std::string nickname) {
	if (find(_invites.begin(), _invites.end(), nickname) != this->_invites.end())
		return ;
	this->_invites.push_back(nickname);
}

bool Channel::checkIfClientIsInvited(std::string nickname) {
	for (size_t i = 0; i < this->_invites.size(); i++)
	{
		std::cout << "invites : " << this->_invites[i] << std::endl;
		if (this->_invites[i] == nickname)
			return (true);
	}
	return (false);
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

