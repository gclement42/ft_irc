/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:25:28 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/28 12:25:33 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "main.hpp"

class Commands {

    private:
		std::map<std::string, void (Commands::*)()>		_cmd;
        std::map<int, Client>           				&_clients;
        std::map<std::string, Channel>  				&_channels;
        Client                          				&_client;
        std::vector<std::string>        				_args;
        std::string                     				_operPassword;

    public:
        Commands(std::map<int, Client> &clients, std::map<std::string, Channel> &channels,  Client &client);
        Commands(const Commands &src);

        ~Commands();
        Commands &operator=(const Commands &src);


        //Commands
		void	                    quit();
        void	                    join();
		void	                    topic();
        void                        privateMsg();
		void						nick();
		void						kick();
		void						invite();
		void						part();
		void						mode();

        //Utils commands

		std::map<std::string, Channel>		&getChannels() const;
		std::map<int, Client>				&getClients() const;
		Client								&getClient() const;
		std::vector<std::string>			&getArgs();
		void								removeOperatorFromChannels();

		std::string					concatenate(std::vector<std::string> stringTab);
		std::vector<std::string>	splitByComa(std::string str);
		std::vector<std::string>	parseChannelName(std::vector<std::string> arg);
		std::vector<std::string>	parseKey(std::vector<std::string> arg);
        void						parseBuffer(std::string buffer);
        std::vector<std::string>    allClientsOnChannel(std::string channel);
		void 						sendPrivMsgChannel(std::map<int, Client> &clients, std::vector<std::string> allClients, \
										std::string client, std::string channel, std::vector<std::string> args);
		void						sendPrivMsgUser(std::map<int, Client> &clients, Client &client, \
										std::vector<std::string> args, std::string target);
		void                        sendMsgToAllClientsInChannel(std::vector<std::string> allClients, std::string msg);
		bool						checkIfChannelExist(std::string channelName);
		bool 						checkIfThisUserIsOnChannel(std::string channelName);
		bool 						checkIfTargetClientIsOnChannel(std::string channelName, std::string targetClient);
		Client						&getClientFromNickname(std::string nickname);
        void                        addChannelInMap(std::string nickname, std::string channelName);
        int                         isOperatorInChannel(std::string nickname, std::string channel);
		Channel						&getChannelFromName(std::string name);

        void	                    addClientInChannel(std::string channel, std::string topic);
	    void                        displayListClientOnChannel(std::string channelName);
		void						displayModeChannel();

		void 						reachModestring(std::string modestring, std::vector<std::string> modeArgs, Channel &channel);
		void 						operatorMode(std::string arg, Channel &channel, char symbol);
		void 						operatorRemove(Channel &channel, std::vector<std::string> &operators, Client &target);
};


#endif
