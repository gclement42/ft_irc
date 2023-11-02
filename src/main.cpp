/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:15 by gclement          #+#    #+#             */
/*   Updated: 2023/11/02 10:42:38 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	
	//---------------------------
	// char str[1024] = "JOIN #boulaokptdrtest";
	// check_channel_name(str);
	// std::cout << "\n\n";

	//----------------------------
	
	
	Server server(5000);
	server.start();
	while (1)
	{
		server.acceptClientConnexion();
		server.checkFdsEvent();
	}
	return (0);
}