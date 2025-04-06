//
// Created by sphdx on 06.03.2025.
//

#ifndef CAR_H
#define CAR_H
#include <sstream>
#include <string>
#include <utility>

class Car {
    std::string make_{}, model_{};

public:
    Car(std::string make, std::string model);

    Car();

    [[nodiscard]] std::string get_make() const;

    [[nodiscard]] std::string get_model() const;

    bool operator<(const Car &other) const;

    bool operator>(const Car &other) const;

    bool operator==(const Car &other) const;

    bool operator!() const;

    friend std::ostream &operator<<(std::ostream &os, const Car &car);

    [[nodiscard]] std::string to_string() const;

    static inline Car parse(const std::string &car);
};

inline std::ostream &operator<<(std::ostream &os, const Car &car) {
    return os << car.to_string();
}

inline Car::Car(std::string make, std::string model) : make_(std::move(make)), model_(std::move(model)) {
}

inline Car::Car() = default;

inline std::string Car::get_make() const {
    return make_;
}

inline std::string Car::get_model() const {
    return model_;
}

inline bool Car::operator<(const Car &other) const {
    return model_ < other.model_ && make_ < other.make_;
}

inline bool Car::operator>(const Car &other) const {
    return model_ > other.model_ && make_ > other.make_;
}

inline bool Car::operator==(const Car &other) const {
    return model_ == other.model_ && make_ == other.make_;
}

inline bool Car::operator!() const {
    return model_.empty();
}

inline std::string Car::to_string() const {
    return make_ + " " + model_;
}

inline Car Car::parse(const std::string &car) {
    std::istringstream iss(car);
    std::string make, model;
    iss >> make >> model;
    return Car{make, model};
}

#endif //CAR_H
