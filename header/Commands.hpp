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

    public:
        Commands(std::map<int, Client> &clients, std::map<std::string, Channel> &channels,  Client &client);
        Commands(const Commands &src);

        ~Commands();
        Commands &operator=(const Commands &src);

        void						parseBuffer(std::string buffer);
		std::vector<std::string>	parseChannelName(std::vector<std::string> arg);
		std::vector<std::string>	parseKey(std::vector<std::string> arg);

		void	quit();
        void	join();
		void	topic();
//        void	Topic();

};


#endif
