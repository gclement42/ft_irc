/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:10:34 by gclement          #+#    #+#             */
/*   Updated: 2023/11/10 14:28:23 by lboulatr         ###   ########.fr       */
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
		Client(std::string nickname, std::string username, std::string realname, int fd, std::string password);
		Client(const Client &src);
		~Client();
		Client		&operator=(const Client &src);
		int						    getFd() const;
		std::string				    getPassword() const;
		std::string				    getNickname() const;
		std::string				    getUsername() const;
        bool                        getIsConnected() const;
		std::vector<std::string>    &getChannels();
		bool				    	getWaitingForSend() const;
		bool 					    checkIfPasswordIsValid(Client client, std::string passwordServer);
        bool                        checkIfNicknameIsValid(std::map<int, Client> clients);
		bool						checkIfUsernameIsValid();
		bool					    checkIfClientIsStillConnected() const;
		void					    sendAllMessageToClient();
		void					    addMessageToSend(std::string message);
		void						addChannel(std::string channelName);
        void                        setIsConnected(bool isConnected);
		void						setNickname(std::string nickname);
		void				    	setWaitingForSend(bool waitingForSend);
        bool                        getIsConnected() const;
        std::vector<std::string>    getMessageToSend();

	private :
		const int					_fd;
		const std::string			_password;
		std::string			_nickname;
		const std::string			_username;
		const std::string			_realname;
		std::vector<std::string>	_channel;
		std::vector<std::string>	_messagesToSend;
        bool                        _isConnected;
		bool					    _waitingForSend;

		bool 					    checkIfNicknameIsAlreadyUsed(std::map<int, Client> clients);
		bool				   		checkIfNicknameIsNotEmpty();
		bool						checkIfNicknameContainsForbiddenCharacters();
};

std::ostream	&operator<<(std::ostream &o, const Client &src);

#endif