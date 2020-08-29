#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

/*!
 * @brief Класс-синглтон, предназначенный для сбора и сохранения информации о работе программы.
 * Информация записывается в буфер и файлы
 */

std::string localTime();

class Logger
{
    
public:
    
    /*!
     * @brief Четыре уровня подробности лога:
     * DEBUG_LEVEL_DISABLED - Полное отключение лога
     * DEBUG_LEVEL_ERROR - Вывод только ошибок
     * DEBUG_LEVEL_WARNING - Вывод предупреждений и ошибок
     * DEBUG_LEVEL_INFO - Вывод сообщений
     */
    enum DebugLevel
    {
        DEBUG_LEVEL_DISABLED = 0,
        DEBUG_LEVEL_ERROR = 1,
        DEBUG_LEVEL_WARNING = 2,
        DEBUG_LEVEL_INFO = 3,
    };
    
    /*!
     * @brief Четыре уровня вида сообщений:
     * MESSAGE_INFO - Информационное сообщение
     * MESSAGE_WARNING - Предупреждение
     * MESSAGE_ERROR - Ошибка
     * MESSAGE_ALL - Сообщения всех видов (информационное сообщение, предупреждение, ошибка)
     */
    enum MessageType
    {
        MESSAGE_INFO = 1,
        MESSAGE_WARNING,
        MESSAGE_ERROR,
        MESSAGE_ALL
    };
    
    
    /*!
     * @brief Создание единственного объекта
     */
    static void instance();
    
    /*!
     * @TODO: Установление уровня подробности лога
     * @param level - Уровень лога
     */
    static void setDebugLevel(DebugLevel level);
    
    /*!
     * @details Производный класс от класссов стандартной библиотеки.
     * Для каждого вида потока создается объект, поэтому конструкторы принимают параметр MessageType.
     * Класс вывода наследуется от ostream, за формирование строки отвечает вложенный класс StringBuffer, который унаследован от stringbuf.
     * После завершениия формирования сообщения, автоматически вызвается метод sync, в котором выполняется непосредственный вывод.
     * Завершение вывода сообщается стандартными для буферизируемых потоков с помощью вызова метода flush
     */
    class Streamer : public std::ostream
    {
    public:
        /*!
         * @brief Консруктор для связывания потока вывода со строковым буфером
         * @param messageType - Тип сообщения
         */
        Streamer(Logger::MessageType messageType);
        
        /*!
         * @brief Деструктор для удаление потока буфера
         */
        ~Streamer();
        
    private:
        class StringBuffer : public std::stringbuf
        {
        public:
            
            /*!
             * @brief Конструктор для отправление типа сообщения
             * @param messageType - Тип сообщения
             */
            StringBuffer(Logger::MessageType messageType);
            
            /*!
             * @brief Деструктор.
             * При разрушении буфера вызывается на всякий случай его синхронизация.
             * Это действие предотвратит «пропадание» сообщения, если забыть вызвать flush или endl.
             */
            ~StringBuffer();
            
            /*!
             * @brief Синхронизация строкового буфера потока
             */
            virtual int sync();
            
        private:
            Logger::MessageType messageType_;
        };
    };
    
    static Streamer info;    /// Объект потока для информационных сообщений
    static Streamer warning; /// Объект потока для предупреждений
    static Streamer error;   /// Объект потока для ошибок
    
protected:
    Logger() {}
    ~Logger();
    
    /*!
     * @brief Запрет копирования
     */
    Logger(const Logger&) = delete;
    
    /*!
     * @brief Запрет оператора присваивания
     */
    Logger& operator=(Logger&) = delete;
    
private:
    static Logger *logger_;                /// Объект-одиночка
    static DebugLevel debugLevel_;         /// Уровень подробности лога
    static std::ofstream logFile_;         /// Выходной файловый поток
    
    /*!
     * @brief Запись информационных сообщений.
     * Запись производится одновременно в файл и буфер в двух потоках
     * @param message - Записываемое сообщение
     */
    void writeInfo(const std::string &message);
    
    /*!
     * @brief Запись предупреждений.
     * Запись производится одновременно в файл и буфер в двух потоках
     * @param message - Записываемое сообщение
     */
    void writeWarning(const std::string &message);
    
    /*!
     * @brief Запись ошибок.
     * Запись производится одновременно в файл и буфер в двух потоках
     * @param message - Записываемое сообщение
     */
    void writeError(const std::string &message);
    
    /*!
     * @brief Запись в буфер.
     * Запись производится в определенный буфер в зависимости от уровня вида сообщения
     * @param message - Записываемое сообщение
     * @param messageType - Уровень вида сообщений
     */
    static void writeToBuffer(const std::string &message, MessageType messageType);
    
    /*!
     * @brief Запись в файл
     * @param message - Записываемое сообщение
     */
    void writeToFile(const std::string &message);
    
    /*!
     * @brief Вывод информационных сообщений на экран
     */
    static void printInfo();
    
    /*!
     * @brief Вывод предупреждений на экран
     */
    static void printWarning();
    
    /*!
     * @brief Вывод ошибок на экран
     */
    static void printError();
    
    /*!
     * @brief Вывод всех сообщений (информационные сообщений, предупреждения, ошибки) на экран
     */
    static void printAllMessages();
};

#endif /* Logger_h */
