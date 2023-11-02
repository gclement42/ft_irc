/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:15 by gclement          #+#    #+#             */
/*   Updated: 2023/11/02 10:30:07 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	if (argc != 2)
	{
		std::cout << "Usage: ./ft_irc <port>" << std::endl;
		return (0);
	}
	int port = atoi(argv[1]);
	Server server(port);
	server.start();
	while (1)
	{
		server.acceptClientConnexion();
		server.checkFdsEvent();
	}
	server.stop();
	return (0);
}