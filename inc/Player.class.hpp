/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 20:36:36 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 21:06:20 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include "Character.class.hpp"
#include <iostream>
#include <string>

class Player : public Character {
public:
    Player();
    Player(std::string name);
    Player(std::string name, float x, float y, int w, int h);
    Player(Player const & src);
    ~Player();

    Player &    operator=(Player const & rhs);

    int     getScore() const;
    int     getLives() const;

    void    addScore(int amount);
    void    setScore(int score);
    void    setLives(int lives);

    void    die(void);

    void    shoot(void);
    void    newInput(int const input);
    void    update(float const deltaTime);
    bool    isDead() const;

protected:

private:
    float   _deathState;
    float   _hitState;
    int     _score;
    int     _lives;
    int     _direction;
    float   _speed;
    static std::string const _deathAnimation[8];
    static std::string const _hitAnimation[8];
};

std::ostream &  operator<<(std::ostream & o, Player const & rhs);

#endif
