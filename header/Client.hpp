/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:10:34 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 15:35:14 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "main.hpp"
# include "Server.hpp"

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
		int					_fd;
		std::string			_password;
		std::string			_nickname;
		std::string			_username;
		std::string			_channel;
};

#endif