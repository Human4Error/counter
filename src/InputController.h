//
//
// Created by Alireza on 3/15/2023.
//

#ifndef COUNTER_INPUTCONTROLLER_H
#define COUNTER_INPUTCONTROLLER_H

#include <iostream>
#include <stdint.h>
#include <string>
#include <sstream>
#include "GameController.h"


class InputController {

public:
    InputController() = default;

    virtual ~InputController() = default;

    void start_cli(GameController *game_con);

private:
    uint32_t read_num_rounds();

    uint32_t read_round_num_CMD();

    std::string read_one_line_cmd();

    void setup_start_round(GameController *game_con);

    void result_end_round(GameController *game_con);

    void translate_string_2_method(std::string cmd, GameController *game_con);


};


#endif //COUNTER_INPUTCONTROLLER_H
