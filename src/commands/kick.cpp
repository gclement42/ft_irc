/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:17 by maujogue          #+#    #+#             */
/*   Updated: 2023/11/15 15:30:17 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/main.hpp"
#include <sstream>
#include <string>

std::vector<std::string>	parseComaSeparatedArgs(std::vector<std::string> arg)
{
	std::vector<std::string> 	result;
	std::string::iterator it;
	std::string token;
	size_t i = 1;

	while (arg[i].find("#") != std::string::npos)
		i++;
	if (arg[i].find(",") != std::string::npos)
	{
		std::stringstream ss(arg[i]);
		while (std::getline(ss, token, ','))
		{
			if (token[0] == ':')
				token.erase(0, 1);
			result.push_back(token.erase(0,1));
		}
	}
	else
	{
		if (arg[i][0] == ':')
			arg[i].erase(0, 1);
		result.push_back(arg[i]);
	}
	return (result);
}

void	Commands::kick()
{
	std::vector<std::string> channelNameTab = this->parseChannelName(this->_args);
//	for (size_t i = 0; i < channelNameTab.size(); i++)
//		std::cout << channelNameTab[i] << std::endl;
	if (channelNameTab.size() > 2)
		return ;
	else if (channelNameTab.empty())
		this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "KICK"));

	std::vector<std::string> usersTab = parseComaSeparatedArgs(this->_args);
	for (size_t i = 0; i < usersTab.size(); i++)
		std::cout << usersTab[i] << std::endl;
	std::map<std::string, Channel>::iterator channel = this->_channels.find(channelNameTab[0]);
	std::cout << channel->first << std::endl;
}