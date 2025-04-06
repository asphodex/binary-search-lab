//
// Created by sphdx on 17.01.2025.
//

#ifndef PERSON_name_H
#define PERSON_name_H

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>

class PersonName {
    std::string first_name_{}, last_name_{}, middle_name_{};

    static std::string get_first_three(const std::string &str);

public:
    PersonName(std::string first_name, std::string last_name, std::string middle_name);

    PersonName();

    bool operator<(const PersonName &other) const;

    bool operator>(const PersonName &other) const;

    bool operator==(const PersonName &other) const;

    bool operator!() const;

    friend std::ostream &operator<<(std::ostream &os, const PersonName &pn);

    [[nodiscard]] std::string to_string() const;

    static PersonName parse(const std::string &name);
};

inline std::ostream &operator<<(std::ostream &os, const PersonName &pn) {
    return os << pn.last_name_ << " " << pn.first_name_ << " " << pn.middle_name_;
}

inline bool PersonName::operator<(const PersonName &other) const {
    const std::string this_first_three = get_first_three(last_name_) + get_first_three(first_name_) +
                                         get_first_three(middle_name_);
    const std::string other_first_three = get_first_three(other.last_name_) + get_first_three(other.first_name_) +
                                          get_first_three(other.middle_name_);

    if (this_first_three != other_first_three) {
        return this_first_three < other_first_three;
    }

    // recursive calls
    if (first_name_ != other.first_name_) return first_name_ < other.first_name_;
    if (last_name_ != other.last_name_) return last_name_ < other.last_name_;
    return middle_name_ < other.middle_name_;
}

inline bool PersonName::operator>(const PersonName &other) const {
    return other < *this;
}

inline bool PersonName::operator==(const PersonName &other) const {
    return first_name_ == other.first_name_ && last_name_ == other.last_name_ && middle_name_ == other.middle_name_;
}

inline bool PersonName::operator!() const {
    return first_name_.empty() && last_name_.empty() && middle_name_.empty();
}

inline std::string PersonName::to_string() const {
    return first_name_ + " " + last_name_ + " " + middle_name_;
}

inline std::string PersonName::get_first_three(const std::string &str) {
    return str.substr(0, std::min(3, static_cast<int>(str.length())));
}

inline PersonName PersonName::parse(const std::string &name) {
    std::istringstream iss(name);
    std::string lastName, firstName, middleName;
    iss >> lastName >> firstName >> middleName;
    return PersonName{firstName, lastName, middleName};
}

inline PersonName::PersonName(std::string first_name, std::string last_name,
                              std::string middle_name) : first_name_(std::move(first_name)),
                                                         last_name_(std::move(last_name)),
                                                         middle_name_(std::move(middle_name)) {
}

inline PersonName::PersonName() = default;

#endif //PERSON_name_H
