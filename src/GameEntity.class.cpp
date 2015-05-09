/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEntity.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 22:12:34 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/GameEntity.class.hpp"

GameEntity::GameEntity() : _active(false) {

}

GameEntity::GameEntity(float x, float y, int w, int h) :
    _x(x), _y(y), _width(w), _height(h), _active(false) {

}

GameEntity::GameEntity(GameEntity const & src) {
    *this = src;
}

GameEntity::~GameEntity() {

}

Block const & GameEntity::getShape() {
    this->_shape.x = getX();
    this->_shape.y = getY();
    return this->_shape;
}
float   GameEntity::getX() const { return this->_x; }
float   GameEntity::getY() const { return this->_y; }
int     GameEntity::getWidth() const { return this->_width; }
int     GameEntity::getHeight() const { return this->_height; }
bool    GameEntity::isActive() const { return this->_active; }

void    GameEntity::setX(float x) { this->_x = x; }
void    GameEntity::setY(float y) { this->_y = y; }
void    GameEntity::setWidth(int width) { this->_width = width; }
void    GameEntity::setHeight(int height) { this->_height = height; }
void    GameEntity::setActive(bool active) { this->_active = active; }
void    GameEntity::setColor(Block::color c) { this->_shape.setColor(c); }
void    GameEntity::setContent(std::string content) { this->_shape.setContent(content); }

bool    GameEntity::isCollide(GameEntity const & target) {
    if (    this->_x + this->getWidth() -1 < target.getX()
         || this->_x > target.getX() + target.getWidth()
         || this->_y + this->getHeight() -1 < target.getY()
         || this->_y > target.getY() + target.getHeight() )
        return false;
    return true;
}

GameEntity &    GameEntity::operator=(GameEntity const & rhs) {
    this->_x = rhs.getX();
    this->_y = rhs.getY();
    this->_width = rhs.getWidth();
    this->_height = rhs.getHeight();
    this->_active = rhs.isActive();

    return *this;
}
