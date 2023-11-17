#include "main.hpp"

static std::vector<std::string>	parseModeArgs(std::string )
void Commands::mode()
{
	std::string modestring;
	std::string modeArgs;

	if (!checkModeArgs())
	{
		// PAS BON
		_client.addMessageToSend(ERR_NEEDMOREPARAMS(_client.getNickname(), _args[0]));
		return ;
	}
	Channel &channel = this->_channels.find(this->_args[1])->second;
	stringmode = _args[2];

}
