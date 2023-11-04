/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:10:25 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 15:58:21 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"
# include "Client.hpp"

class Server {
	public:
		Server(int port, std::string password);
		Server(const Server &src);
		~Server(void);
		Server	&operator=(const Server &src);
		void					start(void);
		void					stop(void);
		void					insertFd(pollfd client);
		void					eraseFd(pollfd client);
		size_t					getNbFd(void) const;
		int						getSocketServer(void) const;
		void					acceptClientConnexion(void);
		void					checkFdsEvent(void);
		void 					joinCommand(void);
		pollfd					*getAllFds(void);
		std::string				readInBuffer(int fd);
		void					displayClients(void);
	private:
		std::map<int, Client>	_clients;
		pollfd					*_allFds;
		size_t					_nbFds;
		int						_socketServer;
		int						_port;
		std::string				_password;
};

#endif