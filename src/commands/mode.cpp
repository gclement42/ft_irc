/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:39:36 by gclement          #+#    #+#             */
/*   Updated: 2023/11/20 07:39:36 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/*
 0 = MODE
 1 = target
 2 = modestring
 3 et + = args
 */
static	void	parseModeArgs(std::vector<std::string> args, std::vector<std::string> &modeArgs);
static	bool	checkModeArgs(std::vector<std::string> args);
static	bool	checkIfModeExist(char mode);

void Commands::mode()
{
	std::string					modestring;
	std::vector<std::string>	modeArgs;

	if (!checkModeArgs(_args))
	{
		if (_args.size() == 2)
			this->displayModeChannel();
		else
			_client.addMessageToSend(ERR_NEEDMOREPARAMS(_client.getNickname(), "MODE"));
		return ;
	}
	if (this->_channels.find(this->_args[1]) == this->_channels.end())
	{
		_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), _args[1]));
		return ;
	}
	Channel &channel = this->_channels.find(this->_args[1])->second;
	if (!channel.checkIfClientIsOperator(_client.getNickname()))
	{
		_client.addMessageToSend(ERR_CHANOPRIVSNEEDED(_client.getNickname(), channel.getName()));
		return ;
	}
	parseModeArgs(_args, modeArgs);
	modestring = _args[2];
	this->addOrRemoveMode(modestring, modeArgs, channel);
}


void Commands::addOrRemoveMode(std::string modestring, std::vector<std::string> modeArgs, Channel &channel)
{
	char		symbol;
	size_t 		x;
	std::string arg;
	std::string channelMode;

	x = 0;
	symbol = 0;
	channelMode = channel.getMode();
	for (size_t i = 0; i < modestring.length(); i++)
	{
		std::string mode = std::string(&modestring[i]).substr(0, 1);
		if (modestring[i] == '+' || modestring[i] == '-')
			symbol = modestring[i];
		else if (!checkIfModeExist(modestring[i]))
			continue ;
		else
		{
			if (symbol == 0)
			{
				this->_client.addMessageToSend(ERR_BADFORMATMODE());
				return ;
			}
			if (modestring[i] == 'o')
			{
				this->operatorMode(modeArgs[x], channel, symbol);
				x++;
			}
			else if (symbol == '+')
			{
				if (modestring[i] != 'k' && modestring[i] != 'l')
					channel.addMode(modestring[i]);
				else
				{
					if (x >= modeArgs.size())
						continue ;
					arg = modeArgs[x];
					channel.addMode(modestring[i], arg.c_str());
					x++;
				}
				this->sendMsgToAllClientsInChannel(this->allClientsOnChannel(channel.getName()),
												   RPL_MODESET(mode, channel.getName()));
			}
			else
			{
				if (channelMode.find(modestring[i]) == std::string::npos)
					continue ;
				channel.removeMode(modestring[i]);
				this->sendMsgToAllClientsInChannel(this->allClientsOnChannel(channel.getName()),
												   RPL_MODEREMOVE(mode, channel.getName()));
			}
		}
	}
}

void Commands::displayModeChannel()
{
	if (this->_channels.find(this->_args[1]) == this->_channels.end())
		_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), _args[1]));

	Channel channel = this->_channels.find(this->_args[1])->second;
	std::string msg = ":irc 324 " + _client.getNickname() + " " + _args[1] + " ";
}
static bool checkModeArgs(std::vector<std::string> args)
{
	if (args.size() < 3)
		return (false);
	return (true);
}

static void	parseModeArgs(std::vector<std::string> args, std::vector<std::string> &modeArgs)
{
	if (args.size() < 4)
		return ;
	for (size_t i = 3; i < args.size(); i++)
		modeArgs.push_back(args[i]);
}

static bool checkIfModeExist(char mode)
{
	if (mode == 'o' || mode == 'k' || mode == 'l' || mode == 't' || mode == 'i')
		return (true);
	return (false);
}
