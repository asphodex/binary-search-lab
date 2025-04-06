#include <iostream>
#include <vector>

#include "include/App.h"
#include "include/BinarySearch.h"
#include "include/FileReader.h"
#include "include/LinearSearch.h"
#include "include/Slog.h"
#include "include/path.h"
#include "include/data-types/Application.h"
#include "include/data-types/LicensePlate.h"
#include "include/data-types/PersonName.h"
#include "include/data-types/Car.h"
#include "include/data-types/CollectedType.h"


int main() {
    system("chcp 65001");

    //auto generator = Generator();

    //generator.generate_file<LicensePlate, PersonName, Car, Application>(
    //    get_absolute_file_path("resources/input/input.txt"), 100000, Generator::Lang::ENGLISH);


    // в случае CollectedType добавить статическую counter и метод parse(str)
    try {
        App app;
        app.run<Application>(get_absolute_file_path("resources/input/input.txt"), get_absolute_file_path("resources/output/"), "output.txt");
    } catch (const std::exception &e) {
        Slog::error(e.what());
    }
}
