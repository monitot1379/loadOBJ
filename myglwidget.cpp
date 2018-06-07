#include<qdebug.h>
#include<tchar.h>
#include<errno.h>
#include "myglwidget.h"
#include"light.h"
#define BMP_Header_Length 54
using namespace std;
double rotateX=0,rotateY=0;
double rotCopyX=0,rotCopyY=0;
int pressPos[2];
double WindowWidth,WindowHeight;
const double Pi=3.1415926535897932484626;
double eyeR=200;
myGLWidget::myGLWidget(QWidget *parent)
        : QOpenGLWidget(parent)
{

}
myGLWidget::~myGLWidget()
{

}
bool myGLWidget::openOBJFile(QString filename)
{
    //delete objFile;
    rotateX=0;rotateY=0;
    objFile=glReadOBJ(filename);
    update();
    return (objFile==NULL)? false:true;
}

void myGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        rotateX=rotCopyX-((event->x()-pressPos[0])*0.1);
        rotateY=rotCopyY+((event->y()-pressPos[1])*0.1);
        if(rotateY>90)
            rotateY=90;
        if(rotateY<-90)
            rotateY=-90;
    }
    update();
}

void myGLWidget::wheelEvent(QWheelEvent *event)
{
    double radio = 4.0;
    if(event->delta() < 0)
    {
        eyeR = (eyeR >= 400) ? eyeR : eyeR + radio;
    }
    else
    {
        eyeR = (eyeR <= 0.1) ? eyeR : eyeR - radio;
    }
    update();
}

void myGLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        pressPos[0]=event->x();
        pressPos[1]=event->y();
        rotCopyX=rotateX;
        rotCopyY=rotateY;

    }
}

void myGLWidget::drawScreen()
{
    switch(showMode)
    {
    case 0:
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    }
    case 1:
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    }
    case 2:
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }
    }

    if(objFile==NULL)
        return;
    //mat.preSet(supLight);
    glSetMaterial(mat);
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    bool TexIsReady=false;
    if(texMode&&list_ImagePath.size()!=0&&objFile->num_Textcoords!=0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureArray[list_ImagePath.size()-1]);
        TexIsReady=true;
    }

    for (size_t i = 0; i < objFile->num_Faces; i++)
    {
        Face f = objFile->list_Faces.at(i);

        glBegin(GL_POLYGON);
        for (int k = 0; k < f.list_index_Points.size(); k++)
        {
            if(TexIsReady)
            {
                TextCoords tx=objFile->list_Textcoords.at(f.list_index_TextCoords.at(k));
                glTexCoord2f(tx.U,tx.V);
            }
            if(f.list_index_VertNormals.size()>0)
            {
                VertNormals vn = objFile->list_Normals.at(f.list_index_VertNormals.at(k));
                glNormal3f(vn.VNX, vn.VNY, vn.VNZ);
            }
            else if(!objFile->list_FaceNormal.empty())
            {
                FacetNormal fn = objFile->list_FaceNormal.at(f.list_index_Points.at(k));
                float cross[3];
                cross[0]=fn.NX;cross[1]=fn.NY;cross[2]=fn.NZ;
                vNormal(cross);
                //glNormal3f(fn.NX,fn.NY,fn.NZ);
                glNormal3fv(cross);
            }
            Point3 p = objFile->list_Vertices.at(f.list_index_Points.at(k));
            glVertex3f(p.PX, p.PY, p.PZ);
        }
        glEnd();
    }
    glPopMatrix();
}

void myGLWidget::initializeGL()
{
    glClearColor(0.0,0.0,0.0,0.0);
    objFile=NULL;
}

void myGLWidget::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, WindowWidth / WindowHeight, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeR*cos(rotateY*Pi/180)*sin(rotateX*Pi/180),
              eyeR*sin(rotateY*Pi/180) ,
              eyeR*cos(rotateY*Pi/180)*cos(rotateX*Pi/180),
              0, 0, 0, 0, 1, 0);
    Light lit0;
    Light lit1;
    if(lightmode)
    {
        lit1.preSet(supLight);
        lit0.preSet(supLight2);
    }
    else
    {
        lit0.preSet(blacklight);
        lit1.preSet(blacklight);
    }
    setLight(lit0,0);
    setLight(lit1,1);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    drawScreen();
}
void myGLWidget::resizeGL(int w, int h)
{
    qDebug()<<"resize";
    WindowWidth=w;
    WindowHeight=h;
    glViewport(0,0,(GLint)w,(GLint)h);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(100, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //gluLookAt(0, 150, 150, 0, 50, 0, 0, 1, 0);
}
void myGLWidget::setLight(Light l, int num)
{
    if(num<0||num>7)
        return;
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    glLightfv(GL_LIGHT0+num, GL_POSITION, l.light_position);
    glLightfv(GL_LIGHT0+num, GL_AMBIENT,  l.light_ambient);
    glLightfv(GL_LIGHT0+num, GL_DIFFUSE,  l.light_diffuse); //漫反射
    glLightfv(GL_LIGHT0+num, GL_SPECULAR, l.light_specular);//镜面反射
}
int power_of_two(int n)
{
    if (n <= 0)
        return 0;
    return (n & (n - 1)) == 0;
}
GLuint myGLWidget::loadTex(QString filename)
{
    GLint width=0, height=0, total_bytes=0;
    GLubyte* pixels = 0;
    GLint last_texture_ID;
    GLuint texture_ID = 0;
    // 打开文件，如果失败，返回
    FILE* pFile = _wfopen(filename.toStdWString().c_str(), L"rb");
    qDebug()<<errno;
    if (pFile == 0)
        return 0;
    // 读取文件中图象的宽度和高度
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);
    // 计算每行像素所占字节数，并根据此数据计算总像素字节数
    {
        GLint line_bytes = width * 3;
        while (line_bytes % 4 != 0)
            ++line_bytes;
        total_bytes = line_bytes * height;
    }
    qDebug()<<width<<height;
    // 根据总像素字节数分配内存
    pixels = (GLubyte*)malloc(total_bytes);
    if (pixels == 0)
    {
        fclose(pFile);
        return 0;
    }

    // 读取像素数据
    if (fread(pixels, total_bytes, 1, pFile) <= 0)
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    {
        GLint max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
        if (!power_of_two(width)
            || !power_of_two(height)
            || width > max
            || height > max)
        {
            const GLint new_width = 256;
            const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;

            // 计算每行需要的字节数和总字节数
            new_line_bytes = new_width * 3;
            while (new_line_bytes % 4 != 0)
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;

            // 分配内存
            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if (new_pixels == 0)
            {
                free(pixels);
                fclose(pFile);
                return 0;
            }

            // 进行像素缩放
            gluScaleImage(GL_RGB,
                width, height, GL_UNSIGNED_BYTE, pixels,
                new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

            // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
            free(pixels);
            pixels = new_pixels;
            width = new_width;
            height = new_height;
        }
    }

    // 分配一个新的纹理编号
    glGenTextures(1, &texture_ID);
    if (texture_ID == 0)
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, last_texture_ID);

    free(pixels);
    return texture_ID;
}


