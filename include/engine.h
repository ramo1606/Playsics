#ifndef ENGINE_H
#define ENGINE_H

void engine_init(Engine* engine);
void engine_input(Engine* engine);
void engine_update(Engine* engine);
void engine_render(Engine* engine);
void engine_destroy(Engine* engine);

#endif /* ENGINE_H */