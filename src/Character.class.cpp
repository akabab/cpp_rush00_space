/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 20:39:28 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Character.class.hpp"

Character::Character() : GameEntity(0, 0, 1, 1) {

}

Character::Character(std::string name)
    : GameEntity(0, 0, 1, 1), _name(name) {

}

Character::Character(std::string name, float x, float y, int w, int h)
    : GameEntity(x, y, w, h), _name(name) {

}

Character::Character(Character const & src) : GameEntity(src) {
    *this = src;
}

Character::~Character() {

}

std::string     Character::getName() const { return this->_name; }


Character &    Character::operator=(Character const & rhs) {
    GameEntity::operator=(rhs);
    this->_name = rhs.getName();

    return *this;
}

