#include "channel.h"

Channel::Channel(int place, QList<int> range_value, QObject *parent) : QObject{parent}
{
    this->place = place;

    if (range_value[0] <= range_value[1]) this->range_value = range_value;
    else this->range_value = {0, 255};
}

void Channel::set_place(int place)
{
    if (place >= 0 && place <= 255)
        this->place = place;
}

QString Channel::get_type() { return this->type; }

int Channel::get_place() { return this->place; }

void Channel::set_value(int value)
{
    if (value >= this->range_value[0] && value <= this->range_value[1])
        this->value = value;
}

int Channel::get_value() { return this->value; }

void Channel::set_range_value(QList<int> range)
{
    if (range_value[0] <= range_value[1])
        this->range_value = range;
}

QList<int> Channel::get_range_value() { return this->range_value; }

ChannelDimmer::ChannelDimmer(int place, QList<int> range_value, QObject *parent) : Channel{place, range_value, parent}
{
    this->type = "Dimmmer channel";
}

ChannelStrobe::ChannelStrobe(int place, QList<int> range_value, QObject *parent) : Channel{place, range_value, parent}
{
    this->type = "Stroboscopic channel";
}

ChannelSound::ChannelSound(int place, QList<int> range_value, QObject *parent) : Channel{place, range_value, parent}
{
    this->type = "Sound Channel";
}

ChannelR::ChannelR(int place, QList<int> range_value, QObject *parent) : Channel{place, range_value, parent}
{
    this->type = "Red channel";
}

ChannelG::ChannelG(int place, QList<int> range_value, QObject *parent) : Channel{place, range_value, parent}
{
    this->type = "Green channel";
}

ChannelB::ChannelB(int place, QList<int> range_value, QObject *parent) : Channel{place, range_value, parent}
{
    this->type = "Blue channel";
}
