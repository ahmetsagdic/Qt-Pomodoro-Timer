#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void setCountdown(int min,int sec);
    void countdown();
    void playAlert();
    void update();

    void on_bPomodoro_clicked();
    void on_bShortBreak_clicked();
    void on_bLongBreak_clicked();
    void on_bStartStop_clicked();

private:
    Ui::MainWindow *ui;
    bool active;
    bool inPomodoro; // false: on break, true: doing pomodoro
    int pomodoroCount;
    QTimer *timer;
};
#endif // MAINWINDOW_H
