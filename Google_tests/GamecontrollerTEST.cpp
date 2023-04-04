//
// Created by Alireza on 3/31/2023.
//
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "GameController.h"
#include <string>
#include <iostream>
#include <sstream>

static const std::string c_attacker_is_dead = "attacker is dead";
static const std::string c_attacked_is_dead = "attacked is dead";
static const std::string c_no_such_gun = "no such gun";
static const std::string c_friendly_fire = "friendly fire";
static const std::string c_nice_shot = "nice shot";

static const std::string c_invalid_username = "invalid username";
static const std::string c_deads_can_not_buy = "deads can not buy";
static const std::string c_out_of_time = "you are out of time";
static const std::string c_invalid_gun_category = "invalid category gun";
static const std::string c_you_have_a_pistol = "you have a pistol";
static const std::string c_you_have_a_heavy = "you have a heavy";
static const std::string c_no_enough_money = "no enough money";
static const std::string c_hope_use = "I hope you can use it";

static const std::string c_you_are_already_in_game = "you are already in this game";
static const std::string c_user_added_T = "this user added to Terrorist";
static const std::string c_user_added_CT = "this user added to Counter-Terrorist";
static const std::string c_team_is_full = "this team is full";

static const std::string c_ct_players = "Counter-Terrorist-Players:";
static const std::string c_t_players = "Terrorist-Players:";
static const std::string c_ct_won = "Counter-Terrorist won";
static const std::string c_t_won = "Terrorist won";

//using ::testing::_;
//using ::testing::AtLeast;
//using ::testing::Exactly;
//using ::testing::Gt;
//using ::testing::Return;
//using ::testing::StrEq;
//using ::testing::ThrowsMessage;

//-----------------------------------------------------------------------------

class MockOutputFormat : public OutputFormat {
public:
    MOCK_METHOD(void, print_line, (const std::string &out_str), (override));
};

class GameControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void AddUsers() {
        g_con->cmd_add_user("terr1", "Terrorist", "00:02:001");
        g_con->cmd_add_user("terr2", "Terrorist", "00:02:003");
        g_con->cmd_add_user("Ct1", "Counter-Terrorist", "00:02:002");
        g_con->cmd_add_user("Ct2", "Counter-Terrorist", "00:02:004");

    }

    // void TearDown() override {}

    MockOutputFormat Out_con;
    std::unique_ptr<GameController> g_con = std::make_unique<GameController>(&Out_con);

};

TEST(TimeControllerTest, String2Time) {
    std::string str_time = "00:03:025";
    EXPECT_EQ(Game_time_str2time_stamp_ms(str_time), 3025);
}

TEST_F(GameControllerTest, ShopControllerCheckErrors1) {
    // Arrange
    AddUsers();
    // Expectations
    EXPECT_CALL(Out_con, print_line(c_no_enough_money))
            .Times(1);
    // Act
    g_con->cmd_buy("terr1","AK","00:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShopControllerCheckErrors2) {
    // Arrange
    AddUsers();
    // Expectations
    EXPECT_CALL(Out_con, print_line(c_invalid_username))
            .Times(1);

    // Act
    g_con->cmd_buy("bibi","AK","00:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShopControllerCheckErrors3) {
    // Arrange
    AddUsers();
    // Expectations
    EXPECT_CALL(Out_con, print_line(c_out_of_time))
            .Times(1);
    // Act
    g_con->cmd_buy("terr1","Glock-18","01:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShopControllerCheckErrors4) {
    // Arrange
    AddUsers();
    // Expectations
    EXPECT_CALL(Out_con, print_line(c_invalid_gun_category))
            .Times(2);

    // Act
    g_con->cmd_buy("terr1","UPS-S","00:20:320");
    g_con->cmd_buy("Ct1","Glock-18","00:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShopControllerCheckErrors5) {
    // Arrange
    AddUsers();
    g_con->cmd_add_user("terr3", "Terrorist", "00:03:001");

    // Expectations
    EXPECT_CALL(Out_con, print_line(c_deads_can_not_buy))
            .Times(1);

    // Act
    g_con->cmd_buy("terr3","UPS-S","00:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShopControllerCheckErrors6) {
    // Arrange
    AddUsers();
    g_con->cmd_buy("terr1","Glock-18","00:20:320");

    // Expectations
    EXPECT_CALL(Out_con, print_line(c_you_have_a_pistol))
            .Times(1);

    // Act
    g_con->cmd_buy("terr1","Revolver","00:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShopControllerCheckErrors7) {
    // Arrange
    AddUsers();
    g_con->result_end_round();
    g_con->result_end_round();

    g_con->cmd_buy("Ct1","M4A1","00:20:320");
    g_con->result_end_round();
    // Expectations
    EXPECT_CALL(Out_con, print_line(c_you_have_a_heavy))
            .Times(1);

    // Act
    g_con->cmd_buy("Ct1","AWP","00:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShopControllerCheck) {
    // Arrange
    AddUsers();
    g_con->result_end_round();
    g_con->result_end_round();

    // Expectations
    EXPECT_CALL(Out_con, print_line(c_hope_use))
            .Times(1);

    // Act
    g_con->cmd_buy("Ct1","M4A1","00:20:320");
    // Assert
    //Check by calling
}



TEST_F(GameControllerTest, ShootingControllerCheckErrors1) {
    // Arrange
    AddUsers();
    g_con->cmd_add_user("terr3", "Terrorist", "00:03:001");

    // Expectations
    EXPECT_CALL(Out_con, print_line(c_attacker_is_dead))
            .Times(1);

    // Act
    g_con->cmd_tap("terr3","Ct1","knife","00:20:320");
    // Assert
    //Check by calling
}
TEST_F(GameControllerTest, ShootingControllerCheckErrors2) {
    // Arrange
    AddUsers();
    g_con->cmd_add_user("terr3", "Terrorist", "00:03:001");

    // Expectations
    EXPECT_CALL(Out_con, print_line(c_attacked_is_dead))
            .Times(1);

    // Act
    g_con->cmd_tap("Ct1","terr3","knife","00:20:320");
    // Assert
    //Check by calling
}




