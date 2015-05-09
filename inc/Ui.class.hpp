/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ui.class.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 13:18:16 by cdenis            #+#    #+#             */
/*   Updated: 2015/01/11 21:53:03 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

#include "../inc/GameEntity.class.hpp"
#include <string>

class Ui {
public:
    enum elem {
        SCORE,
        TIME,
        LIVES,
        TITLE,
        PLAY,
        REPLAY,
        YCRIBIER,
        CDENIS,
        MUAHA,
        QQ,
        MAX_ELEM_COUNT
    };
    int border;
    int x;
    int y;
    Block::color c;
    std::string text;
    int value;
    bool active;

    Ui(void);
    Ui(Ui const & src);
    ~Ui(void);
    Ui & operator=(Ui const & rhs);

    Block toBlock(void) const;
    static Ui elems[MAX_ELEM_COUNT];
    static void init(void);

private:
    static void setElem(Ui::elem i, std::string msg, int v, Block::color c, int x, int y);
};

#endif
