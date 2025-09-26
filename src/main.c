#include "engine.h"

/* Playdate API instance */
PlaydateAPI* pd = NULL;
Engine engine;

/* Function prototypes */
static int update(void* userdata) 
{
    // Check if application is still running
    if (!engine_is_running(&engine)) 
    {
        return 0; // Signal to stop the update loop
    }

    // Handle input
    engine_input(&engine);

    // Update game logic
    engine_update(&engine);

    // Render the frame
    engine_render(&engine);

    return 1; // Continue the update loop
}

/* Main Playdate event handler */
#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // Suppress unused parameter warning

    switch (event) 
    {
        case kEventInit:
            // Store the API pointer globally
            pd = playdate;

            // Set the update callback
            pd->system->setUpdateCallback(update, NULL);

            // Initialize the engine
            engine_init(&engine);
            break;

        case kEventTerminate:
            // Cleanup when the game is terminated
            engine_destroy(&engine);
            break;

        case kEventPause:
            // Handle pause if needed
            break;

        case kEventResume:
            // Handle resume if needed
            break;

        case kEventLock:
            // Handle system lock if needed
            break;

        case kEventUnlock:
            // Handle system unlock if needed
            break;

        case kEventLowPower:
            // Handle low power state if needed
            break;
    }

    return 0;
}
