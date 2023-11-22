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
static	void	parseAddMode(Commands &cmd, Channel &channel, std::string mode, std::vector<std::string> arg, size_t &x);
static	void	parseRemoveMode(Commands &cmd, Channel &channel, std::string mode);

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
	this->reachModestring(modestring, modeArgs, channel);
}


void Commands::reachModestring(std::string modestring, std::vector<std::string> modeArgs, Channel &channel)
{
	char		symbol;
	size_t 		x;
	std::string arg;


	x = 0;
	symbol = 0;
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
				parseAddMode(*this, channel, mode, modeArgs, x);
			else
				parseRemoveMode(*this, channel, mode);
		}
	}
}

static void parseRemoveMode(Commands &cmd, Channel &channel, std::string mode)
{
	std::string channelMode;

	channelMode = channel.getMode();
	if (channelMode.find(mode) == std::string::npos)
		return ;
	channel.removeMode(mode[0]);
	cmd.sendMsgToAllClientsInChannel(cmd.allClientsOnChannel(channel.getName()),
									   RPL_MODEREMOVE(mode, channel.getName()));
}

static void	parseAddMode(Commands &cmd, Channel &channel, std::string mode, std::vector<std::string> args, size_t &x)
{
	std::string arg;
	char		modeChar;

	modeChar = mode[0];
	if (modeChar != 'k' && modeChar != 'l')
		channel.addMode(mode[0]);
	else
	{
		if (x >= args.size())
			return ;
		arg = args[x];
		channel.addMode(mode[0], arg.c_str());
		x++;
	}
	cmd.sendMsgToAllClientsInChannel(cmd.allClientsOnChannel(channel.getName()),
									   RPL_MODESET(mode, channel.getName()));
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
