.POSIX:

VERSION   = 1.0
PREFIX    = /usr/local
WLCFLAGS    = -std=c99 -pedantic -Wall -O2 $(CPPFLAGS) $(CFLAGS)
SRC				= minibar.c $(wildcard mods/*.c) $(PROTO:.h=.c)
OBJ       = $(SRC:.c=.o)

all: minibar

.c.o:
	$(CC) -o $@ $(WLCFLAGS) -c $<

$(OBJ): config.h $(PROTO)

config.h:
	cp config.def.h $@

minibar: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f minibar $(OBJ) $(PROTO) $(PROTO:.h=.c)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f minibar $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/minibar

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/minibar

.PHONY: all clean install uninstall
