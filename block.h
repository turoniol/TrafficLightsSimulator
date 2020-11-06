#ifndef DRAWER_H
#define DRAWER_H

#include <QGraphicsItem>
#define PIXMAP_SIZE 60

enum BlockType {
  GRASS = 0,
  DOWN = 2,
  UP = 8,
  LEFT = 1,
  RIGHT = 4,
  UP_LEFT = UP + LEFT,
  UP_RIGHT = UP + RIGHT,
  DOWN_LEFT = DOWN + LEFT,
  DOWN_RIGHT = DOWN + RIGHT
};

class Block : public QGraphicsPixmapItem
{
private:
    unsigned int block_type;
    bool full, haveTL;
    QPixmap pixmap;
    void setBlock_type(const unsigned type);
public:
    Block();
    void drawBlock();
    void redrawPixmap();
    unsigned int getBlock_type() const;
    void createBlock(int x, int y, const unsigned int type);
    bool isFull() const;
    void setFull(bool value);
    bool getHaveTL() const;
    void setHaveTL(bool value);
    QString getFileNameByKey(BlockType key);
};

#endif // DRAWER_H
