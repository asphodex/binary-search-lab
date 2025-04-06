//
// Created by sphdx on 06.04.2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <cstddef>
#include <string>
#include <sstream>

class Application {
    std::size_t number_ = 0;

public:
    Application() = default;

    explicit Application(const std::size_t number) : number_(number) {}

    bool operator<(const Application &other) const;

    bool operator>(const Application &other) const;

    bool operator==(const Application &other) const;

    bool operator!() const;

    [[nodiscard]] std::size_t get_number() const;

    [[nodiscard]] std::string to_string() const;

    static Application parse(const std::string &s);

    friend std::ostream &operator<<(std::ostream &os, const Application &app);
};

inline std::ostream & operator<<(std::ostream &os, const Application &app) {\
    return os << app.to_string();
}

inline bool Application::operator<(const Application &other) const {
    return number_ < other.number_;
}

inline bool Application::operator>(const Application &other) const {
    return number_ > other.number_;
}

inline bool Application::operator==(const Application &other) const {
    return number_ == other.number_;
}

inline bool Application::operator!() const {
    return number_ == 0;
}

inline std::size_t Application::get_number() const {
    return number_;
}

inline std::string Application::to_string() const {
    return std::to_string(number_);
}

inline Application Application::parse(const std::string &s) {
    std::istringstream iss(s);
    std::size_t number;
    iss >> number;
    return Application(number);
}

#endif //APPLICATION_H
