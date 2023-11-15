#include "main.hpp"

void Commands::oper()
{
	if (this->_args.size() != 3)
	{
		this->_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), std::string("OPER")));
		return ;
	}
	if (this->_args[2] != _operPassword)
	{
		this->_client.addMessageToSend(ERR_PASSWDMISMATCH(this->_client.getNickname()));
		return ;
	}
	else
	{
		this->_client.setIsOperator(true);
		this->_client.addMessageToSend(RPL_YOUREOPER());
	}
}
