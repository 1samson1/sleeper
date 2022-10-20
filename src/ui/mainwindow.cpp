#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    ui->logo->setAlignment(Qt::AlignCenter);
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

MainWindow::~MainWindow()
{
    delete ui;
}


