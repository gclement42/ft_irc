//
// Created by gclement on 11/10/23.
//

#ifndef REPLYMESSAGES_HPP
#define REPLYMESSAGES_HPP

#include "main.hpp"

#define RPL_WELCOME(nickname) "Welcome to the ft_irc " + nickname + "\r\n"
#define RPL_YOUREOPER() ":irc 381You are now an IRC operator\r\n"
#define	RPL_QUIT(reason) "QUIT :" + reason + "\r\n"
#define RPL_TOPIC(nickname, channelName, topicName) ":irc 332 " + nickname + " " + channelName + " " + topicName + "\r\n"
#define RPL_TOPICWHOTIME(nickname, channelName, topicName, timeString) ":irc 333" + nickname + " " + channelName + " " + topicName + " " + timeString + "\r\n"
#define RPL_NOTOPIC(nickname, channelName) ":irc 331 " + nickname + " "  + channelName + " :No topic is set\r\n"
#endif
