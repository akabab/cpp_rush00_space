/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Screen.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 13:16:15 by cdenis            #+#    #+#             */
/*   Updated: 2015/01/10 23:14:32 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H

# include <ncurses.h>
# include <stdint.h>
# include <iostream>
# include "../inc/Block.class.hpp"

# define LIMIT_Y            3

class Screen {
public:
    Screen(void);
    Screen(Screen const & src);
    ~Screen(void);

    // Accessors
    int getX(void) const;
    int getY(void) const;
    int getSize(void) const;

    // Members
    void paint(void) const;
    void paintRewrite(void) const;
    void putBlock(Block const & b);
    void putBlock(int const x, int const y, Block::color const c);
    void wipe(void);

    void log(std::string const & msg);
    static int getInput(void);

private:
    int _x;
    int _y;
    int _size;
    bool _isImpair;
    std::string _debugMsg;
    Block * _currentPaint;
    Block * _previousPaint;

    Block::color * _color;
    char *          _content;

    Screen & operator=(Screen & rhs);

    void destroy(void);
    void init(void);

};

#endif
