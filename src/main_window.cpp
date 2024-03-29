#include <QTimer>

#include <string>
#include <thread>
#include <chrono>

#include "main_window.h"
#include "ui_main_window.h"
#include "button.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainwindow_(new Ui::MainWindow),
      iTaskControl_(new ITaskControl(numberThreads_)),
      timer_ (new QTimer(this)),
      buttons_(numberThreads_)
{
    mainwindow_->setupUi(this);
    timer_->start(0);
    // Добавление кнопок
    for (std::size_t i = 0; i < numberThreads_; ++i)
    {
        std::shared_ptr<Button> button = std::make_shared<Button>(i + 1, this);
        mainwindow_->verticalLayout->addWidget(&*button);
        buttons_[i] = button;
        QObject::connect(&*button, &Button::leftClicked, this, &MainWindow::on_button_clicked); // Отслеживание на нажатие кнопки
    }
    QObject::connect(&*timer_, &QTimer::timeout, this, &MainWindow::taskEnded); // Отслеживание таймера
}

MainWindow::~MainWindow()
{
    delete mainwindow_;
}

void MainWindow::on_button_clicked()
{
    Button *button = static_cast<Button*>(sender());
    QString name = "Поток " + QString::number(button->getNumber()) + " свободен";
    button->setText(name);
    button->setEnabled(false);
    std::size_t number = button->getNumber();
    iTaskControl_->cancel(number - 1);
}

int factorial(int number, bool &isInterrupt)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (isInterrupt)
    {
        return 1;
    }
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
        int result = factorial(number - 1, isInterrupt);
        Logger::info << "Промежуточный результат: " << result << std::endl;
        return number * result;
    }
}

int doubleFactorial(int number, bool &isInterrupt)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (isInterrupt)
    {
        return 1;
    }
    if (number == 0 || number == 1)
    {
        return 1;
    }
    return number * doubleFactorial(number - 2, isInterrupt);
}

void MainWindow::on_calculate_1_clicked()
{
    int number = mainwindow_->lineEdit->text().toInt(); // Число
    std::packaged_task<int(int, bool&)> task(factorial);
    queue_.push(std::make_tuple(std::move(task), number, FACTORIAL_1));
}

void MainWindow::on_calculate_2_clicked()
{
    int number = mainwindow_->lineEdit_2->text().toInt(); // Число
    std::packaged_task<int(int, bool&)> task(doubleFactorial);
    queue_.push(std::make_tuple(std::move(task), number, FACTORIAL_2));
}

void MainWindow::taskEnded()
{
    auto statuses = iTaskControl_->statuses();
    for (std::size_t i = 0; i < numberThreads_; ++i)
    {
        if (statuses[i] == READY)
        {
            if (!queue_.empty())
            {
                auto &task = queue_.front();
                iTaskControl_->createTask(task, i);
                queue_.pop();
            }
            QString name = "Поток " + QString::number(buttons_[i]->getNumber()) + " свободен";
            buttons_[i]->setText(name);
            buttons_[i]->setEnabled(false);
        }
        else if (statuses[i] == BUSY)
        {
            QString name = "Отменить поток " + QString::number(buttons_[i]->getNumber());
            buttons_[i]->setText(name);
            buttons_[i]->setEnabled(true);
        }
    }
    QString text = "Потоков в очереди: " + QString::number(queue_.size());
    mainwindow_->label_5->setText(text);
}
