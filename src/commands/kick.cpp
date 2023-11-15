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
	std::stringstream ss;
	std::string token;
	std::cout << "DEBUG :"<< std::endl;
	for (size_t i = 0; i < arg.size(); i++) {
		ss.str(arg[i]);
		std::cout << arg[i] << std::endl;
		while (std::getline(ss, token, ',')) {
			result.push_back(token);
		}
	}
	std::cout << "END DEBUG :"<< std::endl;
	return (result);
}

void	Commands::kick()
{
	std::vector<std::string> channelNameTab = this->parseChannelName(this->_args);
	for (size_t i = 0; i < channelNameTab.size(); i++)
		std::cout << channelNameTab[i] << std::endl;
	if (channelNameTab.size() > 2)
		return ;
	else if (channelNameTab.empty())
		this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), "KICK"));

	std::vector<std::string> usersTab = parseComaSeparatedArgs(this->_args);
	std::cout << "OK" << std::endl;
	for (size_t i = 0; i < usersTab.size(); i++)
		std::cout << usersTab[i] << std::endl;
	std::cout << "OK" << std::endl;
	std::map<std::string, Channel>::iterator channel = this->_channels.find(channelNameTab[0]);
	std::cout << channel->first << std::endl;
}