#include "canal.h"

Canal::Canal(QObject *parent) : QObject{parent}
{
    this->value = 0;
}

void Canal::set_value(int value)
{
    if (value >= 0 && value <= 255)
        this->value = value;
}

QString Canal::get_type() { return this->type; }

int Canal::get_value() { return this->value; }
