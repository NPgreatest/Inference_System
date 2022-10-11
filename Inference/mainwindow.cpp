#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculate_clicked()
{
    Process_Command(ui->textEdit->toPlainText());
}

void MainWindow::Process_Command(QString c)
{
    QStringList x=c.split(" ");
    if(x[0]=="ADDTRUTH"){
        if(x[1].toInt()>=0)
        t.Add_Truth(x[1].toInt(),x[2]);
        Show_Input_1();
    }else if(x[0]=="ADDINFER"){
        QSet<int> t;
        for(int i=1;i<x.size()-1;i++)
            t.insert(x[i].toInt());
        in.Insert_Infer(t,x[x.size()-1].toInt());
        Show_Input_2();
    }else if(x[0]=="INFER"){
        QSet<int> tset;
        for(int i=1;i<x.size();i++)
            tset.insert(x[i].toInt());
        Show_Result(in.Check_Infer(tset,t));
    }else{
        QMessageBox msgBox;
        msgBox.setText("Wrong Command!");
        msgBox.exec();
    }
}


void MainWindow::on_actionAbout_Inference_System_triggered()
{
    help =new helpwindow();
    help->show();
}

void MainWindow::Show_Input_1()
{
    input_1= new QStringListModel(t.Get_Truth());
    ui->Input_1->setModel(input_1);
}

void MainWindow::Show_Input_2()
{
    //if(input_1)input_1->~QStringListModel();
    input_2= new QStringListModel(in.Get_Infer(t));
    ui->Input_2->setModel(input_2);
}

void MainWindow::Show_Result(QStringList res)
{
    //if(output)output->~QStringListModel();
    output= new QStringListModel(res);
    ui->output->setModel(output);
}


void MainWindow::on_actionFrom_File_triggered()
{
    QString Address = QFileDialog::getOpenFileName(this, tr("Choose File"), nullptr, tr("Files (*.txt)"));
    QFile file(Address);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::about(NULL,  "Oops",  "Can not open file");
          return;
    }
    QTextStream in(&file);
    QString line;
    while (in.readLineInto(&line)) {
        Process_Command(line);
    }
}


void MainWindow::on_actionAs_File_2_triggered()
{

    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("Open File"),"/data",tr("Text File(*.txt)"));
    if(fileName == "") return;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("Wrong"),tr("Open File failed"));
        return;
    }
    else
    {
        QTextStream textStream(&file);
        QStringList str =t.Get_Truth_File();
        foreach(QString t, str)
            textStream<<t;
        str=in.Get_Infer_File();
        foreach(QString t, str)
            textStream<<t;
        QMessageBox::warning(this,tr("Tips"),tr("Save Success"));
        file.close();
    }

}


void MainWindow::on_add_clicked()
{
    QStringList x=ui->textEdit->toPlainText().split(" ");
    if(x[0].toInt()>=0){
    t.Add_Truth(x[0].toInt(),x[1]);
    Show_Input_1();
    }
}


void MainWindow::on_add_2_clicked()
{
    QStringList x=ui->textEdit->toPlainText().split(" ");
    QSet<int> t;
    for(int i=0;i<x.size()-1;i++)
        t.insert(x[i].toInt());
    in.Insert_Infer(t,x[x.size()-1].toInt());
    Show_Input_2();
}


void MainWindow::on_diminish_2_clicked()
{
    QStringList list=ui->textEdit->toPlainText().split(" ");
    QSet<int> tar;
    for(int i=0;i<list.size();i++)
        tar.insert(list[i].toInt());
    in.Del_Infer(tar);
    Show_Input_2();
}


void MainWindow::on_diminish_clicked()
{
    int target=ui->textEdit->toPlainText().toInt();
    t.Del_Truth(target);
    Show_Input_1();
}


void MainWindow::on_actionFrom_DataBase_triggered()
{
     QString command;
     query=new QSqlQuery();
     query->prepare("select factor from command");
     bool res = query->exec();
     if(!res){qDebug()<<query->lastQuery();}
     while(query->next()){
        command=query->value("factor").toString();
        Process_Command(command);
     }
     Show_Input_1();
     Show_Input_2();
}


void MainWindow::on_actionAs_File_triggered()
{
    QString command;
    query=new QSqlQuery();
    query->prepare("delete from command");
    bool res = query->exec();
    if(!res){qDebug()<<query->lastQuery();}
    QStringList str =t.Get_Truth_File();
    foreach(QString t, str){
        query->prepare("insert into inference.command (factor)" "values(:command)");
        query->bindValue(":command",t.left(t.size()-1));
        res = query->exec();
        if(!res){qDebug()<<query->lastQuery();}
    }
    str=in.Get_Infer_File();
    foreach(QString t, str){
        query->prepare("insert into inference.command (factor)" "values(:command)");
        query->bindValue(":command",t.left(t.size()-1));
        res = query->exec();
        if(!res){qDebug()<<query->lastQuery();}
    }
}


void MainWindow::on_actionLink_MySql_triggered()
{
    db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("mysql");
        db.setUserName("root");
        db.setPassword("root");
        bool ok = db.open();
        if (ok){
            QMessageBox::information(this, "infor", "link success");
        }
        else {
            QMessageBox::information(this, "infor", "link failed");
        }
}


void MainWindow::on_Infer_clicked()
{
    QStringList x=ui->textEdit->toPlainText().split(" ");
    QSet<int> tset;
    for(int i=0;i<x.size();i++)
        tset.insert(x[i].toInt());
    Show_Result(in.Check_Infer(tset,t));
}


void MainWindow::on_actionChinese_triggered()
{

    tran.load(QString(":/Inference_CN.qm"));
    qApp->installTranslator(&tran);
    ui->retranslateUi(this);


}


void MainWindow::on_actionEnglish_US_triggered()
{
    tran.load(":/Inference_en_US.qm");
    qApp->installTranslator(&tran);
    ui->retranslateUi(this);
}

