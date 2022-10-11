#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QStringListModel>
#include<QFileDialog>
#include<QTranslator>
#include<QSettings>
#include<QFile>
#include<QSqlQuery>
#include<QTextStream>
#include"helpwindow.h"
#include"truth.h"
#include"infer.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculate_clicked();
    void Process_Command(QString c);
    void on_actionAbout_Inference_System_triggered();

    void on_actionFrom_File_triggered();

    void on_actionAs_File_2_triggered();

    void on_add_clicked();

    void on_add_2_clicked();

    void on_diminish_2_clicked();

    void on_diminish_clicked();

    void on_actionFrom_DataBase_triggered();

    void on_actionAs_File_triggered();

    void on_actionLink_MySql_triggered();

    void on_Infer_clicked();

    void on_actionChinese_triggered();

    void on_actionEnglish_US_triggered();

private:
    Ui::MainWindow *ui;
    truth t;
    infer in;
    helpwindow *help;
    QStringListModel *input_1,*input_2,*output;
    QSqlQuery *query;
    QSqlDatabase db;
    void Show_Input_1();
    void Show_Input_2();
    QTranslator tran;
    void Show_Result(QStringList res);
};
#endif // MAINWINDOW_H
