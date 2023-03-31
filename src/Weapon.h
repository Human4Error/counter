//
// Created by Alireza on 3/15/2023.
//

#ifndef COUNTER_WEAPON_H
#define COUNTER_WEAPON_H

#include <string>
#include <vector>
#include <stdint.h>

typedef enum WeaponType {
    HEAVY_WP,
    LIGHT_WP,
    MELE_WP,
} WEAPON_TYPE;
typedef enum WeaponUser_t {
    TERRORIST_WP,
    COUNTER_TERRORIST_WP,
    FREE_FOR_ALL,
} WEAPON_USER_TYPE;

class Weapon {

public:

    Weapon() = delete;

    Weapon(std::string _name,
           uint32_t _damage,
           uint32_t _price,
           uint32_t _kill_reward,
           WEAPON_TYPE _wp_t,
           WEAPON_USER_TYPE _wp_user_t);

    ~Weapon() = default;

    const std::string &getMName() const;

    uint32_t getMDamage() const;

    uint32_t getMPrice() const;

    uint32_t getKillReward() const;

    WEAPON_TYPE getWpType() const;

    WEAPON_USER_TYPE getWpUser() const;

private:
    std::string m_name = "";
    uint32_t m_damage{0};
    uint32_t m_price{0};
    uint32_t m_Kill_reward{0};
    WEAPON_TYPE m_wp_type{};
    WEAPON_USER_TYPE m_wp_user{};
};

class WeaponSets {
public:
    WeaponSets();

    ~WeaponSets() = default;


    std::vector<Weapon>::iterator findWP(std::string wp_name, bool &find_that_wp);


    void addHeavyWP(Weapon wp);

    void addLightWP(Weapon wp);

    void addMeleeWP(Weapon wp);

private:
    std::vector<Weapon>::iterator findWP_in_list(std::vector<Weapon> &wp_list, std::string &wp_name);

    std::vector<Weapon> list_Heavy_WP;
    std::vector<Weapon> list_Light_WP;
    std::vector<Weapon> list_Mele_WP;

};


#endif //COUNTER_WEAPON_H


