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
const std::string& player_name = "PLAYER_NAME";

// ------------------- INSTANTIATE SERVER AND CLIENT -------------------

Socket server_test(server_port);
Protocol client_protocol(ip, server_port);
Socket peer_test = server_test.accept();
Protocol server_protocol(std::move(peer_test));

// ------------------- TESTS -------------------

TEST(ProtocolTestMove, SendAndReceiveMoveLeft) {
    Move* move = new Move(player_id, LEFT);
    client_protocol.send_Command(move);

    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Move* received_move = dynamic_cast<Move*>(cmd.get());

    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMove, SendAndReceiveMoveRight) {
    Move* move = new Move(player_id, RIGHT);
    client_protocol.send_Command(move);

    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Move* received_move = dynamic_cast<Move*>(cmd.get());


    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMove, SendAndReceiveMoveUP) {
    Move* move = new Move(player_id, UP);
    client_protocol.send_Command(move);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Move* received_move = dynamic_cast<Move*>(cmd.get());
    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMove, SendAndReceiveMoveDown) {
    Move* move = new Move(player_id, DOWN);
    client_protocol.send_Command(move);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Move* received_move = dynamic_cast<Move*>(cmd.get());
    EXPECT_EQ(move->get_playerId(), received_move->get_playerId());
    EXPECT_EQ(move->get_dir(), received_move->get_dir());
    EXPECT_EQ(move->get_commandType(), received_move->get_commandType());
    delete move;
}

TEST(ProtocolTestMoveFaster, SendAndReceiveMoveFasterRight) {
    MoveFaster* move_faster = new MoveFaster(player_id, RIGHT);
    client_protocol.send_Command(move_faster);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    MoveFaster* received_move_faster = dynamic_cast<MoveFaster*>(cmd.get());
    EXPECT_EQ(move_faster->get_playerId(), received_move_faster->get_playerId());
    EXPECT_EQ(move_faster->get_dir(), received_move_faster->get_dir());
    EXPECT_EQ(move_faster->get_commandType(), received_move_faster->get_commandType());
    delete move_faster;
}

TEST(ProtocolTestMoveFaster, SendAndReceiveMoveFasterLeft) {
    MoveFaster* move_faster = new MoveFaster(player_id, LEFT);
    client_protocol.send_Command(move_faster);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    MoveFaster* received_move_faster = dynamic_cast<MoveFaster*>(cmd.get());
    EXPECT_EQ(move_faster->get_playerId(), received_move_faster->get_playerId());
    EXPECT_EQ(move_faster->get_dir(), received_move_faster->get_dir());
    EXPECT_EQ(move_faster->get_commandType(), received_move_faster->get_commandType());
    delete move_faster;
}

TEST(ProtocolTestJump, SendAndReceiveJumpUPERROR) {
    Jump* jump = new Jump(player_id, UP);
    client_protocol.send_Command(jump);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Jump* received_jump = dynamic_cast<Jump*>(cmd.get());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_jump->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    delete jump;
}

TEST(ProtocolTestJump, SendAndReceiveJumpDownERROR) {
    Jump* jump = new Jump(player_id, DOWN);
    client_protocol.send_Command(jump);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Jump* received_jump = dynamic_cast<Jump*>(cmd.get());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    delete jump;
}

TEST(ProtocolTestJump, SendAndReceiveJumpRight) {
    Jump* jump = new Jump(player_id, RIGHT);
    client_protocol.send_Command(jump);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Jump* received_jump = dynamic_cast<Jump*>(cmd.get());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_jump->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    delete jump;
}

TEST(ProtocolTestJump, SendAndReceiveJumpLeft) {
    Jump* jump = new Jump(player_id, LEFT);
    client_protocol.send_Command(jump);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Jump* received_jump = dynamic_cast<Jump*>(cmd.get());
    EXPECT_EQ(jump->get_playerId(), received_jump->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_jump->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_jump->get_commandType());
    delete jump;
}

TEST(ProtocolTestShoot, SendAndReceiveShoot) {
    Shoot* shoot = new Shoot(player_id);
    client_protocol.send_Command(shoot);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    Shoot* received_shoot = dynamic_cast<Shoot*>(cmd.get());
    EXPECT_EQ(shoot->get_playerId(), received_shoot->get_playerId());
    EXPECT_EQ(shoot->get_commandType(), received_shoot->get_commandType());
    delete shoot;
}

