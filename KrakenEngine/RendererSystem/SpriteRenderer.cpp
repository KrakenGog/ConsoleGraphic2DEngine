#include "SpriteRenderer.h"



void SpriteRenderer::Render(ComponentIterator<SpriteRenderData>& it, RenderField& field, Camera& camera)
{
    for (; !it.IsEnd(); ++it)
    {
        Sprite& sprite = (*it).GetSprite();
        Transform& transform = (*it).GetOwner().GetTransform();

        for (size_t i = 0; i < sprite.GetData().size(); i++)
        {
            for (size_t t = 0; t < sprite.GetData()[i].length(); t++)
            {
                if (field.IsGreaterDepthAt(i,t,(*it).GetOrder())) {
                    Vector2 screenPos = camera.WorldToScreen(Vector2(transform.position.X() + t, transform.position.Y()  - i));
                    field.SetAt(screenPos.X(), screenPos.Y(), sprite.GetData()[i][t]);
                    field.SetDepthAt(screenPos.X(), screenPos.Y(), (*it).GetOrder());
                }
            }
        }
    }
}
