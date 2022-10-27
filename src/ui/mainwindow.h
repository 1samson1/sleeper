#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

enum class WorkMode {
    Timer,
    DateTime
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void timeout();

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_btn_start_clicked();
    void on_btn_stop_clicked();
    void on_is_timer_mode_clicked();
    void on_is_datetime_mode_clicked();

    void updateTime();
    void changeDateTime(const QDateTime &dateTime);

private:
    void resizeLogo();
    void changeEnableBtn();
    void changeWorkMode(WorkMode mode);
    void setTimer(qint64 time);

    int toTimeStamp(int seconds, int minutes = 0, int hours = 0);

    QTimer _time_updater;
    qint64 _interval;
    WorkMode _mode = WorkMode::Timer;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
