/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 13:45:19 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/11 13:45:23 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

static void			accept_client(t_server *server)
{
	unsigned char	i;
	int				new_socket;

	if (g_vm->count_players >= 4)
		return ;
	new_socket = accept(server->master_socket, NULL, NULL);
	(!new_socket) ? ft_error("Error: accept_client()") : 0;
	i = 0;
	while (i < server->n_client_sockets)
	{
		if (server->client_sockets[i] == 0)
		{
			server->client_sockets[i] = new_socket;
			g_vm->count_players++;
			return ;
		}
		i++;
	}
}

static void			check_clients(t_server *server)
{
	unsigned char	buffer[15];
	int				sd;
	unsigned char	i;

	i = 0;
	while (i < server->n_client_sockets)
	{
		ft_bzero(buffer, 15);
		sd = server->client_sockets[i];
		if (FD_ISSET(sd, &server->read_fds))
		{
			if (read(sd, &buffer, 15) <= 0)
			{
				g_vm->count_players--;
				server->client_sockets[i] = 0;
				close(sd);
			}
		}
		i++;
	}
}

/*
** FD_ISSET checks whether someone wants to connect to the server.
*/

void		dispatcher_sockets(t_server *server)
{
	if (FD_ISSET(server->master_socket, &server->read_fds))
		accept_client(server);
	else
		check_clients(server);
}