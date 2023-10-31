/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:15 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 10:28:32 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"
#include "Pollfds.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	Server server(5000);
	server.start();
	while (1)
	{
		server.acceptClientConnexion();
		server.checkClientEvent();
		//std::cout << "fds.getNbClients() = " << fds.getNbClients() << std::endl;
		if (server.getAllClients().getNbClients() > 2)
		{
			std::cout << "NbClient > 2" << std::endl;
			server.getAllClients().erase(server.getAllClients().getFds()[2]);
		}
	}
	return (0);
}