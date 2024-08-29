NAME = solver
FLAGS = -I ./include -lm -std=c++17#-Wall -Wextra
SRC = $(wildcard src/*)
OBJ = $(subst src,build,$(SRC:.cpp=.o))

all: clean $(OBJ)
	g++ -o $(NAME) $(OBJ) 

build/%.o: src/%.cpp
	@mkdir -p build
	g++ $(FLAGS) -c $< -o $@

clean:
	@rm -rf build/*