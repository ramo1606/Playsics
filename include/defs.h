#ifndef DEFS_H
#define DEFS_H	

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define FPS        30.0
#define LOGIC_RATE (FPS / 1000)

#endif // !DEFS_H
