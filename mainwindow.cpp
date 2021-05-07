#include "mainwindow.h"
#include "ui_mainwindow.h"

QString RED_STYLE="QLabel { background-color : rgba(219,82,77,255);}";
QString GREEN_STYLE="QLabel { background-color : rgba(70,142,145,255);}";
short POMODORO_SESSION=25;
short SHORT_BREAK=5;
short LONG_BREAK=15;
short LONG_BREAK_INTERVAL=4;
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
    setCountdown(25,0);
    ui->lcdPomodoroCount->display(QString::number(0).rightJustified(2,'0'));
    setFixedSize(width(),height()); // to make unresizable.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playAlert(){
    QSound::play(":/audio/audio/SynthChime10.wav");
}

void MainWindow::update(){
    if(active){
        ui->lstatusBar->setStyleSheet(RED_STYLE);
        ui->bStartStop->setText("Stop");
        timer->start(1000);
    }else{
        ui->lstatusBar->setStyleSheet(GREEN_STYLE);
        ui->bStartStop->setText("Start");
        timer->stop();
    }
}

void MainWindow::countdown(){
    int min=ui->lcdMinute->value();
    int sec=ui->lcdSecond->value();
    if(sec==0){
        if(min==0){
            playAlert();
            if(inPomodoro){
                ui->lstatusBar->setText("Break Time");
                ui->lcdPomodoroCount->display(QString::number(++pomodoroCount).rightJustified(2,'0'));
                if(pomodoroCount%LONG_BREAK_INTERVAL==0){
                    setCountdown(LONG_BREAK,0); // long break
                }else{
                    setCountdown(SHORT_BREAK,0); // short break
                }
            }else{
                ui->lstatusBar->setText("Pomodoro Time");
                setCountdown(POMODORO_SESSION,0);
            }
            inPomodoro=!inPomodoro;
            active=false;
            update();
        }else{
            min--;
            sec=59;
            ui->lcdMinute->display(QString::number(min).rightJustified(2,'0'));
        }
    }else{
        sec--;
    }
    ui->lcdSecond->display(QString::number(sec).rightJustified(2,'0'));
}

void MainWindow::setCountdown(int min,int sec){
    ui->lcdMinute->display(QString::number(min).rightJustified(2,'0'));
    ui->lcdSecond->display(QString::number(sec).rightJustified(2,'0'));
    active=false;
    update();
}

void MainWindow::on_bPomodoro_clicked()
{
    inPomodoro=true;
    ui->lstatusBar->setText("Pomodoro Time");
    setCountdown(POMODORO_SESSION,0);
}

void MainWindow::on_bShortBreak_clicked()
{
    inPomodoro=false;
    ui->lstatusBar->setText("Break Time");
    setCountdown(SHORT_BREAK,0);
}

void MainWindow::on_bLongBreak_clicked()
{
    inPomodoro=false;
    ui->lstatusBar->setText("Break Time");
    setCountdown(LONG_BREAK,0);
}

void MainWindow::on_bStartStop_clicked()
{
    active=!active;
    update();
}
