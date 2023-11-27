/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:10:34 by gclement          #+#    #+#             */
/*   Updated: 2023/11/15 08:43:24 by lboulatr         ###   ########.fr       */
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
		Client(int fd);
		Client(const Client &src);
		~Client();
		Client		&operator=(const Client &src);

		int						    getFd() const;
		std::string				    &getPassword();
		std::string				    &getNickname();
		std::string				    &getUsername();
		std::string				    &getRealname();
        bool                        getIsConnected() const;
		std::vector<std::string>    &getChannels();
		bool				    	getWaitingForSend() const;
        std::vector<std::string>    getMessageToSend();

		bool 					    checkIfPasswordIsValid(Client client, std::string passwordServer);
        bool                        checkIfNicknameIsValid(std::map<int, Client> clients);
		bool						checkIfUsernameIsValid();

		void					    sendAllMessageToClient();
		void					    addMessageToSend(std::string message);
		void						addChannel(std::string channelName);

        void                        setIsConnected(bool isConnected);
		void				    	setWaitingForSend(bool waitingForSend);
		void						setNickname(std::string nickname);
		void						setUsername(std::string username);
		void						setRealname(std::string realname);
		void						setPassword(std::string password);
		bool						checkIfAllDataIsFilled();



	private :
		const int					_fd;
		std::string					_password;
		std::string					_nickname;
		std::string					_username;
		std::string					_realname;
		std::vector<std::string>	_channel;
		std::vector<std::string>	_messagesToSend;
        bool                        _isConnected;
		bool					    _waitingForSend;

		bool 					    checkIfNicknameIsAlreadyUsed(std::map<int, Client> clients);
		bool				   		checkIfNicknameIsNotEmpty();
		bool						checkIfNicknameContainsForbiddenCharacters();
};

std::ostream	&operator<<(std::ostream &o, Client &src);

#endif