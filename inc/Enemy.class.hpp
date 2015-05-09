/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 20:40:24 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

#include "Character.class.hpp"
#include <iostream>
#include <string>

class Enemy : public Character {
public:
    Enemy();
    Enemy(std::string name);
    Enemy(std::string name, float x, float y, int w, int h);
    Enemy(Enemy const & src);
    ~Enemy();

    void    update(float const deltaTime);
    void    shoot(void);

    Enemy &    operator=(Enemy const & rhs);

protected:

private:

};

std::ostream &  operator<<(std::ostream & o, Enemy const & rhs);

#endif
