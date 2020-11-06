#include "trafficlightgroup.h"
#include <QDebug>

TrafficLightGroup::TrafficLightGroup(Map* map_ptr)
{
    time = 5000;
    timer = new QTimer(this);
    this->map_ptr = map_ptr;
    prevstatus = true;
    status = false;
    zone_size = 3;
    connect(timer, SIGNAL(timeout()), this, SLOT(changeColor()));
    timer->start(time);
}
void TrafficLightGroup::changeColor()
{
    setStatus(!status);
    changeStatus();
}
void TrafficLightGroup::joinTL(TrafficLight *tl, TrafficLight *array[])
{
    unsigned int x = static_cast<unsigned int>(tl->pos().rx());
    unsigned int y = static_cast<unsigned int>(tl->pos().ry());
    unsigned int x_pos = x/PIXMAP_SIZE;
    unsigned int y_pos = y/PIXMAP_SIZE;

    include(x_pos, y_pos, array);
    include(x_pos + 1, y_pos, array);
    include(x_pos , y_pos + 1, array);
    include(x_pos + 1, y_pos + 1, array);

    setZone();
}
void TrafficLightGroup::changeStatus()
{
    if (status)
    {
        group[1]->setColorGreen();
        group[2]->setColorGreen();
        group[0]->setColorRed();
        group[3]->setColorRed();
        timer->start(time);
    }
    else
    {
        group[0]->setColorGreen();
        group[3]->setColorGreen();
        group[1]->setColorRed();
        group[2]->setColorRed();
        timer->start(time);
    }
}
void TrafficLightGroup::setStatus(bool value){
    prevstatus = status;
    status = value;
}
void TrafficLightGroup::setZone()
{
    // инициализация
    int x = static_cast<int>(group[0]->x());
    int y = static_cast<int>(group[0]->y());
    // добавление блоков в зону
    addZoneUp(x, y);
    addZoneDown(x, y + PIXMAP_SIZE);
    addZoneDown(x + PIXMAP_SIZE, y + PIXMAP_SIZE);
    addZoneUp(x  + PIXMAP_SIZE, y);
    addZoneLeft(x, y);
    addZoneRight(x + PIXMAP_SIZE, y);
    addZoneRight(x + PIXMAP_SIZE, y + PIXMAP_SIZE);
    addZoneLeft(x, y + PIXMAP_SIZE);
}
void TrafficLightGroup::addZoneLeft(int x, int y)
{
    unsigned int iterations = 0;
    for(x -= PIXMAP_SIZE; x >=  0 && iterations < zone_size && !map_ptr->getBlockAt(x, y).getHaveTL(); x -= PIXMAP_SIZE, ++iterations)
        zone.emplace_back(&map_ptr->getBlockAt(x, y));

    while(iterations < zone_size){
        auto free_road = new Block;
        free_road->createBlock(0, 0, UP);
        zone.emplace_back(free_road);
        ++iterations;
    }
}
void TrafficLightGroup::addZoneRight(int x, int y)
{
    unsigned int iterations = 0;
    for(x += PIXMAP_SIZE; x <  (int)map_ptr->getMax_x() && iterations < zone_size   && !map_ptr->getBlockAt(x, y).getHaveTL();
    x += PIXMAP_SIZE, ++iterations)
        zone.emplace_back(&map_ptr->getBlockAt(x, y));

    while(iterations < zone_size){
        auto free_road = new Block;
        free_road->createBlock(0, 0, UP);
        zone.emplace_back(free_road);
        ++iterations;
    }

}
void TrafficLightGroup::addZoneUp(int x, int y)
{
    unsigned int iterations = 0;
    for(y -= PIXMAP_SIZE; y >=  0 && iterations < zone_size  && !map_ptr->getBlockAt(x, y).getHaveTL() ; y -= PIXMAP_SIZE, ++iterations)
        zone.emplace_back(&map_ptr->getBlockAt(x, y));

    while(iterations < zone_size){
        auto free_road = new Block;
        free_road->createBlock(0, 0, UP);
        zone.emplace_back(free_road);
        ++iterations;
    }
}
void TrafficLightGroup::addZoneDown(int x, int y)
{
    unsigned int iterations = 0;
    bool yLessThanMaxY = y <  (int)map_ptr->getMax_y();
    for(y += PIXMAP_SIZE; yLessThanMaxY && iterations < zone_size && !map_ptr->getBlockAt(x, y).getHaveTL() ; y += PIXMAP_SIZE, ++iterations)
        zone.emplace_back(&map_ptr->getBlockAt(x, y));

    while(iterations < zone_size){
        auto free_road = new Block;
        free_road->createBlock(0, 0, UP);
        zone.emplace_back(free_road);
        ++iterations;
    }
}
void TrafficLightGroup::include(const unsigned int x_pos, const unsigned int y_pos, TrafficLight* array[])
{
    array[x_pos + y_pos*map_ptr->getArray_x()]->setGroup(true);
    group.emplace_back(array[x_pos + y_pos*map_ptr->getArray_x()]);
}
unsigned int TrafficLightGroup::getLineNumber() const
{
    return zone.size()/zone_size;
}
unsigned int TrafficLightGroup::getZoneBlockNumber() const
{
    return zone.size();
}
bool TrafficLightGroup::getBlockFullAt(unsigned int iterator)
{
    return zone[iterator]->isFull();
}
void TrafficLightGroup::renewTLStatus(){
    for(auto obj : group)
        obj->checkColor();
}
TrafficLightGroup::~TrafficLightGroup(){
    delete timer;
    for(auto obj : group)
        delete obj;
}
