#include "environmentsettingdialog.h"
#include "ui_environmentsettingdialog.h"
#include <QDebug>

void EnvironmentSettingDialog::setType(EnvironmentSettingDialog::EnvironmentType type)
{
    m_type=type;
    ui->comboBox->setCurrentIndex((int)type);
}

EnvironmentSettingDialog::EnvironmentSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnvironmentSettingDialog)
{
    ui->setupUi(this);
}

EnvironmentSettingDialog::~EnvironmentSettingDialog()
{
    delete ui;
}

void EnvironmentSettingDialog::on_comboBox_currentIndexChanged(int index)
{
    m_type=(EnvironmentType)index;

    qDebug()<<index;

}
