#ifndef ERRORMESSAGES_HPP
# define ERRORMESSAGES_HPP

# include "main.hpp"

#define ERROR(reason) "ERROR :" + reason + "\r\n"
#define ERR_PASSWDMISMATCH(username) username + " :Password incorrect\r\n"

#endif