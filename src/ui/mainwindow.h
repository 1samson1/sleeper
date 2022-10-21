#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_btn_start_clicked();
    void on_btn_stop_clicked();

    void timeout();
    void updateTime();

private:
    void resizeLogo();
    void changeActiveBtn();
    void stopTimer();

    int toTimeStamp(int seconds, int minutes = 0, int hours = 0);

    QTimer _timer;
    QTimer _time_updater;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
