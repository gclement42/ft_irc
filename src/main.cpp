/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:15 by gclement          #+#    #+#             */
/*   Updated: 2023/11/06 13:16:52 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: ./ft_irc <port> <password>" << std::endl;
		return (0);
	}
	std::string password = "salut";
	int port = atoi(argv[1]);
	if (argv[2])
		password = argv[2];
	Server server(port, password);
	server.start();
	while (1)
	{
		server.acceptClientConnexion();
		server.checkFdsEvent();
	}
	server.stop();
	return (0);
}