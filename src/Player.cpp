//
// Created by Alireza on 3/15/2023.
//

#include "Player.h"

Player::Player(std::string user_name, TEAM_ID team_ID, uint32_t pl_ID) : m_username(std::move(user_name)), m_teamID(team_ID),
                                                                         m_player_ID(pl_ID) {


}

void Player::set_Is_alive(bool t) {
    m_player_is_alive = t;
}

TEAM_ID Player::get_team_ID() const {
    return m_teamID;
}

std::string Player::get_name() const {
    return m_username;
}

bool Player::get_Is_alive() const {
    return m_player_is_alive;
}

uint32_t Player::getHealth() const {
    return m_health;
}

void Player::setHealth(uint32_t h) {
    if (h <= HEALTH_MAX) {
        if (h > HEALTH_MIN) {
            set_Is_alive(true);
        } else {
            set_Is_alive(false);
        }
        m_health = h;
    }
}

void Player::reduceHealth(uint32_t damage) {
    int new_health = (int) m_health - (int) damage;
    if (new_health <= HEALTH_MIN) {
        m_health = HEALTH_MIN;
        set_Is_alive(false);
    } else {
        m_health = new_health;
    }
}

uint32_t Player::getMoney() const {
    return m_money;
}

void Player::setMoney(uint32_t m) {
    m_money = m;
}

void Player::reduceMoney(uint32_t red_m) {
    long int new_mon = m_money - red_m;
    if (new_mon < 0) {
        // throw exp
    } else {
        m_money = new_mon;
    }
}

void Player::increaseMoney(uint32_t inc_m) {
    m_money += inc_m;
    if (m_money > MAX_MONEY) {
        m_money = MAX_MONEY;
    }
}

uint32_t Player::getNumber_of_kills() const {
    return m_number_of_kills;
}

uint32_t Player::getNumber_of_deaths() const {
    return m_number_of_deaths;
}

void Player::number_of_kills_Increment_one() {
    m_number_of_kills++;
}

void Player::number_of_deaths_Increment_one() {
    m_number_of_deaths++;
}

void Player::setHeavy_weapon(Weapon *wp) {//  todo use refrence
    m_Heavy_wp = wp;
}

void Player::setLight_weapon(Weapon *wp) {
    m_Light_wp = wp;
}

void Player::removeHeavy_weapon() {
    setHeavy_weapon(nullptr);
}

void Player::removeLight_weapon() {
    setLight_weapon(nullptr);
}

void Player::setMele_weapon(Weapon *wp) {
    m_mele_wp = wp;
}

Weapon *Player::getHeavy_weapon() const {
    return m_Heavy_wp;
}

Weapon *Player::getLight_weapon() const {
    return m_Light_wp;
}

Weapon *Player::getMele_weapon() const {
    return m_mele_wp;
}

uint32_t Player::getPlayer_ID() const {
    return m_player_ID;
}

void Team::add_player(const Player &pl, TEAM_ID teamId) {
    if (check_team_is_full(teamId)) {
        return;
    }
    if (teamId == TERRORIST) {
        m_T_player_list.push_back(pl);
    } else {
        m_CT_player_list.push_back(pl);
    }
}

bool Team::check_team_is_full(TEAM_ID teamId) const {
    uint32_t player_count = m_team_max_player;
    if (teamId == TERRORIST) {
        player_count = m_T_player_list.size();
    } else {
        player_count = m_CT_player_list.size();
    }


    if (player_count >= m_team_max_player) {
        return true;
    } else {
        return false;
    }

}

Player &Team::return_PLayer_by_username(std::string& username) {
    auto it = m_CT_player_list.begin();
    bool found = false;
    for (it = m_CT_player_list.begin(); it < m_CT_player_list.end(); ++it) {
        if (it->get_name() == username) {
            found = true;
            break;
        }
    }
    if (!found) {
        for (it = m_T_player_list.begin(); it < m_T_player_list.end(); ++it) {
            if (it->get_name() == username) {
                found = true;
                break;
            }
        }
    }

    return *it;
}

