/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:03:42 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/20 13:05:51 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(int port, std::string password) : _port(port), _password(password)
{
	this->_socket = new Socket(port);
	this->_socket->connect();
	this->_socket->send("NICK BotAlfred\r\n");
	this->_socket->send("USER BotAlfred 0 * :BotAlfred\r\n");
	this->_socket->send("JOIN #42\r\n");
	this->_socket->send("PRIVMSG NickServ :identify " + password + "\r\n");
}