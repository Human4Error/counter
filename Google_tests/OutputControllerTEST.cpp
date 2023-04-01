//
// Created by Alireza on 3/31/2023.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "OutputController.h"

#include <string>
#include <iostream>
#include <sstream>


TEST(OutoutConTest, coutString) {
    OutputFormat test_obj;

    std::string expected = "This is a test output";

    std::stringstream buffer;
    // Redirect std::cout to buffer
    std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    // BEGIN: Code being tested
    test_obj.print_line(expected);
    // END:   Code being tested

    // Use the string value of buffer to compare against expected output
    std::string text = buffer.str();
    int result = text.compare(expected);

    // Restore original buffer before exiting
    std::cout.rdbuf(prevcoutbuf);
    EXPECT_EQ(1, result);

}
