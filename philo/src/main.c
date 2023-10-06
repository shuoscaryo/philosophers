/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:58 by orudek            #+#    #+#             */
/*   Updated: 2023/10/06 16:49:33 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(&data, argc, argv))
		return (1);
	int i = -1;
	while (++i < data->num_philos)
	{
		pthread_create();
	}
}