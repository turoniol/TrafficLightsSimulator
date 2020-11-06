#include "map.h"
#include "QDebug"

Map::Map()
{
  map_ptr = nullptr;
}

unsigned int Map::getArray_x() const
{
  return array_x;
}

unsigned int Map::getArray_y() const
{
  return array_y;
}

void Map::loadMapFromFile(const QString &file_name) //загружает и рисует карту из текстового файла
{
  std::fstream file(file_name.toStdString());

  file >> array_x >> array_y; //считывание размера карты в блока�

  max_x = PIXMAP_SIZE*array_x;
  max_y = PIXMAP_SIZE*array_y;

  unsigned int map_size = array_x + array_y*array_x;  //переменная для хранения размера карты
  map_ptr = new Block[map_size]; //создание массива размером map_size
  unsigned int type;

  for(unsigned int counter_y = 0; counter_y < array_y; counter_y++){
      for(unsigned int counter_x = 0; counter_x < array_x; counter_x++){
          file >> type;  //считывание информации о каждом блоке и запись в переменную а
          map_ptr[counter_x + counter_y*array_x].createBlock(PIXMAP_SIZE*counter_x, PIXMAP_SIZE*counter_y, type);
        }
    }

  file.close();
}

Block& Map::getBlockAt(qreal x, qreal y) const
{
  unsigned int x_mod = static_cast<unsigned int>( x -  (static_cast<unsigned int>(x) % PIXMAP_SIZE ) ) / PIXMAP_SIZE;
  unsigned int y_mod = static_cast<unsigned int>( y -  (static_cast<unsigned int>(y) % PIXMAP_SIZE ) ) / PIXMAP_SIZE;

  return map_ptr[x_mod + array_x*y_mod];
}

Block *Map::getMap_ptr() const
{
  return map_ptr;
}

unsigned int Map::getMax_y() const
{
  return max_y;
}

unsigned int Map::getMax_x() const
{
  return max_x;
}

Map::~Map()
{
  delete []map_ptr;
}
