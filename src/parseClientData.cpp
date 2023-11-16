/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseClientData.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:14:12 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 15:45:34 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
# include "Client.hpp"

static std::string	searchRealname(std::string str);
static void			pass(std::string str, std::string &password);
static void			user(std::string str, std::string &username, std::string &realname);
static void			nick(std::string str, std::string &nickname);

Client parseClientData(std::string buffer, int fd)
{
	std::stringstream	streamBuffer(buffer);
	std::string 		token;
	std::string			nickname;
	std::string			username;
	std::string			password;
	std::string 		realname;

	password = "";
	while (getline(streamBuffer, token))
	{
		token = token.substr(0, token.find("\r"));
		if (token.find("PASS") != std::string::npos)
			pass(token, password);
		if (token.find("NICK") != std::string::npos)
			nick(token, nickname);
		if (token.find("USER") != std::string::npos)
			user(token, username, realname);
	}
	Client client(nickname, username, realname, fd, password);
	return (client);
}

static void pass(std::string str, std::string &password)
{
	if (str.length() > 5)
		password = str.substr(str.find("PASS") + 5);
}

static void nick(std::string str, std::string &nickname)
{
	if (str.length() > 5)
		nickname = str.substr(str.find("NICK") + 5);
}

static void user(std::string str, std::string &username, std::string &realname)
{
	int endUsername = str.find("0");
	if (str.length() > 5)
		username = str.substr(str.find("USER") + 5, endUsername - 1 - str.find("USER") - 5);
	if (username.length() > USERLEN)
		username = username.substr(0, USERLEN);
	realname = searchRealname(str);
}

static std::string searchRealname(std::string str)
{
	std::string realname;

	if (str.find(":") == std::string::npos)
		return ("");
	realname = str.substr(str.find(":"));
	return (realname);
}

