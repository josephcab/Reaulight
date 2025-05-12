#include "channel.h"

Channel::Channel(int place, QObject *parent) : QObject{parent}
{
    this->place = place;
}

void Channel::set_place(int place)
{
    if (place >= 0 && place <= 255)
        this->place = place;
}

QString Channel::get_type() { return this->type; }

int Channel::get_place() { return this->place; }
