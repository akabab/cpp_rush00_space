/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 13:16:15 by cdenis            #+#    #+#             */
/*   Updated: 2015/01/11 22:11:47 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include <string>

class Block {
public:
    enum color {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        COLOR_MAX,
    };

    int x;
    int y;
    color c;
    std::string content;

    Block(void);
    Block(int x, int y);
    Block(int x, int y, color c);
    Block(int x, int y, color c, std::string content);
    Block(Block const & src);
    ~Block(void);

    void    setColor(color c);
    void    setContent(std::string content);

    Block & operator=(Block const & rhs);

    bool repaint(Block const & rhs) const;
    bool operator==(Block const & rhs) const;
};

#endif

