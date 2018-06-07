#ifndef MODELDATA_H
#define MODELDATA_H
#include<string>
#include<gl/glut.h>
#include<qstring.h>
#include<QList>
#define MAX_TEXTURE 1024
using namespace std;
//材质
struct  Material
{
    size_t index_Material;//当前的材质的索引,代表在model中的集合中的第几个
    QString materialName;

    GLfloat mat_ambient[4]  = { 0.192250f, 0.192250f, 0.192250f, 1.000000f};
    GLfloat mat_diffuse[4]  = { 0.507540f, 0.507540f, 0.507540f, 1.000000f};
    GLfloat mat_specular[4] = { 0.508273f, 0.508273f, 0.508273f, 1.000000f};
    GLfloat mat_emission[4] = {0.0f, 0.0f, 0.0f, 1.0f};//本身颜色
    GLfloat mat_shininess  = 51.200001f;//反光

    QString imageName;//图片的路径名称，此处应为完整路径
    QString imagePath;//纹理路径
    void preSet(double mat[])
    {
        mat_ambient[0]=mat[0];mat_ambient[1]=mat[1];mat_ambient[2]=mat[2];mat_ambient[3]=mat[3];
        mat_diffuse[0]=mat[4];mat_diffuse[1]=mat[5];mat_diffuse[2]=mat[6];mat_diffuse[3]=mat[7];
        mat_specular[0]=mat[8];mat_specular[1]=mat[9];mat_specular[2]=mat[10];mat_specular[3]=mat[11];
        mat_shininess=mat[12];
    }
};
struct Light
{
    GLfloat light_position[4]={100.0,100.0,100.0,0.0};
    GLfloat light_ambient[4]={0.0f, 0.0f, 0.0f, 1.0f}; //环境光
    GLfloat light_diffuse[4]= {1.0f, 1.0f, 1.0f, 1.0f};//漫反射
    GLfloat light_specular[4]= {1.0f, 1.0f, 1.0f, 1.0f};//镜面反射
    void preSet(double light[])
    {
        light_ambient[0]=light[0];light_ambient[1]=light[1];light_ambient[2]=light[2];light_ambient[3]=light[3];
        light_diffuse[0]=light[4];light_diffuse[1]=light[5];light_diffuse[2]=light[6];light_diffuse[3]=light[7];
        light_specular[0]=light[8];light_specular[1]=light[9];light_specular[2]=light[10];light_specular[3]=light[11];
        light_position[0]=light[12];light_position[1]=light[13];light_position[2]=light[14];light_position[3]=light[15];
    }
};

//节点
struct Point3
{
    GLfloat PX;
    GLfloat PY;
    GLfloat PZ;
};
//节点法向量
struct VertNormals
{
    GLfloat VNX;
    GLfloat VNY;
    GLfloat VNZ;
};
//节点纹理坐标
struct TextCoords
{
    GLfloat U;
    GLfloat V;
};

struct FacetNormal
{
    GLfloat NX;
    GLfloat NY;
    GLfloat NZ;
    FacetNormal operator +(FacetNormal fn)
    {
        fn.NX+=NX;
        fn.NY+=NY;
        fn.NZ+=NZ;
        return fn;
    }
    FacetNormal& operator +=(FacetNormal fn)
    {
        *this=*this+fn;
        return *this;
    }
};

struct Face
{
    QString materialName;//对应材质名称

    int index_Face;//平面法向量的索引
    int index_Text;//
    int index_Name;//pickname

    QList<int> list_index_Points;//面的点集合在model中的索引
    QList<int> list_index_TextCoords;//
    QList<int> list_index_VertNormals;

};
#endif // MODELDATA_H
