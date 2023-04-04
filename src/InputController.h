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

class InputControllerBase {
public:

    virtual void start_cli(GameControllerBase *game_con) = 0;

    virtual void translate_string_2_method(std::string cmd, GameControllerBase *game_con) = 0;

private:
    virtual uint32_t read_num_rounds() = 0;

    virtual uint32_t read_round_num_CMD() = 0;

    virtual std::string read_one_line_cmd() = 0;

    virtual void setup_start_round(GameControllerBase *game_con) = 0;

    virtual void result_end_round(GameControllerBase *game_con) = 0;


};


class InputController : public InputControllerBase {

public:
    InputController() = default;

    virtual ~InputController() = default;

    // Copy c_tor
    InputController(const InputController &_i) = default;

    // copy assignment
    InputController &operator=(const InputController &_i) = default;

    // move constructor
    InputController(InputController &&_i) = default;

    // move assignment
    InputController &operator=(InputController &&_i) = default;

    void start_cli(GameControllerBase *game_con) override;

    void translate_string_2_method(std::string cmd, GameControllerBase *game_con) override;

private:
    uint32_t read_num_rounds() override;

    uint32_t read_round_num_CMD() override;

    std::string read_one_line_cmd() override;

    void setup_start_round(GameControllerBase *game_con) override;

    void result_end_round(GameControllerBase *game_con) override;


};


#endif //COUNTER_INPUTCONTROLLER_H
