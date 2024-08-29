#include "CardView.h"

Rect CardView::GetRect()
{
    return rect;
}

float CardView::GetZPosition()
{
    return zPositon;
}

//void CardView::OnSelected(Point point)
//{
//    transform.position = point - sprite.GetSize() / 2;
//}


void CardView::OnPointEnter(Point point)
{
    attributes = FOREGROUND_BLUE;
}

void CardView::OnPointExit(Point point)
{
    attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
}
