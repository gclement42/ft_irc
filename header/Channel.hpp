/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:41:57 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/13 10:16:43 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "main.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Server;
class Client;

class Channel
{
	public:

		Channel(std::string name, std::string topic, std::string key, std::string mode, int userLimit);
		Channel(const Channel &src);
		~Channel(void);

		Channel					&operator=(const Channel &src);

		std::string				getName(void) const;
		std::string				getTopic(void) const;
		std::string				getKey(void) const;
		std::string				getMode(void) const;
		int						getUserLimit(void) const;
		int						getUserCount(void) const;
		bool					getInviteMode(void) const;

		void					setTopic(std::string topic);
		void					incrementUserCount(void);

	private:

		std::string				_name;
		std::string				_topic;
		std::string				_key;
		std::string				_mode;
		int						_userLimit;
		int						_userCount;
		bool					_inviteMode;

};

std::ostream	&operator<<(std::ostream &o, const Channel &src);

#endif