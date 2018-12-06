#include "pawngraphics.hh"

pawngraphics::pawngraphics()
{

}

void pawngraphics::set_coords(QPointF coordinates)
{
    xycoords_ = coordinates;
}


void pawngraphics::set_pawnSlot(int slot)
{
    pawnSlot_ = slot;
}

int pawngraphics::get_pawnSlot()
{
    return pawnSlot_;
}


