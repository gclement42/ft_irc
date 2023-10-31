/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pollfds.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:44:26 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 10:13:05 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pollfds.hpp"

Pollfds::Pollfds(void) {
	_fds = NULL;
	_nbClients = 0;
}

Pollfds::Pollfds(const Pollfds &src) {
	*this = src;
}

Pollfds::~Pollfds(void) {
	if (_fds)
		delete [] _fds;
}

Pollfds &Pollfds::operator=(const Pollfds &src)
{
	size_t	i;

	i = 0;
	if (&src == this)
		return (*this);
	delete [] _fds;
	_fds = new pollfd[src._nbClients];
	while (i < src._nbClients)
	{
		_fds[i] = src._fds[i];
		i++;
	}
	_nbClients = src._nbClients;
	return (*this);
}

void	Pollfds::insert(pollfd client)
{
	pollfd	*tmp;
	size_t	i;

	i = 0;
	tmp = new pollfd[_nbClients + 1];
	while (i < _nbClients)
	{
		tmp[i] = _fds[i];
		i++;
	}
	tmp[i] = client;
	delete [] _fds;
	_fds = tmp;
	_nbClients++;
}

void	Pollfds::erase(pollfd client)
{
	pollfd		*tmp;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	tmp = new pollfd[_nbClients - 1];
	while (i < _nbClients)
	{
		if (_fds[i].fd != client.fd)
		{
			tmp[j] = _fds[i];
			j++;
		}
		i++;
	}
	delete [] _fds;
	_fds = tmp;
	_nbClients--;
}

pollfd	*Pollfds::getFds(void) const
{
	return (_fds);
}

size_t	Pollfds::getNbClients(void) const
{
	return (_nbClients);
}


