/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:03:16 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/22 09:36:47 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

static int checkPort(int port);

int main(int argc, char **argv)
{
	int 			port;
	std::string 	password;

	if (argc != 3)
		return (printError("Usage: ./bot [port] [password]"), FAILURE);

	port = atoi(argv[1]);
	password = argv[2];

	if (checkPort(port) == FAILURE)
		return (printError("Invalid port"), FAILURE);

	Bot bot(port, password);
	
	bot.startBot();
	bot.runBot();
	bot.closeBot();
	
	return (SUCCESS);
}

static int checkPort(int port)
{
	if (port <= 0 || port > 65535)
		return (FAILURE);
	return (SUCCESS);
}

void printError(std::string error)
{
	std::cout << "\033[1;31m";
	std::cout << error << std::endl;
	std::cout << "\033[0m";
}