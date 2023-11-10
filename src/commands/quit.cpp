/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientQuit.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:06:34 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 11:24:43 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

void Commands::quit()
{
    std::string reason = "Client quit";

	this->_client.setIsConnected(false);
    if (this->_args.size() > 0) {
        reason = this->_args[0];
	}
	this->_client.addMessageToSend("QUIT :" + reason + "\r\n");
}