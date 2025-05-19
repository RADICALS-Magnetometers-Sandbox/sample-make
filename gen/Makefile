
CFLAGS = -O3 -Wall

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

OBJ = hal_str.o

all: libhal.a

libhal.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

.PHONY : clean
clean:
	-rm libhal.a $(OBJ)
