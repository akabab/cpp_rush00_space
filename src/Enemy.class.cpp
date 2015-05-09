/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 22:14:50 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Enemy.class.hpp"
#include "../inc/Bullet.class.hpp"
#include "../inc/Game.class.hpp"
#include <cstdlib>
#include <ctime>

Enemy::Enemy()
    : Character("Enemy", 0, 0, 1, 1) {
    this->type = GameEntity::ENEMY;
    _shape.c = Block::MAGENTA;
    _shape.content = "<]";
    this->_width = 2;
}

Enemy::Enemy(std::string name)
    : Character(name, 0, 0, 1, 1) {

}

Enemy::Enemy(std::string name, float x, float y, int w, int h)
    : Character(name, x, y, w, h) {

}

Enemy::Enemy(Enemy const & src) : Character() {
    *this = src;
}

Enemy::~Enemy() {

}

void    Enemy::update(float const deltaTime) {
    this->_x -= deltaTime * (std::rand() % 5 + 10);

    if (this->_x < 0)
        this->_active = false;

    if (!(std::rand() % 1000))
        shoot();
};

void    Enemy::shoot() {
    Bullet *  bullets = Game::s_game->getBulletsPool();

    for (int i = 0; i < BULLET_POOL_SIZE; i++) {
        Bullet &    bullet = bullets[i];
        if (!bullet.isActive()) {
            bullet.type = GameEntity::ENEMY;
            bullet.setContent("~");
            bullet.setWidth(1);
            bullet.setColor(Block::MAGENTA);
            bullet.setX(this->_x - 1);
            bullet.setY(this->_y);
            bullet.setSpeed(-20);
            bullet.setActive(true);
            break;
        }
    }
}

Enemy &    Enemy::operator=(Enemy const & rhs) {
	Character::operator=(rhs);

	return *this;
}

std::ostream &  operator<<(std::ostream & o, Enemy const & rhs) {
    o   << "Enemy: [" << rhs.getName() << "]";
    return o;
}
