#include "filterable.h"

Filterable::Filterable()
{
    filtered = false;
}

bool Filterable::isFiltered() const
{
    return filtered;
}

void Filterable::setFiltered(bool value)
{
    filtered = value;
}
