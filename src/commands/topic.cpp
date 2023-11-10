/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:34:14 by maujogue          #+#    #+#             */
/*   Updated: 2023/11/07 15:43:41 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

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