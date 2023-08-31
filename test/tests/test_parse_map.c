#include "cub3d.h"
#include "unity.h"

void	test_bad(void)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, parse_map("maps/color_invalid_rgb.cup"),
		"#1");
}

void	test_good(void)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(0, parse_map("maps/cheese_maze.cub"), "#1");
}

int	test_parse_map(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_bad);
	RUN_TEST(test_good);
	return (UNITY_END());
}
