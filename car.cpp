#include "car.h"
#include <time.h>
#include <windows.h>
#include <QDebug>
#include <QThread>

Car::Car(QPointF start_pos, Map* map_ptr, unsigned int *iptr, unsigned int *died)
{
    size_x = map_ptr->getArray_x();
    size_y = map_ptr->getArray_y();
    this->map_ptr = map_ptr;

    int car_color_rand = rand() % 3;
    kill = died;
    iterations = iptr;
    counter = 0;
    speed_x = 0;
    speed_y = 0;
    direction = 0;
    fps = 1000/160;
    previous_block = nullptr;
    move_timer = new QTimer(this);

    position.setX(start_pos.rx());
    position.setY(start_pos.ry());

    chooseCarColor(car_color_rand);

    setPos(start_pos);
    setDirection();
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(fps);
}
void Car::move(){
    if(isNextBlock() || previous_block == nullptr){
        setDirection();
        choosePixmapDirection();
        setSpeed();
    }
    if(isNextBlockFull())
        moveBy(speed_x, speed_y);
    deleteCar();
    ++counter;
}
void Car::setDirection()
{
    direction = map_ptr->getBlockAt(position.rx(), position.ry()).getBlock_type();
    rotate();
}
void Car::setSpeed(){
    int speed = 1;
    switch(direction){
    case UP:
        speed_x = 0;
        speed_y = -speed;
        break;
    case DOWN:
        speed_x = 0;
        speed_y = speed;
        break;
    case RIGHT:
        speed_x = speed;
        speed_y = 0;
        break;
    case LEFT:
        speed_x = -speed;
        speed_y = 0;
        break;
    case GRASS:
        speed_x = 0;
        speed_y = 0;
        break;
    }
}
void Car::choosePixmapDirection(){
    setPixmap(pixmap);
    setTransformOriginPoint(pixmap.width()/2, pixmap.height()/2);
    switch (direction){
    case RIGHT:
        setRotation(0);
        break;
    case LEFT:
        setRotation(180);
        break;
    case UP:
        setRotation(-90);
        break;
    case DOWN:
        setRotation(90);
        break;
    }
}
void Car::rotate()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int rotate_random = rand() & 2;
    switch(map_ptr->getBlockAt(position.rx(), position.ry()).getBlock_type()){
    case UP + LEFT:          // повороты
        if(rotate_random)
            direction = UP;
        else
            direction = LEFT;
        break;
    case DOWN + LEFT:
        if(rotate_random)
            direction = DOWN;
        else
            direction = LEFT;
        break;
    case UP + RIGHT:
        if(rotate_random)
            direction = UP;
        else
            direction = RIGHT;
        break;
    case DOWN + RIGHT:
        if(rotate_random)
            direction = DOWN;
        else
            direction = RIGHT;
        break;
    }
}
bool Car::isNextBlockFull()
{
    auto next_block = &getNextBlock();
    switch (direction) {
    case UP:
        if(next_block->getBlock_type() == UP + LEFT)
            return true;
        else
            return !next_block->isFull();
    case DOWN:
        if(next_block->getBlock_type() == DOWN + RIGHT)
            return true;
        else
            return !next_block->isFull();
    case RIGHT:
        if(next_block->getBlock_type() == UP + RIGHT)
            return true;
        else
            return !next_block->isFull();
    case LEFT:
        if(next_block->getBlock_type() == DOWN + LEFT)
            return true;
        else
            return !next_block->isFull();
    }
    return !next_block->isFull();
}
bool Car::isNextBlock()
{
    Block* current_block = &map_ptr->getBlockAt(position.rx(), position.ry());
    current_block->setFull(true);
    switch (direction) {
    case UP:
        if(pos().ry() + pixmap.height() < current_block->pos().ry()){
            previous_block = current_block;
            if(!previous_block->getHaveTL())
                previous_block->setFull(false);
            position.setY(position.ry() - PIXMAP_SIZE);
            return true;
        }
        break;
    case DOWN:
        if(pos().ry() - PIXMAP_SIZE  > current_block->pos().ry()){
            previous_block = current_block;
            if(!previous_block->getHaveTL())
                previous_block->setFull(false);
            position.setY(position.ry() + PIXMAP_SIZE);
            return true;
        }
        break;
    case LEFT:
        if(pos().rx() + pixmap.width() < current_block->pos().rx()){
            previous_block = current_block;
            if(!previous_block->getHaveTL())
                previous_block->setFull(false);
            position.setX(position.rx() - PIXMAP_SIZE);
            return true;
        }
        break;
    case RIGHT:
        if(pos().rx() - PIXMAP_SIZE  > current_block->pos().rx()){
            previous_block = current_block;
            if(!previous_block->getHaveTL())
                previous_block->setFull(false);
            position.setX(position.rx() + PIXMAP_SIZE);
            return true;
        }
        break;
    }
    return false;
}
Block &Car::getNextBlock()
{
    switch (direction) {
    case UP:
        if(position.ry() >= PIXMAP_SIZE)
            return map_ptr->getBlockAt(position.rx(), position.ry() - PIXMAP_SIZE);
        break;
    case DOWN:
        if(position.ry() <= PIXMAP_SIZE*(size_y - 2))
            return map_ptr->getBlockAt(position.rx(), position.ry() + PIXMAP_SIZE);
        break;
    case LEFT:
        if(position.rx() >= PIXMAP_SIZE)
            return map_ptr->getBlockAt(position.rx() - PIXMAP_SIZE, position.ry());
        break;
    case RIGHT:
        if(position.ry() <= PIXMAP_SIZE*(size_y - 2))
            return map_ptr->getBlockAt(position.rx() + PIXMAP_SIZE, position.ry());
        break;
    }
    return map_ptr->getBlockAt(position.rx(), position.ry());
}
void Car::chooseCarColor(int prmtr){
    switch (prmtr) {
    case 0:
        pixmap.load(":/images/blue_car.png");
        break;
    case 1:
        pixmap.load(":/images/red_car.png");
        break;
    case 2:
        pixmap.load(":/images/yellow_car.png");
        break;
    }
}
void Car::deleteCar()
{
    if(pos().rx() < 0 || pos().ry() < 0
            || pos().rx() > PIXMAP_SIZE*(size_x - 1) || pos().ry() > PIXMAP_SIZE*(size_y - 1)
/*            || (counter > 1.5f*map_ptr->getMax_x() && map_ptr->getMax_x() > map_ptr->getMax_y())
            || (counter > 1.5f*map_ptr->getMax_y() && map_ptr->getMax_x() < map_ptr->getMax_y()) */){
        if(!map_ptr->getBlockAt(position.rx(), position.ry()).getHaveTL())
            map_ptr->getBlockAt(position.rx(), position.ry()).setFull(false);
        ++(*kill);
        *iterations += counter;
        delete this;
    }
}
Car::~Car()
{
    delete move_timer;
}
