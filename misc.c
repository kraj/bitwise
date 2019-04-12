/* Copyright 2019
 * Ramon Fried <ramon.fried@gmail.com
 */

#include <ctype.h>
#include "bitwise.h"

void init_terminal(void)
{
	initscr();
	if(has_colors() == FALSE)
		die("Your terminal does not support color\n");
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
}

void deinit_terminal(void)
{
	endwin();
}

void die(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	deinit_terminal();
	vfprintf(stderr, fmt, args);

	exit(1);
}

int validate_input(int ch, int base)
{
	switch (base) {
	case 2:
		 LOG("validating 2\n");
		if (ch == '0' || ch == '1')
			return 0;
		break;
	case 8:
		 LOG("validating 8\n");
		if (ch >= '0' && ch <= '7')
			return 0;
		break;
	case 16:
		 LOG("validating 16\n");
		if ((ch >= '0' && ch <= '9') ||
		     (ch >= 'A' && ch <= 'F') ||
		     (ch >= 'a' && ch <= 'f'))
			 return 0;
		 break;
	case 10:
		 LOG("validating 10\n");
		 if (isdigit(ch))
			 return 0;
		 break;
	default:
		 LOG("What the fuck\n");
		 break;
	}


	LOG("validating input failed\n");
	return 1;
}

uint64_t base_scanf(const char *buf, int base)
{
	uint64_t value;
	int ret;

	switch (base) {
	case 10:
		ret = sscanf(buf, "%lu", &value);
		break;
	case 16:
		ret = sscanf(buf, "%lx", &value);
		break;
	case 8:
		ret = sscanf(buf, "%lo", &value);
		break;
	default:
		fprintf(stderr, "Unknown base\n");
		break;
	}

	if (ret == EOF || !ret) {
		fprintf(stderr, "Couldn't parse parameter\n");
		exit(1);
	}

	return value;
}


void lltostr(uint64_t val, char *buf, int base)
{
	switch (base) {
	case 10:
		sprintf(buf, "%lu", val);
		return;
	case 16:
		sprintf(buf, "%lx", val);
		return;
	case 8:
		sprintf(buf, "%lo", val);
		return;
	case 2:
		sprintf(buf, "Not implemeted");
	}
}

