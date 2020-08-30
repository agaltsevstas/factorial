#include <experimental/filesystem>
#include <iomanip>

#include "logger.h"

Logger* Logger::logger_ = nullptr;                                                 // Определение уровня подробности лога
Logger::DebugLevel Logger::debugLevel_ = Logger::DebugLevel::DEBUG_LEVEL_DISABLED; // Определение уровня подробности лога
std::ofstream Logger::logFile_;                                                    // Определение выходного файлового потока
Logger::Streamer Logger::info(Logger::MESSAGE_INFO);                               // Определение поля информационного сообщения для Logger
Logger::Streamer Logger::warning(Logger::MESSAGE_WARNING);                         // Определение поля предупреждения для Logger
Logger::Streamer Logger::error(Logger::MESSAGE_ERROR);                             // Определение поля ошибки для Logger

std::string localTime()
{
    std::stringstream ss;
    time_t t = std::time(nullptr);
    auto tm = *localtime(&t);
    ss << std::put_time(&tm, "%d.%m.%Y_%H:%M:%S");
    return ss.str();
}

void Logger::instance()
{
    namespace fs = std::experimental::filesystem;
    
    delete logger_; // Очищение указателя на случай двойной инициализации
    logger_ = new Logger;
    debugLevel_ = DEBUG_LEVEL_INFO;
    
//    fs::path fileName = localTime() + ".log";
//    fs::path directory = "../log/";
//    fs::create_directory(directory); // Проверка на существование каталога. В случае отсутсвия, создается каталог
//    std::string filePath = directory.string() + fileName.string();
//    logFile_.open(filePath);
}

void Logger::setDebugLevel(Logger::DebugLevel debugLevel)
{
    debugLevel_ = debugLevel;
}

Logger::Streamer::Streamer(Logger::MessageType messageType)
: std::ostream(new StringBuffer(messageType))
{
}

Logger::Streamer::~Streamer()
{
    delete rdbuf();
}

Logger::Streamer::StringBuffer::StringBuffer(Logger::MessageType messageType)
: messageType_(messageType)
{
}

Logger::Streamer::StringBuffer::~StringBuffer()
{
    pubsync();
}

int Logger::Streamer::StringBuffer::sync()
{
    std::string text(str()); // Получение текста из буфера
    if (Logger::logger_ == nullptr || text.empty())
    {
        return 0;
    }
    str(""); // Очищение буфера
    switch (messageType_)
    {
        case MESSAGE_INFO:
            Logger::logger_->writeInfo(text);
            break;
            
        case MESSAGE_WARNING:
            Logger::logger_->writeWarning(text);
            break;
            
        case MESSAGE_ERROR:
            Logger::logger_->writeError(text);
            break;
    }
    return 0;
};

void Logger::writeInfo(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_INFO)
    {
        const std::string localtime = "[" + localTime() + "] ";
        const std::string str = localtime + message;
        writeToFile(str);
    }
}

void Logger::writeWarning(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_WARNING)
    {
        const std::string localtime = "[" + localTime() + "] ";
        const std::string type = "[Warning] ";
        const std::string str = localtime + type + message;
        writeToFile(str);
    }
}

void Logger::writeError(const std::string &message)
{
    if (debugLevel_ >= DEBUG_LEVEL_ERROR)
    {
        const std::string localtime = "[" + localTime() + "] ";
        const std::string type = "[Error] ";
        const std::string str = localtime + type + message;
        writeToFile(str);
    }
}

void Logger::writeToFile(const std::string &message)
{
    logFile_ << message << std::flush; // Принудительный сброс буфера
}

Logger::~Logger()
{
    delete logger_;
    logFile_.flush();
    logFile_.close();
}

