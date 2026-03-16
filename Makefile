CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 
PREFIX = /usr/local

BINS = vst vfs vpr vcn vpt vt5 vfl vlk vlg

# Указываем, что это не имена файлов
.PHONY: all clean install uninstall

all: $(BINS)

# Универсальное правило сборки
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(BINS)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(BINS) $(DESTDIR)$(PREFIX)/bin/

uninstall:
	rm -f $(addprefix $(DESTDIR)$(PREFIX)/bin/, $(BINS))
