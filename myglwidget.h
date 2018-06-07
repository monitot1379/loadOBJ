#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QWidget>
#include <QOpenGLWidget>
#include <gl/glut.h>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include<cmath>
#include"objmodel.h"
#include<iostream>
using namespace std;
class myGLWidget : public QOpenGLWidget
{
public:
    myGLWidget(QWidget *parent=0);
    ~myGLWidget(); 
    bool openOBJFile(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void drawScreen();
    void setLight(Light l,int num);
    GLuint loadTex(QString filename);
    QList<QString> list_ImagePath;//贴图路径集合
    int textureArray[MAX_TEXTURE];//注册纹理数组
    int showMode=0;//0 point mode 1 line mode 2 face mode
    bool texMode=false;//0 no texture
    bool lightmode=false;//0 no light
    Material mat;
protected:
     OBJModel *objFile;
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    Material axisMat(int mode);
};

#endif // MYGLWIDGET_H
