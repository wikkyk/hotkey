/*
 * Printev
 * Prints out EV_KEY events from an evdev device.
 *
 * Copyright (C) 2014 Wiktor W Brodlo <wiktor@brodlo.net>
 *
 * Printev is released under the MIT licence. See the LICENSE file for copyright
 * details.
 */

#include <linux/input.h>
#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	struct input_event ev;
	int fd;

	if (argc != 2) {
		printf("Usage: %s <evdev>\ne.g. /dev/input/event5\n", argv[0]);
		return 1;
	}

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		err(2, "open %s", argv[1]);

	while (1) {
		read(fd, &ev, sizeof ev);
		if (ev.type == EV_KEY)
			printf("code: 0x%x, value: 0x%x\n", ev.code, ev.value);
	}
}

