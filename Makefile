include config.mk

SRC = hotkey.c printev.c
OBJ = ${SRC:.c=}

all: ${OBJ} config.h

.c:
	${CC} ${CFLAGS} -o $@ $<

install: ${OBJ}
	mkdir -p ${PREFIX}/bin
	cp -f ${OBJ} ${PREFIX}/bin
	for o in ${OBJ}; do chmod 755 ${PREFIX}/bin/$$o; done

clean:
	rm -f ${OBJ}

uninstall:
	for o in ${OBJ}; do rm -f ${PREFIX}/bin/$$o; done

.PHONY: all install openrc clean uninstall
