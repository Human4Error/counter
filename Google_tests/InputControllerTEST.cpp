//
// Created by Alireza on 3/31/2023.
//
#include "InputController.h"
#include "GameController.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

//using ::testing::_;
//using ::testing::AtLeast;
//using ::testing::Exactly;
//using ::testing::Gt;
//using ::testing::Return;
//using ::testing::StrEq;
//using ::testing::ThrowsMessage;

//-----------------------------------------------------------------------------

class MockGameControllerBase : public GameControllerBase {
public:

    MOCK_METHOD(void, start_round, (), (override));
    MOCK_METHOD(void, result_end_round, (), (override));
    MOCK_METHOD(void, cmd_add_user, (std::string username, std::string team_str, std::string time_str), (override));
    MOCK_METHOD(void, cmd_get_money, (std::string username, std::string time_str), (override));
    MOCK_METHOD(void, cmd_get_health, (std::string username, std::string time_str), (override));
    MOCK_METHOD(void, cmd_tap, (std::string username_attacker, std::string username_attacked,
            std::string wp_type_str, std::string time_str), (override));
    MOCK_METHOD(void, cmd_buy, (std::string username, std::string gun_name_str, std::string time_str), (override));
    MOCK_METHOD(void, cmd_show_score_board, (std::string time_str), (override));
};


TEST(InputConTest, String2CommandAddUser) {
    // Arrange
    MockGameControllerBase MockGameCon;
    std::string cmd = "ADD-USER King2Krazy Counter-Terrorist 00:01:130";
    // Expectations
    EXPECT_CALL(MockGameCon, cmd_add_user("King2Krazy",
                                          "Counter-Terrorist",
                                          "00:01:130"))
            .Times(1);
    // Act
    InputController in_con;
    in_con.translate_string_2_method(cmd, &MockGameCon);

    // Assert
    //Check by calling
}

TEST(InputConTest, String2CommandGetMoney) {
    // Arrange
    MockGameControllerBase MockGameCon;
    std::string cmd = "GET-MONEY Cat 00:04:715";
    // Expectations
    EXPECT_CALL(MockGameCon, cmd_get_money("Cat",
                                           "00:04:715"))
            .Times(1);
    // Act
    InputController in_con;
    in_con.translate_string_2_method(cmd, &MockGameCon);

    // Assert
    //Check by calling
}

TEST(InputConTest, String2CommandGetHealth) {
    // Arrange
    MockGameControllerBase MockGameCon;
    std::string cmd = "GET-HEALTH King2Krazy 00:05:004";
    // Expectations
    EXPECT_CALL(MockGameCon, cmd_get_health("King2Krazy",
                                            "00:05:004"))
            .Times(1);
    // Act
    InputController in_con;
    in_con.translate_string_2_method(cmd, &MockGameCon);

    // Assert
    //Check by calling
}

TEST(InputConTest, String2CommandTap) {
    // Arrange
    MockGameControllerBase MockGameCon;
    std::string cmd = "TAP King2Krazy Cat knife 00:13:000";
    // Expectations
    EXPECT_CALL(MockGameCon, cmd_tap("King2Krazy",
                                     "Cat",
                                     "knife",
                                     "00:13:000"))
            .Times(1);
    // Act
    InputController in_con;
    in_con.translate_string_2_method(cmd, &MockGameCon);

    // Assert
    //Check by calling
}

TEST(InputConTest, String2CommandBuy) {
    // Arrange
    MockGameControllerBase MockGameCon;
    std::string cmd = "BUY John-Wick AK 00:06:000";
    // Expectations
    EXPECT_CALL(MockGameCon, cmd_buy("John-Wick",
                                     "AK",
                                     "00:06:000"))
            .Times(1);
    // Act
    InputController in_con;
    in_con.translate_string_2_method(cmd, &MockGameCon);

    // Assert
    //Check by calling
}

TEST(InputConTest, String2CommandShowScoreBoard) {
    // Arrange
    MockGameControllerBase MockGameCon;
    std::string cmd = "SCORE-BOARD 01:17:200";
    // Expectations
    EXPECT_CALL(MockGameCon, cmd_show_score_board("01:17:200"))
            .Times(1);
    // Act
    InputController in_con;
    in_con.translate_string_2_method(cmd, &MockGameCon);

    // Assert
    //Check by calling
}