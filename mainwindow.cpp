#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"materials.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("打开"),
            "",
            tr("obj文件 (*.obj)"),
            0);
        if (!fileName.isNull())
        {
            if(!ui->openGLWidget->openOBJFile(fileName))
                QMessageBox::warning(NULL, "warning", "打开失败", QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {

        }
}

void MainWindow::on_point_triggered()
{
    ui->openGLWidget->showMode=0;
    ui->openGLWidget->update();
}

void MainWindow::on_line_triggered()
{
    ui->openGLWidget->showMode=1;
    ui->openGLWidget->update();
}

void MainWindow::on_face_triggered()
{
    ui->openGLWidget->showMode=2;
    ui->openGLWidget->update();
}

void MainWindow::on_loadTex_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("打开"),
            "",
            tr("bmp文件 (*.bmp)"),
            0);
        if (!fileName.isNull())
        {
            int texID=ui->openGLWidget->loadTex(fileName);
            if(texID==0)
                QMessageBox::warning(NULL, "warning", "打开失败", QMessageBox::Yes, QMessageBox::Yes);
            else
            {
                int size=ui->openGLWidget->list_ImagePath.size();
                ui->openGLWidget->list_ImagePath.push_back(fileName);
                ui->openGLWidget->textureArray[size]=texID;
            }
        }
        else
        {

        }

}

void MainWindow::on_showTex_triggered()
{
    if(!ui->openGLWidget->texMode)
        ui->showTex->setText("关闭贴图");
    else
        ui->showTex->setText("显示贴图");
    ui->openGLWidget->texMode=!ui->openGLWidget->texMode;
    ui->openGLWidget->update();
}

void MainWindow::on_setLight_triggered()
{
    if(!ui->openGLWidget->lightmode)
        ui->setLight->setText("关闭灯光");
    else
        ui->setLight->setText("打开灯光");
    ui->openGLWidget->lightmode=!ui->openGLWidget->lightmode;
    ui->openGLWidget->update();
}

void MainWindow::on_action_3_triggered()
{
    ui->openGLWidget->mat.preSet(brass);
    ui->openGLWidget->update();
}

void MainWindow::on_action_4_triggered()
{
    ui->openGLWidget->mat.preSet(bronze);
    ui->openGLWidget->update();
}

void MainWindow::on_action_5_triggered()
{
    ui->openGLWidget->mat.preSet(litbrin);
    ui->openGLWidget->update();
}

void MainWindow::on_action_6_triggered()
{
    ui->openGLWidget->mat.preSet(chrome);
    ui->openGLWidget->update();
}

void MainWindow::on_action_7_triggered()
{
    ui->openGLWidget->mat.preSet(copper);
    ui->openGLWidget->update();
}

void MainWindow::on_action_8_triggered()
{
    ui->openGLWidget->mat.preSet(lightCo);
    ui->openGLWidget->update();
}

void MainWindow::on_action_9_triggered()
{
    ui->openGLWidget->mat.preSet(gold);
    ui->openGLWidget->update();
}

void MainWindow::on_action_10_triggered()
{
    ui->openGLWidget->mat.preSet(lightGold);
    ui->openGLWidget->update();
}

void MainWindow::on_action_11_triggered()
{
    ui->openGLWidget->mat.preSet(wax);
    ui->openGLWidget->update();
}

void MainWindow::on_action_12_triggered()
{
    ui->openGLWidget->mat.preSet(sliver);
    ui->openGLWidget->update();
}

void MainWindow::on_action_13_triggered()
{
    ui->openGLWidget->mat.preSet(lightSl);
    ui->openGLWidget->update();
}

void MainWindow::on_action_14_triggered()
{
    ui->openGLWidget->mat.preSet(jadeite);
    ui->openGLWidget->update();
}

void MainWindow::on_action_15_triggered()
{
    ui->openGLWidget->mat.preSet(greJade);
    ui->openGLWidget->update();
}

void MainWindow::on_action_16_triggered()
{
    ui->openGLWidget->mat.preSet(obsidian);
    ui->openGLWidget->update();
}

void MainWindow::on_action_17_triggered()
{
    ui->openGLWidget->mat.preSet(pearl);
    ui->openGLWidget->update();
}

void MainWindow::on_action_18_triggered()
{
    ui->openGLWidget->mat.preSet(ruby);
    ui->openGLWidget->update();
}

void MainWindow::on_action_19_triggered()
{
    ui->openGLWidget->mat.preSet(beryl);
    ui->openGLWidget->update();
}

void MainWindow::on_action_20_triggered()
{
    ui->openGLWidget->mat.preSet(blackPlastic);
    ui->openGLWidget->update();
}

void MainWindow::on_action_21_triggered()
{
    ui->openGLWidget->mat.preSet(blackRubber);
    ui->openGLWidget->update();
}

void MainWindow::on_action_22_triggered()
{
    ui->openGLWidget->mat.preSet(violet);
    ui->openGLWidget->update();
}
