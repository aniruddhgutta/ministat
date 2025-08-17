.POSIX:

VERSION   = 1.0
PREFIX    = /usr/local
WLCFLAGS    = -std=c99 -pedantic -Wall -O2 $(CPPFLAGS) $(CFLAGS)
SRC				= ministat.c $(wildcard mods/*.c) $(PROTO:.h=.c)
OBJ       = $(SRC:.c=.o)

all: ministat

.c.o:
	$(CC) -o $@ $(WLCFLAGS) -c $<

$(OBJ): config.h $(PROTO)

config.h:
	cp config.def.h $@

ministat: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lasound

clean:
	rm -f ministat $(OBJ) $(PROTO) $(PROTO:.h=.c)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f ministat $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/ministat

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/ministat

.PHONY: all clean install uninstall
