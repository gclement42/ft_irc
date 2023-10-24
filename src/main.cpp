/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:15 by gclement          #+#    #+#             */
/*   Updated: 2023/10/24 15:35:35 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	Server server(5000);
	server.start();
	while (1)
		server.update();
	return (0);
}