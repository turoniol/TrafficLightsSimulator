#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scene.h>
#include <QTimer>
#define SEC 1000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void map_posLabel();
    void createMapFileNameArray();
public slots:
    void addScene();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_right_clicked();    
    void renewTL();
    void on_switchbutt_clicked();

private:
    int w = 1920, h = 1000;
    unsigned int lastMapIndex;
    unsigned int mapIndex;
    Scene *scene;
    QTimer *carSpawnTimer;
    QTimer *timer;
    Ui::MainWindow *ui;
    std::vector<QString> fileMapNames;
};

#endif // MAINWINDOW_H
