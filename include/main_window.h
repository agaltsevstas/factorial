#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <queue>
#include <future>

class ITaskControl;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculate_1_clicked();
    void on_calculate_2_clicked();

private:
    Ui::MainWindow *mainwindow_ = nullptr;
    ITaskControl *iTaskControl_ = nullptr;
};
#endif // MAINWINDOW_H
