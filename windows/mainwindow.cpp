#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map/map.h"
#include <QDir>
#include <QScrollBar>
#include <QScreen>
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
  QRect rec = screen->geometry();
  w = rec.width();
  h = rec.height();
  // graphics
  ui->graphicsView->setGeometry(0, 0, w, h);
  ui->pushButton->setGeometry(1700, 0, 100, 50);
  ui->pushButton_left->setGeometry(1700, 50, 50, 50);
  ui->pushButton_right->setGeometry(1750, 50, 50, 50);
  ui->switchbutt->setGeometry(1700, 100, 100, 50);

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
  scene->setSceneRect(0, 0, w, h);

  createMapFileNameArray();

  scene->addMap(fileMapNames[mapIndex]);
  scene->addTrafficLights();
}

void MainWindow::on_pushButton_clicked()
{
  scene->addCar();
}
void MainWindow::on_pushButton_left_clicked()
{
  if(mapIndex == 0)
    mapIndex = lastMapIndex;
  else
    --mapIndex;
  addScene();
}
void MainWindow::on_pushButton_right_clicked()
{
  if(mapIndex == lastMapIndex)
    mapIndex = 0;
  else
    ++mapIndex;
  addScene();
}
MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_switchbutt_clicked()
{
  if(!scene->getSystem_on()){
      ui->switchbutt->setText("Switch off");
      scene->setSystem_on(true);
    }
    else
    {
      ui->switchbutt->setText("Switch on");
      scene->setSystem_on(false);
    }
}
