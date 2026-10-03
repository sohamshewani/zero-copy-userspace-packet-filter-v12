CC=gcc
CFLAGS=-Wall -Werror -g
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)
HDRS=$(wildcard include/*.h)
TARGET=zero_copy_filter

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(filter-out %.o, $(OBJS))

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) -t

integtest: $(TARGET)
	./$(TARGET) -i

clean:
	rm -f $(OBJS) $(TARGET)
