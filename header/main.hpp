/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:11 by gclement          #+#    #+#             */
/*   Updated: 2023/11/06 15:49:43 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <poll.h>
# include <unistd.h>
# include <string.h>
# include <sstream>
# include <vector>
# include <fcntl.h>
# include <cerrno>
# include <cstring>
# include <csignal>
# include <cstdlib>
# include <map>
# include "errorMessages.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define FAILURE 		0
# define SUCCESS 		1
# define USER_LIMITS 	10

class Server;
class Client;
class Channel;

Client 			parseClientData(std::string buffer, int fd);
std::string 	readInBuffer(int fd);
void 			printError(std::string error);
void			parseBuffer(Client &client, std::string buffer);
void			commandJoin(Client &client, std::string buffer);

#endif