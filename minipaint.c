#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int		H;
int		W;
char	BG;
char	**tab;

typedef	struct	s_draw
{
	char	type;
	float	x;
	float	y;
	float	r;
	char	c;
}				t_zone;

int	err_msg(FILE *fd, int err)
{
	int	i;

	i = 0;
	if (err == 2)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		err = 1;
	}
	else if (err == 1)
		write(1, "Error: argument\n", 16);
	else if (err == 0)
	{
		while (i < H)
		{
			write(1, tab[i], W);
			write(1, "\n", 1);
			i++;
		}
	}
	if (fd)
		fclose(fd);
	return (err);
}

int	main(int argc, char **argv)
{
	FILE	*fd;
	t_zone	map;
	int		res;
	int		j;
	int		i;
	float	sqrt;

	if (argc != 2)
		return (err_msg(fd, 1));
	if ((fd = fopen(argv[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c\n", &W, &H, &BG)) == 3)
		{
			if (H <= 300 && H > 0 && W <= 300 && W > 0)
			{
				tab = malloc(sizeof(char *) * H * W);
				while (j < H)
				{
					tab[j] = malloc(sizeof(char) * W);
					memset(tab[j], BG, W);
					j++;
				}
				while ((res = fscanf(fd, "%c %f %f %f %c\n", &map.type, &map.x, &map.y, &map.r, &map.c)) == 5)
				{
					if ((map.type != 'c' && map.type != 'C') || map.r <= 0)
						return (err_msg(fd, 2));
					i = 0;
					while (i < H)
					{
						j = 0;
						while (j < W)
						{
							sqrt = sqrtf(powf((float)j - map.x, 2.) + powf((float)i - map.y, 2.));
							if (sqrt <= map.r)
							{
								if (map.type == 'c' && sqrt + 1 > map.r)
									tab[i][j] = map.c;
								else if (map.type == 'C')
									tab[i][j] = map.c;
							}
							j++;
						}
						i++;
					}
				}
			}
			else
				return (err_msg(fd, 2));
		}
		else
			return (err_msg(fd, 2));
	}
	else
		return (err_msg(fd, 2));
	return (err_msg(fd, 0));
}