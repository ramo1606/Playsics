#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "pd_api.h"

extern PlaydateAPI* pd;

typedef struct
{
	LCDFont* font;
	bool initialized;
} Renderer;

typedef struct
{
	bool is_running;
	bool debug;

	Renderer* renderer;
} Engine;

#endif // !CORE_H
