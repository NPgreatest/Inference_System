#include "helpwindow.h"
#include "ui_helpwindow.h"

helpwindow::helpwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::helpwindow)
{
    ui->setupUi(this);
}

helpwindow::~helpwindow()
{
    delete ui;
}

void helpwindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com", QUrl::TolerantMode));
}

