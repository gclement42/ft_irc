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

std::string Server::readInBuffer(int fd) {
	char		buffer[1024];
	std::string	bufferString;
	ssize_t 	bytes;

	bytes = recv(fd, buffer, 1024, 0);
	if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		std::cout << "EAGAIN" << std::endl;
		return ("");
	}
	bufferString = buffer;
	bufferString = bufferString.substr(0, bytes);
	this->_buffer += bufferString;
	if (this->_buffer.find('\n', 0) != std::string::npos)
	{
		bufferString = this->_buffer;
		this->_buffer.clear();
	}
	if (bytes == -1) {
		if ((errno == EAGAIN || errno == EWOULDBLOCK))
			return (bufferString);
		//std::cerr << "errno : " << errno << std::endl;
		// throw exception (????)
		return ("");
	}
	return (bufferString);
}