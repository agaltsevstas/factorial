#include "button.h"

Button::Button(const std::size_t number, QWidget *parent) :
    QPushButton(parent),
    number_    (number)
{
    QString name = "Поток " + QString::number(number_) + " свободен";
    setText(name);                                                 // Установка имени
    setEnabled(false);
    setCursor(QCursor(Qt::PointingHandCursor));                    // Изменение курсора при наведении
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // Изменение ширины и высоты при масштабировании
    QPalette palette;
    QBrush green(QColor(78, 154, 6, 255));                         // Кисть зеленого цвета
    QBrush white(QColor(255, 255, 255, 255));                      // Кисть белого цвета
    palette.setBrush(QPalette::Active, QPalette::Button, green);   // Установка цвета для активного состояния
    palette.setBrush(QPalette::Inactive, QPalette::Button, green); // Установка цвета для неактивного состояния
    palette.setBrush(QPalette::Disabled, QPalette::Button, green); // Установка цвета для отключенного состояния
    setPalette(palette);
}

void Button::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)  emit leftClicked();
}
