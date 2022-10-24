#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <chrono>

using namespace std::chrono_literals;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->logo->setAlignment(Qt::AlignCenter);

    connect(&_time_updater, &QTimer::timeout,
            this, &MainWindow::updateTime);
    _time_updater.setInterval(1s);
}

void MainWindow::showEvent(QShowEvent *event)
{
    resizeLogo();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeLogo();
}

void MainWindow::resizeLogo()
{
    QPixmap logo(":/icon512");
    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(logo.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::changeActiveBtn()
{
    if(ui->btn_start->isEnabled())
    {
        ui->box_mode->setEnabled(false);
        ui->box_time->setEnabled(false);
        ui->btn_start->setEnabled(false);
        ui->btn_stop->setEnabled(true);
    }
    else {
        ui->box_mode->setEnabled(true);
        ui->box_time->setEnabled(true);
        ui->btn_start->setEnabled(true);
        ui->btn_stop->setEnabled(false);
    }
}

int MainWindow::toTimeStamp(int seconds, int minutes, int hours)
{
    return seconds + minutes * 60 + hours * 3600;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked()
{
    changeActiveBtn();

    _interval = toTimeStamp(ui->seconds->value(),
                            ui->minutes->value(),
                            ui->hours->value());

    qDebug() << _interval;
    _time_updater.start();
}


void MainWindow::on_btn_stop_clicked()
{
    changeActiveBtn();
    _time_updater.stop();
}

void MainWindow::timeout()
{
    _time_updater.stop();

    QMessageBox::information(this, "Sleep", "Sleep");
    changeActiveBtn();
}

void MainWindow::updateTime()
{
    if(_interval == 0){
        return timeout();
    }

    --_interval;

    int time = _interval;
    ui->seconds->setValue(time % 60); time /= 60;
    ui->minutes->setValue(time % 60); time /= 60;
    ui->hours->setValue(time);
}
