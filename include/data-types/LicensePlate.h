//
// Created by sphdx on 17.01.2025.
//

#ifndef LICENSEPLATE_H
#define LICENSEPLATE_H

#include <ostream>
#include <utility>

class LicensePlate {
    std::string letter1_{}, letter2_{}, letter3_{};
    int number_ = 0;

public:
    LicensePlate(std::string l1, int num, std::string  l2, std::string  l3);

    LicensePlate();

    bool operator<(const LicensePlate &other) const;

    bool operator>(const LicensePlate &other) const;

    bool operator==(const LicensePlate &other) const;

    bool operator!() const;

    friend std::ostream &operator<<(std::ostream &os, const LicensePlate &lp);

    [[nodiscard]] std::string to_string() const;

    // isValidLicensePlate takes string like 'A123AA' and returns false if it is invalid license plate or true if valid
    static bool is_valid_license_plate(const std::string &plate);

    // parseLicensePlate takes string like 'A123AA' and returns an object of licensePlate structure
    static LicensePlate parse(const std::string &plate);
};

inline std::ostream &operator<<(std::ostream &os, const LicensePlate &lp) {
    return os << lp.letter1_ << lp.number_ << lp.letter2_ << lp.letter3_;
}

inline LicensePlate::LicensePlate(std::string  l1, const int num, std::string  l2, std::string  l3)
    : letter1_(std::move(l1)), letter2_(std::move(l2)), letter3_(std::move(l3)), number_(num) {
}

inline LicensePlate::LicensePlate() = default;

inline bool LicensePlate::operator<(const LicensePlate &other) const {
    if (letter1_ != other.letter1_) return letter1_ < other.letter1_;
    if (number_ != other.number_) return number_ < other.number_;
    if (letter2_ != other.letter2_) return letter2_ < other.letter2_;
    return letter3_ < other.letter3_;
}

inline bool LicensePlate::operator>(const LicensePlate &other) const {
    if (letter1_ != other.letter1_) return letter1_ > other.letter1_;
    if (number_ != other.number_) return number_ > other.number_;
    if (letter2_ != other.letter2_) return letter2_ > other.letter2_;
    return letter3_ > other.letter3_;
}

inline bool LicensePlate::operator==(const LicensePlate &other) const {
    return letter1_ == other.letter1_ && number_ == other.number_ && letter2_ == other.letter2_ && letter3_ == other.
           letter3_;
}

inline bool LicensePlate::operator!() const {
    return letter1_.empty() && number_ == 0 && letter2_.empty() && letter3_.empty();
}

inline std::string LicensePlate::to_string() const {
    return letter1_ + std::to_string(number_) + letter2_ + letter3_;
}

inline bool LicensePlate::is_valid_license_plate(const std::string &plate) {
    return plate.length() == 6 &&
           std::isalpha(plate[0]) &&
           std::isdigit(plate[1]) &&
           std::isdigit(plate[2]) &&
           std::isdigit(plate[3]) &&
           std::isalpha(plate[4]) &&
           std::isalpha(plate[5]);
}

inline LicensePlate LicensePlate::parse(const std::string &plate) {
    return {plate.substr(0, 1), std::stoi(plate.substr(1, 3)), plate.substr(4, 1), plate.substr(5, 1)};
}


#endif //LICENSEPLATE_H
