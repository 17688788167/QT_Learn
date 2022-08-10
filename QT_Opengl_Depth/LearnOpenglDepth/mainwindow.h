#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actRender_triggered();

    void on_actClear_triggered();

    void on_actBoxMode_triggered();

    void on_actBoxMode_triggered(bool checked);

    void on_actEnvironmentSetting_triggered();

    void on_actloadModel_triggered();

    void getMousePickingPos(const QVector3D &pos);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
