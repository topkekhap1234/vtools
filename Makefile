CC = gcc
CFLAGS = -Wall -Wextra -O2
# uncomment next line for fully static
# LDFLAGS = -static

BINS = vst vfs vpr vcn vpt vt5 vfl vlk vlg

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(BINS)

install: all
	cp $(BINS) /usr/local/bin/

uninstall:
	rm -f $(addprefix /usr/local/bin/, $(BINS))
