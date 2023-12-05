/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:15 by gclement          #+#    #+#             */
/*   Updated: 2023/11/23 09:04:23 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"

bool quit = false;
static bool checkPort(char *port);

void	sigint_handler(int sig)
{
	(void) sig;
	quit = true;
}

bool checkArgs(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./ft_irc <port> <password>" << std::endl;
		return (false);
	}
	if (!checkPort(argv[1]))
	{
		std::cout << "Invalid port" << std::endl;
		return (false);
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (!checkArgs(argc, argv))
		return (0);

	std::string password;

	int port = atoi(argv[1]);
	if (argv[2])
		password = argv[2];
	Server server(port, password);
	server.start();
	while (!quit)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		server.acceptClientConnexion();
		server.checkFdsEvent();
	}
	server.stop();
	return (0);
}

static bool checkPort(char *port)
{
	for (int i = 0; port[i]; i++)
	{
		if (isdigit(port[i]) == false)
			return (false);
	}

	int portInt = atoi(port);
	
	if (portInt < 1 || portInt > 65535)
		return (false);
	return (true);
}