bool Team::find_player_by_username(std::string& username) const {


    for (const auto& p: m_CT_player_list) {
        if (p.get_name() == username) {
            return true;
        }
    }
    for (const auto& p: m_T_player_list) {
        if (p.get_name() == username) {
            return true;
        }
    }

    return false;
}

void Team::sort_player_list() {

    std::sort(m_CT_player_list.begin(), m_CT_player_list.end(),
              [](Player &a, Player &b) {
                  if (a.getNumber_of_kills() == b.getNumber_of_kills()) {

                      if (a.getNumber_of_deaths() == b.getNumber_of_deaths()) {
                          return a.getPlayer_ID() < b.getPlayer_ID();
                      } else {
                          return a.getNumber_of_deaths() < b.getNumber_of_deaths();
                      }

                  } else {
                      return a.getNumber_of_kills() > b.getNumber_of_kills();
                  }
              });
    std::sort(m_T_player_list.begin(), m_T_player_list.end(),
              [](Player &a, Player &b) {
                  if (a.getNumber_of_kills() == b.getNumber_of_kills()) {

                      if (a.getNumber_of_deaths() == b.getNumber_of_deaths()) {
                          return a.getPlayer_ID() < b.getPlayer_ID();
                      } else {
                          return a.getNumber_of_deaths() < b.getNumber_of_deaths();
                      }

                  } else {
                      return a.getNumber_of_kills() > b.getNumber_of_kills();
                  }
              });

}

void Team::reset_health_all_players() {
    for (auto it = m_CT_player_list.begin(); it < m_CT_player_list.end(); ++it) {
        it->setHealth(HEALTH_MAX);
    }
    for (auto it = m_T_player_list.begin(); it < m_T_player_list.end(); ++it) {
        it->setHealth(HEALTH_MAX);
    }
}

void Team::increase_money_T_players(uint32_t money) {
    for (auto it = m_T_player_list.begin(); it < m_T_player_list.end(); ++it) {
        it->increaseMoney(money);
    }
}

void Team::increase_money_CT_players(uint32_t money) {
    for (auto it = m_CT_player_list.begin(); it < m_CT_player_list.end(); ++it) {
        it->increaseMoney(money);
    }
}

void Team::remove_heavy_pistol_wp_from_deads() {
    for (auto it = m_CT_player_list.begin(); it < m_CT_player_list.end(); ++it) {
        if (!(it->get_Is_alive())) {
            it->removeHeavy_weapon();
            it->removeLight_weapon();
        }
    }
    for (auto it = m_T_player_list.begin(); it < m_T_player_list.end(); ++it) {
        if (!(it->get_Is_alive())) {
            it->removeHeavy_weapon();
            it->removeLight_weapon();
        }
    }
}

uint32_t Team::get_number_of_alive_T_player() {
    uint32_t cnt = 0;
    for (auto it = m_T_player_list.begin(); it < m_T_player_list.end(); ++it) {
        if ((it->get_Is_alive())) {
            cnt++;
        }
    }
    return cnt;
}

uint32_t Team::get_number_of_alive_CT_player() {
    uint32_t cnt = 0;
    for (auto it = m_CT_player_list.begin(); it < m_CT_player_list.end(); ++it) {
        if ((it->get_Is_alive())) {
            cnt++;
        }
    }
    return cnt;
}

void Team::print_lists_ct() {
    uint32_t rank = 1;
    for (auto it = m_CT_player_list.begin(); it < m_CT_player_list.end(); ++it) {
        std::string line = std::to_string(rank) + " " + it->get_name() + " " +
                           std::to_string(it->getNumber_of_kills()) + " " +
                           std::to_string(it->getNumber_of_deaths());
        OutputFormat::print_line(line);
        rank++;
    }

}

void Team::print_lists_t() {
    uint32_t rank = 1;

    for (auto it = m_T_player_list.begin(); it < m_T_player_list.end(); ++it) {
        std::string line = std::to_string(rank) + " " + it->get_name() + " " +
                           std::to_string(it->getNumber_of_kills()) + " " +
                           std::to_string(it->getNumber_of_deaths());
        OutputFormat::print_line(line);
        rank++;
    }
}
