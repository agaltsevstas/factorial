#include <QTimer>

#include <string>
#include <thread>
#include <chrono>

#include "main_window.h"
#include "ui_main_window.h"
#include "button.h"
#include "itask.hpp"
#include "itask_control.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainwindow_(new Ui::MainWindow),
      iTaskControl_(new ITaskControl(numberThreads_)),
      timer_ (new QTimer(this)),
      buttons_(numberThreads_)
{
    mainwindow_->setupUi(this);
    timer_->start(100);
    // Добавление кнопок
    for (std::size_t i = 0; i < numberThreads_; ++i)
    {
        std::shared_ptr<Button> button = std::make_shared<Button>(i + 1, this);
        mainwindow_->verticalLayout->addWidget(&*button);
        buttons_[i] = button;
        QObject::connect(&*button, &Button::leftClicked, this, &MainWindow::on_button_clicked); // Отслеживание на нажатие кнопки
    }
    auto threads = iTaskControl_->getThreads();
    QObject::connect(&*timer_, &QTimer::timeout, this, &MainWindow::timerAlarm);               // Отслеживание таймера на наличие хотя бы 1 связи между модулями
}

MainWindow::~MainWindow()
{
    delete mainwindow_;
}

void MainWindow::on_button_clicked()
{
    auto &threads = iTaskControl_->getThreads();
    Button *button = static_cast<Button*>(sender());
    QString name = "Поток " + QString::number(button->getNumber()) + " свободен";
    button->setText(name);
    button->setEnabled(false);
    std::size_t number = button->getNumber();
    threads[number - 1]->cancel();
}

int factorial(int number)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(number < 0)
    {
        return 0;
    }
    if (number == 0)
    {
        return 1;
    }
    else
    {
        return number * factorial(number - 1);
    }
}

int doubleFactorial(int number)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (number == 0 || number == 1)
    {
        return 1;
    }
    return number * doubleFactorial(number - 2);
}

void MainWindow::on_calculate_1_clicked()
{
    int number = mainwindow_->lineEdit->text().toInt(); // Число
    queue_.push(std::async(factorial, number));
}

void MainWindow::on_calculate_2_clicked()
{
    int number = mainwindow_->lineEdit_2->text().toInt(); // Число
    queue_.push(std::async(doubleFactorial, number));
}

void MainWindow::timerAlarm()
{
    auto &threads = iTaskControl_->getThreads();

    for (std::size_t i = 0; i < numberThreads_; ++i)
    {
        if (threads[i] == nullptr && !queue_.empty())
        {
            auto &task = queue_.front();
            iTaskControl_->createTask(task, i, FACTORIAL_1);
            queue_.pop();
            QString name = "Отменить поток " + QString::number(buttons_[i]->getNumber());
            buttons_[i]->setText(name);
            buttons_[i]->setEnabled(true);
        }
        else if (threads[i] != nullptr)
        {
            if (i == 0)
                int k = 0;
            if (threads[i]->status() == READY)
            {
                if (!queue_.empty())
                {
                    auto &task = queue_.front();
                    iTaskControl_->createTask(task, i, FACTORIAL_1);
                    queue_.pop();
                }
                QString name = "Поток " + QString::number(buttons_[i]->getNumber()) + " свободен";
                buttons_[i]->setText(name);
                buttons_[i]->setEnabled(false);
            }
            if (threads[i]->status() == BUSY)
            {
                QString name = "Отменить поток " + QString::number(buttons_[i]->getNumber());
                buttons_[i]->setText(name);
                buttons_[i]->setEnabled(true);
            }
        }
    }
}
