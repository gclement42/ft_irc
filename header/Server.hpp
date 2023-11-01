/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:10:25 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 12:59:19 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "main.hpp"

class Server {
	public:
		Server(int port);
		Server(const Server &src);
		~Server(void);
		Server	&operator=(const Server &src);
		void			start(void);
		void			insertFd(pollfd client);
		void			eraseFd(pollfd client);
		size_t			getNbFd(void) const;
		void			acceptClientConnexion(void);
		void			checkFdsEvent(void);
		void 			joinCommand(void);
		pollfd			*getAllFds(void);
	private:
		pollfd	*_allFds;
		size_t	_nbFds;
		int		_socketServer;
		int		_port;
};

#endif