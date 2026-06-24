CC      = clang
DEBUG   = -g
CFLAGS  = -Wall -Wextra -std=c23 -pedantic \
          $(shell pkg-config --cflags gtk4) \
          $(DEBUG)
LDFLAGS = $(shell pkg-config --libs gtk4)

BINARY  = main
SOURCES = $(shell find src -name '*.c')

default: $(BINARY)

$(BINARY): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

rund: $(BINARY)
	GTK_DEBUG=interactive ./$(BINARY)

run: $(BINARY)
	./$(BINARY)

clean:
	rm -f $(BINARY)

.PHONY: default run rund clean
