#include "engine.h"
#include "logging.h"
#include "renderer.h"

bool engine_is_running(Engine* engine)
{
	return engine != NULL && engine->is_running;
}

void engine_init(Engine* engine)
{
	if (engine == NULL)
	{
		LOG_ERROR("engine:init: Engine pointer is NULL");
		return;
	}

	engine->is_running = true;
	engine->debug = false;
	engine->renderer = renderer_create();
	if (engine->renderer == NULL)
	{
		LOG_ERROR("engine:init: Failed to create renderer");
		engine->is_running = false;
		return;
	}
	renderer_init(engine->renderer);
}

void engine_input(Engine* engine)
{
}

void engine_update(Engine* engine)
{
}

void engine_render(Engine* engine)
{
	if (engine != NULL && engine->renderer != NULL)
	{
		renderer_draw(engine->renderer);
	}
}

void engine_destroy(Engine* engine)
{
	if (engine->renderer != NULL)
	{
		renderer_destroy(engine->renderer);
		engine->renderer = NULL;
	}
	engine->is_running = false;
}
