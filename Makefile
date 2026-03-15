CC = gcc
CFLAGS = -Wall -Wextra -O2
# uncomment next line for fully static
# LDFLAGS = -static

BINS = vstat vdf vproc vconn vport vtop vlog vfiles vlock

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Очистка папки от бинарников
clean:
	rm -f $(BINS)

# Установка в систему (нужен sudo или права на /usr/local/bin)
install: all
	cp $(BINS) /usr/local/bin/

# Удаление из системы
uninstall:
	rm -f $(addprefix /usr/local/bin/, $(BINS))
