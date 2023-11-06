/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulatr <lboulatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:41:57 by lboulatr          #+#    #+#             */
/*   Updated: 2023/11/06 10:09:48 by lboulatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "main.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Channel
{
	public:

		Channel(std::string name, std::string topic, std::string key, std::string mode, int id, int userLimit);
		Channel(const Channel &src);
		~Channel(void);

		Channel					&operator=(const Channel &src);

		int						getId(void) const;
		int						getUserLimit(void) const;
		std::string				getName(void) const;
		std::string				getTopic(void) const;
		std::string				getKey(void) const;
		std::string				getMode(void) const;

	private:

		const std::string		_name;
		const std::string		_topic;
		const std::string		_key;
		const std::string		_mode;
		int						_id;
		int						_userLimit;

};

#endif