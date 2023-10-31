/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:10:34 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 14:12:48 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
# include "Server.hpp"

class Client {
	public :
		Client(std::string nickname);
		Client(const Client &src);
		~Client(void);
		Client	&operator=(const Client &src);
	private :
		pollfd				_data;	
		const std::string	_nickname;
		const std::string	_username;
		std::string			_channel;
};