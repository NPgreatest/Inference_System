#ifndef INFER_H
#define INFER_H
#include<QVector>
#include<QMap>
#include<QSet>
#include<QString>
#include"truth.h"
class infer
{
private:
    QVector<QPair<QSet<int>,int>> in;
public:
    infer();
    void Insert_Infer(QSet<int> key,int value);
    void Del_Infer(QSet<int> key);
    QStringList Check_Infer(QSet<int> x,truth &tru);
    QStringList Get_Infer(truth &tru);
    QStringList Get_Infer_File();
    QSet<int> Check_Infer_Reverse(int x);
};

#endif // INFER_H
