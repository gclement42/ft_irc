/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseClientData.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:14:12 by gclement          #+#    #+#             */
/*   Updated: 2023/11/03 11:22:43 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
# include "Client.hpp"

Client parseClientData(std::string buffer, pollfd pollClient)
{
	std::stringstream	streamBuffer(buffer);
	std::string 		token;
	std::string			nickname;
	std::string			username;
	std::string			password;

	password = "";
	while (getline(streamBuffer, token))
	{
		if (token.find("PASS") != std::string::npos)
		{
			std::cout << "token PASS: " << token << std::endl;
			password = token.substr(token.find("PASS") + 5);
		}
		if (token.find("NICK") != std::string::npos)
			nickname = token.substr(token.find("NICK") + 5);
		if (token.find("USER") != std::string::npos)
		{
			int endUsername = token.find("0");
			username = token.substr(token.find("USER") + 5, endUsername - 1);
		}
	}
	Client client(nickname, username, pollClient, password);
	return (client);
}