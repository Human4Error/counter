//
// Created by Alireza on 3/31/2023.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Player.h"


TEST(PlayerTest, Ctor) {

    Player pl("ali", TERRORIST, 23);
    EXPECT_EQ(pl.get_name(), "ali");
    EXPECT_EQ(pl.get_team_ID(), TERRORIST);
    EXPECT_EQ(pl.getPlayer_ID(), 23);

}

TEST(PlayerTest, playerIsAlive) {

    Player pl("ali", TERRORIST, 23);
    EXPECT_TRUE(pl.get_Is_alive());
    pl.set_Is_alive(false);
    EXPECT_FALSE(pl.get_Is_alive());
    pl.setHealth(HEALTH_MAX);
    EXPECT_TRUE(pl.get_Is_alive());
    pl.setHealth(HEALTH_MIN);
    EXPECT_FALSE(pl.get_Is_alive());

}

TEST(PlayerTest, PlayerHealth) {
    uint32_t health = 26;
    Player pl("ali", TERRORIST, 23);
    EXPECT_EQ(pl.getHealth(), HEALTH_MAX);
    pl.setHealth(health);
    EXPECT_EQ(pl.getHealth(), health);
}

TEST(PlayerTest, PlayerMoney) {

    uint32_t money = 1000;
    uint32_t inc_money = 3000;

    Player pl("ali", TERRORIST, 23);
    EXPECT_EQ(pl.getMoney(), 0);
    pl.setMoney(money);
    EXPECT_EQ(pl.getMoney(), money);
    pl.increaseMoney(inc_money);
    EXPECT_EQ(pl.getMoney(), money + inc_money);
    inc_money = MAX_MONEY;
    pl.increaseMoney(inc_money);
    EXPECT_EQ(pl.getMoney(), MAX_MONEY);

}

TEST(PlayerTest, PlayerKillDeathNum) {
    Player pl("ali", TERRORIST, 23);
    EXPECT_EQ(pl.getNumber_of_deaths(), 0);
    EXPECT_EQ(pl.getNumber_of_kills(), 0);

    pl.number_of_deaths_Increment_one();

    pl.number_of_kills_Increment_one();
    pl.number_of_kills_Increment_one();
    pl.number_of_kills_Increment_one();

    EXPECT_EQ(pl.getNumber_of_deaths(), 1);
    EXPECT_EQ(pl.getNumber_of_kills(), 3);
}

TEST(PlayerTest, PlayerWeapon) {

    Weapon wp_h("AK", 31, 2700, 100,
                HEAVY_WP, TERRORIST_WP);
    Weapon wp_l("Revolver", 51, 600, 150,
                LIGHT_WP, TERRORIST_WP);
    Weapon wp_m("knife", 43, 0, 500,
                MELE_WP, FREE_FOR_ALL);

    Player pl("ali", TERRORIST, 23);
    EXPECT_EQ(pl.getMele_weapon(), nullptr);
    EXPECT_EQ(pl.getLight_weapon(), nullptr);
    EXPECT_EQ(pl.getHeavy_weapon(), nullptr);

    pl.setHeavy_weapon(&wp_h);
    pl.setLight_weapon(&wp_l);
    pl.setMele_weapon(&wp_m);

    EXPECT_EQ(pl.getMele_weapon(), &wp_m);
    EXPECT_EQ(pl.getLight_weapon(), &wp_l);
    EXPECT_EQ(pl.getHeavy_weapon(), &wp_h);

}

class TeamTest : public ::testing::Test {
protected:
    void SetUp() override {

        pl_t_2.number_of_kills_Increment_one();

        pl_ct_2.number_of_kills_Increment_one();
        pl_ct_2.number_of_kills_Increment_one();
        pl_ct_3.number_of_deaths_Increment_one();


        team.add_player(pl_t_1, TERRORIST);
        team.add_player(pl_t_2, TERRORIST);

        team.add_player(pl_ct_1, COUNTER_TERRORIST);
        team.add_player(pl_ct_2, COUNTER_TERRORIST);
        team.add_player(pl_ct_3, COUNTER_TERRORIST);
    }

    // void TearDown() override {}
    Team team;
    Player pl_t_1{"terror1", TERRORIST, 23};
    Player pl_t_2{"terror2", TERRORIST, 24};
    Player pl_t_3{"terror3", TERRORIST, 22};

    Player pl_ct_1{"C_terror1", COUNTER_TERRORIST, 25};
    Player pl_ct_2{"C_terror2", COUNTER_TERRORIST, 26};
    Player pl_ct_3{"C_terror3", COUNTER_TERRORIST, 27};
    Player pl_ct_4{"C_terror4", COUNTER_TERRORIST, 28};
    Player pl_ct_5{"C_terror5", COUNTER_TERRORIST, 29};
    Player pl_ct_6{"C_terror6", COUNTER_TERRORIST, 30};
    Player pl_ct_7{"C_terror7", COUNTER_TERRORIST, 31};
    Player pl_ct_8{"C_terror8", COUNTER_TERRORIST, 32};
    Player pl_ct_9{"C_terror9", COUNTER_TERRORIST, 33};
    Player pl_ct_10{"C_terror10", COUNTER_TERRORIST, 34};


};

