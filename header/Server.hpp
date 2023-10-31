/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:10:25 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 10:29:35 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Pollfds.hpp"
# include "main.hpp"

class Server
{
	public:
		Server(int port);
		Server(const Server &src);
		~Server(void);
		Server	&operator=(const Server &src);
		void	start(void);
		void	acceptClientConnexion(void);
		void	checkClientEvent(void);
		void 	joinCommand(void);
		Pollfds	&getAllClients(void);
	private:
		Pollfds	_allClients;
		int		_socketServer;
		int		_port;
};

#endif