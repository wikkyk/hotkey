/*
 * Hotkey
 * Executes commands in response to EV_KEY events from an evdev device.
 *
 * Copyright (C) 2014 Wiktor W Brodlo
 *
 * Hotkey is released under the MIT licence. See the LICENSE file for copyright
 * details.
 */

#include <stdint.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>

typedef char *const command;

struct event {
	uint16_t code;
	int32_t value;
	command *cmd;
};

#include "config.h"

const size_t nevents = sizeof(events) / sizeof(events[0]);


int main(void)
{
	struct input_event ev;
	size_t i;

	int fd = open(device, O_RDONLY);
	if (fd == -1)
		err(1, "open %s", device);

	while (1) {
		read(fd, &ev, sizeof(ev));
		for (i = 0; i < nevents; ++i)
			if (ev.code == events[i].code &&
			    ev.value == events[i].value &&
			    ev.type == EV_KEY &&
			    #if DELAY
			    !usleep(DELAY) &&
			    #endif
			    !fork()) {
				close(fd);
		    		execvp(events[i].cmd[0], events[i].cmd);
				err(1, "execvp");
			}
	}
}

