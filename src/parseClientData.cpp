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

static std::string searchRealname(std::string str)
{
	std::string realname;

	if (str.find(":") == std::string::npos)
		return ("");
	realname = str.substr(str.find(":"));
	return (realname);
}

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
			password = token.substr(token.find("PASS") + 5);
		if (token.find("NICK") != std::string::npos)
			nickname = token.substr(token.find("NICK") + 5);
		if (token.find("USER") != std::string::npos)
		{
			int endUsername = token.find("0");
			username = token.substr(token.find("USER") + 5, endUsername - 1 - token.find("USER") - 5);
			if (username.length() > USERLEN)
				username = username.substr(0, USERLEN);
			realname = searchRealname(token);
		}
	}
	Client client(nickname, username, realname, fd, password);
	return (client);
}