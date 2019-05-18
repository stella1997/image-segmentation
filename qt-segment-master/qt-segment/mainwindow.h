#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <QImage>

#include <QRgb>

#include <QElapsedTimer>
#include <QFileDialog>
#include <QResizeEvent>

#include <QMessageBox>

#include "utility.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setImage(QImage im);
    void refresh();
    
private slots:
    void on_sigmaSlider_valueChanged(int value);

    void on_thresholdSlider_valueChanged(int value);

    void on_minSizeSlider_valueChanged(int value);

    void on_actionOpen_triggered();

    void on_actionShow_original_triggered(bool checked);

    void on_actionSave_segmented_as_triggered();

    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QImage im;
    QImage res;
    QGraphicsScene * sceneTo;
    bool showOriginal;
};
#endif // MAINWINDOW_H
