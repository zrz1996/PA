#include "hal.h"

#define NR_KEYS 18

enum {KEY_STATE_EMPTY, KEY_STATE_WAIT_RELEASE, KEY_STATE_RELEASE, KEY_STATE_PRESS};

/* Only the following keys are used in NEMU-PAL. */
static const int keycode_array[] = {
	K_UP, K_DOWN, K_LEFT, K_RIGHT, K_ESCAPE,
	K_RETURN, K_SPACE, K_PAGEUP, K_PAGEDOWN, K_r,
	K_a, K_d, K_e, K_w, K_q,
	K_s, K_f, K_p
};

static int key_event[NR_KEYS]; 
static int key_state[NR_KEYS]; 
static int key_vis[NR_KEYS];

static int find_key_index(int code)
{
	int i;
	code &= 0x7f;
	for (i = 0; i < NR_KEYS; i++)
		if (keycode_array[i] == code)
			return i;
	printf("unknown key = %d\n", code);
	return -1;
}

#define I8042_DATA_PORT 0x60

void
keyboard_event(void) 
{
	int code = (unsigned) (unsigned char) in_byte(I8042_DATA_PORT);
	int index = find_key_index(code);
	if (code < 0x80) 
	{ 
		key_event[index] = 1;
	} 
	else 
	{
		if (key_vis[index]) 
		{
			key_event[index] = 0;
			key_vis[index] = 0;
		}
	}
}

bool 
process_keys(void (*key_press_callback)(int), void (*key_release_callback)(int)) {
	cli();
	bool ret = false;
	int index;
	for (index = 0; index < NR_KEYS; index++) 
	{ 
		int state = key_state[index]; 
		int event = key_event[index]; 
		int action;
		int state_trans;
		if (state == 1) 
		{
			if (event == 1) 
			{
				state_trans = 1;
				action = 0;
			}
			else
			{
				state_trans = 0;
				action = 2; 
			}  
		}
		else
		{
			if (event == 1) 
			{
				state_trans = 1;
				action = 1; 
			}
			else
			{
				state_trans = 0;
				action = 0; 
			} 
		} 
		key_state[index] = state_trans;
		key_vis[index] = 1;
		if (action != 0) 
		{
			if (action == 1) key_press_callback(keycode_array[index]);
			if (action == 2) key_release_callback(keycode_array[index]);
			ret = true;
			goto done;
		}
	}

done:
	sti();
	return ret;
}

