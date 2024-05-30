#include <cstdint>
#include <cstdlib>
#include <memory>
#include <thread>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../common_src/common_socket.h"
#include "../common_src/protocol.h"
#include "../common_src/common_errors.h"
#include "../common_src/snapshots/snapshot.h"
#include "../common_src/constants.h"

const char* server_port = "8080";
const char* ip = "localhost";
const std::string& map_test = "MAP_TEST";
const std::string& match_test = "MATCH_TEST";
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

TEST(ProtocolTest, SendAndReceiveMoveLeft) {
    Move* move = new Move(player_id, LEFT_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(move->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(move->get_dir(), received_command->get_dir());
    EXPECT_EQ(move->get_commandType(), received_command->get_commandType());
    delete move;
}

TEST(ProtocolTest, SendAndReceiveMoveRight) {
    Move* move = new Move(player_id, RIGHT_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(move->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(move->get_dir(), received_command->get_dir());
    EXPECT_EQ(move->get_commandType(), received_command->get_commandType());
    delete move;
}

TEST(ProtocolTest, SendAndReceiveMoveForward) {
    Move* move = new Move(player_id, FORWARD_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(move->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(move->get_dir(), received_command->get_dir());
    EXPECT_EQ(move->get_commandType(), received_command->get_commandType());
    delete move;
}

TEST(ProtocolTest, SendAndReceiveMoveBackward) {
    Move* move = new Move(player_id, BACKWARD_DIR);
    client_protocol.send_Command(move);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(move->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(move->get_dir(), received_command->get_dir());
    EXPECT_EQ(move->get_commandType(), received_command->get_commandType());
    delete move;
}

TEST(ProtocolTest, SendAndReceiveMoveFasterRight) {
    MoveFaster* move_faster = new MoveFaster(player_id, RIGHT_DIR);
    client_protocol.send_Command(move_faster);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(move_faster->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(move_faster->get_dir(), received_command->get_dir());
    EXPECT_EQ(move_faster->get_commandType(), received_command->get_commandType());
    delete move_faster;
}

TEST(ProtocolTest, SendAndReceiveMoveFasterLeft) {
    MoveFaster* move_faster = new MoveFaster(player_id, LEFT_DIR);
    client_protocol.send_Command(move_faster);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(move_faster->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(move_faster->get_dir(), received_command->get_dir());
    EXPECT_EQ(move_faster->get_commandType(), received_command->get_commandType());
    delete move_faster;
}

TEST(ProtocolTest, SendAndReceiveJumpForwardERROR) {
    Jump* jump = new Jump(player_id, FORWARD_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(jump->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_command->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_command->get_commandType());
    EXPECT_ANY_THROW(jump->execute_Command(&offCheat, needsMove));
    delete jump;
}

TEST(ProtocolTest, SendAndReceiveJumpBackwardERROR) {
    Jump* jump = new Jump(player_id, BACKWARD_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(jump->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(jump->get_commandType(), received_command->get_commandType());
    EXPECT_ANY_THROW(jump->execute_Command(&offCheat, needsMove));
    delete jump;
}

TEST(ProtocolTest, SendAndReceiveJumpRight) {
    Jump* jump = new Jump(player_id, RIGHT_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(jump->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_command->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_command->get_commandType());
    delete jump;
}

TEST(ProtocolTest, SendAndReceiveJumpLeft) {
    Jump* jump = new Jump(player_id, LEFT_DIR);
    client_protocol.send_Command(jump);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(jump->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(jump->get_dir(), received_command->get_dir());
    EXPECT_EQ(jump->get_commandType(), received_command->get_commandType());
    delete jump;
}

TEST(ProtocolTest, SendAndReceiveShoot) {
    Shoot* shoot = new Shoot(player_id);
    client_protocol.send_Command(shoot);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(shoot->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(shoot->get_commandType(), received_command->get_commandType());
    delete shoot;
}

TEST(ProtocolTest, SendAndReceiveSpecialLoriForwardERROR) {
    SpecialLori* special_lori = new SpecialLori(player_id, FORWARD_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(special_lori->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_command->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_command->get_commandType());
    EXPECT_ANY_THROW(special_lori->execute_Command(&offCheat, needsMove));
    delete special_lori;
}

TEST(ProtocolTest, SendAndReceiveSpecialLoriBackwardERROR) {
    SpecialLori* special_lori = new SpecialLori(player_id, BACKWARD_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(special_lori->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_command->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_command->get_commandType());
    EXPECT_ANY_THROW(special_lori->execute_Command(&offCheat, needsMove));
    delete special_lori;
}

TEST(ProtocolTest, SendAndReceiveSpecialLoriRight) {
    SpecialLori* special_lori = new SpecialLori(player_id, RIGHT_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(special_lori->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_command->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_command->get_commandType());
    delete special_lori;
}

TEST(ProtocolTest, SendAndReceiveSpecialLoriLeft) {
    SpecialLori* special_lori = new SpecialLori(player_id, LEFT_DIR);
    client_protocol.send_Command(special_lori);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(special_lori->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(special_lori->get_dir(), received_command->get_dir());
    EXPECT_EQ(special_lori->get_commandType(), received_command->get_commandType());
    delete special_lori;
}

TEST(ProtocolTest, SendAndReceiveSpecialSpazRight) {
    SpecialSpaz* special_spaz = new SpecialSpaz(player_id, RIGHT_DIR);
    client_protocol.send_Command(special_spaz);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(special_spaz->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(special_spaz->get_dir(), received_command->get_dir());
    EXPECT_EQ(special_spaz->get_commandType(), received_command->get_commandType());
    delete special_spaz;
}

TEST(ProtocolTest, SendAndReceiveSpecialSpazLeft) {
    SpecialSpaz* special_spaz = new SpecialSpaz(player_id, LEFT_DIR);
    client_protocol.send_Command(special_spaz);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(special_spaz->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(special_spaz->get_dir(), received_command->get_dir());
    EXPECT_EQ(special_spaz->get_commandType(), received_command->get_commandType());
    delete special_spaz;
}

TEST(ProtocolTest, SendAndReceiveSpecialJazz) {
    SpecialJazz* special_jazz = new SpecialJazz(player_id);
    client_protocol.send_Command(special_jazz);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(special_jazz->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(special_jazz->get_commandType(), received_command->get_commandType());
    delete special_jazz;
}

TEST(ProtocolTest, SendAndReceiveChangeWeapon) {
    ChangeWeapon* change_weapon = new ChangeWeapon(player_id);
    client_protocol.send_Command(change_weapon);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    EXPECT_EQ(change_weapon->get_playerId(), received_command->get_playerId());
    EXPECT_EQ(change_weapon->get_commandType(), received_command->get_commandType());
    delete change_weapon;
}

TEST(ProtocolTest, SendAndReceiveSelectChampion) {
    SelectChampion* select_champion = new SelectChampion(player_id, Jazz, map_test, match_test);
    client_protocol.send_Command(select_champion);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    std::shared_ptr<SelectChampion> received_select_champion = std::dynamic_pointer_cast<SelectChampion>(received_command);
    EXPECT_EQ(select_champion->get_playerId(), received_select_champion->get_playerId());
    EXPECT_EQ(select_champion->get_commandType(), received_select_champion->get_commandType());
    EXPECT_EQ(select_champion->get_championType(), received_select_champion->get_championType());
    EXPECT_EQ(select_champion->get_match_name(), received_select_champion->get_match_name());
    EXPECT_EQ(select_champion->get_map_name(), received_select_champion->get_map_name());
    delete select_champion;
}

TEST(ProtocolTest, SendAndReceiveMatch) {
    MatchCommand* match = new MatchCommand(player_id, number_players, map_test, match_test);
    client_protocol.send_Command(match);
    std::shared_ptr<Command> received_command = server_protocol.receive_Command();
    std::shared_ptr<MatchCommand> received_match = std::dynamic_pointer_cast<MatchCommand>(received_command);
    EXPECT_EQ(match->get_playerId(), received_match->get_playerId());
    EXPECT_EQ(match->get_commandType(), received_match->get_commandType());
    EXPECT_EQ(match->get_match_name(), received_match->get_match_name());
    EXPECT_EQ(match->get_map_name(), received_match->get_map_name());
    delete match;
}
