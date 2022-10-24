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

public slots:
    void timeout();

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_btn_start_clicked();
    void on_btn_stop_clicked();

    void updateTime();

private:
    void resizeLogo();
    void changeActiveBtn();

    int toTimeStamp(int seconds, int minutes = 0, int hours = 0);

    QTimer _time_updater;
    int _interval;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
