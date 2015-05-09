/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:02:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/05/09 15:23:46 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <ncurses.h>
# include "../inc/Player.class.hpp"
# include "../inc/Screen.class.hpp"
# include "../inc/Enemy.class.hpp"
# include "../inc/Bullet.class.hpp"
# include "../inc/Ui.class.hpp"

# define ENEMY_POOL_SIZE    100
# define BULLET_POOL_SIZE   100

class Game {
public:
    Game(void);
    Game(Game const & src);
    ~Game(void);

    Player *        getPlayer();
    Enemy *         getEnemiesPool();
    Bullet *        getBulletsPool();
    Screen *        getScreen();

    void loop(void);

    static Game     *s_game;

protected:

private:
    bool            _run;
    Screen *        _screen;
    Player *        _player;
    Enemy *         _enemies;
    Bullet *        _bullets;

    int             _lastInput;
    float           _instantiateRatio;

    void init(void);
    void update(float const deltaTime);
    void render(void);
    void manageCollision(void);
    void instantiateEnemy(void);

    Game const &    operator=(Game const & rhs) const;
};

#endif
