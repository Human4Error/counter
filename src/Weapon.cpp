//
// Created by Alireza on 3/15/2023.
//

#include "Weapon.h"

#include <utility>



Weapon::Weapon(std::string _name, uint32_t _damage, uint32_t _price, uint32_t _kill_reward, WEAPON_TYPE _wp_t,
               WEAPON_USER_TYPE _wp_user_t) : m_name(std::move(_name)),
                                              m_damage(_damage),
                                              m_price(_price),
                                              m_Kill_reward(_kill_reward),
                                              m_wp_type(_wp_t),
                                              m_wp_user(_wp_user_t) {

}

const std::string &Weapon::getMName() const {
    return m_name;
}

uint32_t Weapon::getMDamage() const {
    return m_damage;
}

uint32_t Weapon::getMPrice() const {
    return m_price;
}

uint32_t Weapon::getKillReward() const {
    return m_Kill_reward;
}

WEAPON_TYPE Weapon::getWpType() const {
    return m_wp_type;
}

WEAPON_USER_TYPE Weapon::getWpUser() const {
    return m_wp_user;
}



WeaponSets::WeaponSets() {
    list_Heavy_WP.emplace_back("AK", 31, 2700, 100,
                               HEAVY_WP, TERRORIST_WP);
    list_Heavy_WP.emplace_back("AWP", 110, 4300, 50,
                               HEAVY_WP, FREE_FOR_ALL);
    list_Heavy_WP.emplace_back("M4A1", 29, 2700, 100,
                               HEAVY_WP, COUNTER_TERRORIST_WP);

    list_Light_WP.emplace_back("Revolver", 51, 600, 150,
                               LIGHT_WP, TERRORIST_WP);
    list_Light_WP.emplace_back("Glock-18", 11, 300, 200,
                               LIGHT_WP, TERRORIST_WP);

    list_Light_WP.emplace_back("Desert-Eagle", 53, 600, 175,
                               LIGHT_WP, COUNTER_TERRORIST_WP);
    list_Light_WP.emplace_back("UPS-S", 13, 300, 225,
                               LIGHT_WP, COUNTER_TERRORIST_WP);

    list_Melee_WP.emplace_back("knife", 43, 0, 500,
                               MELE_WP, FREE_FOR_ALL);

}

std::vector<Weapon>::iterator WeaponSets::findWP(std::string wp_name, bool &find_that_wp) { /// check find_
    find_that_wp = false;
    std::vector<Weapon>::iterator it1 = findWP_in_list(list_Heavy_WP, wp_name);
    if (it1 != list_Heavy_WP.end()) {
        find_that_wp = true;
        return it1;
    }
    it1 = findWP_in_list(list_Light_WP, wp_name);
    if (it1 != list_Light_WP.end()) {
        find_that_wp = true;
        return it1;
    }
    it1 = findWP_in_list(list_Melee_WP, wp_name);
    if (it1 != list_Melee_WP.end()) {
        find_that_wp = true;
        return it1;
    }

    return it1;
}

[[maybe_unused]] void WeaponSets::addHeavyWP(const Weapon& wp) {
    list_Heavy_WP.push_back(wp);
}

void WeaponSets::addLightWP(const Weapon& wp) {
    list_Light_WP.push_back(wp);
}

void WeaponSets::addMeleeWP(const Weapon& wp) {
    list_Melee_WP.push_back(wp);
}

std::vector<Weapon>::iterator WeaponSets::findWP_in_list(std::vector<Weapon> &wp_list, std::string &wp_name) {

    for (auto it = wp_list.begin(); it < wp_list.end(); ++it) {
        if (it->getMName() == wp_name) {
            return it;
        }
    }
    return wp_list.end();
}

