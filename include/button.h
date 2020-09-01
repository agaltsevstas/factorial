#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QMouseEvent>

/**
 * Класс Кнопка
 * Содержит название модуля и сигналы нажатий по кнопке.
 */
class Button : public QPushButton
{
    Q_OBJECT

public:
    /**
     * Конструктор
     * @param module Имя модуля.
     */
    Button(const std::size_t name, QWidget *parent = nullptr);
    inline std::size_t getNumber() const { return number_; } /// Получение названия.

signals:
    void rightClicked(); /// Нажатие правой кнопки на мыши.
    void leftClicked();  /// Нажатие левой кнопки на мыши (не задействованно).
    void midClicked();   /// Нажатие средней кнопки мыши (не задействованно).

protected:    
    void mousePressEvent(QMouseEvent *event) override;

private:
    std::size_t number_; /// Номер.
};

#endif // BUTTON_H
