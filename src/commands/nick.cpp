#include "main.hpp"

void Commands::nick()
{
	std::string oldNickname = _client.getNickname();
	if (_args.size() < 2)
	{
		_client.addMessageToSend(ERR_NONIKNAMEGIVEN());
		return ;
	}
	_client.setNickname(_args[1]);
	if (!_client.checkIfNicknameIsValid(_clients))
	{
		_client.setNickname(oldNickname);
		return ;
	}
	_client.addMessageToSend(std::string(":" + _client.getUsername() + " NICK " + _args[1] + "\r\n"));
	std::vector<std::string> clientChannels = _client.getChannels();
	for (size_t i = 0; i < clientChannels.size(); i++)
	{
		displayListClientOnChannel(clientChannels[i]);
	}
}