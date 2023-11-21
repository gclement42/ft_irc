/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:03:16 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/21 09:06:38 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int main(int argc, char **argv)
{
	int 			port;
	std::string 	password;

	if (argc != 3)
		return (printError("Usage: ./bot [port] [password]"), FAILURE);

	port = atoi(argv[1]);
	password = argv[2];

	Bot bot(port, password, "ptdr");
	bot.startBot();
	bot.runBot();
	bot.closeBot();
	return (SUCCESS);
}

void printError(std::string error)
{
	std::cout << "\033[1;31m";
	std::cout << error << std::endl;
	std::cout << "\033[0m";
}