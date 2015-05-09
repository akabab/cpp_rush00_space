/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 20:40:15 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_H
# define CHARACTER_H

#include "GameEntity.class.hpp"
#include <string>

class Character : public GameEntity {
public:
    Character();
    Character(std::string name);
    Character(std::string name, float x, float y, int w, int h);
    Character(Character const & src);
    ~Character();

    std::string     getName() const;

    //attack

    Character &    operator=(Character const & rhs);

protected:
    std::string     _name;
    int             _dmg;

private:

};

#endif
