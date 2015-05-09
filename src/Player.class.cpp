/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 20:33:42 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 22:15:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Player.class.hpp"
#include "../inc/Game.class.hpp"

Player::Player()
    : Character("Player", 0, 0, 1, 1) {
    this->type = GameEntity::PLAYER;
    _shape.c = Block::CYAN;
    _shape.content = " }=>";
    this->_width = 4;
    this->_height = 1;
}

Player::Player(std::string name)
    : Character(name, 0, 0, 1, 1), _deathState(-1),  _hitState(-1), _score(0), _lives(3), _direction(0), _speed(1.0f) {
    this->type = GameEntity::PLAYER;
    _shape.c = Block::CYAN;
    _shape.content = " }=>";
    this->_width = 4;
    this->_height = 1;
}

Player::Player(std::string name, float x, float y, int w, int h)
    : Character(name, x, y, w, h), _deathState(-1), _hitState(-1), _score(0), _lives(3), _direction(0), _speed(1.0f) {
    this->type = GameEntity::PLAYER;
    _shape.c = Block::CYAN;
    _shape.content = " }=>";
    this->_width = 4;
    this->_height = 1;
}

Player::Player(Player const & src) : Character(src) {
    *this = src;
}

Player::~Player() {

}

/*GETTERS*/
int     Player::getScore() const { return this->_score; }
int     Player::getLives() const { return this->_lives; }

/*SETTERS*/
void    Player::addScore(int amount) {
    this->_score += amount;
    Ui::elems[Ui::SCORE].value = this->_score;
}
void    Player::setScore(int score) {
    this->_score = score;
    Ui::elems[Ui::SCORE].value = this->_score;
}
void    Player::setLives(int lives) {
    if (_hitState >= 0.0f) {
        return;
    } else {
        _hitState = 0.0f;
    }
    if (lives <= 0) {
        this->_lives = 0;
        this->die();
    }
    else
        this->_lives = lives;
    Ui::elems[Ui::LIVES].value = this->_lives;
}

/*SPECS*/
void    Player::die() {
    if (_deathState < 0.0f) {
        Game::s_game->getScreen()->log("GAME OVER");
        _deathState = 0;
    }
}

bool    Player::isDead() const {
    return (_deathState >= 12.0f);
}

void    Player::shoot() {
    if (_deathState >= 0.0f) { return; }
    Bullet *  bullets = Game::s_game->getBulletsPool();

    for (int i = 0; i < BULLET_POOL_SIZE; i++) {
        Bullet &    bullet = bullets[i];
        if (!bullet.isActive()) {
            bullet.type = GameEntity::PLAYER;
            bullet.setContent("+-");
            bullet.setWidth(2);
            bullet.setColor(Block::CYAN);
            bullet.setX(this->_x + this->_width);
            bullet.setY(this->_y);
            bullet.setSpeed(40);
            bullet.setActive(true);
            break;
        }
    }
}

float     calcSpeed(int dir, float value) {
    return ((dir == 100 || dir == 97) ? 2.0f * value : value);
}

void    Player::newInput(int const input) {
    switch (input) {
    case 97:
    case 100:
    case 115:
    case 119: {
        if (input == _direction) {
            _speed += calcSpeed(input, (15.0f - _speed) / 8.0f);
        } else if (_speed <= 0.5f) {
            switch (input) {
            case 119: _y -= 1.0f; break; // W (up)
            case 115: _y += 1.0f; break; // S (down)
            case 100: _x += 1.0f; break; // D (left)
            case 97:  _x -= 1.0f; break; // A
            }
            _speed = 0.0f;
        } else if ((input == 119 && _direction == 115)
                || (input == 115 && _direction == 119)
                || (input == 100 && _direction == 97)
                || (input == 97  && _direction == 100)) {
            _speed = 0.0f;
        } else if (_speed > 1.0f) {
            _speed -= calcSpeed(input, _speed - 1.0f) / 2.0f;
        }
        _direction = input;
        break;
    }
    default: shoot(); break;
    }
}

void    Player::update(float const deltaTime) {
    if (_speed > 1.0f) {
        _speed -= calcSpeed(_direction, deltaTime * 5);
    } else if (_speed > 0.0f) {
        _speed -= calcSpeed(_direction, deltaTime * 2);
    } else {
        _speed = 0.0f;
    }
    if (_deathState >= 0.0f) {
        _deathState += deltaTime * 10;
        if (_deathState <= 7.9f) {
            _shape.content = _deathAnimation[(int)_deathState];
        } else {
            _shape.content = " ";
        }
    } else {
        if (_speed <= 0.2f) {
            _shape.content = " }=>";
        } else {
            switch (_direction) {
            case 119: _y -= deltaTime * 2.5f * _speed; _shape.content = "'}=>"; break; // W (up)
            case 115: _y += deltaTime * 2.5f * _speed; _shape.content = ".}=>"; break; // S (down)
            case 100: _x += deltaTime * 5.0f * _speed; _shape.content = ":}=>"; break; // D (left)
            case 97:  _x -= deltaTime * 5.0f * _speed; _shape.content = " }=>"; break; // A (right)
            default: _shape.content = " }=>"; break;
            }
        }
        if (_hitState >= 0.0f) {
            _hitState += deltaTime * 25;
            if ((int)_hitState % 2) {
                _shape.content += ')';
            }
            if (_hitState > 30.0f) {
                _hitState = -1.0f;
            }
        }
    }
    //Area limits
    int const maxX = COLS - (_shape.content.size());
    if (_x < 0) {
        _x = 0;
    } else if (_x > maxX) {
        _x = maxX;
    }
    if (_y < LIMIT_Y) {
        _y = LIMIT_Y;
    } else if (_y >= LINES) {
        _y = LINES - 1;
    }
}


Player &    Player::operator=(Player const & rhs) {
    Character::operator=(rhs);

    return *this;
}

std::ostream &  operator<<(std::ostream & o, Player const & rhs) {
    o   << "Player: [" << rhs.getName() << "]";
    return o;
}

std::string const Player::_deathAnimation[8] = {
    "  -  ",
    "  +  ",
    " <+> ",
    "< + >",
    "-:o:-",
    "~:X:~",
    "~> <~",
    ">   <"
};

std::string const Player::_hitAnimation[8] = {
    " (  )",
    " }=> ",
    " }=>)",
    " }=> ",
    " }=>)",
    " }=> ",
    " }=>)",
    " }=> "
};
