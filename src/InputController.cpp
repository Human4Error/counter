//
// Created by Alireza on 3/15/2023.
//
#include "InputController.h"

void InputController::start_cli(GameController *game_con) {

    uint32_t num_rounds = read_num_rounds();
    for (int i = 0; i < num_rounds; ++i) {
        uint32_t cmd_num4this_round = read_round_num_CMD();
        setup_start_round(game_con);

        for (int j = 0; j < cmd_num4this_round; ++j) {
            translate_string_2_method(read_one_line_cmd(), game_con);
        }
        result_end_round(game_con);
    }

}

uint32_t InputController::read_num_rounds() {
    uint32_t temp = 0;
    std::cin >> temp;
    return temp;
}

uint32_t InputController::read_round_num_CMD() {
    std::string temp_str;
    uint32_t num_cmd{0};
    std::getline(std::cin >> std::ws, temp_str);
    sscanf(temp_str.c_str(), "ROUND %d", &num_cmd);
    return num_cmd;
}

std::string InputController::read_one_line_cmd() {
    std::string temp_str;
    std::getline(std::cin >> std::ws, temp_str);
    return temp_str;
}

void InputController::setup_start_round(GameController *game_con) {
    game_con->start_round();
}

void InputController::result_end_round(GameController *game_con) {
    game_con->result_end_round();
}

void InputController::translate_string_2_method(std::string cmd, GameController *game_con) {
    std::stringstream cmd_2_process(cmd);
    std::string command_type("");
    cmd_2_process >> command_type;
    std::string username;
    std::string time;

    // todo have function map is better.
    if (command_type == "ADD-USER") {
        std::string team_str;
        cmd_2_process >> username;
        cmd_2_process >> team_str;
        cmd_2_process >> time;
        game_con->cmd_add_user(username, team_str, time);

    } else if (command_type == "GET-MONEY") {
        cmd_2_process >> username;
        cmd_2_process >> time;
        game_con->cmd_get_money(username, time);

    } else if (command_type == "GET-HEALTH") {
        cmd_2_process >> username;
        cmd_2_process >> time;
        game_con->cmd_get_health(username, time);

    } else if (command_type == "TAP") {
        std::string user_attacker;
        std::string user_attacked;
        std::string wp_type;

        cmd_2_process >> user_attacker;
        cmd_2_process >> user_attacked;
        cmd_2_process >> wp_type;
        cmd_2_process >> time;
        game_con->cmd_tap(user_attacker, user_attacked,
                          wp_type, time);

    } else if (command_type == "BUY") {
        std::string gun_name;

        cmd_2_process >> username;
        cmd_2_process >> gun_name;
        cmd_2_process >> time;
        game_con->cmd_buy(username, gun_name, time);


    } else if (command_type == "SCORE-BOARD") {
        cmd_2_process >> time;
        game_con->cmd_show_score_board(time);
    } else {
        // now nothing todo;
    }

}
