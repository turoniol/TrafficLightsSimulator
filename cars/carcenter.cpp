#include "carcenter.h"
#include <QDebug>

CarCenter::CarCenter()
{
  carMoveTimer = new QTimer();
  carMoveTimer->start(1000/120);
  connect(carMoveTimer, &QTimer::timeout, [this](){
      for (auto &obj : cars)
        {
          if (obj != nullptr)
            {
              if (obj->canDeleteCar())
                {
                  delete obj;
                  obj = nullptr;
                }
              else
                obj->move();
            }
        }
    });
}

Car* CarCenter::findNullPtr()
{
  for (auto &obj : cars)
    {
      if (obj == nullptr)
        {
          return obj;
        }
    }
  return nullptr;
}

void CarCenter::searchCenterPoint(Map* map)
{
  for (unsigned int y = 0; y < map->getArray_y(); y++)
    {
      for (unsigned int x = 0; x < map->getArray_x(); x++)
        {
          auto obj = &map->getMap_ptr()[x + y*map->getArray_x()];
          switch (obj->getBlock_type()) {
            case DOWN:
              if(y == 0)
                spawners.append(obj);
              break;
            case UP:
              if(y == map->getArray_y() - 1)
                spawners.append(obj);
              break;
            case LEFT:
              if(x == map->getArray_x() - 1)
                spawners.append(obj);
              break;
            case RIGHT:
              if(x == 0)
                spawners.append(obj);
              break;
            }
        }
    }
}

Car &CarCenter::addNewCar(Map* map_ptr)
{
  Car* car = nullptr;
  srand(static_cast<unsigned int>(time(nullptr)));
  unsigned int random = 0;

  if(spawners.size() != 0)
    random = (unsigned int)(rand()) % spawners.size();

  QPointF spawnerPos = spawners[random]->pos();

  if(!map_ptr->getBlockAt(spawnerPos.rx(), spawnerPos.ry()).isFull())
    car = new Car(spawners[random]->pos(), map_ptr);


  Car* _ptr = findNullPtr();
  if (_ptr != nullptr)
    _ptr = car;
  else
    cars.append(car);


  return *car;
}


CarCenter::~CarCenter()
{
  delete carMoveTimer;
  for (auto &obj : cars)
    delete obj;
}
