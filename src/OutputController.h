//
// Created by Alireza on 3/30/2023.
//

#ifndef COUNTER_OUTPUTCONTROLLER_H
#define COUNTER_OUTPUTCONTROLLER_H

#include "iostream"

class OutputFormat {
public:
    OutputFormat() = default;

    // Copy c_tor
    OutputFormat(const OutputFormat &_o) = default;

    // copy assignment
    OutputFormat &operator=(const OutputFormat &_o) = default;

    // move constructor
    OutputFormat(OutputFormat &&_o) = default;

    // move assignment
    OutputFormat &operator=(OutputFormat &&_o) = default;

    ~OutputFormat() = default;

    virtual void print_line(const std::string &out_str) {
        std::cout << out_str << std::endl;
    }

};

#endif //COUNTER_OUTPUTCONTROLLER_H
