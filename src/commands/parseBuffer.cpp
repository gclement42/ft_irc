/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseBuffer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:22 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/06 15:48:41 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Client.hpp"
#include "Channel.hpp"

static std::vector<std::string> splitBuffer(std::string str, char c);

void	Commands::parseBuffer(std::string buffer)
{	
	this->_args = splitBuffer(buffer, ' ');
	
	if (_args[0] == "JOIN")
		this->join();
    if (_args[0] == "QUIT")
        this->quit();
	// else if (cmd == "KICK")
	// 	// cmd_kick(buffer);
	// 	std::cout << "KICK" << std::endl;
	// else if (cmd == "INVITE")
	// 	// cmd_invite(buffer);
	// 	std::cout << "INVITE" << std::endl;
	 else if (_args[0] == "TOPIC")
	 	 this->topic();
//	 	std::cout << "TOPIC" << std::endl;
	// else if (cmd == "MODE")
	// 	// cmd_mode(buffer);
	// 	std::cout << "MODE" << std::endl;
	else
	{
		printError("This command does not exist.");
		return ;
	}
}

void printError(std::string error)
{
	std::cout << "\033[44m";
	std::cout << error;
	std::cout << "\033[0m" << std::endl;
}

static std::vector<std::string> splitBuffer(std::string str, char c)
{
	std::vector<std::string>	arguments;
	std::string					tmp;
	size_t						i = 0;

	while(i < str.size())
	{
		if (str[i] == c)
		{
			arguments.push_back(tmp);
			tmp.clear();
		}
		else
			tmp += str[i];
		i++;
	}

	arguments.push_back(tmp);

	return (arguments);
}