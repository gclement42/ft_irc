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
static void			pass(std::string str, Client &client);
static void			user(std::string str, Client &client);
static void			nick(std::string str, Client &client);

void parseClientData(std::string buffer, Client &client)
{
	std::stringstream ss(buffer);
	std::string 	token;

	while (std::getline(ss, token, '\r'))
	{
		if (token.find("PASS") != std::string::npos)
			pass(token, client);
		if (token.find("NICK") != std::string::npos)
			nick(token, client);
		if (token.find("USER") != std::string::npos)
			user(token, client);

	}
}

static void pass(std::string str, Client &client)
{
	std::string &password = client.getPassword();

	if (str.length() > 5)
	{
		password = str.substr(str.find("PASS") + 5);
		client.setPassword(password);
	}
}

static void nick(std::string str, Client &client)
{
	std::string &nickname = client.getNickname();

	if (client.getPassword().empty())
	{
		client.addMessageToSend("ERROR : No password given");
		return ;
	}
	if (str.length() > 5) {
		nickname = str.substr(str.find("NICK") + 5);
		client.setNickname(nickname);
	}
}

static void user(std::string str, Client &client)
{
	std::string &username = client.getUsername();
	std::string &realname = client.getRealname();

	if (client.getPassword().empty())
	{
		client.addMessageToSend("ERROR : No password given");
		return ;
	}
	int endUsername = str.find("0");
	if (str.length() > 5)
	{
		username = str.substr(str.find("USER") + 5, endUsername - 1 - str.find("USER") - 5);
	}
	if (username.length() > USERLEN)
	{
		username = username.substr(0, USERLEN);
	}
	client.setUsername(username);
	realname = searchRealname(str);
	if (!realname.empty())
		client.setRealname(realname);
}

static std::string searchRealname(std::string str)
{
	std::string realname;

	if (str.find(":") == std::string::npos)
		return ("");
	realname = str.substr(str.find(":"));
	return (realname);
}

