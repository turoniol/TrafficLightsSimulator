#include "trafficlight.h"
#include <QDebug>

bool TrafficLight::isInGroup() const
{
    return in_group;
}
void TrafficLight::setGroup(bool value)
{
    in_group = value;
}
void TrafficLight::setPtr(Map& ptr){
    map_ptr = &ptr;
}
TrafficLight::TrafficLight(){
    map_ptr = nullptr;
    refered = true;
    in_group = false;
}
TrafficLight::TrafficLight(Map& ptr)
{
    map_ptr = &ptr; //указатель на поле карты объекта Map
    refered = true;
    in_group = false;
}
void TrafficLight::searchCrossroad()
{
    //пробежка по всей карте и поиск перекрёстков
    for(unsigned int counter_y = 0; counter_y < map_ptr->getArray_y(); counter_y++){
        for(unsigned int counter_x = 0; counter_x < map_ptr->getArray_x(); counter_x++){
            if( map_ptr->getMap_ptr()[counter_x + counter_y*map_ptr->getArray_x()].getBlock_type() == DOWN + LEFT &&
                    map_ptr->getMap_ptr()[counter_x + 1 + counter_y*map_ptr->getArray_x()].getBlock_type() == UP + LEFT &&
                    map_ptr->getMap_ptr()[counter_x + (counter_y + 1)*map_ptr->getArray_x()].getBlock_type() == DOWN + RIGHT){
                //добавление перекрёстков в контейнер container
                container.emplace_back(&map_ptr->getMap_ptr()[counter_x + counter_y*map_ptr->getArray_x()]);
                container.emplace_back(&map_ptr->getMap_ptr()[counter_x + 1 + counter_y*map_ptr->getArray_x()]);
                container.emplace_back(&map_ptr->getMap_ptr()[counter_x + (counter_y + 1)*map_ptr->getArray_x()]);
                container.emplace_back(&map_ptr->getMap_ptr()[counter_x + 1 + (counter_y + 1)*map_ptr->getArray_x()]);
            }
        }
    }
}
void TrafficLight::setTrafficLight(std::vector<TrafficLight*> &light_ptr)
{
    unsigned int block_type;
    TrafficLight *new_item = nullptr;
    for(auto obj : container){
        new_item = new TrafficLight(*map_ptr);  //создание нового объекта
        new_item->setPos(obj->pos());  //установка его параметров
        block_type = obj->getBlock_type();
        if(block_type == DOWN + LEFT || block_type == UP + RIGHT){  //выбор начального цвета
            new_item->setPixmap(QPixmap(":/images/redl.png"));
            new_item->color = RED;
        }
        else if(block_type == UP + LEFT|| block_type == DOWN + RIGHT){ //выбор начального цвета
            new_item->setPixmap(QPixmap(":/images/greenl.png"));
            new_item->color = GREEN;
        }
        light_ptr.emplace_back(new_item); //запись объекта в массив light_ptr
    }
}
void TrafficLight::setFullBlock()
{
    for(auto obj : container)
        obj->setHaveTL(true);
}
TrafficLight* TrafficLight::getTrafficLightVector(){
    int position = 0;
    TrafficLight *new_item = new TrafficLight[container.size()];
    for(auto obj : container){
        new_item[position].setPtr(*map_ptr);
        new_item[position].setPos(obj->pos());
        switch (obj->getBlock_type()) {
        case DOWN + LEFT:
            new_item[position].setPixmap(QPixmap(":/images/redl.png"));
            new_item[position].color = RED;
            break;
        case DOWN + RIGHT:
            new_item[position].setPixmap(QPixmap(":/images/greenl.png"));
            new_item[position].color = GREEN;
            break;
        case UP + RIGHT:
            new_item[position].setPixmap(QPixmap(":/images/redl.png"));
            new_item[position].color = RED;
            break;
        case UP + LEFT:
            new_item[position].setPixmap(QPixmap(":/images/greenl.png"));
            new_item[position].color = GREEN;
            break;
        }
        position++;
    }
    return new_item;
}
unsigned int TrafficLight::getContainerSize() const{
    return container.size();
}
void TrafficLight::checkColor() // занять блок или освободить
{
    auto block_at_this_pos = &map_ptr->getBlockAt(x(), y());
    switch (color){
    case GREEN:
        block_at_this_pos->setFull(false);
        break;
    case RED:
        block_at_this_pos->setFull(true);
        break;
    case YELLOW:
        block_at_this_pos->setFull(true);
        break;
    }
}
void TrafficLight::setColorRed(){
    setPixmap(QPixmap(":/images/redl.png"));
    color = RED;
}
void TrafficLight::setColorGreen(){
    setPixmap(QPixmap(":/images/greenl.png"));
    color = GREEN;
}
void TrafficLight::setColorYellow(){
    setPixmap(QPixmap(":/images/yellowl.png"));
    color = YELLOW;
}
