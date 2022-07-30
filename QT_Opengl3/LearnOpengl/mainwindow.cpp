#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actRender_triggered()
{
    ui->openGLWidget->drawShape(Rect);
}

void MainWindow::on_actClear_triggered()
{
    ui->openGLWidget->drawShape(None);
}


void MainWindow::on_actBoxMode_triggered(bool checked)
{
    ui->openGLWidget->setWireFrame(checked);
}
