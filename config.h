/* These are only examples, not defaults. Adjust as needed. */

/* Device file to read events from */
const char *device = "/dev/input/event5";

/* Commands to run */
command mute[] = {"amixer", "set", "Master", "toggle", NULL};
command voldn[] = {"amixer", "set", "Master", "1%-", NULL};
command volup[] = {"amixer", "set", "Master", "1%+", NULL};
command susp[] = {"pm_suspend", NULL};
command startx[] = {"startx", NULL};

/*
 * Rules
 * The possible values are:
 *  0:  Key release
 *  1:  Key press
 *  2:  Key hold
 * Normally, you'll get 1 followed by 0. If you hold the key past some
 * threshold,you'll get 1, then lots of 2s for as long as the key is depressed,
 * then 0.
 * Play around with printev to see exactly how it works, and to find out the
 * right codes.
 * For a simple hit, use 0.
 * To keep executing a command while a button is being held, 1 followed by 2
 * works well - see how voldn and volup work. 2s are only fired after a delay.
 */
struct event events[] = {
	/*code, value, command*/
	{0x71, 0, mute},
	{0x72, 1, voldn},
	{0x72, 2, voldn},
	{0x73, 1, volup},
	{0x73, 2, volup},
	{0x8e, 0, susp},
	{0x43, 0, startx},
};

/*
 * Since holding a key creates lots of processes, it can result in a heavy load
 * on weaker systems. We'll usleep(DELAY) before forking to alleviate this.
 * Use 0 to disable the delay completely.
 */
#define DELAY 5
