/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:05:06 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/02 10:45:28 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "Server.hpp"
//:username JOIN #channelname\r\n

int		check_channel_name(char *buffer, int fd)
{
	std::string 	channel_name(buffer);
	size_t			first_space;
	int				status;
	
	send(fd, ":boula JOIN #test_join\r\n", 23, 0);
	first_space = channel_name.find_first_of(" ") + 1;
	channel_name = channel_name.substr(first_space, channel_name.size());
	
	if (channel_name.find("#", 0) == 0 || channel_name.find("&", 0) == 0)
		status = SUCCESS;
	else
	{
		print_error("Wrong channel type. Please use `#channel_name` or ` &channel_name`.");
		return (FAILURE);		
	}
	
	if (channel_name.find(" ", 0) < 1024 || channel_name.find(",", 0) < 1024)
	{
		print_error("Wrong channel name. You cannot use ` ` or `,` in a channel name.");
		return (FAILURE);		
	}
	return (SUCCESS);
}

void	print_error(std::string msg)
{
	std::cout << "\033[44m";
	std::cout << msg;
	std::cout << "\033[0m" << std::endl;
}