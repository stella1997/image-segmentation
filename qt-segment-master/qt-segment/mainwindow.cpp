#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    showOriginal = false;
    ui->setupUi(this);
    this->sceneTo = new QGraphicsScene(this);
    ui->graphicsViewTo->setScene(this->sceneTo);
    this->refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setImage(QImage im)
{
    this->im = im;
    this->refresh();
}

void MainWindow::refresh() {
    statusBar()->showMessage("Processing...");
    QElapsedTimer timer;
    timer.start();

    float sigma = this->ui->sigmaSlider->value() * 0.05;
    this->ui->sigmaVal->setText(QString().setNum(sigma));
    float k = this->ui->thresholdSlider->value();
    this->ui->thresholdVal->setText(QString().setNum(k));
    int min_size = this->ui->minSizeSlider->value();
    this->ui->minSizeVal->setText(QString().setNum(min_size));

    if (showOriginal) {
        QPixmap pixmapFrom = QPixmap::fromImage(im);
        this->sceneTo->clear();
        this->sceneTo->addPixmap(pixmapFrom);
        this->sceneTo->setSceneRect(0, 0, pixmapFrom.width(), pixmapFrom.height());

        statusBar()->showMessage("");
    } else {
        image <rgb> *input = Utility::qImageToImage(im);

        int num_ccs;
        image<rgb> *seg = Utility::segmentImage(input, sigma, k, min_size, &num_ccs);
        res = Utility::imageToQImage(seg);

        delete input;
        delete seg;

        QPixmap pixmapTo = QPixmap::fromImage(res);
        this->sceneTo->clear();
        this->sceneTo->addPixmap(pixmapTo);

        qint64 overall = timer.elapsed();
        statusBar()->showMessage(QString("Number of components: ") + QString().setNum(num_ccs) + "    Overall processing time: " + QString().setNum(overall) + QString("ms"));
    }


}


void MainWindow::on_sigmaSlider_valueChanged(int value)
{
    this->refresh();
}

void MainWindow::on_thresholdSlider_valueChanged(int value)
{
    this->refresh();
}

void MainWindow::on_minSizeSlider_valueChanged(int value)
{
    this->refresh();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open image...", QString(), "Image Files (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm);;All files (*.*)");
    this->setImage(QImage(filename));
    this->refresh();
}

void MainWindow::on_actionShow_original_triggered(bool checked)
{
    showOriginal = checked;
    this->refresh();
}

void MainWindow::on_actionSave_segmented_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save segmented image as...", QString(), "Image Files (*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    res.save(filename);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "This software has been implemented by Sebastien Drouyer and is under MIT license.\nhttps://github.com/sdrdis/qt-segment\n\nThis software is derived from \"Efficient Graph-Based Image Segmentation\" by Pedro F. Felzenszwalb and Daniel P. Huttenlocher.\nhttp://cs.brown.edu/~pff/segment/");
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
