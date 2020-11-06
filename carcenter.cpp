#include "carcenter.h"

CarCenter::CarCenter()
{
    car_number = 0;
    car_iterations = 0;
    car = nullptr;
}

void CarCenter::searchCenterPoint(Map* map)
{
    for(unsigned int y = 0; y < map->getArray_y(); y++){
        for(unsigned int x = 0; x < map->getArray_x(); x++){
            auto obj = &map->getMap_ptr()[x + y*map->getArray_x()];  // указатель obj для более удобной работы
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
    if(car_number % 50 == 0 && car_number != 0 && car_iterations != 0){
        qDebug("%d", car_iterations);
        car_iterations = 0;
    }
    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int random = 0;  //переменная для выбора случайного спаунера из контейнера
    if(spawners.size() != 0)
        random = static_cast<unsigned int>(rand()) % spawners.size();
    if(!map_ptr->getBlockAt(spawners[random]->pos().rx(), spawners[random]->pos().ry()).isFull()){
        car = new Car(spawners[random]->pos(), map_ptr, &car_iterations, &car_number);
    }
    else
        car = nullptr;
    return *car;
}

unsigned int CarCenter::getCarNumber() const
{
    return car_number;
}
