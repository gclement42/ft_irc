/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:10:25 by gclement          #+#    #+#             */
/*   Updated: 2023/11/10 14:35:30 by lboulatr         ###   ########.fr       */
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
		Server(int port, const std::string& password);
		Server(const Server &src);
		~Server();
		Server	&operator=(const Server &src);
		void					start() const;
		void					stop() const;
		void					insertFd(pollfd client);
		void					eraseFd(int fd);

		size_t					getNbFd() const;
		int						getSocketServer() const;
		pollfd					*getAllFds();

		void					acceptClientConnexion();
		void 					disconnectClient(int fd);
		void 					fillClientData(Client &client, std::string buffer);

		void					checkFdsEvent();
		bool                   	checkIfClientIsWaitingForSend(int fd);
		std::string				readInBuffer(int fd);

	private:
		std::map<int, Client>	        _clients;
		std::map<std::string, Channel>	_channels;
		pollfd					        *_allFds;
		size_t					        _nbFds;
		int						        _socketServer;
		int						        _port;
		std::string				        _password;
		std::map<int, std::string>		_buffer;
        void receiveMessageFromClient(pollfd &pollClient);
        void sendMessageToClient(pollfd &pollClient);

};

#endif