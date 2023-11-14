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

        void						parseBuffer(std::string buffer);

        //Commands
		void	                    quit();
        void	                    join();
		void	                    topic();
        void                        privateMsg();
        void                        oper();
		void						nick();
		void						invite();

        //Utils commands
        std::vector<std::string>    allClientsOnChannel(std::string channel);
        void                        sendMsgToAllClients(std::vector<std::string> allClients, std::string msg);
		bool						checkIfChannelExist(std::string channelName);
		bool 						checkIfThisUserIsOnChannel(std::string channelName);
		bool checkIfTargetClientIsOnChannel(std::string channelName, std::string targetClient);
};


#endif
