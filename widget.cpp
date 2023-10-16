#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("elevator");

    e1 = new Elevator();

    connect(ui->buttonGroup_chooseFloor,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,&Widget::dealIn);
    connect(ui->buttonGroup_up,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,&Widget::dealUp);
    connect(ui->buttonGroup_down,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,&Widget::dealDown);
    connect(e1,&Elevator::floorChanged,this,&Widget::onFloorChanged);
    ui->label_floor->setText("第 " + QString::number(e1->currentFloor) + " 层");

    iniElevator();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::iniElevator()
{
    e1->currentFloor = 1;
    e1->running = false;
    e1->uping = false;
    e1->downing = false;
    e1->opening = false;
    e1->closeing = false;
    e1->opened = false;
    e1->closed = true;
    ui->pushButton_01->setStyleSheet("background-color:yellow");
}

void Widget::dealIn(QAbstractButton* button)
{
    qDebug() << button->text();
    int destinationFloor = button->text().toInt();
    if(destinationFloor > e1->currentFloor)
    {
        e1->eDown(destinationFloor - e1->currentFloor);
    }
    else if(destinationFloor < e1->currentFloor)
    {
        e1->eUp(e1->currentFloor - destinationFloor);
    }
    else
    {
        qDebug() << "当前在第 " << e1->currentFloor << " 层";
    }
    e1->eMoveTo(destinationFloor);
    if(button->isChecked())
    {
        button->setChecked(false);
    }
}

void Widget::dealUp(QAbstractButton* button)
{
    qDebug() << button->property("upId").toInt();
    while (!e1->idleing) {
//        QEventLoop loop;
//        QTimer::singleShot(1000, &loop, SLOT(quit()));
//        loop.exec();
        continue;
    }
    int moveToFloorId = button->property("upId").toInt();;
    if(e1->currentFloor > moveToFloorId)
    {
        e1->eDown(moveToFloorId);
    }
    else if (e1->currentFloor < moveToFloorId)
    {
        e1->eUp(moveToFloorId);
    }
    else
    {
        qDebug() << "当前在第 " << e1->currentFloor << " 层";

    }

    e1->opening = true;
    qDebug() << "opening";
    QEventLoop loop1;
    QTimer::singleShot(1000, &loop1, SLOT(quit()));
    loop1.exec();
    e1->opened = true;
    e1->opening = false;
    qDebug() << "opened";
    QEventLoop loop2;
    QTimer::singleShot(1000, &loop2, SLOT(quit()));
    loop2.exec();
    e1->closeing = true;
    e1->opened = false;
    qDebug() << "closeing";
    QEventLoop loop3;
    QTimer::singleShot(1000, &loop3, SLOT(quit()));
    loop3.exec();
    e1->closed = true;
    qDebug() << "closed";
    if (button->isChecked())
    {
        button->setChecked(false);
    }
}

void Widget::dealDown(QAbstractButton* button)
{
    qDebug() << button->property("downId").toInt();
    while (!e1->idleing) {
//        QEventLoop loop;
//        QTimer::singleShot(1000, &loop, SLOT(quit()));
//        loop.exec();
        continue;
    }
    int downToFloorId = button->property("downId").toInt();
    if(e1->currentFloor > downToFloorId)
    {
        e1->eDown(downToFloorId);
    }
    else if (e1->currentFloor < downToFloorId)
    {
        e1->eUp(downToFloorId);
    }
    else
    {
        qDebug() << "当前在第 " << e1->currentFloor << " 层";
    }

    e1->opening = true;
    qDebug() << "opening";
    QEventLoop loop1;
    QTimer::singleShot(1000, &loop1, SLOT(quit()));
    loop1.exec();
    e1->opened = true;
    e1->opening = false;
    qDebug() << "opened";
    QEventLoop loop2;
    QTimer::singleShot(1000, &loop2, SLOT(quit()));
    loop2.exec();
    e1->closeing = true;
    e1->opened = false;
    qDebug() << "closeing";
    QEventLoop loop3;
    QTimer::singleShot(1000, &loop3, SLOT(quit()));
    loop3.exec();
    e1->closed = true;
    qDebug() << "closed";
    if (button->isChecked())
    {
        button->setChecked(false);
    }
}

void Widget::on_pushButton_open_clicked()
{
    if (e1->eOpen())
    {
        qDebug() << "开门成功";
    }
    else
    {
        qDebug() << "开门失败";
    }
}


void Widget::on_pushButton_close_clicked()
{
    if (e1->eClose())
    {
        qDebug() << "关门成功";
    }
    else
    {
        qDebug() << "关门失败";
    }
}


void Widget::onFloorChanged()
{
    qDebug() << "aaaaa";
    foreach(QAbstractButton *btn,ui->buttonGroup_door->buttons())
    {
        if (btn->property("id").toInt() == e1->currentFloor)
        {
            btn->setStyleSheet("background/*-color*/:yellow");
        }
        else
        {
            btn->setStyleSheet("background/*-colo*/r:transparent");
        }
    }
    ui->label_floor->setText("第 " + QString::number(e1->currentFloor) + " 层");
}

