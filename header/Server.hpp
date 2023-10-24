/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:10:25 by gclement          #+#    #+#             */
/*   Updated: 2023/10/24 15:31:19 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <iostream>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <poll.h>

class Server
{
	public:
		Server(int port);
		Server(const Server &src);
		~Server(void);
		Server	&operator=(const Server &src);
		void	start(void);
		void	update(void);
	private:
		pollfd	*_socketClient;
		int		_socketServer;
		int		_port;
		
};

#endif