#include "main.hpp"

void Commands::nick()
{
	if (!_client.checkIfNicknameIsValid(_clients))
		return ;
	_client.setNickname(_args[1]);
	_client.addMessageToSend(std::string(":" + _client.getUsername() + " NICK " + _args[1] + "\r\n"));
	std::vector<std::string> clientChannels = _client.getChannels();
	for (size_t i = 0; i < clientChannels.size(); i++)
	{
		displayListClientOnChannel(clientChannels[i]);
	}
}