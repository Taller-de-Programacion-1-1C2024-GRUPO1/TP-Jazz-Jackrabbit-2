#include <cstdint>
#include <cstdlib>
#include <memory>
#include <thread>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../common_src/common_errors.h"
#include "../common_src/common_socket.h"
#include "../common_src/constants.h"
#include "../common_src/protocol.h"
#include "../common_src/snapshots/snapshot.h"
#include "../game_src/commands/cheats.h"
#include "../game_src/commands/command.h"
#include "../game_src/commands/command_change_weapon.h"
#include "../game_src/commands/command_jump.h"
#include "../game_src/commands/command_match.h"
#include "../game_src/commands/command_move.h"
#include "../game_src/commands/command_move_faster.h"
#include "../game_src/commands/command_select_champion.h"
#include "../game_src/commands/command_shoot.h"
#include "../game_src/commands/command_special_jazz.h"
#include "../game_src/commands/command_special_lori.h"
#include "../game_src/commands/command_special_spaz.h"
#include "../game_src/constants_game.h"

const char* server_port = "8080";
const char* ip = "localhost";
const std::string& map_test = "MAP_TEST";
const std::string& match_test = "MATCH_TEST";
const ChampionType jazz = Jazz;
const int player_id = 1;
const int number_players = 3;
bool offCheat = false;
bool onCheat = true;
bool needsNoMove = false;
bool needsMove = true;

// ------------------- INSTANTIATE SERVER AND CLIENT -------------------

Socket server_test(server_port);
Protocol client_protocol(ip, server_port);
Socket peer_test = server_test.accept();
Protocol server_protocol(std::move(peer_test));

// ------------------- TESTS -------------------

