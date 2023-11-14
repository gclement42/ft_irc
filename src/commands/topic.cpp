/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:34:14 by maujogue          #+#    #+#             */
/*   Updated: 2023/11/13 10:47:53 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static std::vector<std::string>		parseChannelName(std::vector<std::string> arg);
static std::vector<std::string>		parseKey(std::vector<std::string> arg);

void	Commands::topic()
{
	std::string		channelName = parseChannelName(this->_args)[0];
	std::string		key 		= parseKey(this->_args)[1];
	std::string		topicMessage = ":irc 332 " + this->_client.getNickname() + " " +  channelName + " :" + key  + "\r\n";

	if (channelName.empty())
		return ;
	Channel channel = this->_channels.find(channelName)->second;
	if (key.empty())
	{
		std::string 	emptyTopicMessage = ":irc 331 Topic for " + channelName + " is: " + channel.getTopic() + "\r\n";
		this->_client.addMessageToSend(emptyTopicMessage);
		return ;
	}
	else
	{
		channel.setTopic(key);
		this->_client.addMessageToSend(topicMessage);
	}
}

static std::vector<std::string>		parseChannelName(std::vector<std::string> arg)
{
	std::vector<std::string> 	channelName;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i][0] == '#' || arg[i][0] == '&')
			channelName.push_back(arg[i]);
	}

	return (channelName);
}

static std::vector<std::string>		parseKey(std::vector<std::string> arg)
{
	std::vector<std::string> 	keys;

	for (size_t i = 0; i < arg.size(); i++)
	{
		if (!(arg[i][0] == '#' || arg[i][0] == '&'))
			keys.push_back(arg[i]);
	}

	return (keys);
}
