#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#include "global.h"

// This is a wrapper module for the C++11 std::map container. The functions are
// named to match the functions in the C++ standard library

typedef void *Map;

EXTERNC void *map_create();

EXTERNC void map_put(void* map, unsigned int k, int v);

EXTERNC int map_get(void* map, unsigned int k);

EXTERNC bool map_exists(void *map, unsigned int k);

EXTERNC void map_destroy(void *map);

EXTERNC void map_reset(void *map);

EXTERNC void map_remove(void *map, unsigned int k);

#undef EXTERNC
