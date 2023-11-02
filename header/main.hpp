/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:11 by gclement          #+#    #+#             */
/*   Updated: 2023/11/02 10:40:44 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <poll.h>
# include <unistd.h>
# include <string.h>
# include <sstream>
# include <vector>
# include <fcntl.h>
# include <cerrno>
# include <cstring>

# define FAILURE 0
# define SUCCESS 1

void   	initServer(void);

//========== Channels ==========
int		check_channel_name(char *buffer, int fd);
void	print_error(std::string msg);


#endif