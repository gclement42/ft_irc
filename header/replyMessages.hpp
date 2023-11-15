//
// Created by gclement on 11/10/23.
//

#ifndef REPLYMESSAGES_HPP
#define REPLYMESSAGES_HPP

#include "main.hpp"

#define RPL_WELCOME(nickname) "Welcome to the ft_irc " + nickname + "\r\n"
#define RPL_YOUREOPER() ":irc 381You are now an IRC operator\r\n"
#define	RPL_QUIT(reason) "QUIT :" + reason + "\r\n"
#define RPL_NAMREPLY(nickname, channel, listUsers) ":irc 353 " + nickname + " = " + channel + " " + listUsers + "\r\n"
#define RPL_ENDOFNAMES(nickname, channel) ":irc 366 " + nickname + " " + channel + " :End of /NAMES list\r\n"

#define RPL_TOPIC(nickname, channelName, topicName) ":irc 332 " + nickname + " " + channelName + " " + topicName + "\r\n"
#define RPL_TOPICWHOTIME(client, channelName, nickname, timeString) ":irc 333 " + client + " " + channelName + " " + nickname + " " + timeString + "\r\n"
#define RPL_NOTOPIC(nickname, channelName) ":irc 331 " + nickname + " "  + channelName + " :No topic is set\r\n"
#define RPL_INVITING(nickname, channelName, target) ":irc 341 " + nickname + " " + channelName + " " + target + "\r\n"
#define RPL_INVITE(nickname, target, channelName) ":" + nickname + " INVITE " + target + " " + channelName + "\r\n"

#define RPL_JOIN(nickname, channelName) ":" + nickname + " JOIN " + channelName + "\r\n"
#define RPL_PRIVMSG(nickname, channelName, msg) ":" + nickname + " PRIVMSG " + channelName + " :" + msg + "\r\n"
#endif
