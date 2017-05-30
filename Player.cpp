#include "Player.hpp"

using std::queue;

Player::Player(int _x, int _y, char _icon, queue <MapAction*>*_q) : Creature(_x, _y, _icon, _q) {
    direction = UP;
}

void Player::shoot()
{
    int x = getX();
    int y = getY();

    switch(direction)
    {
        case UP:
            y -= 1;
            break;
        case DOWN:
            y += 1;
            break;
        case LEFT:
            x -= 1;
            break;
        case RIGHT:
            x += 1;
            break;
        default:
            break;
    }

    actionQueue -> push(new MapAction( 0, x, y, 'o', '\0', ADD, direction));
}
void Player::setDirection(Direction d)
{
    direction = d;
}

void Player::goUp() {
    setDirection(UP);
    Creature::goUp();
}

void Player::goRight()
{
    setDirection(RIGHT);
    Creature::goRight();
}

void Player::goDown()
{
    setDirection(DOWN);
    Creature::goDown();
}

void Player::goLeft()
{
    setDirection(LEFT);
    Creature::goLeft();
}

char Player::getIcon() {
    switch(direction)
    {
        case UP:
            return '^';
        case RIGHT:
            return '>';
        case DOWN:
            return 'v';
        case LEFT:
            return '<';
        default:
            return '\0';
    }
}


