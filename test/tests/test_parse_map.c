#include "cub3d.h"
#include "unity.h"
#include <dirent.h>

void	test_bad(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			*path;
	char			*message;
	int				i;

	d = opendir("maps/bad/");
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type == DT_REG)
			{
				asprintf(&path, "maps/bad/%s", dir->d_name);
				asprintf(&message, "#%d", i);
				TEST_ASSERT_EQUAL_INT_MESSAGE(1, parse_map(path), message);
				// printf("%s - %s\n", path, message);
				free(path);
				free(message);
				i++;
			}
		}
		closedir(d);
	}
}

void	test_good(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			*path;
	char			*message;
	int				i;

	d = opendir("maps/good/");
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_type == DT_REG)
			{
				asprintf(&path, "maps/good/%s", dir->d_name);
				asprintf(&message, "#%d", i);
				TEST_ASSERT_EQUAL_INT_MESSAGE(1, parse_map(path), message);
				// printf("%s - %s\n", path, message);
				free(path);
				free(message);
				i++;
			}
		}
		closedir(d);
	}
}

int	test_parse_map(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_bad);
	RUN_TEST(test_good);
	return (UNITY_END());
}
