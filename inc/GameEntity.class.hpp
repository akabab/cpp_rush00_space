/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEntity.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 22:11:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENTITY_H
# define GAME_ENTITY_H

#include "../inc/Block.class.hpp"

class GameEntity {
public:
    enum type {
        NONE,
        PLAYER,
        ENEMY
    };
    type type;

    GameEntity();
    GameEntity(float x, float y, int w, int h);
    GameEntity(GameEntity const & src);
    ~GameEntity();

    Block const &  getShape();
    float   getX() const;
    float   getY() const;
    int     getWidth() const;
    int     getHeight() const;
    bool    isActive() const;

    void    setX(float x);
    void    setY(float y);
    void    setWidth(int width);
    void    setHeight(int height);
    void    setActive(bool active);
    void    setShape(Block & newShape);
    void    setColor(Block::color c);
    void    setContent(std::string content);

    bool    isCollide(GameEntity const & target);

    GameEntity &    operator=(GameEntity const & rhs);

protected:
    float       _x;
    float       _y;
    int         _width;
    int         _height;
    bool        _active;
    Block       _shape;

private:

};

#endif
