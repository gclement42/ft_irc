#ifndef ERRORMESSAGES_HPP
# define ERRORMESSAGES_HPP

# include "main.hpp"

// Generic errors
# define ERROR(reason) "ERROR :" + reason + "\r\n"
# define ERR_NEEDMOREPARAMS(client, command) ": 461 " + client + " " + command + " :Not enough parameters\r\n"

// Passwords
# define ERR_PASSWDMISMATCH(username) username + " :Password incorrect\r\n"
# define ERR_NOPASSWDGIVEN() "No password given\r\n"

// Nicknames and usernames
# define ERR_NICKNAMEINUSE(nickname) nickname + " :Nickname is already in use\r\n"
# define ERR_NONIKNAMEGIVEN() "No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nickname) nickname + " :Erroneus nickname\r\n"

// Channels
# define ERR_CHANNELISFULL(channel) channel + " :Cannot join channel: channel is full.\r\n"
# define ERR_INVITEONLYCHAN(channel) channel + " :Cannot join channel: channel is in invite mode (+i).\r\n"
# define ERR_BADCHANNELKEY(channel) channel + " :Cannot join channel: bad channel key.\r\n"
# define ERR_NOSUCHCHANNEL(nickname, channelName) ":irc 403 " + nickname + " "  + channelName + " :No such channel\r\n"
# define ERR_NOTONCHANNEL(nickname, channelName) ":irc 442 " + nickname + " "  + channelName + " :" + nickname + " is not on that channel\r\n"
# define ERR_USERONCHANNEL(nickname, channelName) ":irc 443 " + nickname + " "  + channelName + " :is already on channel\r\n"
# define ERR_USERNOTINCHANNEL(srcNickname, targetNickname, channelName) ":irc 441 "+ srcNickname + " " + targetNickname + " " + channelName + " :They aren't on that channel\r\n"
# define ERR_NOSUCHNICK(nickname, target) ":irc 401 " + nickname + " " + target + " :No such nick/channel\r\n"
# define ERR_CHANOPRIVSNEEDED(nickname, channelName) ":irc 482 " + nickname + " " + channelName + " :You're not channel operator\r\n"
# define ERR_BADCHANMASK(channelName) ":irc 476 " + channelName + " :Bad Channel Mask\r\n"
# define ERR_CANNOTSENDTOCHAN(nickname, channelName) ":irc 404 " + nickname + " " + channelName + " :Cannot send to channel\r\n"
# define ERR_NOTEXTTOSEND(nickname) ":irc 412 " + nickname + " :No text to send\r\n"

# define ERR_BADFORMATMODE() "MODE :Bad format mode\r\n"
# define ERR_ISNOTOPER(nickname) nickname + " : Is not an IRC operator\r\n"
# define ERR_UNKNOWNMODE(nickname, mode) ":irc 472 " + nickname + " " + mode + " :is unknown mode char to me\r\n"

#endif