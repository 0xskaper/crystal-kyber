CFLAGS = -Wall -Wextra -O3 -I.

all: test_kyber

test_kyber: poly.o polyvec.o ntt.o fips202.o symmetric.o kyber.o test_kyber.o
	gcc $(CFLAGS) -o test_kyber poly.o polyvec.o ntt.o fips202.o symmetric.o kyber.o test_kyber.o

poly.o: poly.c
	gcc $(CFLAGS) -c poly.c -o poly.o

polyvec.o: polyvec.c
	gcc $(CFLAGS) -c polyvec.c -o polyvec.o

ntt.o: ntt.c
	gcc $(CFLAGS) -c ntt.c -o ntt.o

fips202.o: fips202.c
	gcc $(CFLAGS) -c fips202.c -o fips202.o

symmetric.o: symmetric.c
	gcc $(CFLAGS) -c symmetric.c -o symmetric.o

kyber.o: kyber.c
	gcc $(CFLAGS) -c kyber.c -o kyber.o

test_kyber.o: test_kyber.c
	gcc $(CFLAGS) -c test_kyber.c -o test_kyber.o

clean:
	rm -f *.o test_kyber