TEST_F(TeamTest, Ctor) {

    EXPECT_EQ(team.get_number_of_alive_CT_player(), 3);
    EXPECT_EQ(team.get_number_of_alive_T_player(), 2);

}

TEST_F(TeamTest, AddPlayer) {
    team.add_player(pl_ct_4, COUNTER_TERRORIST);
    EXPECT_EQ(team.get_number_of_alive_CT_player(), 4);

}

TEST_F(TeamTest, TeamIsFull) {
    EXPECT_EQ(team.check_team_is_full(TERRORIST), false);
    EXPECT_EQ(team.check_team_is_full(COUNTER_TERRORIST), false);
    team.add_player(pl_ct_4, COUNTER_TERRORIST);
    team.add_player(pl_ct_5, COUNTER_TERRORIST);
    team.add_player(pl_ct_6, COUNTER_TERRORIST);
    team.add_player(pl_ct_7, COUNTER_TERRORIST);
    team.add_player(pl_ct_8, COUNTER_TERRORIST);
    team.add_player(pl_ct_9, COUNTER_TERRORIST);
    team.add_player(pl_ct_10, COUNTER_TERRORIST);
    EXPECT_EQ(team.check_team_is_full(TERRORIST), false);
    EXPECT_EQ(team.check_team_is_full(COUNTER_TERRORIST), true);
    EXPECT_EQ(team.get_number_of_alive_CT_player(), 10);

}

TEST_F(TeamTest, returnPlayerByUsername) {
    std::string username = "C_terror2";
    EXPECT_EQ(team.return_PLayer_by_username(username).get_name(), pl_ct_2.get_name());

}

TEST_F(TeamTest, FindPlayerByUsername) {
    std::string username = "C_terror1";
    EXPECT_EQ(team.find_player_by_username(username), true);
    username = "C_terror223";
    EXPECT_EQ(team.find_player_by_username(username), false);
}

TEST_F(TeamTest, ResetHealthAllPlayers) {

    pl_ct_4.setHealth(0);
    pl_t_1.setHealth(0);
    team.add_player(pl_t_1, TERRORIST);
    team.add_player(pl_ct_4, COUNTER_TERRORIST);
    EXPECT_EQ(team.get_number_of_alive_CT_player(), 3);
    EXPECT_EQ(team.get_number_of_alive_T_player(), 2);
    team.reset_health_all_players();
    EXPECT_EQ(team.get_number_of_alive_CT_player(), 4);
    EXPECT_EQ(team.get_number_of_alive_T_player(), 3);

}

TEST_F(TeamTest, IncreaseMoneyOfTeams) {
    uint32_t t_inc_money = 520;
    uint32_t ct_inc_money = 1789;

    team.increase_money_T_players(t_inc_money);
    team.increase_money_CT_players(ct_inc_money);

    std::string ter_username = "terror1";
    std::string ct_username = "C_terror2";
    EXPECT_EQ(team.return_PLayer_by_username(ter_username).getMoney(), t_inc_money);
    EXPECT_EQ(team.return_PLayer_by_username(ct_username).getMoney(), ct_inc_money);

}

TEST_F(TeamTest, RemoveHeavyPistolFromDeads) {
    Weapon wp_h("AK", 31, 2700, 100,
                HEAVY_WP, TERRORIST_WP);
    Weapon wp_l("Revolver", 51, 600, 150,
                LIGHT_WP, TERRORIST_WP);

    pl_t_3.setLight_weapon(&wp_l);
    pl_t_3.setHealth(HEALTH_MIN);
    pl_ct_4.setHeavy_weapon(&wp_h);
    pl_ct_4.setHealth(HEALTH_MIN);

    team.add_player(pl_t_3, TERRORIST);
    team.add_player(pl_ct_4, COUNTER_TERRORIST);

    team.remove_heavy_pistol_wp_from_deads();

    std::string ter_username = "terror3";
    std::string ct_username = "C_terror4";
    EXPECT_EQ(team.return_PLayer_by_username(ter_username).getLight_weapon(), nullptr);
    EXPECT_EQ(team.return_PLayer_by_username(ct_username).getHeavy_weapon(), nullptr);

}

TEST_F(TeamTest, sortPlayer) {

    team.sort_player_list();
    EXPECT_EQ(team.return_PLayer_by_index(0,TERRORIST).get_name(), "terror2");

    EXPECT_EQ(team.return_PLayer_by_index(0,COUNTER_TERRORIST).get_name(), "C_terror2");
    EXPECT_EQ(team.return_PLayer_by_index(1,COUNTER_TERRORIST).get_name(), "C_terror1");
    EXPECT_EQ(team.return_PLayer_by_index(2,COUNTER_TERRORIST).get_name(), "C_terror3");


}






