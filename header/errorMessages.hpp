#ifndef ERRORMESSAGES_HPP
# define ERRORMESSAGES_HPP

# include "main.hpp"

#define ERROR(reason) "ERROR :" + reason + "\r\n"
#define ERR_PASSWDMISMATCH(username) username + " :Password incorrect\r\n"
#define ERR_NICKNAMEINUSE(nickname) nickname + " :Nickname is already in use\r\n"
#define ERR_NONIKNAMEGIVEN() "No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(nickname) nickname + " :Erroneus nickname\r\n"
#define ERR_NEEDMOREPARAMS(command) command + " :Not enough parameters\r\n"

#endif