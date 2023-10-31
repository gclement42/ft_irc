/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pollfds.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:40:54 by gclement          #+#    #+#             */
/*   Updated: 2023/10/31 10:29:37 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Pollfds_HPP
# define Pollfds_HPP

# include "main.hpp"

class Pollfds
{
	public:
		Pollfds(void);
		Pollfds(const Pollfds &src);
		~Pollfds(void);
		Pollfds	&operator=(const Pollfds &src);
		void	insert(pollfd client);
		void	erase(pollfd client);
		pollfd	*getFds(void) const;
		size_t	getNbClients(void) const;
	private:
		pollfd	*_fds;
		size_t	_nbClients;
};

#endif