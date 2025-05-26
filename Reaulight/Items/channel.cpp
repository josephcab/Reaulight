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

void Channel::set_value(int value) { this->value = value; }

int Channel::get_value() { return this->value; }

ChannelR::ChannelR(int place, QObject *parent) : Channel{place, parent}
{
    this->place = place;
    this->value = 0;
    this->type = "Red channel";
}

ChannelG::ChannelG(int place, QObject *parent) : Channel{place, parent}
{
    this->place = place;
    this->value = 0;
    this->type = "Green channel";
}

ChannelB::ChannelB(int place, QObject *parent) : Channel{place, parent}
{
    this->place = place;
    this->value = 0;
    this->type = "Blue channel";
}
