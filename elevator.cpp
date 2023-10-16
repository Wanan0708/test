#include "elevator.h"

Elevator::Elevator()
{
    currentFloor = 1;
}


void Elevator::eUp(int floor)
{
    this->running = true;
    this->uping = true;
    this->idleing = false;
    qDebug() << "当前在第" << currentFloor << "层";
    for(int i = currentFloor; i < floor; i++)
    {
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, SLOT(quit()));
        loop.exec();
//        QCoreApplication::processEvents();
        this->currentFloor++;
        emit floorChanged();
        qDebug() << "当前在第" << currentFloor << "层";
    }
    this->running = false;
    this->uping = false;
    this->idleing = true;
}

void Elevator::eDown(int floor)
{
    this->running = true;
    this->downing = true;
    this->idleing = false;
    qDebug() << "当前在第" << currentFloor << "层";
    for(int i = currentFloor; i > floor; i--)
    {
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, SLOT(quit()));
        loop.exec();
        this->currentFloor--;
        emit floorChanged();
        qDebug() << "当前在第" << currentFloor << "层";
    }
    this->running = false;
    this->downing = false;
    this->idleing = true;
}

bool Elevator::eOpen()
{
    bool isOk = false;
    if(this->running || this->uping || this->downing)
    {
        qDebug() << "正在运行，请不要尝试此操作";
        isOk = false;
    }
    else if(this->closed)
    {
        QEventLoop loop1;
        QTimer::singleShot(1000, &loop1, SLOT(quit()));
        loop1.exec();
        this->opening = true;
        this->closed = false;
        QEventLoop loop2;
        QTimer::singleShot(1000, &loop2, SLOT(quit()));
        loop2.exec();
        this->opened = true;
        this->opening = false;
        qDebug() << "已开门";
        isOk = true;
    }
    else if(this->closeing)
    {
        QEventLoop loop1;
        QTimer::singleShot(500, &loop1, SLOT(quit()));
        loop1.exec();
        qDebug() << "opening";
        this->opening = true;
        QEventLoop loop2;
        QTimer::singleShot(500, &loop2, SLOT(quit()));
        loop2.exec();
        this->opening = false;
        this->opened = true;
        qDebug() << "已开门";
        isOk = true;
    }
    else if(this->opening)
    {
        QEventLoop loop1;
        QTimer::singleShot(1000, &loop1, SLOT(quit()));
        loop1.exec();
        this->opened = true;
        qDebug() << "已开门";
        isOk = true;
    }
    else if(this->opened)
    {
        isOk = true;
        qDebug() << "已开门";
    }
    qDebug() << "isOk" << isOk;
    return isOk;
}

bool Elevator::eClose()
{
    bool isOk = false;
    if(this->running || this->uping || this->downing)
    {
        qDebug() << "正在运行，请不要尝试此操作";
        isOk = false;
    }
    else if(this->opened)
    {
        QEventLoop loop1;
        QTimer::singleShot(1000, &loop1, SLOT(quit()));
        loop1.exec();
        this->closeing = true;
        this->opened = false;
        QEventLoop loop2;
        QTimer::singleShot(1000, &loop2, SLOT(quit()));
        loop2.exec();
        this->closeing = false;
        this->closed = true;
        qDebug() << "已关门";
        isOk = true;
    }
    else if(this->closeing)
    {
        QEventLoop loop1;
        QTimer::singleShot(1000, &loop1, SLOT(quit()));
        loop1.exec();
        this->closed = true;
        this->closeing = false;
        qDebug() << "已关门";
        isOk = true;
    }
    else if(this->opening)
    {
        QEventLoop loop1;
        QTimer::singleShot(1000, &loop1, SLOT(quit()));
        loop1.exec();
        this->closed = true;
        qDebug() << "已关门";
        isOk = true;
    }
    else if(this->closed)
    {
        isOk = true;
    }
    qDebug() << "isOk" << isOk;
    return isOk;
}

void Elevator::eMoveTo(int destinationFloor)
{
    if(this->opening == true || this->opened == true || this->closeing == true)
    {
        qDebug() << "门未关好，请等待";
        this->eClose();
    }
    this->running = true;
    this->idleing = false;
    qDebug() << "当前在第" << currentFloor << "层";
    while (this->currentFloor != destinationFloor) {
        if(this->currentFloor > destinationFloor)
        {
            this->downing = true;
            QEventLoop loop1;
            QTimer::singleShot(1000, &loop1, SLOT(quit()));
            loop1.exec();
            this->currentFloor--;
            emit floorChanged();
        }
        else if(this->currentFloor < destinationFloor)
        {
            this->uping = true;
            QEventLoop loop1;
            QTimer::singleShot(1000, &loop1, SLOT(quit()));
            loop1.exec();
            this->currentFloor++;
            emit floorChanged();
        }
        qDebug() << "当前在第" << currentFloor << "层";
    }
    this->running = false;
    this->uping = false;
    this->downing = false;
    this->idleing = true;
}

//void Elevator::floorChanged()
//{
//    qDebug() << "信号被触发";
//}
