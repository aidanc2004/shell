CC = cc
SRC = main.c
OUT = shell
FLAGS = -Wall -Wextra -pedantic

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean
