#include <numeric>
#include <future>
#include <string>
#include <mutex>

#include "main_window.h"
#include "ui_main_window.h"
#include "itask.hpp"
#include "itask_control.h"
#include "logger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainwindow_(new Ui::MainWindow),
      iTaskControl_(new ITaskControl(10))
{
    mainwindow_->setupUi(this);
//    connect(button, &Button::leftClicked, this, &MainWindow::addButton); // Отслеживание на нажатие кнопки
}

MainWindow::~MainWindow()
{
    delete mainwindow_;
    delete iTaskControl_;
}

int factorial(int number)
{
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
    if (number == 0 || number == 1)
    {
        return 1;
    }
    return number * doubleFactorial(number - 2);
}

void MainWindow::on_calculate_1_clicked()
{
    int number = mainwindow_->lineEdit->text().toInt(); // Число
    iTaskControl_->createTask(factorial, number);
}

void MainWindow::on_calculate_2_clicked()
{
    int number = mainwindow_->lineEdit->text().toInt(); // Число
    iTaskControl_->createTask(factorial, number);
}

void taskEnded
