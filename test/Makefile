T = ./tests/

FLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I../inc -I../libft/inc -I./unity -I./inc -I../MLX42/include
LIBRARIES	= -L../libft -lft -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -L../build/ -lmlx42
# SANITIZE = -fsanitize=address,undefined
TEST = ./unity/unity.c ./test.c
TESTS = \
	$T/test_parse_map.c
CUB3D =
PS := $(filter-out %main.c, $(CUB3D))

all: clean run_test

run_test:
	gcc $(FLAGS) $(INCLUDES) $(SANITIZE) $(TEST) $(TESTS) $(PS:%=../%) $(LIBRARIES) -o run_tests
	./run_tests

clean:
	rm -fr run_*

# gcc $(FLAGS) $(INCLUDES) $(SANITIZE) $(TEST) $(TESTS) $(PS:%=../%) -L../libft -lft -o run_tests
# gcc -std=c99 -c -o test.c.o test.c
# g++ -std=c++0x -c -o test.cpp.o test.cpp
# g++ -o executable test.cpp.o test.c.o
