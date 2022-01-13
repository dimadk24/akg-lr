#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//Класс главного окна
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    //Обработчик события нажатия на кнопку "Обновить"
    void on_pushButton_clicked();

    //Вращение по оси Х
    void on_horizontalSlider_X_actionTriggered();
    //Вращение по оси Y
    void on_horizontalSlider_Y_actionTriggered();
    //Вращение по оси Z
    void on_horizontalSlider_Z_actionTriggered();
};
#endif // MAINWINDOW_H
