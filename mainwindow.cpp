#include "mainwindow.h"
#include "ui_mainwindow.h"

QString RED_STYLE="QLabel { background-color : rgba(219,82,77,255);}";
QString GREEN_STYLE="QLabel { background-color : rgba(70,142,145,255);}";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::countdown);
    active=false;
    inPomodoro=false;
    pomodoroCount=0;
    ui->setupUi(this);
    setFixedSize(width(),height()); // to make unresizable.

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::playAlert(){
    //TODO play a custom alert sound...
    QApplication::beep();
}

void MainWindow::countdown(){
    int min=ui->lcdMinute->value();
    int sec=ui->lcdSecond->value();
    if(sec==0){
        if(min==0){
            if(inPomodoro){
                ui->lcdPomodoroCount->display(++pomodoroCount);
                if(pomodoroCount%4==0){
                    setCountdown(15,0); // long break
                }else{
                    setCountdown(5,0); // short break
                }
            }else{
                setCountdown(20,0);
            }
            ui->lstatusBar->setStyleSheet(GREEN_STYLE);
            ui->bStartStop->setText("Start");
            active=false;
            timer->stop();
        }else{
            min--;
            sec=59;
            ui->lcdMinute->display(min);
        }
    }else{
        sec--;
    }
    ui->lcdSecond->display(sec);
}

void MainWindow::setCountdown(int min,int sec){
    ui->lcdMinute->display(min);
    ui->lcdSecond->display(sec);
    timer->stop();
    active=false;
    ui->lstatusBar->setStyleSheet(GREEN_STYLE);
    ui->bStartStop->setText("Start");
}

void MainWindow::on_bPomodoro_clicked()
{
    inPomodoro=true;
    setCountdown(25,0);
}

void MainWindow::on_bShortBreak_clicked()
{
    inPomodoro=false;
    setCountdown(5,0);
}

void MainWindow::on_bLongBreak_clicked()
{
    inPomodoro=false;
    setCountdown(15,0);
}

void MainWindow::on_bStartStop_clicked()
{
    if(!active){
        timer->start(1000);
        active=true;
        ui->lstatusBar->setStyleSheet(RED_STYLE);
        ui->bStartStop->setText("Stop");
    }else{
        timer->stop();
        active=false;
        ui->lstatusBar->setStyleSheet(GREEN_STYLE);
        ui->bStartStop->setText("Start");
    }
}
