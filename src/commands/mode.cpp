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
static	void	setSymbol(char &symbol, char newSymbol);

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
	parseModeArgs(_args, modeArgs);
	modestring = _args[2];
	this->addOrRemoveMode(modestring, modeArgs, channel);
}


void Commands::addOrRemoveMode(std::string modestring, std::vector<std::string> modeArgs, Channel &channel)
{
	char		symbol;
	size_t 		x;
	std::string arg;

	x = 0;
	symbol = 0;
	for (size_t i = 0; i < modestring.length(); i++)
	{
		if (modestring[i] == '+' || modestring[i] == '-')
			setSymbol(symbol, modestring[i]);
		else
		{
			if (symbol == 0)
			{
				this->_client.addMessageToSend(ERR_BADFORMATMODE());
				return ;
			}
			if (symbol == '+')
			{
				if (modestring[i] != 'o' && modestring[i] != 'k' && modestring[i] != 'l')
					channel.addMode(modestring[i]);
				else
				{
					if (x >= modeArgs.size())
						continue ;
					arg = modeArgs[x];
					if (modestring[i] == 'o')
						this->operatorMode(arg, channel);
					else
						channel.addMode(modestring[i], arg.c_str());
					_client.addMessageToSend(RPL_MODESET(std::string(&modestring[i]), channel.getName()));
					x++;
				}
			}
			else
			{
				channel.removeMode(modestring[i]);
				_client.addMessageToSend(RPL_MODEREMOVE(std::string(&modestring[i]), channel.getName()));
			}
		}
	}
}

void Commands::operatorMode(std::string arg, Channel &channel)
{
	Client &target = this->getClientFromNickname(arg);
	if (target.getNickname() == this->_client.getNickname()) {
		this->_client.addMessageToSend(ERR_ERRONEUSNICKNAME(target.getNickname()));
		return ;
	}
	if (!checkIfTargetClientIsOnChannel(channel.getName(), target.getNickname()))
	{
		this->_client.addMessageToSend(ERR_NOTONCHANNEL(target.getNickname(), channel.getName()));
		return ;
	}
	channel.addMode('o', target.getNickname().c_str());

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

static void setSymbol(char &symbol, char newSymbol)
{
	symbol = newSymbol;
}