TEST(ProtocolTestMove, SendAndReceiveMoveLeft) {
    Move* move = new Move(player_id, LEFT_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Move> received_move =
            std::dynamic_pointer_cast<Move>(server_protocol.receive_Command());
    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMove, SendAndReceiveMoveRight) {
    Move* move = new Move(player_id, RIGHT_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Move> received_move =
            std::dynamic_pointer_cast<Move>(server_protocol.receive_Command());
    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMove, SendAndReceiveMoveForward) {
    Move* move = new Move(player_id, FORWARD_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Move> received_move =
            std::dynamic_pointer_cast<Move>(server_protocol.receive_Command());
    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMove, SendAndReceiveMoveBackward) {
    Move* move = new Move(player_id, BACKWARD_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Move> received_move =
            std::dynamic_pointer_cast<Move>(server_protocol.receive_Command());
    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMoveFaster, SendAndReceiveMoveFasterRight) {
    MoveFaster* move_faster = new MoveFaster(player_id, RIGHT_DIR);
    client_protocol.send_Command(move_faster);
    std::shared_ptr<MoveFaster> received_move_faster =
            std::dynamic_pointer_cast<MoveFaster>(server_protocol.receive_Command());
    EXPECT_EQ(move_faster->get_playerId(), received_move_faster->get_playerId());
    EXPECT_EQ(move_faster->get_dir(), received_move_faster->get_dir());
    EXPECT_EQ(move_faster->get_commandType(), received_move_faster->get_commandType());
    delete move_faster;
}

TEST(ProtocolTestMoveFaster, SendAndReceiveMoveFasterLeft) {
    MoveFaster* move_faster = new MoveFaster(player_id, LEFT_DIR);
    client_protocol.send_Command(move_faster);
    std::shared_ptr<MoveFaster> received_move_faster =
            std::dynamic_pointer_cast<MoveFaster>(server_protocol.receive_Command());
    EXPECT_EQ(move_faster->get_playerId(), received_move_faster->get_playerId());
    EXPECT_EQ(move_faster->get_dir(), received_move_faster->get_dir());
    EXPECT_EQ(move_faster->get_commandType(), received_move_faster->get_commandType());
    delete move_faster;
}

TEST(ProtocolTestJump, SendAndReceiveJumpForwardERROR) {
    Jump* jump = new Jump(player_id, FORWARD_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Jump> received_jump =
            std::dynamic_pointer_cast<Jump>(server_protocol.receive_Command());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_jump->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    // EXPECT_ANY_THROW(jump->execute_Command(&offCheat, needsMove));
    delete jump;
}

TEST(ProtocolTestJump, SendAndReceiveJumpBackwardERROR) {
    Jump* jump = new Jump(player_id, BACKWARD_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Jump> received_jump =
            std::dynamic_pointer_cast<Jump>(server_protocol.receive_Command());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    // EXPECT_ANY_THROW(received_jump->execute_Command(&offCheat, needsMove));
    delete jump;
}

TEST(ProtocolTestJump, SendAndReceiveJumpRight) {
    Jump* jump = new Jump(player_id, RIGHT_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Jump> received_jump =
            std::dynamic_pointer_cast<Jump>(server_protocol.receive_Command());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_jump->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    delete jump;
}

TEST(ProtocolTestJump, SendAndReceiveJumpLeft) {
    Jump* jump = new Jump(player_id, LEFT_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Jump> received_jump =
            std::dynamic_pointer_cast<Jump>(server_protocol.receive_Command());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_jump->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    delete jump;
}

TEST(ProtocolTestShoot, SendAndReceiveShoot) {
    Shoot* shoot = new Shoot(player_id);
    client_protocol.send_Command(shoot);
    std::shared_ptr<Shoot> received_shoot =
            std::dynamic_pointer_cast<Shoot>(server_protocol.receive_Command());
    EXPECT_EQ(shoot->get_playerId(), received_shoot->get_playerId());
    EXPECT_EQ(shoot->get_commandType(), received_shoot->get_commandType());
    delete shoot;
}

TEST(ProtocolTestSpecialLori, SendAndReceiveSpecialLoriForward) {
    SpecialLori* special_lori = new SpecialLori(player_id, FORWARD_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<SpecialLori> received_special_lori =
            std::dynamic_pointer_cast<SpecialLori>(server_protocol.receive_Command());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    delete special_lori;
}

TEST(ProtocolTestSpecialLori, SendAndReceiveSpecialLoriBackward) {
    SpecialLori* special_lori = new SpecialLori(player_id, BACKWARD_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<SpecialLori> received_special_lori =
            std::dynamic_pointer_cast<SpecialLori>(server_protocol.receive_Command());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    delete special_lori;
}

TEST(ProtocolTest, SendAndReceiveSpecialLoriRightERROR) {
    SpecialLori* special_lori = new SpecialLori(player_id, RIGHT_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<SpecialLori> received_special_lori =
            std::dynamic_pointer_cast<SpecialLori>(server_protocol.receive_Command());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    EXPECT_ANY_THROW(special_lori->execute_Command(&offCheat, needsMove));
    EXPECT_ANY_THROW(special_lori->execute_Command(&offCheat, needsMove));
    delete special_lori;
}

TEST(ProtocolTestSpecialLori, SendAndReceiveSpecialLoriLeftERROR) {
    SpecialLori* special_lori = new SpecialLori(player_id, LEFT_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<SpecialLori> received_special_lori =
            std::dynamic_pointer_cast<SpecialLori>(server_protocol.receive_Command());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    delete special_lori;
}

TEST(ProtocolTestSpecialSpaz, SendAndReceiveSpecialSpazRight) {
    SpecialSpaz* special_spaz = new SpecialSpaz(player_id, RIGHT_DIR);
    client_protocol.send_Command(special_spaz);
    std::shared_ptr<SpecialSpaz> received_special_spaz =
            std::dynamic_pointer_cast<SpecialSpaz>(server_protocol.receive_Command());
    EXPECT_EQ(special_spaz->get_playerId(), received_special_spaz->get_playerId());
    EXPECT_EQ(special_spaz->get_dir(), received_special_spaz->get_dir());
    EXPECT_EQ(special_spaz->get_commandType(), received_special_spaz->get_commandType());
    delete special_spaz;
}

TEST(ProtocolTestSpecialSpaz, SendAndReceiveSpecialSpazLeft) {
    SpecialSpaz* special_spaz = new SpecialSpaz(player_id, LEFT_DIR);
    client_protocol.send_Command(special_spaz);
    std::shared_ptr<SpecialSpaz> received_special_spaz =
            std::dynamic_pointer_cast<SpecialSpaz>(server_protocol.receive_Command());
    EXPECT_EQ(special_spaz->get_playerId(), received_special_spaz->get_playerId());
    EXPECT_EQ(special_spaz->get_dir(), received_special_spaz->get_dir());
    EXPECT_EQ(special_spaz->get_commandType(), received_special_spaz->get_commandType());
    delete special_spaz;
}

TEST(ProtocolTestSpecialJazz, SendAndReceiveSpecialJazz) {
    SpecialJazz* special_jazz = new SpecialJazz(player_id);
    client_protocol.send_Command(special_jazz);
    std::shared_ptr<SpecialJazz> received_special_spaz =
            std::dynamic_pointer_cast<SpecialJazz>(server_protocol.receive_Command());
    EXPECT_EQ(special_jazz->get_playerId(), received_special_spaz->get_playerId());
    EXPECT_EQ(special_jazz->get_commandType(), received_special_spaz->get_commandType());
    delete special_jazz;
}

TEST(ProtocolTestChangeWeapon, SendAndReceiveChangeWeapon) {
    ChangeWeapon* change_weapon = new ChangeWeapon(player_id);
    client_protocol.send_Command(change_weapon);
    std::shared_ptr<ChangeWeapon> received_change_weapon =
            std::dynamic_pointer_cast<ChangeWeapon>(server_protocol.receive_Command());
    EXPECT_EQ(change_weapon->get_playerId(), received_change_weapon->get_playerId());
    EXPECT_EQ(change_weapon->get_commandType(), received_change_weapon->get_commandType());
    delete change_weapon;
}


TEST(ProtocolTestMatch, SendAndReceiveMatch) {
    MatchCommand* match = new MatchCommand(player_id, number_players, match_test, map_test, jazz);
    client_protocol.send_Command(match);
    std::shared_ptr<MatchCommand> received_match =
            std::dynamic_pointer_cast<MatchCommand>(server_protocol.receive_Command());
    EXPECT_EQ(match->get_playerId(), received_match->get_playerId());
    EXPECT_EQ(match->get_commandType(), received_match->get_commandType());
    EXPECT_EQ(match->get_match_name(), received_match->get_match_name());
    EXPECT_EQ(match->get_map_name(), received_match->get_map_name());
    delete match;
}
