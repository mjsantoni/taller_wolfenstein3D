#include "server/game/positions_calculator.h"
#include <math.h>

std::vector<Coordinate>
PositionsCalculator::straightLine(Coordinate old_pos, Coordinate new_pos) {
    std::vector<Coordinate> items;
    int x_old = old_pos.x; int y_old = old_pos.y;
    int x_new = new_pos.x; int y_new = new_pos.y;
    if (x_new == x_old) {
        for (int i = y_old; (y_old < y_new) ? i <= y_new : i >= y_new; (y_old < y_new) ? i++ : i--) {
            Coordinate pos(x_old,i);
            items.push_back(pos);
        }
    } else if (y_new == y_old) {
        for (int i = x_old; (x_old < x_new) ? i <= x_new : i >= x_new; (x_old < x_new) ? i++ : i--) {
            Coordinate pos(i,y_old);
            items.push_back(pos);
        }
    } else {
        bool it_on_x = abs(y_new - y_old) < abs(x_new - x_old);
        double m = (it_on_x) ? ((double) (y_new - y_old) / (x_new - x_old)) :
                   ((double) (x_new - x_old) / (y_new - y_old));
        double b = (double) y_old - (m * x_old);
        int axis_old = it_on_x ? x_old : y_old;
        int axis_new = it_on_x ? x_new : y_new;
        //Si se quiere algo mucho mas aproximado no hacer el for del else
        //y solo hacer el primer for. Esto es mucho mas overfiteado.
        for (int i = axis_old; (axis_old < axis_new) ? i <= axis_new : i >= axis_new; (axis_old < axis_new) ? i++ : i--) {
            Coordinate pos(-1, -1);
            if (it_on_x) {
                //std::cout << "AntesITX: " << pos.x << " - Y: " << pos.y << "\n";
                pos.x = i;
                pos.y = std::round(m * i + b);
                //std::cout << "DespsITX: " << pos.x << " - Y: " << pos.y << "\n";
            }
            else {
                //std::cout << "AntesX: " << pos.x << " - Y: " << pos.y << "\n";
                pos.x = std::round(m * i + b); // esto esta roto
                pos.y = i;
                //std::cout << "DespsX: " << pos.x << " - Y: " << pos.y << "\n";
            }
            items.push_back(pos);
        }
    }
    return items;
}