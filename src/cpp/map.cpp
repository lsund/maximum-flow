
#include <map>

typedef std::map<unsigned int, int> Map;
typedef std::map<unsigned int, void *> _Map;
typedef std::map<unsigned int, void *>::iterator it_type;

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

    void map_update(void *map, unsigned int k, int v)
    {
        Map *m = reinterpret_cast<Map *> (map);
        (*m)[k] = v;
    }

    size_t map_size(void *map) 
    {
        Map *m = reinterpret_cast<Map *> (map);
        return m->size();
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

    void map_remove(void *map, unsigned int k)
    {
        Map *m = reinterpret_cast<Map *> (map);
        m->erase(k);
    }

    ////////////////////////////////////////////
    void* _map_create() 
    {
        return reinterpret_cast<void*> (new _Map);
    }

    void _map_put(void *map, unsigned int k, void *v) 
    {
        _Map *m = reinterpret_cast<_Map *> (map);
        m->insert(std::pair<unsigned int, void *>(k, v));
    }

    size_t _map_size(void *map) 
    {
        _Map *m = reinterpret_cast<_Map *> (map);
        return m->size();
    }

    void *_map_get(void *map, unsigned int k)
    {
        _Map *m = reinterpret_cast<_Map *> (map);
        return m->at(k);
    }

    bool _map_exists(void *map, unsigned int k)
    {
        _Map *m = reinterpret_cast<_Map *> (map);
        return m->find(k) != m->end();
    }

    void _map_destroy(void *map)
    {
        _Map *m = reinterpret_cast<_Map *> (map);
        delete m;
    }

    void _map_reset(void *map)
    {
        _Map *m = reinterpret_cast<_Map *> (map);
        m->clear();
    }

    void _map_remove(void *map, unsigned int k)
    {
        _Map *m = reinterpret_cast<_Map *> (map);
        m->erase(k);
    }
}
