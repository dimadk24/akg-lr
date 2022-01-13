#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool converted_r, converted_phi, converted_theta;
    double r = ui->lineEdit->text().toDouble(&converted_r);
    double phi = ui->lineEdit_2->text().toDouble(&converted_phi);
    double theta = ui->lineEdit_3->text().toDouble(&converted_theta);
    if(!converted_r || !converted_phi || !converted_theta){
        QMessageBox::critical(this, "Ошибка", "Некорректный ввод");
        return;
    }
    SphereToPoint3D(r, phi, theta, ui->openglwidget->eye_point);
    ui->openglwidget->update();
}

void MainWindow::on_horizontalSlider_X_actionTriggered()
{
    ui->openglwidget->cube.Rotate((ui->horizontalSlider_X->value() - ui->openglwidget->rotate_x) / 10.0, X);
    ui->openglwidget->rotate_x = ui->horizontalSlider_X->value();
    ui->openglwidget->update();
}

void MainWindow::on_horizontalSlider_Y_actionTriggered()
{
    ui->openglwidget->cube.Rotate((ui->horizontalSlider_Y->value() - ui->openglwidget->rotate_y) / 10.0, Y);
    ui->openglwidget->rotate_y = ui->horizontalSlider_Y->value();
    ui->openglwidget->update();
}

void MainWindow::on_horizontalSlider_Z_actionTriggered()
{
    ui->openglwidget->cube.Rotate((ui->horizontalSlider_Z->value() - ui->openglwidget->rotate_z) / 10.0, Z);
    ui->openglwidget->rotate_z = ui->horizontalSlider_Z->value();
    ui->openglwidget->cube.CheckVisibility(ui->openglwidget->eye_point);
    ui->openglwidget->update();
}
