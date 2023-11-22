# include "main.hpp"

void Commands::invite() {
	if (_args.size() != 3) {
		_client.addMessageToSend(ERR_NEEDMOREPARAMS(this->_client.getNickname(), _args[0]));
		return ;
	}
	std::string channelName = _args[2];
	std::string targetNickname = _args[1];
	if (!this->checkIfChannelExist(channelName)) {
		_client.addMessageToSend(ERR_NOSUCHCHANNEL(_client.getNickname(), channelName));
		return ;
	}
	if (!this->checkIfThisUserIsOnChannel(channelName)) {
		_client.addMessageToSend(ERR_NOTONCHANNEL(_client.getNickname(), channelName));
		return ;
	}
	if (this->checkIfTargetClientIsOnChannel(channelName, targetNickname)) {
		_client.addMessageToSend(ERR_USERONCHANNEL(_client.getNickname(), channelName));
		return ;
	}
	Client &target = this->getClientFromNickname(targetNickname);
	target.addMessageToSend(RPL_INVITE(_client.getNickname(), targetNickname, channelName));
	target.setWaitingForSend(true);
	Channel &channel = this->_channels.find(channelName)->second;
	channel.addInvite(targetNickname);
	_client.addMessageToSend(RPL_INVITING(_client.getNickname(), targetNickname, channelName));
}

