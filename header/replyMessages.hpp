//
// Created by gclement on 11/10/23.
//

#ifndef REPLYMESSAGES_HPP
#define REPLYMESSAGES_HPP

#include "main.hpp"

#define RPL_WELCOME(nickname) "Welcome to the ft_irc " + nickname + "\r\n"
#define RPL_YOUREOPER(nickname) ": You are now an IRC operator\r\n"
#define	RPL_QUIT(reason) "QUIT :" + reason + "\r\n"


#endif
