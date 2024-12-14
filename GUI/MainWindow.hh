#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QProgressDialog>
#include <QString>
#include <QThread>

#include "ui_main.h"
#include "ui_about.h"

#include "GUI/CameraMenu.hh"
#include "GUI/Builder.hh"
#include "DataService/Output.hh"
#include "Render/RayTracing.hh"

#include "Controller.hh"

QT_BEGIN_NAMESPACE
class QSlider;
class QLabel;
QT_END_NAMESPACE

namespace Ui {
   class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage getImage();

protected:
    void keyPressEvent(QKeyEvent *event);

private:

    Ui::Main *ui;
    QLabel   screen;
    Output   *outputFile;
    QImage    image;

    Builder    *builder;
    CameraMenu *cameraMenu;

private slots:
    void on_valWidth_valueChanged(int arg1);
    void on_valHeight_valueChanged(int arg1);
    void on_valSamples_valueChanged(int arg1);
    void on_valDepth_valueChanged(int arg1);
    void on_valSoftShadows_stateChanged();
    void on_valNHits_stateChanged();
    void on_valBoundingVolumes_stateChanged();
    void on_valShadows_stateChanged();
    void on_backGround_stateChanged();
    void refreshWindow();
    void aboutMenu();
    void trace();
    void runAnimation();
    void setColorTop();
    void setColorBottom();
};

