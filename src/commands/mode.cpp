/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:39:36 by gclement          #+#    #+#             */
/*   Updated: 2023/11/28 09:51:42 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static	void	parseModeArgs(std::vector<std::string> args, std::vector<std::string> &modeArgs);
static	bool	checkModeArgs(std::vector<std::string> args);
static	bool	checkIfModeExist(char mode, Client &client, std::string channelName);
static	void	parseAddMode(Commands &cmd, Channel &channel, std::string mode, std::vector<std::string> arg, size_t &x);
static	void	parseRemoveMode(Commands &cmd, Channel &channel, std::string mode);
static	bool	checkIfError(Commands &cmd);

void Commands::mode()
{
	std::string					modestring;
	std::vector<std::string>	modeArgs;

	if (checkIfError(*this))
		return ;
	parseModeArgs(_args, modeArgs);
	modestring = _args[2];
	Channel &channel = this->_channels.find(this->_args[1])->second;
	if (!channel.checkIfClientIsOperator(_client.getNickname()))
	{
		_client.addMessageToSend(ERR_CHANOPRIVSNEEDED(_client.getNickname(), channel.getName()));
		return ;
	}
	this->reachModestring(modestring, modeArgs, channel);
}

static	bool	checkIfError(Commands &cmd)
{
	std::map<std::string, Channel> &channels = cmd.getChannels();
	Client &client = cmd.getClient();
	std::vector <std::string> &args = cmd.getArgs();

	if (!checkModeArgs(args))
	{
		std::cout << "arg.size = " << args.size() << std::endl;
		if (args.size() == 2)
			cmd.displayModeChannel();
		else
			client.addMessageToSend(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));
		return (true); ;
	}
	if (channels.find(args[1]) == channels.end())
	{
		client.addMessageToSend(ERR_NOSUCHCHANNEL(client.getNickname(), args[1]));
		return (true);
	}
	if (!cmd.checkIfThisUserIsOnChannel(args[1]))
	{
		client.addMessageToSend(ERR_NOTONCHANNEL(client.getNickname(), args[1]));
		return (true);
	}

	return (false);
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
		else if (!checkIfModeExist(modestring[i], this->_client, channel.getName()))
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
				if (x >= modeArgs.size())
				{
					this->_client.addMessageToSend(ERR_NEEDMOREPARAMSMODE(this->_client.getNickname(), channel.getName(),"o"));
					continue ;
				}
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
		channel.addMode(mode[0], 1);
	else
	{
		if (x >= args.size())
		{
			cmd.getClient().addMessageToSend(ERR_NEEDMOREPARAMSMODE(cmd.getClient().getNickname(), channel.getName(), mode));
			return ;
		}
		arg = args[x];
		channel.addMode(mode[0], 1, arg.c_str());
		x++;
	}
	cmd.sendMsgToAllClientsInChannel(cmd.allClientsOnChannel(channel.getName()), \
			RPL_MODESET(channel.getName(), cmd.getClient().getNickname(), mode));
}

void Commands::displayModeChannel()
{
	if (this->_channels.find(this->_args[1]) == this->_channels.end())
	{
		_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), _args[1]));
		return ;
	}
	Channel channel = this->_channels.find(this->_args[1])->second;
	std::string msg = ":irc 324 " + _client.getNickname() + " " + _args[1] + " ";
	this->_client.addMessageToSend(msg + channel.getMode() + "\r\n");
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

static bool checkIfModeExist(char mode, Client &client, std::string channelName)
{
	if (mode == 'o' || mode == 'k' || mode == 'l' || mode == 't' || mode == 'i')
		return (true);
	client.addMessageToSend(ERR_UNKNOWNMODE(client.getNickname(), channelName, mode));
	return (false);
}
