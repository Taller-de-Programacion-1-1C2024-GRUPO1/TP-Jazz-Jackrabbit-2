#include "manager.h"

Manager::Manager(PhysicalMap map):gameMap(map){}



void Manager::check_colision(){

};

void Manager::update(){
    for (auto player : players){
        player->update();
    }
    for (auto enemy : enemies){
        enemy->update();
    }
    for (auto bullet : bullets){
        bullet->update();
    }
    check_colision();
};

void Manager::render(SDL_Renderer* renderer){
    gameMap.render(renderer);
    for (auto player : players){
        player->render(renderer);
    }
    for (auto enemy : enemies){
        enemy->render(renderer);
    }

    /*
    for (auto bullet : bullets){
        bullet->render(renderer);
    }
    for (auto item : items){
        item->render(renderer);
    }
    */
};



void Manager::add_player(Player* player){
    players.push_back(player);
}

void Manager::add_enemy(Enemy* enemy){
    enemies.push_back(enemy);
}

void Manager::add_bullet(Bullet* bullet){
    bullets.push_back(bullet);
}

void Manager::add_item(Item* item){
    items.push_back(item);
}
