#include "bullet.h"

bullet::bullet()
{

}

void bullet::fly()
{
    setPos(x(), y() - 3);
    emit attack(x(), y());
    if(y() < -40) {
        this->scene()->removeItem(this);
        delete this;
    }
}
