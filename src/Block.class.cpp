/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 13:16:15 by cdenis            #+#    #+#             */
/*   Updated: 2015/01/11 22:12:24 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Block.class.hpp"

Block::Block(void) :
    x(0),
    y(0),
    c(BLACK),
    content("  ") { }

Block::Block(int x, int y) :
    x(x),
    y(y),
    c(BLACK),
    content("  ") { }

Block::Block(int x, int y, color c) :
    x(x),
    y(y),
    c(c),
    content("  ") { }

Block::Block(int x, int y, color c, std::string content) :
    x(x),
    y(y),
    c(c),
    content(content) { }

Block::Block(Block const & src) {
    *this = src;
}

Block::~Block(void) { }

void    Block::setColor(color c) { this->c = c; }
void    Block::setContent(std::string content) { this->content = content; }

Block & Block::operator=(Block const & rhs) {
    if (this != &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->c = rhs.c;
        this->content = rhs.content;
    }
    return *this;
}

bool Block::repaint(Block const & rhs) const {
    return (c != rhs.c || content != rhs.content);
}

bool Block::operator==(Block const & rhs) const {
    return (content == rhs.content
        && c == rhs.c
        && x == rhs.x
        && y == rhs.y);
}
