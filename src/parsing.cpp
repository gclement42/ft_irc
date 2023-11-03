/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 08:58:22 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/03 11:03:59 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

void	parsing(std::string buffer)
{
	int				cmd_exist;
	std::string 	cmd;
	size_t			first_space;
	std::string     commands[5] =
    {
        "JOIN",
        "KICK",
        "INVITE",
        "TOPIC",
		"MODE",
    };

	first_space = buffer.find(" ", 0);
	cmd = buffer.substr(0, first_space);
	
	for (int i = 0; i < N_COMMANDS; i++)
	{
		if (cmd == commands[i])
		{
			cmd_exist = SUCCESS;
			break;
		}
		if (i == N_COMMANDS - 1)
			cmd_exist = FAILURE;
	}

	if (cmd_exist == FAILURE)
	{
		print_error("This command does not exist.");
		return ;
	}
}


std::string get_channel_name(std::string buffer)
{
	int				status = FAILURE;
	std::string		channel_name;
	size_t			first_space;
	
	first_space = buffer.find(" ", 0) + 1;
	channel_name = buffer.substr(first_space, buffer.length());
	std::cout << "Channel name: '" << channel_name << "'" << std::endl;
	
	if (channel_name.find("#", 0) == 0 || channel_name.find("&", 0) == 0)
		status = SUCCESS;
	else
	{
		print_error("Wrong channel name. Please use `#` or `&` to start a channel name.");
		return (NULL);
	}

	if (channel_name.find(" ", 0) < 1024 || channel_name.find(",", 0) < 1024)
	{
		print_error("Wrong channel name. You cannot use a ` ` or a `,` in the channel name.");
		return (NULL);
	}
	return (channel_name);
}

void print_error(std::string error)
{
	std::cout << "\033[44m";
	std::cout << error;
	std::cout << "\033[0m" << std::endl;
}