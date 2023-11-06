/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:11 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 11:29:13 by lboulatr         ###   ########.fr       */
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
# include <csignal>
# include <cstdlib>

# define FAILURE 		0
# define SUCCESS 		1

void			initServer(void);

// ====== PARSING ======
void			parseBuffer(std::string buffer);

// ====== COMMANDS ======

void	commandJoin(std::string buffer);

// ====== UTILS ======
void 			printError(std::string error);

#endif