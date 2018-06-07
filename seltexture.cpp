#include "seltexture.h"
#include "ui_seltexture.h"

selTexture::selTexture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selTexture)
{
    ui->setupUi(this);
}

selTexture::~selTexture()
{
    delete ui;
}
