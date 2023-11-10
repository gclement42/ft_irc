/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseBuffer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:22 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/10 08:59:39 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Client.hpp"
#include "Channel.hpp"

static std::vector<std::string> splitBuffer(std::string str, char c);

void	Commands::parseBuffer(std::string buffer)
{
	std::cout << "\033[1;35mbuffer: " << buffer << "\033[0m" << std::endl;
	
	this->_args = splitBuffer(buffer, ' ');
	std::string cmdName = this->_args[0];

	if (this->_cmd.find(cmdName) != this->_cmd.end())
		(this->*_cmd[cmdName])();
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