CC      = clang
DEBUG   = -g
CFLAGS  = -Wall -Wextra -std=c23 -pedantic \
          $(shell pkg-config --cflags gtk4) \
          $(DEBUG)
LDFLAGS = $(shell pkg-config --libs gtk4)

ifeq ($(OS),Windows_NT)
	LDFLAGS += -mwindows
endif

BINARY  = main
SOURCES = $(shell find src -name '*.c')
HEADERS = $(shell find src -name '*.h')

default: $(BINARY)

$(BINARY): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

rund: $(BINARY)
	GTK_DEBUG=interactive ./$(BINARY)

run: $(BINARY)
	./$(BINARY)

clean:
	rm -f $(BINARY)

.PHONY: default run rund clean
