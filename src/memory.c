#include "common.h"
#include "memory.h"
#include "logging.h"

void* pd_realloc(void* ptr, size_t size)
{
    void* new_ptr = pd->system->realloc(ptr, size);
    if (new_ptr == NULL && size != 0)
    {
        LOG_ERROR("pd_realloc: Failed to reallocate memory (size: %zu)", size);
    }
    return new_ptr;
}

void* pd_malloc(size_t size)
{
    return pd_realloc(NULL, size);
}

void* pd_calloc(size_t count, size_t size)
{
    void* ptr = pd_malloc(count * size);
    if (ptr != NULL)
    {
        memset(ptr, 0, count * size);
    }
    return ptr;
}

void pd_free(void* ptr)
{
    pd->system->realloc(ptr, 0);
}