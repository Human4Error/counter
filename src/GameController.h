//
// Created by Alireza on 3/15/2023.
//

#ifndef COUNTER_GAMECONTROLLER_H
#define COUNTER_GAMECONTROLLER_H

#include <iostream>
#include <sstream>
#include <string>
#include "Player.h"
#include "Weapon.h"
#include "OutputController.h"


uint32_t Game_time_str2time_stamp_ms(const std::string &time_str);

class TimeControllerBase {

    [[nodiscard]] virtual uint32_t get_dead_start_ms() const = 0;

    [[nodiscard]] virtual uint32_t get_max_time_to_buy_ms() const = 0;

};

class TimeController : public TimeControllerBase {
public:
    TimeController() = default;

    ~TimeController() = default;

    [[nodiscard]] uint32_t get_dead_start_ms() const override;

    [[nodiscard]] uint32_t get_max_time_to_buy_ms() const override;

private:
    uint32_t m_dead_start_ms{3000};
    uint32_t m_max_time_to_buy_ms{45000};
    uint32_t m_max_round_time_ms{135000};

};

class ShootingControllerBase {

    virtual void shoot_player(Player &A, Player &B, WEAPON_TYPE wp_t) = 0;

};

class ShootingController : public ShootingControllerBase {
public:
    ShootingController() = default;

    ~ShootingController() = default;

    void shoot_player(Player &A, Player &B, WEAPON_TYPE wp_t) override;

private:
    OutputFormat m_OutputFormat;

    static bool check_player_have_specified_type_gun(const Player &A, WEAPON_TYPE wp_t);

    static bool check_attacker_player_is_alive(Player &A);

    static bool check_attacked_player_is_alive(Player &B);

    static bool check_attacked_player_is_enemy(Player &A, Player &B);


    [[nodiscard]] static uint32_t damage_of_weapon_attacker(const Player &A, WEAPON_TYPE wp_t);

    [[nodiscard]] static uint32_t reward_gain_from_killing(const Player &A, WEAPON_TYPE wp_t);

    static void damage_attacked_player(Player &B, uint32_t wp_damage);

    static void update_money_of_killer_player(Player &A, uint32_t reward);

    static void update_number_of_two_player_kills_deaths(Player &A, Player &B);


    inline static const std::string c_invalid_username = "invalid username";
    inline static const std::string c_attacker_is_dead = "attacker is dead";
    inline static const std::string c_attacked_is_dead = "attacked is dead";
    inline static const std::string c_no_such_gun = "no such gun";
    inline static const std::string c_friendly_fire = "friendly fire";
    inline static const std::string c_nice_shot = "nice shot";

};

class ShopControllerBase {

    virtual void buy_gun_for_player(Player &pl, WeaponSets &wp_set, std::string weapon,
                                    uint32_t time, TimeController &time_con) = 0;

    virtual void set_knife_for_new_players(Player &pl, WeaponSets &wp_set, std::string weapon) = 0;
};

class ShopController : public ShopControllerBase {
public:
    ShopController() = default;

    virtual ~ShopController() = default;

    void buy_gun_for_player(Player &pl, WeaponSets &wp_set, std::string weapon,
                            uint32_t time, TimeController &time_con) override;

    void set_knife_for_new_players(Player &pl, WeaponSets &wp_set, std::string weapon) override;

private:
    OutputFormat m_OutputFormat;

    [[nodiscard]] static bool check_this_gun_is_valid_for_player(const Player &pl, WEAPON_USER_TYPE wp_user_t);

    [[nodiscard]] static bool check_player_have_enough_money(const Player &pl, uint32_t wp_price);

    static bool check_time_is_valid_for_buying(uint32_t time, TimeController &time_con);

    static void deduction_player_money(Player &pl, uint32_t money);

    static void assign_weapon_for_player(Player &pl, std::vector<Weapon>::iterator &wp_it);

    static bool check_player_now_have_this_gun(Player &pl, std::vector<Weapon>::iterator &wp_it);


    inline static const std::string c_invalid_username = "invalid username";
    inline static const std::string c_deads_can_not_buy = "deads can not buy";
    inline static const std::string c_out_of_time = "you are out of time";
    inline static const std::string c_invalid_gun_category = "invalid category gun";
    inline static const std::string c_you_have_a_pistol = "you have a pistol";
    inline static const std::string c_you_have_a_heavy = "you have a heavy";
    inline static const std::string c_no_enough_money = "no enough money";
    inline static const std::string c_hope_use = "I hope you can use it";


};

class GameControllerBase {

public:
    virtual void start_round() = 0;

    virtual void result_end_round() = 0;

    virtual void cmd_add_user(std::string username, std::string team_str,
                              std::string time_str) = 0;

    virtual void cmd_get_money(std::string username, std::string time_str) = 0;

    virtual void cmd_get_health(std::string username, std::string time_str) = 0;

    virtual void cmd_tap(std::string username_attacker, std::string username_attacked,
                         std::string wp_type_str, std::string time_str) = 0;

    virtual void cmd_buy(std::string username, std::string gun_name_str,
                         std::string time_str) = 0;

    virtual void cmd_show_score_board(std::string time_str) = 0;


};


class GameController : public GameControllerBase {
public:
    GameController() = default;

    // Copy c_tor
    GameController(const GameController &_g) = default;

    // move constructor
    GameController(GameController &&_g) = default;

    virtual ~GameController() = default;

    void start_round() override;

    void result_end_round() override;

    void cmd_add_user(std::string username, std::string team_str,
                      std::string time_str) override;

    void cmd_get_money(std::string username, std::string time_str) override;

    void cmd_get_health(std::string username, std::string time_str) override;

    void cmd_tap(std::string username_attacker, std::string username_attacked,
                 std::string wp_type_str, std::string time_str) override;

    void cmd_buy(std::string username, std::string gun_name_str,
                 std::string time_str) override;

    void cmd_show_score_board(std::string time_str) override;


private:
    static TEAM_ID find_team_ID(std::string &team_str);

    static WEAPON_TYPE find_weapon_type(std::string &wp_t_str);

    bool check_have_player_by_this_username(std::string _user_name);

    bool check_team_is_full(TEAM_ID teamId);

    inline static const std::string c_you_are_already_in_game = "you are already in this game";
    inline static const std::string c_user_added_T = "this user added to Terrorist";
    inline static const std::string c_user_added_CT = "this user added to Counter-Terrorist";
    inline static const std::string c_team_is_full = "this team is full";

    inline static const std::string c_invalid_username = "invalid username";

    inline static const std::string c_ct_players = "Counter-Terrorist-Players:";
    inline static const std::string c_t_players = "Terrorist-Players:";
    inline static const std::string c_ct_won = "Counter-Terrorist won";
    inline static const std::string c_t_won = "Terrorist won";
    inline static const uint32_t c_winner_prize = 2700;
    inline static const uint32_t c_loser_prize = 2400;


    uint32_t m_uniq_player_ID{0};
    WeaponSets m_wp_sets;
    ShopController m_shop_c{};
    ShootingController m_shoot_c{};
    TimeController m_time_control;
    Team m_team;
    OutputFormat m_OutputFormat;
};


#endif //COUNTER_GAMECONTROLLER_H
