CC = gcc
CFLAGS = -Wall -Wextra -O0 -g -I.
TARGET = test_kyber
OBJS = test_kyber.o kyber.o fips202.o poly.o polyvec.o ntt.o symmetric.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)
