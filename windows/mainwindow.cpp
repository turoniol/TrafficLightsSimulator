#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map/map.h"
#include <QDir>
#include <QScrollBar>
#include <QScreen>
#include <QKeyEvent>
#include <QDebug>
#include "dirent.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  mapIndex = 0;
  scene = nullptr;
  ui->setupUi(this);
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rec = screen->availableGeometry();
  w = rec.width();
  h = rec.height();

  // graphics
  int srcollbarHeight = ui->graphicsView->horizontalScrollBar()->height();
  ui->graphicsView->setGeometry(0, 0, w, h - srcollbarHeight);
  ui->label->setGeometry(0, 0, 100, 100);
  ui->label->setText("OFF");

  scene = nullptr;
  graphicsViewZoom = new GraphicsViewZoom(ui->graphicsView);

  addScene();
}

void MainWindow::createMapFileNameArray()
{
  unsigned int i = 0;
  QFile file;
  QString mapsPath = QDir::currentPath() + "/maps/map";
  QString path = mapsPath + QString::number(i) + ".txt";

  file.setFileName(path);
  while(file.exists())
    {
      path = mapsPath + QString::number(i) + ".txt";
      file.setFileName(path);

      if(file.exists())
        {
          fileMapNames.push_back(path);
          lastMapIndex = i++;
        }
    }
}
void MainWindow::addScene()
{
  scene = new Scene;

  ui->graphicsView->setScene(scene);

  createMapFileNameArray();

  scene->addMap(fileMapNames[mapIndex]);
  scene->addTrafficLights();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Z)
    {
      if (mapIndex == 0)
        mapIndex = lastMapIndex;
      else
        --mapIndex;
      addScene();
    }
  else if (event->key() == Qt::Key_X)
    {
      if (mapIndex == lastMapIndex)
        mapIndex = 0;
      else
        ++mapIndex;
      addScene();
    }
  else if (event->key() == Qt::Key_Space)
    {
      if (!scene->getSystem_on())
        {
          ui->label->setText("ON");
          scene->setSystem_on(true);
        }
      else
        {
          ui->label->setText("OFF");
          scene->setSystem_on(false);
        }
    }
}

MainWindow::~MainWindow()
{
  delete ui;
}


