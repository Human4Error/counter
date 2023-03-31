//
// Created by Alireza on 3/15/2023.
//

#ifndef COUNTER_PLAYER_H
#define COUNTER_PLAYER_H

#include <string>
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include "Weapon.h"
#include "OutputController.h"


const uint32_t HEALTH_MAX = 100;
const uint32_t HEALTH_MIN = 0;
const uint32_t MAX_MONEY = 10000;

typedef enum TeamID {
    TERRORIST,
    COUNTER_TERRORIST,
} TEAM_ID;

class TimeController;

class Player {
public:
    Player() = delete;

    Player(std::string user_name, TEAM_ID team_ID, uint32_t pl_ID);

    virtual ~Player() = default;

    void set_Is_alive(bool t);

    const TEAM_ID get_team_ID() const;

    const std::string get_name() const;

    bool get_Is_alive() const;

    uint32_t getHealth() const;

    void setHealth(uint32_t h);

    void reduceHealth(uint32_t damage);

    uint32_t getMoney() const;

    void setMoney(uint32_t m);

    void reduceMoney(uint32_t red_m);

    void increaseMoney(uint32_t inc_m);

    uint32_t getNumber_of_kills() const;

    uint32_t getNumber_of_deaths() const;

    void number_of_kills_Increment_one();

    void number_of_deaths_Increment_one();

    void setHeavy_weapon(Weapon *wp);

    void setLight_weapon(Weapon *wp);

    void removeHeavy_weapon();

    void removeLight_weapon();

    void setMele_weapon(Weapon *wp);

    Weapon *getHeavy_weapon() const;

    Weapon *getLight_weapon() const;

    Weapon *getMele_weapon() const;

    uint32_t getPlayer_ID() const;

private:


    std::string m_username;
    TEAM_ID m_teamID = TERRORIST;
    uint32_t m_player_ID = 0;
    bool m_player_is_alive = true;
    uint32_t m_health = HEALTH_MAX;
    uint32_t m_money = 0;
    uint32_t m_number_of_kills = 0;
    uint32_t m_number_of_deaths = 0;

    Weapon *m_Heavy_wp = nullptr;
    Weapon *m_Light_wp = nullptr;
    Weapon *m_mele_wp = nullptr;

};

class Team {
public:
    Team() = default;

    virtual ~Team() = default;

    void add_player(const Player& pl, TEAM_ID teamId);

    bool check_team_is_full(TEAM_ID teamId) const;

    Player &return_PLayer_by_username(std::string username);

    bool find_player_by_username(std::string username);

    void sort_player_list();

    void reset_health_all_players();

    void increase_money_T_players(uint32_t money);

    void increase_money_CT_players(uint32_t money);

    void remove_heavy_pistol_wp_from_deads();

    uint32_t get_number_of_alive_T_player();

    uint32_t get_number_of_alive_CT_player();

    void print_lists_ct();

    void print_lists_t();

private:
    OutputFormat m_OutputFormat;
    std::vector<Player> m_CT_player_list;
    std::vector<Player> m_T_player_list;
    const uint32_t m_team_max_player = 10;
};

#endif //COUNTER_PLAYER_H
