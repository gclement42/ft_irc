/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:11 by gclement          #+#    #+#             */
/*   Updated: 2023/11/13 09:50:40 by lboulatr         ###   ########.fr       */
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
# include <ctime>
# include <sstream>
# include <sstream>
# include <vector>
# include <fcntl.h>
# include <cerrno>
# include <cstring>
# include <csignal>
# include <cstdlib>
# include <algorithm>
# include <map>
# include "errorMessages.hpp"
# include "replyMessages.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Commands.hpp"

# define FAILURE 		0
# define SUCCESS 		1
# define N_CMD 			7
# define USER_LIMITS 	5
# define USERLEN 		12

class Server;
class Client;
class Channel;

Client 			parseClientData(std::string buffer, int fd);
std::string 	readInBuffer(int fd);
void 			printError(std::string error);
void			parseBuffer(Client &client, std::string buffer, std::map<std::string, Channel> &channels);

void	        joinCommand(Client &client, std::vector<std::string> arg, std::map<std::string, Channel> &channels);
void            quitCommand(Client &client, std::vector<std::string> arg);

#endif