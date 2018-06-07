#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include<QDialog>
#include<QMessageBox>
#include<QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open_triggered();

    void on_point_triggered();

    void on_line_triggered();

    void on_face_triggered();

    void on_loadTex_triggered();

    void on_showTex_triggered();

    void on_setLight_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_8_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_action_11_triggered();

    void on_action_12_triggered();

    void on_action_13_triggered();

    void on_action_14_triggered();

    void on_action_15_triggered();

    void on_action_16_triggered();

    void on_action_17_triggered();

    void on_action_18_triggered();

    void on_action_19_triggered();

    void on_action_20_triggered();

    void on_action_21_triggered();

    void on_action_22_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
