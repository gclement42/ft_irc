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
# include "Server.hpp"

void quitCommand(Client &client, std::vector<std::string> arg)
{
    std::string reason = "Client quit";

	client.setIsConnected();
    if (arg.size() > 0)
        reason = arg[0];
    client.addMessageToSend("QUIT :" + reason + "\r\n");
}