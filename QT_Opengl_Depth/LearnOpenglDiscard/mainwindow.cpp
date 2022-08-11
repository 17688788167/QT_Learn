#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);

    connect(ui->openGLWidget,SIGNAL(mousePickingPos(QVector3D)),this,SLOT(getMousePickingPos(QVector3D)));
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

void MainWindow::getMousePickingPos(const QVector3D &pos)
{
    float x=pos.x();
    float y=pos.y();
    float z=pos.z();

    ui->statusBar->setStyleSheet("font: 14pt ");
    ui->statusBar->showMessage(" 世界坐标    X:"+QString::number(x,'f', 2)
    +" Y:"+QString::number(y,'f', 2)
    +" Z:"+QString::number(z,'f', 2)
    );

}
