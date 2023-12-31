/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseClientData.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:14:12 by gclement          #+#    #+#             */
/*   Updated: 2023/12/11 10:14:25 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
# include "Client.hpp"

static std::string	searchRealname(std::string str);
static void			pass(std::string str, Client &client);
static void			user(std::string str, Client &client);
static void			nick(std::string str, Client &client);
static void			eraseSpaces(std::string &str);
static void			stringToUpper(std::string &str);

void parseClientData(std::string buffer, Client &client)
{
	std::stringstream ss(buffer);
	std::string 	token;
	std::string 	cmd;

	while (std::getline(ss, token))
	{
		token = token.substr(0, token.find("\r"));
		cmd = token.substr(0, token.find_first_of(" "));
		stringToUpper(cmd);
		if (cmd == "PASS")
			pass(token, client);
		if (cmd == "NICK")
			nick(token, client);
		if (cmd == "USER")
			user(token, client);
		if (cmd != "PASS" && cmd != "NICK" && cmd != "USER" && token != "CAP LS 302" && token != "CAP END" && !token.empty())
		{
			client.addMessageToSend("ERROR : Bad registration command\r\n");
			client.setIsConnected(true);
		}
	}
}

static void pass(std::string str, Client &client)
{
	std::string &password = client.getPassword();

	if (str.length() > 5)
	{
		password = str.substr(str.find("PASS") + 5);
		eraseSpaces(password);
		if (password.empty())
		{
			std::cout << "ERROR : No password given" << std::endl;
			client.addMessageToSend(ERR_NOPASSWDGIVEN());
		}
		client.setPassword(password);
	}
	else
	{
		std::cout << "ERROR : No password given" << std::endl;
		client.addMessageToSend(ERR_NOPASSWDGIVEN());
	}
}

static void nick(std::string str, Client &client)
{
	std::string &nickname = client.getNickname();

	if (client.getPassword().empty())
	{
		std::cout << "ERROR : No password given" << std::endl;
		client.addMessageToSend(ERR_NOPASSWDGIVEN());
		return ;
	}
	if (str.length() > 5) {
		nickname = str.substr(str.find("NICK") + 5);
		eraseSpaces(nickname);
		if (nickname.empty())
		{
			std::cout << "ERROR : No nickname given" << std::endl;
			client.addMessageToSend("No nickname given\r\n");
		}
		client.setNickname(nickname);
	}
	else
	{
		std::cout << "ERROR : No nickname given" << std::endl;
		client.addMessageToSend("No nickname given\r\n");
	}
}

static void user(std::string str, Client &client)
{
	std::string &username = client.getUsername();
	std::string &realname = client.getRealname();

	if (client.getPassword().empty())
	{
		client.addMessageToSend(ERR_NOPASSWDGIVEN());
		return ;
	}
	int endUsername = str.find("0");
	if (str.length() > 5)
		username = str.substr(str.find("USER") + 5, endUsername - 1 - str.find("USER") - 5);
	else
	{
		std::cout << "ERROR : No username given" << std::endl;
		client.addMessageToSend("No username given\r\n");
	}
	if (username.length() > USERLEN)
		username = username.substr(0, USERLEN);
	eraseSpaces(username);
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

static void eraseSpaces(std::string &str)
{
	while (str.find(" ") != std::string::npos)
		str.erase(str.find(" "), 1);
}

static void stringToUpper(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = std::toupper(str[i]);
}
