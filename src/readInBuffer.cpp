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

std::string readInBuffer(int fd) {
	char		buffer[1024];
	std::string	concatenateBuffer;
	ssize_t 	bytes;
	int			lastNewline;

	bytes = recv(fd, buffer, 1024, 0);
	if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		std::cout << "EAGAIN" << std::endl;
		return ("");
	}
	concatenateBuffer = buffer;
	lastNewline = concatenateBuffer.find_last_of("\r\n");
	concatenateBuffer = concatenateBuffer.substr(0, lastNewline + 1);
	if (bytes == -1) {
		if ((errno == EAGAIN || errno == EWOULDBLOCK))
		{
			std::cout << "EAGAIN after while" << std::endl;
			return (concatenateBuffer);
		}
		//std::cerr << "errno : " << errno << std::endl;
		// throw exception (????)
		return ("error");
	}
	return (concatenateBuffer);
}