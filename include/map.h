#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#include "global.h"

typedef void *Map;
typedef void *_Map;
typedef void *it_type;

EXTERNC void *map_create();
EXTERNC void map_put(void* map, unsigned int k, int v);
EXTERNC size_t map_size(void* map);
EXTERNC int map_get(void* map, unsigned int k);
EXTERNC bool map_exists(void *map, unsigned int k);
EXTERNC void map_destroy(void *map);
EXTERNC void map_reset(void *map);
EXTERNC void map_remove(void *map, unsigned int k);
EXTERNC void map_update(void *map, unsigned int k, int v);

#undef EXTERNC
