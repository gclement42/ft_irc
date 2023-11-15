#ifndef ERRORMESSAGES_HPP
# define ERRORMESSAGES_HPP

# include "main.hpp"

// Generic errors
# define ERROR(reason) "ERROR :" + reason + "\r\n"
# define ERR_NEEDMOREPARAMS(command) command + " :Not enough parameters\r\n"

// Passwords
# define ERR_PASSWDMISMATCH(username) username + " :Password incorrect\r\n"

// Nicknames and usernames
# define ERR_NICKNAMEINUSE(nickname) nickname + " :Nickname is already in use\r\n"
# define ERR_NONIKNAMEGIVEN() "No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nickname) nickname + " :Erroneus nickname\r\n"

// Channels
# define ERR_CHANNELISFULL(channel) channel + " :Cannot join channel: channel is full.\r\n"
# define ERR_INVITEONLYCHAN(channel) channel + " :Cannot join channel: channel is in invite mode (+i).\r\n"
# define ERR_BADCHANNELKEY(channel) channel + " :Cannot join channel: bad channel key.\r\n"
#define ERR_NOSUCHCHANNEL(nickname, channelName) ":irc 403 " + nickname + " "  + channelName + " :No such channel\r\n"
#endif