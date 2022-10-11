#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>
#include<QDesktopServices>
#include<QString>
#include<QUrl>
namespace Ui {
class helpwindow;
}

class helpwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit helpwindow(QWidget *parent = nullptr);
    ~helpwindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::helpwindow *ui;
};

#endif // HELPWINDOW_H
