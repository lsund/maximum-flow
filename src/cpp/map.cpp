
#include <map>

typedef std::map<unsigned int, int> Map;

extern "C" {

    void* map_create() 
    {
        return reinterpret_cast<void*> (new Map);
    }

    void map_put(void *map, unsigned int k, int v) 
    {
        Map *m = reinterpret_cast<Map *> (map);
        m->insert(std::pair<unsigned int, int>(k, v));
    }

    void map_remove(void *map, unsigned int k)
    {
        Map *m = reinterpret_cast<Map *> (map);
        m->erase(k); 
    }

    int map_get(void *map, unsigned int k)
    {
        Map *m = reinterpret_cast<Map *> (map);
        return m->at(k);
    }

    bool map_exists(void *map, unsigned int k)
    {
        Map *m = reinterpret_cast<Map *> (map);
        return m->find(k) != m->end();
    }

    void map_destroy(void *map)
    {
        Map *m = reinterpret_cast<Map *> (map);
        delete m;
    }

    void map_reset(void *map)
    {
        Map *m = reinterpret_cast<Map *> (map);
        m->clear();
    }
}

