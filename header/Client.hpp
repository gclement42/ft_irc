/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:10:34 by gclement          #+#    #+#             */
/*   Updated: 2023/11/06 12:57:42 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "main.hpp"
# include "Server.hpp"

class Server;
class Channel;

class Client {
	public :
		Client(std::string nickname, std::string username, int fd, std::string password);
		Client(const Client &src);
		~Client(void);
		Client		&operator=(const Client &src);
		int			getFd(void) const;
		std::string	getPassword(void) const;
		std::string	getNickname(void) const;
		std::string	getUsername(void) const;
		std::string	getChannel(void) const;
	private :
		const int					_fd;
		const std::string			_password;
		const std::string			_nickname;
		const std::string			_username;
		std::string					_channel;
};

std::ostream	&operator<<(std::ostream &o, const Client &src);

#endif