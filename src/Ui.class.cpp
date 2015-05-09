/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ui.class.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 13:37:03 by cdenis            #+#    #+#             */
/*   Updated: 2015/01/11 21:55:11 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Screen.class.hpp"
#include "../inc/Ui.class.hpp"
#include <sstream>

Ui::Ui(void) :
    x(0), y(0), c(Block::BLACK), text("UNSET"), value(-1), active(false)  {

}

Ui::Ui(Ui const & src) {
    *this = src;
}

Ui::~Ui(void) { }

Ui & Ui::operator=(Ui const & rhs) {
    (void)rhs;
    return *this;
}

Block Ui::toBlock(void) const {
    std::ostringstream ss;
    ss << text;
    if (value >= 0) {
        ss << ": " << value;
    }
    return Block(x, y, c, ss.str());
}

void Ui::setElem(Ui::elem i, std::string msg, int v, Block::color c, int x, int y) {
    elems[i].text = msg;
    elems[i].c = c;
    elems[i].x = x;
    elems[i].y = y;
    elems[i].value = v;
    elems[i].active = false;
}

void Ui::init(void) {
    setElem(SCORE, "SCORE", 0, Block::WHITE, 10, 1);
    setElem(TIME, "TIME",  0, Block::WHITE, 30, 1);
    setElem(LIVES, "LIVES", 3, Block::WHITE, 50, 1);
    setElem(TITLE, "~::PUMPKIN ZLATAN & QQ THE BIRD::~", -1, Block::WHITE, 10, 1);
    setElem(PLAY, "PLAY", -1, Block::WHITE, 10, LINES / 2);
    setElem(REPLAY, "REPLAY", -1, Block::WHITE, 10, LINES / 2);
    setElem(YCRIBIER, "<] ::YCRIBIER", -1, Block::MAGENTA, COLS - 13, 0);
    setElem(CDENIS, ":}=> ::CDENIS", -1, Block::CYAN, COLS - 13, 1);
    setElem(MUAHA, "( MuAHhahAHAHAhah!!! )>", -1, Block::MAGENTA, COLS - 37, 0);
    setElem(QQ, "( QQ )>", -1, Block::CYAN, COLS - 21, 1);
}

Ui Ui::elems[Ui::MAX_ELEM_COUNT];

