/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 20:40:13 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULLET_H
# define BULLET_H

#include "GameEntity.class.hpp"

class Bullet : public GameEntity {
public:
    Bullet();
    Bullet(float x, float y, int w, int h);
    Bullet(Bullet const & src);
    ~Bullet();

    float   getSpeed();
    void    setSpeed(float speed);

    void    update(float const deltaTime);

    Bullet &    operator=(Bullet const & rhs);

protected:

private:
    float      _speed;
};

#endif
