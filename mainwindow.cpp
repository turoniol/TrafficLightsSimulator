#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include <QDir>
#include <QDebug>
#include "dirent.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  mapIndex = 0;
  scene = nullptr;
  ui->setupUi(this);
  // graphics
  ui->graphicsView->setGeometry(0, 0, w, h);
  ui->pushButton->setGeometry(1700, 0, 100, 50);
  ui->pushButton_left->setGeometry(1700, 50, 50, 50);
  ui->pushButton_right->setGeometry(1750, 50, 50, 50);
  ui->switchbutt->setGeometry(1700, 100, 100, 50);
  ui->label_2->setGeometry(10, 30, 50, 50);

  timer = new QTimer(this);
  carSpawnTimer = new QTimer(this);
  scene = nullptr;

  addScene();

  connect(timer, &QTimer::timeout, this, &MainWindow::renewTL);
  connect(carSpawnTimer, &QTimer::timeout, this, &MainWindow::on_pushButton_clicked);
}

void MainWindow::renewTL(){
  scene->renewTLStatus();
}

void MainWindow::map_posLabel()
{
  ui->label_2->setNum((int)mapIndex);
}

void MainWindow::createMapFileNameArray()
{
  unsigned int i = 0;
  QFile file;
  QString mapsPath = QDir::currentPath() + "/maps/map";
  QString path = mapsPath + QString::number(i) + ".txt";
  qDebug() << mapsPath;

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
//  if (scene != nullptr)
//    delete scene;
  scene = new Scene;

  ui->graphicsView->setScene(scene);
  scene->setSceneRect(0, 0, w + 1600, h + 1500);

  createMapFileNameArray();

  scene->addMap(fileMapNames[mapIndex]);
  scene->addTrafficLights();
  scene->addCar();
  timer->start(500);
  carSpawnTimer->start(500);
  map_posLabel();
}

void MainWindow::on_pushButton_clicked()
{
  scene->addCar();
  ui->label->setNum(static_cast<int>(scene->getCarNumber()));
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
    }else{
      ui->switchbutt->setText("Switch on");
      scene->setSystem_on(false);
    }
}
