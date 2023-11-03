#include "cub3d.h"
#include "unity.h"
#include <dirent.h>
#include <unistd.h>


static void	init_map(t_map *map)
{
	t_vec *m;

	map->cealing_color = -1;
	map->floor_color = -1;

	m = malloc(sizeof(t_vec));
	if (!m)
		dt_error(MALLOC_FAIL);
	if (vec_new(m, 10, sizeof(char *)) < 0)
		dt_error(MALLOC_FAIL);
	map->map = m;
}

static void	destroy_map(t_map *map)
{
	// free map rows
	map->textures.ea = NULL;
	map->textures.so = NULL;
	map->textures.we = NULL;
	map->textures.no = NULL;
	vec_free(map->map);
	free(map->map);
}


void	test_bad(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			*path;
	char			*message;
	int				i;
	t_map 			map;
	int status;


	d = opendir("/Users/tspoof/Documents/HIVE/cub3D/test/maps/bad");
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type == DT_REG)
			{
				asprintf(&path, "/Users/tspoof/Documents/HIVE/cub3D/test/maps/bad/%s", dir->d_name);
				asprintf(&message, "#%d", i);
				if (ft_strlen(ft_strnstr(path, ".cub", ft_strlen(path))) != 4 && ft_strlen(path) > 4)
					continue;
				int pid = fork();

				if (pid == 0)
				{
					init_map(&map);
					parse_map(path, &map);
					destroy_map(&map);
				}
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
				{
					int exit_status = WEXITSTATUS(status);
					if (!exit_status)
					{
						printf("Exit status of %s the child was %d\n", message, exit_status);
						printf("file: %s\n", path);
					}
					TEST_ASSERT_MESSAGE(exit_status > 0, message);
				}
				free(path);
				free(message);
				i++;
			}
		}
		closedir(d);

	}
	TEST_ASSERT(1 < 0);
}

void	test_good(void)

{
	DIR				*d;
	struct dirent	*dir;
	char			*path;
	char			*message;
	int				i;
	t_map 			map;

	d = opendir("/Users/tspoof/Documents/HIVE/cub3D/test/maps/good");
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type == DT_REG)
			{
				asprintf(&path, "/Users/tspoof/Documents/HIVE/cub3D/test/maps/good/%s", dir->d_name);
				asprintf(&message, "#%d", i);
				if (ft_strlen(ft_strnstr(path, ".cub", ft_strlen(path))) != 4 && ft_strlen(path) > 4)
					continue;
				init_map(&map);
				parse_map(path, &map);
				destroy_map(&map);
				free(path);
				free(message);
				i++;
			}
		}
		closedir(d);
		TEST_ASSERT_EQUAL_INT_MESSAGE(0, 0, "All good man");
	}
}

int	test_parse_map(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_bad);
	RUN_TEST(test_good);
	return (UNITY_END());
}
