/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:05:18 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/21 14:01:05 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

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

# define SUCCESS 0
# define FAILURE 1

class Bot
{
	public:

		Bot(int port, std::string password, std::string ip);
		~Bot(void);
		
		int 					startBot(void);
		void 					closeBot(void);
		void 					runBot(void);
		std::string 			readInBuffer(int socket);
		void 					botResponse(std::string buffer, int socket);
		
		std::map<std::string, std::string>		createResponsesMap(void);
		void 									newUserInChannel(int socket);
		void 									privateMsgResponse(std::string buffer, int socket);

	private:

		int 					_socket;
		int 					_port;
		
		std::string 			_serverPassword;
		std::string 			_ip;
		std::string 			_botPassword;
		std::string 			_nickName;
		std::string 			_userName;
		
		struct sockaddr_in 		_addr;

		std::map<std::string, std::string>		_responses;
	
};

void 	printError(std::string error);

#endif