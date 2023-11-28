/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readInBuffer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:43:52 by gclement          #+#    #+#             */
/*   Updated: 2023/11/06 12:46:47 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

static std::map<int, std::string>::iterator 		getBufferByFd(std::map<int, std::string> &buffer, int fd);

int Server::readInBuffer(int fd) {
	char		buffer[1024];
	ssize_t 	bytes;
	std::map<int, std::string>::iterator it;

	it = getBufferByFd(this->_bufferByFd, fd);
	bytes = recv(fd, buffer, 1024, 0);
	if (bytes == -1)
		return (-1);
	this->_buffer = buffer;
	this->_buffer = this->_buffer.substr(0, bytes);
	it->second += this->_buffer;
	if (it->second.find('\n', 0) != std::string::npos)
	{
		_buffer = it->second;
		it->second.clear();
		return (1);
	}
	else
		return (0);
}

static std::map<int, std::string>::iterator 		getBufferByFd(std::map<int, std::string> &buffer, int fd)
{
	std::map<int, std::string>::iterator it;

	if (buffer.find(fd) == buffer.end())
	{
		it = buffer.insert(std::pair<int, std::string>(fd, "")).first;
		return (it);
	}
	return (buffer.find(fd));
}
