/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:10:25 by gclement          #+#    #+#             */
/*   Updated: 2023/11/06 13:14:03 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class Channel;
class Client;

class Server {
	public:
		Server(int port, std::string password);
		Server(const Server &src);
		~Server();
		Server	&operator=(const Server &src);
		void					start() const;
		void					stop() const;
		void					insertFd(pollfd client);
		void					eraseFd(pollfd client);
		size_t					getNbFd() const;
		int						getSocketServer() const;
		void					acceptClientConnexion();
		void					checkFdsEvent();
		pollfd					*getAllFds();
		void					displayClients();
		void 					disconnectClient(int fd);
        void                    createClient(int fd);
	private:
		std::map<int, Client>	        _clients;
		std::map<std::string, Channel>	_channels;
		pollfd					        *_allFds;
		size_t					        _nbFds;
		int						        _socketServer;
		int						        _port;
		std::string				        _password;
        void receiveMessageFromClient(pollfd &pollClient);
        void sendMessageToClient(pollfd &pollClient);
};

#endif