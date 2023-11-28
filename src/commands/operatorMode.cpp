#include "main.hpp"

void Commands::operatorMode(std::string arg, Channel &channel, char symbol)
{
	std::vector<std::string> &operators = channel.getOperators();
	std::cout << "arg : " << arg << std::endl;
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
	if (symbol == '+') {
		operators.push_back(target.getNickname());
		this->sendMsgToAllClientsInChannel(this->allClientsOnChannel(channel.getName()), RPL_NOWISOPER(target.getNickname(), channel.getName()));
		target.addMessageToSend(RPL_YOUREOPER());
		target.setWaitingForSend(true);
		displayListClientOnChannel(channel.getName());
	}
	else
		operatorRemove(channel, operators, target);
}

void	Commands::operatorRemove(Channel &channel, std::vector<std::string> &operators, Client &target)
{
	std::vector<std::string>::iterator it = std::find(operators.begin(), operators.end(), target.getNickname());

	if (it == operators.end())
	{
		this->_client.addMessageToSend(ERR_ISNOTOPER(target.getNickname()));
		return ;
	}
	else
	{
		operators.erase(it);
		sendMsgToAllClientsInChannel(this->allClientsOnChannel(channel.getName()), RPL_NOWISNOTOPER(target.getNickname(), channel.getName()));
		displayListClientOnChannel(channel.getName());
	}
}
