/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:08:24 by ycribier          #+#    #+#             */
/*   Updated: 2015/01/11 20:32:21 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/Game.class.hpp"
#include "../inc/Game.class.hpp"
#include "../inc/Ui.class.hpp"

int main(void) {
    while (1) {
        Game * g = new Game();
        delete g;
    }
    return 0;
}
