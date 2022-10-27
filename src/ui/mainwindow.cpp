#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QDebug>
#include <chrono>

#include "app/types.h"
#include "utils/misc.h"

using namespace std::chrono_literals;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->logo->setAlignment(Qt::AlignCenter);

    // Set time updater
    connect(&_time_updater, &QTimer::timeout,
            this, &MainWindow::updateTime);
    _time_updater.setInterval(1s);

    // Set datetime

    QDateTime current_dt ;
    current_dt.setSecsSinceEpoch(QDateTime::currentDateTime().toSecsSinceEpoch() + 30);

    ui->datetime->setDateTime(current_dt);

    connect(ui->datetime, &QDateTimeEdit::dateTimeChanged,
            this, &MainWindow::changeDateTime);
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

void MainWindow::changeEnableBtn()
{
    bool enable_btns = ui->btn_stop->isEnabled();
    bool disable_btns = ui->btn_start->isEnabled();

    ui->btn_start->setEnabled(enable_btns);
    ui->btn_stop->setEnabled(disable_btns);

    ui->box_action->setEnabled(enable_btns);
    ui->box_mode->setEnabled(enable_btns);
}

void MainWindow::changeWorkMode(WorkMode mode)
{
    _mode = mode;

    ui->box_timer->setEnabled(_mode == WorkMode::Timer);
    ui->datetime->setEnabled(_mode == WorkMode::DateTime);
}

void MainWindow::setTimer(qint64 time)
{
    ui->seconds->setValue(time % 60); time /= 60;
    ui->minutes->setValue(time % 60); time /= 60;
    ui->hours->setValue(time);
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
    if(_mode == WorkMode::DateTime){
        qint64 diff_time = ui->datetime->dateTime().toSecsSinceEpoch() - QDateTime::currentSecsSinceEpoch();

        if(diff_time < 0)
        {
            QMessageBox::critical(this, tr("Outdate"), tr("The date is less than the current one"));
            return;
        }
    }

    changeEnableBtn();
    ui->statusbar->clearMessage();

    if(_mode == WorkMode::Timer)
    {
        _interval = toTimeStamp(ui->seconds->value(),
                                ui->minutes->value(),
                                ui->hours->value());
    }

    _time_updater.start();
}

void MainWindow::on_btn_stop_clicked()
{
    changeEnableBtn();
    _time_updater.stop();
}

void MainWindow::timeout()
{
    _time_updater.stop();

    ShutdownDialogAction action;
    if(ui->is_reboot->isChecked())
        action = ShutdownDialogAction::Reboot;
    else if(ui->is_shutdown->isChecked())
        action = ShutdownDialogAction::Shutdown;
    else if(ui->is_suspend->isChecked())
        action = ShutdownDialogAction::Suspend;

    ui->statusbar->showMessage(tr("Timeout"));
    Utils::Misc::shutdownComputer(action);

    changeEnableBtn();
}

void MainWindow::updateTime()
{
    if(_mode == WorkMode::Timer){
        if(_interval == 0){
            return timeout();
        }

        --_interval;

        setTimer(_interval);
    }
    else {
        qint64 diff_time = ui->datetime->dateTime().toSecsSinceEpoch() - QDateTime::currentSecsSinceEpoch();

        if(diff_time >= 0)
            setTimer(diff_time);
        else
            timeout();
    }
}

void MainWindow::on_is_timer_mode_clicked()
{
    changeWorkMode(WorkMode::Timer);
}


void MainWindow::on_is_datetime_mode_clicked()
{
    changeWorkMode(WorkMode::DateTime);
}

void MainWindow::changeDateTime(const QDateTime &dateTime)
{
    qint64 diff_time = dateTime.toSecsSinceEpoch() - QDateTime::currentSecsSinceEpoch();

    if(diff_time >= 0)
        setTimer(diff_time);
    else
        ui->datetime->setDateTime(QDateTime::currentDateTime());
}
