CC = cc
SRC = main.c
OUT = shell

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean
