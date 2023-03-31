//
// Created by Alireza on 3/15/2023.
//

#include "GameController.h"


uint32_t Game_time_str2time_stamp_ms(const std::string& time_str) {
    uint32_t min, sec, milS;
    sscanf(time_str.c_str(), "%d:%d:%d", &min, &sec, &milS);
    return (min * 60 * 1000) + (sec * 1000) + milS;
}

uint32_t TimeController::get_dead_start_ms() const {
    return m_dead_start_ms;
}

uint32_t TimeController::get_max_time_to_buy_ms() const {
    return m_max_time_to_buy_ms;
}

uint32_t TimeController::get_max_round_time_ms() const {
    return m_max_round_time_ms;
}

void ShootingController::shoot_player(Player &A, Player &B, WEAPON_TYPE wp_t) {

    if (!(this->check_attacker_player_is_alive(A))) {
        m_OutputFormat.print_line(c_attacker_is_dead);
        return;
    }

    if (!(this->check_attacked_player_is_alive(B))) {
        m_OutputFormat.print_line(c_attacked_is_dead);
        return;
    }

    if (!(this->check_player_have_specified_type_gun(A, wp_t))) {
        m_OutputFormat.print_line(c_no_such_gun);
        return;
    }

    if (!(this->check_attacked_player_is_enemy(A, B))) {
        m_OutputFormat.print_line(c_friendly_fire);
        return;
    }

    // shooting is valid _register it
    uint32_t damage = damage_of_weapon_attacker(A, wp_t);
    damage_attacked_player(B, damage);
    if (!(this->check_attacked_player_is_alive(B))) {
        update_money_of_killer_player(A, reward_gain_from_killing(A, wp_t));
        update_number_of_two_player_kills_deaths(A, B);
    }
    m_OutputFormat.print_line(c_nice_shot);

}

const bool ShootingController::check_player_have_specified_type_gun(const Player &A, const WEAPON_TYPE wp_t) {

    bool out = false;
    if (wp_t == HEAVY_WP) {
        if (A.getHeavy_weapon() != nullptr) {
            out = true;
        }
    } else if (wp_t == LIGHT_WP) {
        if (A.getLight_weapon() != nullptr) {
            out = true;
        }
    } else if (wp_t == MELE_WP) {
        if (A.getMele_weapon() != nullptr) {
            out = true;
        }
    } else {

    }

    return out;
}

const bool ShootingController::check_attacker_player_is_alive(Player &A) const {
    return A.get_Is_alive();
}

const bool ShootingController::check_attacked_player_is_alive(Player &B) const {
    return B.get_Is_alive();
}

const bool ShootingController::check_attacked_player_is_enemy(Player &A, Player &B) const {

    if (A.get_team_ID() != B.get_team_ID()) {
        return true;
    }
    return false;
}

const uint32_t ShootingController::damage_of_weapon_attacker(const Player &A, const WEAPON_TYPE wp_t) const {
    uint32_t damage = 0;
    if (wp_t == HEAVY_WP) {
        damage = A.getHeavy_weapon()->getMDamage();
    } else if (wp_t == LIGHT_WP) {
        damage = A.getLight_weapon()->getMDamage();
    } else if (wp_t == MELE_WP) {
        damage = A.getMele_weapon()->getMDamage();
    } else {

    }
    return damage;
}

const uint32_t ShootingController::reward_gain_from_killing(const Player &A, const WEAPON_TYPE wp_t) const {
    uint32_t reward = 0;
    if (wp_t == HEAVY_WP) {
        reward = A.getHeavy_weapon()->getKillReward();
    } else if (wp_t == LIGHT_WP) {
        reward = A.getLight_weapon()->getKillReward();
    } else if (wp_t == MELE_WP) {
        reward = A.getMele_weapon()->getKillReward();
    } else {

    }
    return reward;
}

void ShootingController::damage_attacked_player(Player &B, uint32_t wp_damage) {
    B.reduceHealth(wp_damage);
}

void ShootingController::update_money_of_killer_player(Player &A, uint32_t reward) {
    A.increaseMoney(reward);
}

void ShootingController::update_number_of_two_player_kills_deaths(Player &A, Player &B) {
    A.number_of_kills_Increment_one();
    B.number_of_deaths_Increment_one();
}

void ShopController::buy_gun_for_player(Player &pl, WeaponSets &wp_set, std::string weapon, uint32_t time,
                                        TimeController &time_con) {

    if (!pl.get_Is_alive()) {
        m_OutputFormat.print_line(c_deads_can_not_buy);
        return;
    }

    if (!(this->check_time_is_valid_for_buying(time, time_con))) {
        m_OutputFormat.print_line(c_out_of_time);
        return;
    }

    bool wp_find = false;
    auto wp_it = wp_set.findWP(weapon, wp_find);
    if (wp_find == true) {

        if (!(this->check_this_gun_is_valid_for_player(pl, wp_it->getWpUser()))) {
            m_OutputFormat.print_line(c_invalid_gun_category);
            return;
        }

        if (wp_it->getMName() == "knife") {
            m_OutputFormat.print_line(c_invalid_gun_category);
            return;
        }

        if (this->check_player_now_have_this_gun(pl, wp_it)) {
            if (wp_it->getWpType() == HEAVY_WP) {
                m_OutputFormat.print_line(c_you_have_a_heavy);
            } else {
                m_OutputFormat.print_line(c_you_have_a_pistol);

            }
            return;
        }
        // player not have this
        if (this->check_player_have_enough_money(pl, wp_it->getMPrice())) { /// check player have money

            this->deduction_player_money(pl, wp_it->getMPrice());
            this->assign_weapon_for_player(pl, wp_it);
            m_OutputFormat.print_line(c_hope_use);
        } else {
            m_OutputFormat.print_line(c_no_enough_money);
        }

    } else { // wp not founded
        m_OutputFormat.print_line(c_invalid_gun_category);
        return;
    }
}

void ShopController::set_knife_for_new_players(Player &pl, WeaponSets &wp_set, std::string weapon) {

    bool wp_find = false;
    auto wp_it = wp_set.findWP(weapon, wp_find);
    if (wp_find == true) {
        this->assign_weapon_for_player(pl, wp_it);
    } else {

    }
}

const bool ShopController::check_this_gun_is_valid_for_player(const Player &pl, const WEAPON_USER_TYPE wp_user_t) const {

    bool out = false;
    if ((pl.get_team_ID() == TERRORIST) && (wp_user_t == TERRORIST_WP)) {
        out = true;
    } else if ((pl.get_team_ID() == COUNTER_TERRORIST) && (wp_user_t == COUNTER_TERRORIST_WP)) {
        out = true;
    } else if (wp_user_t == FREE_FOR_ALL) {
        out = true;
    } else {
        out = false;
    }

    return out;
}

const bool ShopController::check_player_have_enough_money(const Player &pl, const uint32_t wp_price) const {
    if (pl.getMoney() >= wp_price) {
        return true;
    }
    return false;
}

const bool ShopController::check_time_is_valid_for_buying(uint32_t time, TimeController &time_con) const {
    if (time >= time_con.get_max_time_to_buy_ms()) {
        return false;
    }
    return true;
}

void ShopController::deduction_player_money(Player &pl, uint32_t money) {
    pl.reduceMoney(money);
}

void ShopController::assign_weapon_for_player(Player &pl, std::vector<Weapon>::iterator &wp_it) {
    auto to_buy_wp_type = wp_it->getWpType();

    if (to_buy_wp_type == HEAVY_WP) {
        pl.setHeavy_weapon(&(*wp_it));
    } else if (to_buy_wp_type == LIGHT_WP) {
        pl.setLight_weapon(&(*wp_it));
    } else if (to_buy_wp_type == MELE_WP) {
        pl.setMele_weapon(&(*wp_it));
    }
}

const bool ShopController::check_player_now_have_this_gun(Player &pl, std::vector<Weapon>::iterator &wp_it
                                                          ) const {

    auto to_buy_wp_type = wp_it->getWpType();
    bool out = false;
    if ((to_buy_wp_type == HEAVY_WP) && (pl.getHeavy_weapon() != nullptr)) {
        out = true;
    } else if ((to_buy_wp_type == LIGHT_WP) && (pl.getLight_weapon() != nullptr)) {
        out = true;
    } else {
    }
    return out;
}

void GameController::start_round() {
    m_team.reset_health_all_players();
}

void GameController::result_end_round() {
    uint32_t t_alive = m_team.get_number_of_alive_T_player();
    uint32_t ct_alive = m_team.get_number_of_alive_CT_player();

    if (((t_alive == 0) && (ct_alive == 0)) || ((t_alive != 0) && (ct_alive != 0))) {
        m_OutputFormat.print_line(c_ct_won);
        m_team.increase_money_CT_players(c_winner_prize);
        m_team.increase_money_T_players(c_loser_prize);
    } else if (t_alive == 0) {
        m_OutputFormat.print_line(c_ct_won);
        m_team.increase_money_CT_players(c_winner_prize);
        m_team.increase_money_T_players(c_loser_prize);
    } else if (ct_alive == 0) {
        m_OutputFormat.print_line(c_t_won);
        m_team.increase_money_CT_players(c_loser_prize);
        m_team.increase_money_T_players(c_winner_prize);
    }
    m_team.remove_heavy_pistol_wp_from_deads();
}

void GameController::cmd_add_user(std::string username, std::string team_str, std::string time_str) {

    if (check_have_player_by_this_username(username)) {
        m_OutputFormat.print_line(c_you_are_already_in_game);
        return;
    }
    TEAM_ID team_id = find_team_ID(team_str);
    uint32_t cmd_time = Game_time_str2time_stamp_ms(time_str);

    if (check_team_is_full(team_id)) {
        m_OutputFormat.print_line(c_team_is_full);
        return;
    }

    Player new_Player(username, team_id, m_uniq_player_ID);
    m_uniq_player_ID++;
    if (cmd_time >= m_time_control.get_dead_start_ms()) {
        new_Player.setHealth(0);
    }
    new_Player.setMoney(1000); // start money
    m_shop_c.set_knife_for_new_players(new_Player, m_wp_sets, "knife");
    m_team.add_player(new_Player, team_id);
    if (team_id == TERRORIST) {
        m_OutputFormat.print_line(c_user_added_T);
    } else {
        m_OutputFormat.print_line(c_user_added_CT);
    }
    return;

}

void GameController::cmd_get_money(std::string username, std::string time_str) {
    if (!check_have_player_by_this_username(username)) {
        m_OutputFormat.print_line(c_invalid_username);
        return;
    }
    uint32_t player_money = m_team.return_PLayer_by_username(username).getMoney();
    m_OutputFormat.print_line(std::to_string(player_money));
}

void GameController::cmd_get_health(std::string username, std::string time_str) {
    if (!check_have_player_by_this_username(username)) {
        m_OutputFormat.print_line(c_invalid_username);
        return;
    }
    uint32_t player_health = m_team.return_PLayer_by_username(username).getHealth();
    m_OutputFormat.print_line(std::to_string(player_health));
}

void GameController::cmd_tap(std::string username_attacker, std::string username_attacked, std::string wp_type_str,
                             std::string time_str) {
    if (!check_have_player_by_this_username(username_attacker)) {
        m_OutputFormat.print_line(c_invalid_username);
        return;
    }
    if (!check_have_player_by_this_username(username_attacked)) {
        m_OutputFormat.print_line(c_invalid_username);
        return;
    }

    m_shoot_c.shoot_player(m_team.return_PLayer_by_username(username_attacker),
                           m_team.return_PLayer_by_username(username_attacked),
                           find_weapon_type(wp_type_str));


}

void GameController::cmd_buy(std::string username, std::string gun_name_str, std::string time_str) {

    if (!check_have_player_by_this_username(username)) {
        m_OutputFormat.print_line(c_invalid_username);
        return;
    }
    m_shop_c.buy_gun_for_player(m_team.return_PLayer_by_username(username),
                                m_wp_sets,
                                gun_name_str,
                                Game_time_str2time_stamp_ms(time_str),
                                m_time_control);
}

void GameController::cmd_show_score_board(std::string time_str) {

    m_team.sort_player_list();
    m_OutputFormat.print_line(c_ct_players);
    m_team.print_lists_ct();
    m_OutputFormat.print_line(c_t_players);
    m_team.print_lists_t();
}

const TEAM_ID GameController::find_team_ID(std::string &team_str) {
    TEAM_ID team_id = TERRORIST;
    if (team_str == "Terrorist") {
        team_id = TERRORIST;
    } else if (team_str == "Counter-Terrorist") {
        team_id = COUNTER_TERRORIST;
    } else {

    }
    return team_id;
}

WEAPON_TYPE GameController::find_weapon_type(std::string &wp_t_str) {
    WEAPON_TYPE out = HEAVY_WP;
    if (wp_t_str == "heavy") {
        out = HEAVY_WP;
    } else if (wp_t_str == "pistol") {
        out = LIGHT_WP;
    } else if (wp_t_str == "knife") {
        out = MELE_WP;
    } else {
        /// nothing
    }

    return out;
}

const bool GameController::check_have_player_by_this_username(std::string _user_name) {
    return m_team.find_player_by_username(_user_name);
}

const bool GameController::check_team_is_full(TEAM_ID teamId) {
    return m_team.check_team_is_full(teamId);
}
