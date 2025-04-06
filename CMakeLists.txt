cmake_minimum_required(VERSION 3.30)
project(binary_search)

set(CMAKE_CXX_STANDARD 26)

add_executable(binary_search main.cpp
        include/BinarySearch.h
        include/slog.h
        include/LinearSearch.h
        include/data-types/Application.h
        include/Generator.h
        include/data-types/CollectedType.h
        include/App.h
        include/CmdInput.h
        include/FileReader.h
        include/data-types/LicensePlate.h
        include/data-types/PersonName.h
        include/data-types/Car.h
        include/ShellSort.h)
