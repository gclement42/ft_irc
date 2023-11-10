/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:06:34 by gclement          #+#    #+#             */
/*   Updated: 2023/11/10 08:18:13 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
# include "Server.hpp"

void quitCommand(Client &client, std::vector<std::string> arg)
{
    std::string reason = "Client quit";

	this->_client.setIsConnected();
    if (this->_args.size() > 0) {
        reason = this->_args[0];
	}
	this->_client.addMessageToSend("QUIT :" + reason + "\r\n");
}