#ifndef MAP_H
#define MAP_H
#include "block.h"
#include "fstream"

class Map
{
private:
    Block *map_ptr;
    unsigned int array_x, array_y;
    unsigned int max_x, max_y;
    unsigned int map_size;
public:
    ~Map();
    void loadMapFromFile(const QString &file_name);
    // getters
    unsigned int getArray_x() const;
    unsigned int getArray_y() const;
    Block &getBlockAt(qreal x, qreal y) const;
    Block *getMap_ptr() const;
    unsigned int getMax_y() const;
    unsigned int getMax_x() const;
    Map();
};

#endif // MAP_H
