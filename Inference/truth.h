#ifndef TRUTH_H
#define TRUTH_H
#include<QHash>
#include<QString>
class truth
{

     QHash<int,QString> hash;
public:
    truth();
    void Add_Truth(int x,QString name);
    QString Check_Truth(int x);
    QStringList Get_Truth();
    QStringList Get_Truth_File();
    void Del_Truth(int x);
    int Check_Key(QString name);
};

#endif // TRUTH_H
