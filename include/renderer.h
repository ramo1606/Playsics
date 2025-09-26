#ifndef RENDERER_H
#define RENDERER_H

#include "core.h"

Renderer* renderer_create(void);
void renderer_init(Renderer* renderer);
void renderer_draw(Renderer* renderer);
void renderer_destroy(Renderer* renderer);

#endif // !RENDERER_H
