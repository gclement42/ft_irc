#include "main.hpp"

void Commands::nick()
{
	if (!_client.checkIfNicknameIsValid(_clients))
		return ;	
	_client.setNickname(_args[1]);
	_client.addMessageToSend(std::string(":" + _client.getUsername() + " NICK " + _args[1] + "\r\n"));
}