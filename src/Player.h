//
// Created by Alireza on 3/15/2023.
//

#ifndef COUNTER_PLAYER_H
#define COUNTER_PLAYER_H

#include <string>
#include <cstdint>
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

class PlayerBase {
public:
    virtual void set_Is_alive(bool t) = 0;

    [[nodiscard]] virtual TEAM_ID get_team_ID() const = 0;

    [[nodiscard]] virtual std::string get_name() const = 0;

    [[nodiscard]] virtual bool get_Is_alive() const = 0;

    [[nodiscard]] virtual uint32_t getHealth() const = 0;

    virtual void setHealth(uint32_t h) = 0;

    virtual void reduceHealth(uint32_t damage) = 0;

    [[nodiscard]] virtual uint32_t getMoney() const = 0;

    virtual void setMoney(uint32_t m) = 0;

    virtual void reduceMoney(uint32_t red_m) = 0;

    virtual void increaseMoney(uint32_t inc_m) = 0;

    [[nodiscard]] virtual uint32_t getNumber_of_kills() const = 0;

    [[nodiscard]] virtual uint32_t getNumber_of_deaths() const = 0;

    virtual void number_of_kills_Increment_one() = 0;

    virtual void number_of_deaths_Increment_one() = 0;

    virtual void setHeavy_weapon(Weapon *wp) = 0;

    virtual void setLight_weapon(Weapon *wp) = 0;

    virtual void removeHeavy_weapon() = 0;

    virtual void removeLight_weapon() = 0;

    virtual void setMele_weapon(Weapon *wp) = 0;

    [[nodiscard]] virtual Weapon *getHeavy_weapon() const = 0;

    [[nodiscard]] virtual Weapon *getLight_weapon() const = 0;

    [[nodiscard]] virtual Weapon *getMele_weapon() const = 0;

    [[nodiscard]] virtual uint32_t getPlayer_ID() const = 0;

};

class Player : public PlayerBase {
public:
    Player() = delete;

    Player(std::string user_name, TEAM_ID team_ID, uint32_t pl_ID);

    // Copy c_tor
    Player(const Player &_p) = default;

    // copy assignment
    Player &operator=(const Player &_p) = default;

    // move constructor
    Player(Player &&_p) = default;

    // move assignment
    Player &operator=(Player &&_p) = default;

    virtual ~Player() = default;

    void set_Is_alive(bool t) override;

    [[nodiscard]] TEAM_ID get_team_ID() const override;

    [[nodiscard]] std::string get_name() const override;

    [[nodiscard]] bool get_Is_alive() const override;

    [[nodiscard]] uint32_t getHealth() const override;

    void setHealth(uint32_t h) override;

    void reduceHealth(uint32_t damage) override;

    [[nodiscard]] uint32_t getMoney() const override;

    void setMoney(uint32_t m) override;

    void reduceMoney(uint32_t red_m) override;

    void increaseMoney(uint32_t inc_m) override;

    [[nodiscard]] uint32_t getNumber_of_kills() const override;

    [[nodiscard]] uint32_t getNumber_of_deaths() const override;

    void number_of_kills_Increment_one() override;

    void number_of_deaths_Increment_one() override;

    void setHeavy_weapon(Weapon *wp) override;

    void setLight_weapon(Weapon *wp) override;

    void removeHeavy_weapon() override;

    void removeLight_weapon() override;

    void setMele_weapon(Weapon *wp) override;

    [[nodiscard]] Weapon *getHeavy_weapon() const override;

    [[nodiscard]] Weapon *getLight_weapon() const override;

    [[nodiscard]] Weapon *getMele_weapon() const override;

    [[nodiscard]] uint32_t getPlayer_ID() const override;

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

class TeamBase {
public:
    virtual void add_player(const Player &pl, TEAM_ID teamId) = 0;

    [[nodiscard]] virtual bool check_team_is_full(TEAM_ID teamId) const = 0;

    virtual Player &return_PLayer_by_username(std::string &username) = 0;

    virtual bool find_player_by_username(std::string &username) const = 0;

    virtual void sort_player_list() = 0;

    virtual void reset_health_all_players() = 0;

    virtual void increase_money_T_players(uint32_t money) = 0;

    virtual void increase_money_CT_players(uint32_t money) = 0;

    virtual void remove_heavy_pistol_wp_from_deads() = 0;

    virtual uint32_t get_number_of_alive_T_player() = 0;

    virtual uint32_t get_number_of_alive_CT_player() = 0;

    virtual void print_lists_ct() = 0;

    virtual void print_lists_t() = 0;
};

class Team : public TeamBase {
public:
    Team() = default;

    // Copy c_tor
    Team(const Team &_t) = default;

    // move constructor
    Team(Team &&_t) = default;

    virtual ~Team() = default;

    void add_player(const Player &pl, TEAM_ID teamId) override;

    [[nodiscard]] bool check_team_is_full(TEAM_ID teamId) const override;

    Player &return_PLayer_by_username(std::string &username) override;

    bool find_player_by_username(std::string &username) const override;

    void sort_player_list() override;

    void reset_health_all_players() override;

    void increase_money_T_players(uint32_t money) override;

    void increase_money_CT_players(uint32_t money) override;

    void remove_heavy_pistol_wp_from_deads() override;

    uint32_t get_number_of_alive_T_player() override;

    uint32_t get_number_of_alive_CT_player() override;

    void print_lists_ct() override;

    void print_lists_t() override;

private:
    OutputFormat m_OutputFormat;
    std::vector<Player> m_CT_player_list;
    std::vector<Player> m_T_player_list;
    const uint32_t m_team_max_player = 10;
};

#endif //COUNTER_PLAYER_H
