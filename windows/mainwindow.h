#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene/scene.h"
#include <QTimer>
#include "scene/graphicsviewzoom.h"
#define SEC 1000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
  int w = 1920, h = 1000;
  unsigned int lastMapIndex;
  unsigned int mapIndex;
  GraphicsViewZoom *graphicsViewZoom;
  Scene *scene;
  Ui::MainWindow *ui;
  std::vector<QString> fileMapNames;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createMapFileNameArray();
public slots:
    void addScene();
    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
