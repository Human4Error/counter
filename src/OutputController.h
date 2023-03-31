//
// Created by Alireza on 3/30/2023.
//

#ifndef COUNTER_OUTPUTCONTROLLER_H
#define COUNTER_OUTPUTCONTROLLER_H

#include "iostream"

class OutputFormat {
public:
    OutputFormat() = default;

    ~OutputFormat() = default;

    static void print_line(const std::string& out_str) {
        std::cout << out_str << std::endl;
    }

};

#endif //COUNTER_OUTPUTCONTROLLER_H
