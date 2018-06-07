#include "objmodel.h"
#include<QFile>
#include<QFileDevice>
#include<QDebug>
OBJModel::OBJModel()
{

}
QString glGetDir(QString filePath)
{
    int index = filePath.lastIndexOf('\\');
    if (index == -1)
        index = filePath.lastIndexOf('/');
    filePath.remove(index + 1, filePath.length() - index - 1);
    return filePath;
}
void glReadMTL(OBJModel *model,QString filename)
{

}

OBJModel* glReadOBJ(QString filename)
{
    QFile file(filename);
    qDebug()<<file.exists();
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug("error!!");
        return NULL;
    }
    qDebug()<<"yep!!";
    QString dirPath=glGetDir(filename);
    QStringList list; QString currentMaterialName;
    OBJModel *model=new OBJModel();
    QString split = ' ';
    model->path=filename;
    model->num_Faces=0;
    model->num_Normals=0;
    model->num_Textcoords=0;
    model->num_Vertices=0;
    Point3 *v;
    TextCoords *vt;
    VertNormals *vn;
    Face *f;
    Material defaultMat;
    FacetNormal defaultFN;
    defaultFN.NX=0;defaultFN.NY=0;defaultFN.NZ=0;
    model->list_Materials.push_back(defaultMat);
    model->num_Materials++;
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        /*qDebug()<<count;//debug!!
        count++;*/
        if(str.size()<2)
            continue;
        if(str[0]=='m')
        {
            QStringList str0 = str.split(' ');
            QString mtlname = str0[1];
            mtlname = mtlname.trimmed();//去掉空格
            dirPath.append(mtlname);
            model->mtllibName = dirPath;
        }
        else if(str[0]=='v')
        {
            if(str[1]=='t')//vt 为材质
            {
                list = str.split(split,QString::SkipEmptyParts);
                vt = new TextCoords();
                vt->U = list[1].toFloat(); vt->V = list[2].toFloat();
                model->num_Textcoords++;
                model->list_Textcoords.push_back(*vt);
            }
            else if(str[1]=='n')//vn为法向量
            {
                list = str.split(split,QString::SkipEmptyParts);
                vn = new VertNormals();
                vn->VNX = list[1].toFloat(); vn->VNY = list[2].toFloat(); vn->VNZ = list[3].toFloat();
                model->num_Normals++;
                model->list_Normals.push_back(*vn);
            }
            else
            {
                //qDebug()<<"readPoint";//debug!!
                list = str.split(split,QString::SkipEmptyParts);
                v = new Point3();
                v->PX = list[1].toFloat(); v->PY = list[2].toFloat(); v->PZ = list[3].toFloat();
                model->num_Vertices++;
                model->list_Vertices.push_back(*v);
                model->list_FaceNormal.push_back(defaultFN);
            }
        }
        else if (str[0] == 'u')//材质的名称
        {
            list = str.split(split,QString::SkipEmptyParts);
            currentMaterialName = list[1];
        }
        else if (str[0] == 'f')//面
        {
            str = str.trimmed();
            list = str.split(split,QString::SkipEmptyParts);

            f = new Face();
            f->materialName = currentMaterialName;

            if (list[1].contains('/'))
            {

                for (int i = 1; i < list.length(); i++)
                {
                    QStringList sublist = list[i].split('/');
                    f->list_index_Points.push_back(sublist[0].toInt() - 1);
                    f->list_index_TextCoords.push_back(sublist[1].toInt() - 1);
                    if (list[1].split('/').length() == 3)//只有v和vt
                    {
                        f->list_index_VertNormals.push_back(sublist[2].toInt() - 1);
                    }
                }
            }
            else//不包括/，那么只有节点
            {
                for (int i = 1; i < list.length(); i++)
                {
                    f->list_index_Points.push_back(list[i].toInt() - 1);
                }
            }
            model->num_Faces++;
            model->list_Faces.push_back(*f);
        }
    }
    glFacetNormals(model);
    return model;
}
void glFacetNormals(OBJModel* model)
{
    FacetNormal fn;
    float u[3];
    float v[3];
    float cross[3];

    for (int i = 0; i < model->list_Faces.length(); i++)
    {
        Face f=model->list_Faces.at(i);
        Point3 p0 = model->list_Vertices.at(f.list_index_Points[0]);
        Point3 p1 = model->list_Vertices.at(f.list_index_Points[1]);
        Point3 pn = model->list_Vertices.at(f.list_index_Points.at(model->list_Faces.at(i).list_index_Points.length() - 1));//最后一点

        u[0] = p1.PX - p0.PX;
        u[1] = p1.PY - p0.PY;
        u[2] = p1.PZ - p0.PZ;

        v[0] = pn.PX - p0.PX;
        v[1] = pn.PY - p0.PY;
        v[2] = pn.PZ - p0.PZ;

        vCross(u, v, cross);

        model->list_Faces[i].index_Face = i;
        fn.NX = cross[0];
        fn.NY = cross[1];
        fn.NZ = cross[2];
        for(int j = 0; j < f.list_index_Points.length(); j++)
        {
            cross[0]+=model->list_FaceNormal[f.list_index_Points[j]].NX;
            cross[1]+=model->list_FaceNormal[f.list_index_Points[j]].NY;
            cross[2]+=model->list_FaceNormal[f.list_index_Points[j]].NZ;
            vNormal(cross);
            model->list_FaceNormal[f.list_index_Points[j]].NX+=cross[0];
            model->list_FaceNormal[f.list_index_Points[j]].NY+=cross[1];
            model->list_FaceNormal[f.list_index_Points[j]].NZ+=cross[2];
        }
    }
}

void glSetMaterial(Material m)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT,   m.mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   m.mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  m.mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  m.mat_emission);//镜面指数
    glMaterialf (GL_FRONT, GL_SHININESS, m.mat_shininess);//颜色
}
