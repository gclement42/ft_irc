/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:10:25 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 10:42:12 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"

class Server
{
	public:
		Server(int port);
		Server(const Server &src);
		~Server(void);
		Server	&operator=(const Server &src);
		void	start(void);
		void	insertClient(pollfd client);
		void	eraseClient(pollfd client);
		size_t	getNbClients(void) const;
		void	acceptClientConnexion(void);
		void	checkClientEvent(void);
		void 	joinCommand(void);
		pollfd	*getAllClients(void);
	private:
		pollfd	*_allClients;
		size_t	_nbClients;
		int		_socketServer;
		int		_port;
};

#endif