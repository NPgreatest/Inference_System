#include "infer.h"

infer::infer()
{

}

void infer::Insert_Infer(QSet<int> key, int value)
{
    in.push_back(QPair<QSet<int>,int>(key,value));
}

void infer::Del_Infer(QSet<int> key)
{
    for(int i=0;i<in.size();i++)
        if(key==in[i].first)
            in.remove(i);
}

QStringList infer::Check_Infer(QSet<int> x,truth &tru)
{
    QStringList res;
    for(int i=0;i<in.size();i++){
        if((x-in[i].first).size()==x.size()-in[i].first.size()){
            QSet<int> t =in[i].first;
            res.push_back("From   ");
            foreach (int value, t){
                res[res.size()-1].append(tru.Check_Truth(value)+"  ");
            }
            res[res.size()-1].append(" to  "+tru.Check_Truth(in[i].second));
            x=x.toList().toSet().subtract(t.intersect(x.toList().toSet()));
            x.insert(in[i].second);
            i=0;
        }
    }
    return res;
}

QStringList infer::Get_Infer(truth &tru)
{
    QStringList res;
    for(int i=0;i<in.size();i++) {
        QString t("From   ");
        QSet<int> tset=in[i].first;
        foreach (int v, tset)
            t.append(tru.Check_Truth(v)+"   ");
        t.append("   to   " +  tru.Check_Truth((in[i].second)));
        res.push_back(t);
    }
    return res;
}

QStringList infer::Get_Infer_File()
{
    QStringList res;
    for(int i=0;i<in.size();i++) {
        QString t("ADDINFER ");
        QSet<int> tset=in[i].first;
        foreach (int v, tset)
            t.append(QString::number(v)+" ");
        t.append( QString::number((in[i].second))+"\n");
        res.push_back(t);
    }
    return res;
}

QSet<int> infer::Check_Infer_Reverse(int x)
{
//    QMap<QSet<int>,int>::const_iterator it = map.constBegin();
//    while (it != map.constEnd()) {
//        if(it.value()==x)return it.key();
//    }
    return QSet<int>();
}
