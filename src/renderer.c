#include "common.h"
#include "renderer.h"
#include "logging.h"
#include "memory.h"

Renderer* renderer_create(void)
{
    Renderer* renderer = (Renderer*)pd_malloc(sizeof(Renderer));
    if (renderer == NULL)
    {
        LOG_ERROR("renderer:create: Memory allocation failed");
        return NULL;
    }

    renderer->initialized = false;
	renderer->font = NULL;

	return renderer;
}

void renderer_init(Renderer* renderer)
{
    if (renderer == NULL )
    {
        LOG_ERROR("renderer:init: Invalid parameters");
        return;
    }

    renderer->initialized = false;

    // Load font (with error handling)
    const char* err;
    const char* fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
    renderer->font = pd->graphics->loadFont(fontpath, &err);

    if (renderer->font == NULL)
    {
        LOG_ERROR("graphics:init: Couldn't load font %s: %s", fontpath, err);
        return;
    }

	renderer->initialized = true;
}

void renderer_draw(Renderer* renderer)
{
    pd->graphics->clear(kColorWhite);
    pd->graphics->drawText("Hello, Playdate!", 15, kASCIIEncoding, 10, 10);
}

void renderer_destroy(Renderer* renderer)
{
    if (renderer != NULL)
    {
        pd_free(renderer);
    }
}
