#ifndef OBJMODEL_H
#define OBJMODEL_H
#include"modeldata.h"
#include"mathfunc.h"
class OBJModel
{
public:
    OBJModel();
    QString path;//obj文件路径
    QString mtllibName;//材质文件名称
    size_t num_Vertices;//节点个数
    size_t num_Normals;//节点向量的个数
    size_t num_Textcoords;//节点纹理坐标个数
    size_t num_Materials;//材质个数
    size_t num_Faces;//面的个数

    QList<Point3> list_Vertices;//节点对象集合
    QList<VertNormals> list_Normals;//节点向量集合
    QList<TextCoords> list_Textcoords;//纹理坐标集合
    QList<Face> list_Faces;//面集合
    QList<Material> list_Materials;//材质集合
    QList<FacetNormal> list_FaceNormal;//面向量集合

    //GLfloat Center[3];//进行归一化之后的坐标中心


};
OBJModel* glReadOBJ(QString filename);
QString glGetDir(QString filePath);
void glReadMTL(OBJModel *model,QString filename);
void glFacetNormals(OBJModel* model);
void glSetMaterial(Material m);
#endif // OBJMODEL_H
