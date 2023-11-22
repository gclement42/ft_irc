/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:41:57 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/20 09:30:38 by lboulatr         ###   ########.fr       */
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
		void					addMode(char mode, ...);
		void					removeMode(char mode);
		void					setTopic(std::string topic);
		void					setKey(char *key);
		void					setUserLimit(char *userLimit);
		void					incrementUserCount(void);
		bool					getKeyMode(void) const;
		bool					getLimitMode(void) const;
		bool					getTopicMode(void) const;
		std::vector<std::string>	&getOperators(void);
		void 						addOperator(std::string nickname);
		bool						checkIfClientIsOperator(std::string nickname);
		void						addInvite(std::string nickname);
		bool						checkIfClientIsInvited(std::string nickname);

	private:

		std::string						_name;
		std::string						_topic;
		std::string						_key;
		std::string						_mode;
		std::vector<std::string>		_operators;
		std::vector<std::string>		_invites;
		int								_userLimit;
		int								_userCount;
		bool							_inviteMode;
		bool					_topicMode;
		bool					_keyMode;
		bool					_limitMode;

};

std::ostream	&operator<<(std::ostream &o, const Channel &src);

#endif