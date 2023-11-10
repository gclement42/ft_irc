/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:10:34 by gclement          #+#    #+#             */
/*   Updated: 2023/11/09 10:12:20 by lboulatr         ###   ########.fr       */
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
		~Client();
		Client		&operator=(const Client &src);
		int						    getFd() const;
		std::string				    getPassword() const;
		std::string				    getNickname() const;
		std::string				    getUsername() const;
		std::vector<std::string>    &getChannels();
		void 					    checkIfPasswordIsValid(Client client, std::string passwordServer);
		bool					    checkIfClientIsStillConnected() const;
		void					    sendAllMessageToClient();
		void					    addMessageToSend(std::string message);
		void						addChannel(std::string channelName);
        void                        setIsConnected();
        bool                        getIsConnected() const;
        std::vector<std::string>    getMessageToSend();
	private :
		const int					_fd;
		const std::string			_password;
		const std::string			_nickname;
		const std::string			_username;
		std::vector<std::string>	_channel;
		std::vector<std::string>	_messagesToSend;
        bool                        _isConnected;
};

std::ostream	&operator<<(std::ostream &o, const Client &src);

#endif