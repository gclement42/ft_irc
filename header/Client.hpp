/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:10:34 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 11:13:53 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
# include "Server.hpp"

class Client {
	public :
		Client(std::string nickname, std::string username, pollfd data, std::string password);
		Client(const Client &src);
		~Client(void);
		Client	&operator=(const Client &src);
		pollfd		getData(void) const;
		std::string	getPassword(void) const;
		std::string	getNickname(void) const;
		std::string	getUsername(void) const;
		std::string	getChannel(void) const;
	private :
		pollfd				_data;
		const std::string	_password;
		const std::string	_nickname;
		const std::string	_username;
		std::string			_channel;
};