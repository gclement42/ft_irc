/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:22 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/06 11:25:03 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Client.hpp"

void	parseBuffer(Client client, std::string buffer)
{	
	std::string 	cmd;
	std::string		arg;
	size_t			first_space;
	size_t			length;

	first_space = buffer.find(" ", 0);
	length = buffer.length() - 1;
	cmd = buffer.substr(0, first_space);
	arg = buffer.substr(first_space + 1, length);
	
	// tableau arguments pr clement
	if (cmd == "JOIN")
		commandJoin(client, arg);
	// else if (cmd == "KICK")
	// 	// cmd_kick(buffer);
	// 	std::cout << "KICK" << std::endl;
	// else if (cmd == "INVITE")
	// 	// cmd_invite(buffer);
	// 	std::cout << "INVITE" << std::endl;
	// else if (cmd == "TOPIC")
	// 	// cmd_topic(buffer);
	// 	std::cout << "TOPIC" << std::endl;
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