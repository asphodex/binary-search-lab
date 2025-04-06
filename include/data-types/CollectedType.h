//
// Created by sphdx on 08.03.2025.
//

#ifndef COLLECTED_TYPE_H
#define COLLECTED_TYPE_H
#include <utility>

#include "Car.h"
#include "LicensePlate.h"
#include "PersonName.h"
#include "Application.h"

class CollectedType {
    LicensePlate license_plate_;
    PersonName person_name_;
    Car car_;
    Application app_;

    int line_ = 0;

public:
    CollectedType(LicensePlate license_plate, PersonName person_name, Car car, Application app, int line);

    CollectedType();

    bool operator<(const CollectedType &other) const;

    bool operator>(const CollectedType &other) const;

    bool operator==(const CollectedType &other) const;

    CollectedType &operator=(const CollectedType &other);

    bool operator!() const;

    [[nodiscard]] LicensePlate get_license_plate() const;

    [[nodiscard]] PersonName get_person_name() const;

    [[nodiscard]] Car get_car() const;

    [[nodiscard]] Application get_application() const;

    [[nodiscard]] int get_line() const;

    friend std::ostream &operator<<(std::ostream &os, const CollectedType &st);

    [[nodiscard]] std::string to_string() const;

    template<class Type>
    void set_field(std::istringstream &iss, int counter);

    template<class... Types>
    void parse(const std::string &line, int counter);
};

inline std::ostream &operator<<(std::ostream &os, const CollectedType &st) {
    return os << st.line_ << " " << st.license_plate_ << " " << st.person_name_ << " " << st.car_ << " " << st.app_;
}

inline CollectedType::CollectedType(LicensePlate license_plate, PersonName person_name, Car car, Application app,
                                    const int line) : license_plate_(std::move(license_plate)),
                                                      person_name_(std::move(person_name)),
                                                      car_(std::move(car)),
                                                      app_(app),
                                                      line_(line) {
}

inline CollectedType::CollectedType() = default;

inline bool CollectedType::operator<(const CollectedType &other) const {
    if (license_plate_ != other.license_plate_) {
        return license_plate_ < other.license_plate_;
    }
    if (person_name_ != other.person_name_) {
        return person_name_ < other.person_name_;
    }
    if (car_ != other.car_) {
        return car_ < other.car_;
    }

    return app_ < other.app_;
}

inline bool CollectedType::operator>(const CollectedType &other) const {
    if (license_plate_ != other.license_plate_) {
        return license_plate_ > other.license_plate_;
    }
    if (person_name_ != other.person_name_) {
        return person_name_ > other.person_name_;
    }
    if (car_ != other.car_) {
        return car_ > other.car_;
    }

    return app_ > other.app_;
}

inline bool CollectedType::operator==(const CollectedType &other) const {
    return license_plate_ == other.license_plate_ && person_name_ == other.person_name_ && car_ == other.car_ && app_ ==
           other.app_;
}

inline CollectedType &CollectedType::operator=(const CollectedType &other) {
    if (this != &other) {
        license_plate_ = other.license_plate_;
        person_name_ = other.person_name_;
        car_ = other.car_;
        app_ = other.app_;

        line_ = other.line_;
    }
    return *this;
}

inline bool CollectedType::operator!() const {
    return !license_plate_ && !person_name_ && !car_ && !app_;
}

inline LicensePlate CollectedType::get_license_plate() const {
    return license_plate_;
}

inline PersonName CollectedType::get_person_name() const {
    return person_name_;
}

inline Car CollectedType::get_car() const {
    return car_;
}

inline Application CollectedType::get_application() const {
    return app_;
}

inline int CollectedType::get_line() const {
    return line_;
}

inline std::string CollectedType::to_string() const {
    return std::to_string(line_) + " " + license_plate_.to_string() + " " + person_name_.to_string() + " " + car_.
           to_string() + " " + app_.to_string();
}

template<typename Type>
void CollectedType::set_field(std::istringstream &iss, const int counter) {
    std::string type;
    line_ = counter;
    if constexpr (std::is_same_v<Type, LicensePlate>) {
        std::getline(iss, type, '\t');
        license_plate_ = LicensePlate::parse(type);
    } else if constexpr (std::is_same_v<Type, PersonName>) {
        std::getline(iss, type, '\t');
        person_name_ = PersonName::parse(type);
    } else if constexpr (std::is_same_v<Type, Car>) {
        std::getline(iss, type, '\t');
        car_ = Car::parse(type);
    } else if constexpr (std::is_same_v<Type, Application>) {
        std::getline(iss, type, '\t');
        app_ = Application::parse(type);
    }
}

template<typename... Types>
void CollectedType::parse(const std::string &line, const int counter) {
    std::istringstream iss(line);
    ((set_field<Types>(iss, counter)), ...);
}

#endif //COLLECTED_TYPE_H
