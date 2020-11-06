#include "block.h"
#include <QDebug>
#include <QMap>

Block::Block()
{
    block_type = GRASS;
    full = false;
    haveTL = false;
}
bool Block::isFull() const
{
    return full;
}
void Block::setFull(bool value)
{
    full = value;
}

void Block::drawBlock()
{
//    int random_grass = rand() % 8;
    setTransformOriginPoint(PIXMAP_SIZE/2, PIXMAP_SIZE/2);
    switch (block_type) {
    case GRASS:
//        if(random_grass > 4)
            pixmap.load(":/images/grass.png");
//        else if(random_grass == 1)
//            pixmap.load(":/images/tree.jpeg");
//        else if(random_grass ==  2)
//            pixmap.load(":/images/build1.png");
//        else if(random_grass ==  3)
//            pixmap.load(":/images/build2.png");
//        else if(random_grass ==  4)
//            pixmap.load(":/images/build3.png");
        break;
    case DOWN:
        pixmap.load(":/images/road.png");
        setRotation(-90);
        break;
    case UP:
        pixmap.load(":/images/road.png");
        setRotation(90);
        break;
    case LEFT:
        pixmap.load(":/images/road.png");
        break;
    case RIGHT:
        pixmap.load(":/images/road.png");
        setRotation(180);
        break;
    case DOWN + RIGHT:
        pixmap.load(":/images/road_central.png");
        setRotation(270);
        break;
    case DOWN + LEFT:
        pixmap.load(":/images/road_central.png");
        break;
    case UP + RIGHT:
        pixmap.load(":/images/road_central.png");
        setRotation(180);
        break;
    case UP + LEFT:
        pixmap.load(":/images/road_central.png");
        setRotation(90);
        break;
    }
    setPixmap(pixmap);
}

bool Block::getHaveTL() const
{
    return haveTL;
}
void Block::setHaveTL(bool value)
{
  haveTL = value;
}
// TODO
QString Block::getFileNameByKey(BlockType key)
{
  QMap<BlockType, QString> fileNameArray;

  fileNameArray[GRASS] = "GRASS";
  fileNameArray[UP] = "UP";
  fileNameArray[UP_RIGHT] = "UP_RIGHT";
  fileNameArray[UP_LEFT] = "UP_LEFT";
  fileNameArray[DOWN] = "DOWN";
  fileNameArray[DOWN_LEFT] = "DOWN_LEFT";
  fileNameArray[DOWN_RIGHT] = "DOWN_RIGHT";

  return fileNameArray[key];
}
void Block::setBlock_type(const unsigned int type)
{
    block_type = type;
}
unsigned int Block::getBlock_type() const
{
    return block_type;
}
void Block::createBlock(int x, int y, const unsigned int type)
{
    setBlock_type(type);
    setPos(x, y);
    drawBlock();
}
void Block::redrawPixmap()
{
    if(isFull()){
        if(block_type != LEFT && block_type != RIGHT && block_type != UP && block_type != DOWN)
            setPixmap(QPixmap(":/images/road_central_false.png"));
        else
            setPixmap(QPixmap(":/images/road_false.png"));
    }
    else
        setPixmap(pixmap);
}
