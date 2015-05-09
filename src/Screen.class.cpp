/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Screen.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:57:59 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 20:56:05 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Screen.class.hpp"
#include <sstream>
#include <ctime>

Screen::Screen(void) {
    this->init();
}

Screen::Screen(Screen const & src) {
    (void)src;
    std::cout << "Why ?" << std::endl;
}

Screen::~Screen(void) {
    this->destroy();
}

// Accessors
int Screen::getX(void)    const { return _x; }
int Screen::getY(void)    const { return _y; }
int Screen::getSize(void) const { return _size; }

//Members
void Screen::putBlock(Block const & b) {
    if ((b.y < _y && b.x < _x) && (b.y >= 0 && b.x >= 0)) {
        if (b.content.size() > 1) {
            std::string s = b.content;
            for (uint32_t i = 0; i < s.size(); i ++) {
                putBlock(Block(b.x + i, b.y, b.c, s.substr(i, 1)));
            }
        } else {
            this->_currentPaint[b.y * _x + b.x] = b;
        }
    }
}

void Screen::putBlock(int const y, int const x, Block::color const c) {
    putBlock(Block(y, x, c));
}

void Screen::log(std::string const & msg) {
    _debugMsg = msg;
}

// Show dem blocks!
void Screen::paint(void) const {
    Block::color prevColor = Block::BLACK;
    int i = 0;
    while (i < _size) {
        Block & b = _currentPaint[i];
        if (prevColor != b.c) {
            attroff(COLOR_PAIR(prevColor));
            attron(COLOR_PAIR(b.c));
            prevColor = b.c;
        }
        if (_previousPaint[i].repaint(b)) {
            mvaddstr(b.y, b.x, b.content.c_str());
        }
        _previousPaint[i] = b;
        b.c = Block::BLACK;
        b.content = " ";
        i++;
    }
    mvaddstr(0, 0, _debugMsg.c_str());
    move(0, 0); // Reset cursor position
    refresh();
}

int Screen::getInput(void) {
    return getch();
}

// Initialisation
void Screen::init(void) {
    // Configure Ncurses
    initscr();                // Initialize ncurse
    start_color();            // Enable colors
    curs_set(0);              // Hide cursor
    noecho();                 // Hide input
    nodelay(stdscr, true);    // No lock on input
    init_pair(Block::BLACK,   COLOR_BLACK,   COLOR_WHITE);
    init_pair(Block::RED,     COLOR_RED,     COLOR_BLACK);
    init_pair(Block::GREEN,   COLOR_GREEN,   COLOR_BLACK);
    init_pair(Block::YELLOW,  COLOR_YELLOW,  COLOR_BLACK);
    init_pair(Block::BLUE,    COLOR_BLUE,    COLOR_BLACK);
    init_pair(Block::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(Block::CYAN,    COLOR_CYAN,    COLOR_BLACK);
    init_pair(Block::WHITE,   COLOR_WHITE,   COLOR_BLACK);
    init_pair(Block::COLOR_MAX,   COLOR_MAGENTA,   COLOR_RED);

    // Draw UI limit
    attron(COLOR_PAIR(Block::WHITE));
    mvhline(LIMIT_Y - 1, 0, '`', COLS);
    attroff(COLOR_PAIR(Block::WHITE));

    // Welcome msg
    _debugMsg = "";

    // Set screen properties
    _x = COLS;
    _y = LINES;
    _size = _y * _x;
    // _color = new Block::color [COLS * LINES];
    // _content = new char [COLS * LINES];
    _currentPaint = new Block [_size];
    _previousPaint = new Block [_size];
}

void Screen::wipe(void) {
    clear();
    // int i = 0;

    // while (i < _size) {
    //     _currentPaint[i].c = Block::BLACK;;
    //     i++;
    // }
}

// Memory cleanup
void Screen::destroy(void) {
    endwin();
    // delete [] _color;
    // delete [] _content;
    delete [] _currentPaint;
    delete [] _previousPaint;
}
