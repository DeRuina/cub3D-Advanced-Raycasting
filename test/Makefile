T = ./tests/

FLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I../inc -I../libft/inc -I./unity -I./inc
# SANITIZE = -fsanitize=address,undefined
TEST = ./unity/unity.c ./test.c
TESTS = \
	$T/test_parse_map.c
CUB3D =
PS := $(filter-out %main.c, $(CUB3D))

all: clean run_test

run_test:
	cc $(FLAGS) $(INCLUDES) $(SANITIZE) $(TEST) $(TESTS) $(PS:%=../%) -L../libft -lft -o run_tests
	./run_tests

clean:
	rm -fr run_*
