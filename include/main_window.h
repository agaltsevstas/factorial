#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <queue>
#include <future>

#include "itask_control.h"

class ITaskControl;
class Button;

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
    /// Добавление кнопки на сцену
    void on_button_clicked();
    void on_calculate_1_clicked();
    void on_calculate_2_clicked();
    void timerAlarm();

private:
    std::size_t numberThreads_ = 10;
    Ui::MainWindow *mainwindow_ = nullptr;
    std::unique_ptr<ITaskControl> iTaskControl_;
    std::vector<ITask*> *threads_;
    std::unique_ptr<QTimer> timer_; /// Таймер
    std::vector<std::shared_ptr<Button>> buttons_;
    std::queue<std::tuple<std::packaged_task<int(int, bool&)>, int, Mode>> queue_;
};
#endif // MAINWINDOW_H
