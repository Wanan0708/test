#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPalette>
#include "elevator.h"
#include <QAbstractButton>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void iniElevator();

    void dealIn(QAbstractButton*);
    void dealUp(QAbstractButton*);
    void dealDown(QAbstractButton*);

public:
    Elevator *e1;
    QList<int> upList;
    QList<int> downList;

private slots:

    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();
    void onFloorChanged();



private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
