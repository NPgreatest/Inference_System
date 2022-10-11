#include "truth.h"

truth::truth()
{

}

void truth::Add_Truth(int x, QString name)
{
    hash.insert(x,name);
}

QString truth::Check_Truth(int x)
{
    return hash.find(x)==hash.end()?QString::number(x):hash.find(x).value();
}

QStringList truth::Get_Truth()
{
    QStringList res;
    QHash<int,QString>::const_iterator i = hash.constBegin();
    while (i != hash.constEnd()) {
        res.push_back(QString::number(i.key()) +" is " +i.value());
        i++;
    }
    return res;
}

QStringList truth::Get_Truth_File()
{
    QStringList res;
    QHash<int,QString>::const_iterator i = hash.constBegin();
    while (i != hash.constEnd()) {
        res.push_back("ADDTRUTH "+QString::number(i.key()) +" " +i.value()+"\n");
        i++;
    }
    return res;
}

void truth::Del_Truth(int x)
{
    if(hash.find(x)==hash.end())return;
    hash.erase(hash.find(x));
}

int truth::Check_Key(QString name)
{
    QHash<int,QString>::const_iterator it = hash.constBegin();
    while (it != hash.constEnd()) {
        if(it.value()==name)return it.key();
    }
    return -1;
}
