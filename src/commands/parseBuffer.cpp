/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseBuffer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:22 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/21 10:14:03 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Client.hpp"
#include "Channel.hpp"

static std::vector<std::string> splitBuffer(std::string str);

void	Commands::parseBuffer(std::string buffer)
{	
	this->_args = splitBuffer(buffer);
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

static std::string cleanCommandNameFormat(std::string cmdName)
{
	size_t i = 0;

	if (cmdName[0] == '/')
		cmdName = cmdName.substr(1, cmdName.size());
	while (i < cmdName.size())
	{
		cmdName[i] = std::toupper(cmdName[i]);
		i++;
	}
	return (cmdName);
}

static std::vector<std::string> splitBuffer(std::string str)
{
	std::vector<std::string>	arguments;
	std::stringstream 			streamBuffer(str);
	std::string					tmp;
	size_t						i = 0;

	while (getline(streamBuffer, tmp, ' '))
	{
		arguments.push_back(tmp);
		i++;
	}
	arguments[0] = cleanCommandNameFormat(arguments[0]);
	return (arguments);
}