/**
 * @file ErrorHandler.h
 *
 * @date 05.06.2024
 * @author d.usov\@kpda.ru
 *
 * (c) 2024, SWD Embedded Systems Limited, http://www.kpda.ru
 */

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include <sstream>
#include <string>

namespace mwa {
    class ErrorHandler {
    public:
        /// Конструктор, принимающий исключение
        explicit ErrorHandler(const std::exception &e);

        ErrorHandler() = default;

        /// Перегрузка оператора <<
        template<typename T>
        ErrorHandler &operator<<(const T &message);

        /// Поддержка basic_ostream
        template <typename T>
        friend std::basic_ostream<T> &operator<<(std::basic_ostream<T> &os, const ErrorHandler &errorHandler) {
            os << errorHandler.m_errorStream.str(); // Вывод сообщения об ошибке
            return os;
        }

        /// Завершение обработки ошибок и вывод JSON
        ~ErrorHandler();

    private:
        /// Поток для накопления сообщений
        std::ostringstream m_errorStream;

        /// Метод для вывода сообщения об ошибке
        static void logError(const std::string &errorMessage);
    };

    template<typename T>
    ErrorHandler &ErrorHandler::operator<<(const T &message) {
        m_errorStream << message;
        return *this;
    }
} // mwa

#endif //ERRORHANDLER_H
