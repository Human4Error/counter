//
// Created by Alireza on 3/31/2023.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Weapon.h"


TEST(WeaponTest, Ctor) {
    Weapon wp_h("AK", 31, 2700, 100,
                HEAVY_WP, TERRORIST_WP);
    EXPECT_EQ(wp_h.getMName(), "AK");
    EXPECT_EQ(wp_h.getMDamage(), 31);
    EXPECT_EQ(wp_h.getMPrice(), 2700);
    EXPECT_EQ(wp_h.getKillReward(), 100);
    EXPECT_EQ(wp_h.getWpType(), HEAVY_WP);
    EXPECT_EQ(wp_h.getWpUser(), TERRORIST_WP);
}

TEST(WeaponSetsTest, FindWeapon) {
    WeaponSets wp_set;

    bool find = false;
    auto wp_it = wp_set.findWP("AWP", find);
    EXPECT_TRUE(find);
    EXPECT_EQ(wp_it->getMName(), "AWP");
    wp_it = wp_set.findWP("dfs", find);
    EXPECT_FALSE(find);

}