TEST(ProtocolTestSpecialLori, SendAndReceiveSpecialLoriUP) {
    SpecialLori* special_lori = new SpecialLori(player_id, UP);
    client_protocol.send_Command(special_lori);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    SpecialLori* received_special_lori = dynamic_cast<SpecialLori*>(cmd.get());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    delete special_lori;
}

TEST(ProtocolTestSpecialLori, SendAndReceiveSpecialLoriDown) {
    SpecialLori* special_lori = new SpecialLori(player_id, DOWN);
    client_protocol.send_Command(special_lori);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    SpecialLori* received_special_lori = dynamic_cast<SpecialLori*>(cmd.get());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    delete special_lori;
}

TEST(ProtocolTest, SendAndReceiveSpecialLoriRightERROR) {
    SpecialLori* special_lori = new SpecialLori(player_id, RIGHT);
    client_protocol.send_Command(special_lori);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    SpecialLori* received_special_lori = dynamic_cast<SpecialLori*>(cmd.get());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    delete special_lori;
}

TEST(ProtocolTestSpecialLori, SendAndReceiveSpecialLoriLeftERROR) {
    SpecialLori* special_lori = new SpecialLori(player_id, LEFT);
    client_protocol.send_Command(special_lori);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    SpecialLori* received_special_lori = dynamic_cast<SpecialLori*>(cmd.get());
    EXPECT_EQ(special_lori->get_playerId(), received_special_lori->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_special_lori->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_special_lori->get_commandType());
    delete special_lori;
}

TEST(ProtocolTestSpecialSpaz, SendAndReceiveSpecialSpazRight) {
    SpecialSpaz* special_spaz = new SpecialSpaz(player_id, RIGHT);
    client_protocol.send_Command(special_spaz);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    SpecialSpaz* received_special_spaz = dynamic_cast<SpecialSpaz*>(cmd.get());
    EXPECT_EQ(special_spaz->get_playerId(), received_special_spaz->get_playerId());
    EXPECT_EQ(special_spaz->get_dir(), received_special_spaz->get_dir());
    EXPECT_EQ(special_spaz->get_commandType(), received_special_spaz->get_commandType());
    delete special_spaz;
}

TEST(ProtocolTestSpecialSpaz, SendAndReceiveSpecialSpazLeft) {
    SpecialSpaz* special_spaz = new SpecialSpaz(player_id, LEFT);
    client_protocol.send_Command(special_spaz);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    SpecialSpaz* received_special_spaz = dynamic_cast<SpecialSpaz*>(cmd.get());
    EXPECT_EQ(special_spaz->get_playerId(), received_special_spaz->get_playerId());
    EXPECT_EQ(special_spaz->get_dir(), received_special_spaz->get_dir());
    EXPECT_EQ(special_spaz->get_commandType(), received_special_spaz->get_commandType());
    delete special_spaz;
}

TEST(ProtocolTestSpecialJazz, SendAndReceiveSpecialJazz) {
    SpecialJazz* special_jazz = new SpecialJazz(player_id);
    client_protocol.send_Command(special_jazz);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    SpecialJazz* received_special_jazz = dynamic_cast<SpecialJazz*>(cmd.get());
    EXPECT_EQ(special_jazz->get_playerId(), received_special_jazz->get_playerId());
    EXPECT_EQ(special_jazz->get_commandType(), received_special_jazz->get_commandType());
    delete special_jazz;
}

TEST(ProtocolTestChangeWeapon, SendAndReceiveChangeWeapon) {
    ChangeWeapon* change_weapon = new ChangeWeapon(player_id);
    client_protocol.send_Command(change_weapon);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    ChangeWeapon* received_change_weapon = dynamic_cast<ChangeWeapon*>(cmd.get());
    EXPECT_EQ(change_weapon->get_playerId(), received_change_weapon->get_playerId());
    EXPECT_EQ(change_weapon->get_commandType(), received_change_weapon->get_commandType());
    delete change_weapon;
}


TEST(ProtocolTestMatch, SendAndReceiveMatch) {
    MatchCommand* match =
            new MatchCommand(player_id, number_players, match_test, map_test, jazz, player_name);
    client_protocol.send_Command(match);
    std::unique_ptr<Command> cmd = server_protocol.receive_Command();
    MatchCommand* received_match = dynamic_cast<MatchCommand*>(cmd.get());

    EXPECT_EQ(match->get_playerId(), received_match->get_playerId());
    EXPECT_EQ(match->get_commandType(), received_match->get_commandType());
    EXPECT_EQ(match->get_match_name(), received_match->get_match_name());
    EXPECT_EQ(match->get_map_name(), received_match->get_map_name());
    delete match;
}
