/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:08:24 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 22:04:18 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Game.class.hpp"
#include "../inc/GameEntity.class.hpp"
#include <sys/time.h>
#include <cstdlib>
#include <ctime>

#define MIN_TICK_LENGHT 50000
#define TO_MICROSECONDS 1000000

Game::Game(void) {
    init();
}

Game::Game(Game const & src) {
    *this = src;
}

Game::~Game(void) {
    _screen->wipe();
    delete this->_screen;
    delete this->_player;
    delete [] this->_enemies;
    delete [] this->_bullets;
}

/*GETTERS*/
Player *        Game::getPlayer() { return this->_player; }
Enemy *         Game::getEnemiesPool() { return this->_enemies; }
Bullet *        Game::getBulletsPool() { return this->_bullets; }
Screen *        Game::getScreen() { return this->_screen; }


/*SPECS*/
void    Game::manageCollision() {
    for (int i = 0; i < BULLET_POOL_SIZE; i++) {
        Bullet &  bullet = this->_bullets[i];
        if (bullet.isActive()) {
            if (bullet.type == GameEntity::PLAYER) { //Bullet vs Enemy
                for (int j = 0; j < ENEMY_POOL_SIZE; j++) {
                    Enemy &  enemy = this->_enemies[j];
                    if (enemy.isActive()) {
                        if (bullet.isCollide(enemy)) {
                            this->_player->addScore(10);
                            bullet.setActive(false);
                            enemy.setActive(false);
                        }
                    }
                }
            }
            else if (!this->_player->isDead() && bullet.type == GameEntity::ENEMY) { //Bullet vs Player
                if (this->_player->isCollide(bullet)) {
                    this->_player->setLives(this->_player->getLives() - 1);
                    bullet.setActive(false);
                }
            }
        }
    }

    //Enemy vs Player
    if (!this->_player->isDead()) {
        for (int i = 0; i < ENEMY_POOL_SIZE; i++) {
            Enemy &   enemy = this->_enemies[i];
            if (enemy.isActive()) {
                if (this->_player->isCollide(enemy)) {
                    this->_player->setLives(this->_player->getLives() - 1);
                    enemy.setActive(false);
                }
            }
        }
    }
}

void    Game::instantiateEnemy() {
    for (int i = 0; i < ENEMY_POOL_SIZE; i++) {
        Enemy & e = this->_enemies[i];
        if (!e.isActive()) {
            e.setX(this->_screen->getX());
            e.setY(std::rand() % (this->_screen->getY() - LIMIT_Y) + LIMIT_Y);
            e.setActive(true);
            return;
        }
    }
}

void Game::update(float const deltaTime) {
    if (!this->_player->isDead()) {
        if (!(std::rand() % (int)this->_instantiateRatio)) {
            if (this->_instantiateRatio > 10)
                this->_instantiateRatio -= 5;
            if (this->_instantiateRatio < 30) {
                if ((std::rand() % 5))
                    Ui::elems[Ui::MUAHA].active = true;
                else
                    Ui::elems[Ui::MUAHA].active = false;
            }
            instantiateEnemy();
        }

        _player->update(deltaTime);
        //enemies
        for (int i = 0; i < ENEMY_POOL_SIZE; i++) {
            Enemy & e = this->_enemies[i];
            if (e.isActive()) {
                e.update(deltaTime);
            }
        }
        //bullets
        for (int i = 0; i < BULLET_POOL_SIZE; i++) {
            Bullet & b = this->_bullets[i];
            if (b.isActive()) {
                b.update(deltaTime);
            }
        }
        manageCollision();
    }
    else {
        Ui::elems[Ui::QQ].active = true;
        _run = false;
    }
}

void Game::render(void) {

    // Draw bullets
    for (int i = 0; i < BULLET_POOL_SIZE; i++) {
        Bullet & b = this->_bullets[i];
        if (b.isActive()) {
            _screen->putBlock(b.getShape());
        }
    }
    // Draw enemies
    for (int i = 0; i < ENEMY_POOL_SIZE; i++) {
        Enemy & e = this->_enemies[i];
        if (e.isActive()) {
            _screen->putBlock(e.getShape());
        }
    }
    // Draw player
    _screen->putBlock(_player->getShape());

    // Draw Ui
    for (int i = 0; i < Ui::MAX_ELEM_COUNT; i++) {
        Ui & u = Ui::elems[i];
        if (u.active) {
            _screen->putBlock(Ui::elems[i].toBlock());
        }
    }

    _screen->paint();
}

void Game::loop(void) {
    _run = true;
    struct timeval t;
    uint64_t lastTick = 0;
    uint64_t newTick;
    int currentInput;
    uint64_t tickLength = 5000;
    float totalTime = 0;

    gettimeofday(&t, NULL);
    lastTick = t.tv_sec * TO_MICROSECONDS + t.tv_usec;
    while (_run) {
        currentInput = _screen->getInput();
        if (currentInput != ERR) {
            _lastInput = currentInput;
            _player->newInput(_lastInput);
        }
        gettimeofday(&t, NULL);
        newTick = t.tv_sec * TO_MICROSECONDS + t.tv_usec;
        if (newTick - lastTick > tickLength) {
            update((float)(newTick - lastTick) / TO_MICROSECONDS);
            render();
            totalTime += (float)(newTick - lastTick) / TO_MICROSECONDS;
            Ui::elems[Ui::TIME].value = totalTime;
            lastTick = newTick;
        }
    }
    Ui::elems[Ui::REPLAY].active = true;
    while (this->_screen->getInput() != 32) {
        render();
    }
}

void Game::init(void) {
    s_game = this;

    std::srand(std::time(0));
    this->_screen = new Screen();

    this->_player = new Player("NAME", 2, this->_screen->getY() / 2, 1, 1);
    this->_enemies = new Enemy[ENEMY_POOL_SIZE];
    this->_bullets = new Bullet[BULLET_POOL_SIZE];

    this->_instantiateRatio = 200;
    Ui::init();

    //menu
    Ui::elems[Ui::TITLE].active = true;
    Ui::elems[Ui::PLAY].active = true;
    Ui::elems[Ui::YCRIBIER].active = true;
    Ui::elems[Ui::CDENIS].active = true;
    while (this->_screen->getInput() != 32) {
        render();
    }
    Ui::elems[Ui::TITLE].active = false;
    Ui::elems[Ui::PLAY].active = false;
    Ui::elems[Ui::SCORE].active = true;
    Ui::elems[Ui::TIME].active = true;
    Ui::elems[Ui::LIVES].active = true;
    this->loop();
}

Game const & Game::operator=(Game const & rhs) const { (void)rhs; return *this; }

Game *  Game::s_game = NULL;
