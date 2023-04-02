//
// Created by Alireza on 3/15/2023.
//

#ifndef COUNTER_WEAPON_H
#define COUNTER_WEAPON_H

#include <string>
#include <vector>
#include <cstdint>

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

class WeaponBase {
public:
    [[nodiscard]] virtual const std::string &getMName() const = 0;

    [[nodiscard]] virtual uint32_t getMDamage() const = 0;

    [[nodiscard]] virtual uint32_t getMPrice() const = 0;

    [[nodiscard]] virtual uint32_t getKillReward() const = 0;

    [[nodiscard]] virtual WEAPON_TYPE getWpType() const = 0;

    [[nodiscard]] virtual WEAPON_USER_TYPE getWpUser() const = 0;

};

class Weapon : public WeaponBase {

public:

    Weapon() = delete;

    Weapon(std::string _name,
           uint32_t _damage,
           uint32_t _price,
           uint32_t _kill_reward,
           WEAPON_TYPE _wp_t,
           WEAPON_USER_TYPE _wp_user_t);

    // Copy c_tor
    Weapon(const Weapon &_w) = default;

    // copy assignment
    Weapon &operator=(const Weapon &_w) = default;

    // move constructor
    Weapon(Weapon &&_w) = default;

    // move assignment
    Weapon &operator=(Weapon &&_w) = default;

    ~Weapon() = default;

    [[nodiscard]] const std::string &getMName() const override;

    [[nodiscard]] uint32_t getMDamage() const override;

    [[nodiscard]] uint32_t getMPrice() const override;

    [[nodiscard]] uint32_t getKillReward() const override;

    [[nodiscard]] WEAPON_TYPE getWpType() const override;

    [[nodiscard]] WEAPON_USER_TYPE getWpUser() const override;

private:
    std::string m_name;
    uint32_t m_damage{0};
    uint32_t m_price{0};
    uint32_t m_Kill_reward{0};
    WEAPON_TYPE m_wp_type{};
    WEAPON_USER_TYPE m_wp_user{};
};

class WeaponSetsBase {
public:
    virtual std::vector<Weapon>::iterator findWP(std::string wp_name, bool &find_that_wp) = 0;
};

class WeaponSets : public WeaponSetsBase {
public:
    WeaponSets();

    ~WeaponSets() = default;

    // Copy c_tor
    WeaponSets(const WeaponSets &_w) = default;

    // copy assignment
    WeaponSets &operator=(const WeaponSets &_w) = default;

    // move constructor
    WeaponSets(WeaponSets &&_w) = default;

    // move assignment
    WeaponSets &operator=(WeaponSets &&_w) = default;

    std::vector<Weapon>::iterator findWP(std::string wp_name, bool &find_that_wp) override;

    /// dont use in this project.
    [[maybe_unused]] void addHeavyWP(const Weapon &wp);

    [[maybe_unused]] void addLightWP(const Weapon &wp);

    [[maybe_unused]] void addMeleeWP(const Weapon &wp);

private:
    std::vector<Weapon>::iterator findWP_in_list(std::vector<Weapon> &wp_list, std::string &wp_name);

    std::vector<Weapon> list_Heavy_WP;
    std::vector<Weapon> list_Light_WP;
    std::vector<Weapon> list_Melee_WP;

};


#endif //COUNTER_WEAPON_H


