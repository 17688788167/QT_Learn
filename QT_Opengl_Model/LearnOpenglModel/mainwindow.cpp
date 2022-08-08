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

void MainWindow::on_actBoxMode_triggered()
{

}

void MainWindow::on_actEnvironmentSetting_triggered()
{
    EnvironmentSettingDialog *dlg=new EnvironmentSettingDialog(this);

   dlg->setType(ui->openGLWidget->getType());

    if (dlg->exec()==QDialog::Accepted)
    {
        ui->openGLWidget->SetEnvironmentType(dlg->getType());

    }
       delete dlg;
}

#include <QFileDialog>
void MainWindow::on_actloadModel_triggered()
{
    QString str=QFileDialog::getOpenFileName(this,"选择模型文件","","OBJ(*.obj);;FBX(*.fbx);;ALL FILES(*.*)");
    ui->openGLWidget->LoadModel((str.toStdString()));
}
