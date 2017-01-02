#include "selectable.h"

Selectable::Selectable()
{
    selected = false;
}

bool Selectable::getSelected() const
{
    return selected;
}

void Selectable::setSelected(bool value)
{
    selected = value;
}
