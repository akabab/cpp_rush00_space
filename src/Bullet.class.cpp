/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 22:05:50 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bullet.class.hpp"
#include "../inc/Game.class.hpp"

Bullet::Bullet() : GameEntity (0, 0, 1, 1), _speed(0) {
    _shape.c = Block::YELLOW;
    _shape.content = "~";
    this->_width = 1;
}

Bullet::Bullet(float x, float y, int w, int h)
    : GameEntity(x, y, w, h), _speed(0)  {

}

Bullet::Bullet(Bullet const & src) : GameEntity (src) {
    *this = src;
}

Bullet::~Bullet() {

}

float   Bullet::getSpeed() { return this->_speed; }

void    Bullet::setSpeed(float speed) { this->_speed = speed; }

void Bullet::update(float const deltaTime) {
    this->_x += deltaTime * this->_speed;

    if (this->_x < 0 || this->_x > Game::s_game->getScreen()->getX())
        this->_active = false;
}

Bullet &    Bullet::operator=(Bullet const & rhs) {
    GameEntity::operator=(rhs);

    return *this;
}
