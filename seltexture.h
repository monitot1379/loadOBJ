#ifndef SELTEXTURE_H
#define SELTEXTURE_H

#include <QDialog>

namespace Ui {
class selTexture;
}

class selTexture : public QDialog
{
    Q_OBJECT

public:
    explicit selTexture(QWidget *parent = 0);
    ~selTexture();

private:
    Ui::selTexture *ui;
};

#endif // SELTEXTURE_H
