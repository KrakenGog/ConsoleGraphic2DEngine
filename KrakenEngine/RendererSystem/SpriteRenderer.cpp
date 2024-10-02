#include "SpriteRenderer.h"
#include <chrono>
#include <string>



int Round(double d) {
    int r = /*static_cast<int>(0.5 + d - (d < 0))*/ std::round(d);
    return r + ((d - r) == .5);
}

void SpriteRenderer::Render(ComponentIterator<SpriteRenderData>& it, RenderField& field, Camera& camera)
{
    for (; !it.IsEnd(); ++it)
    {
        if (!(*it).HasOwner())
            continue;
        //auto s = std::chrono::system_clock::now();
        Sprite& sprite = (*it).GetSprite();
        Transform& transform = (*it).GetOwner().GetTransform();

        Transform* current = &transform;
        Matrix<double> transMatrix(3, 3, 1);
        Matrix<double> inversedTransMatrix(3, 3, 1);
        while (true) {
            transMatrix *= current->GetTransformationMatrix();
            if (current->GetOwner().GetParent() != nullptr) {
                current = &current->GetOwner().GetParent()->GetTransform();
            }
            else {
                break;
            }
        }

        inversedTransMatrix = transMatrix.Inverse();
         
        //auto e = std::chrono::system_clock::now();
        //DBOUT("Get matrix: " << std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count());

        Vector2 endI = camera.WorldToScreen(transMatrix * Vector2(sprite.GetWidth() / sprite.GetPixelPerUnit(), 0));
        Vector2 endJ = camera.WorldToScreen(transMatrix * Vector2(0, sprite.GetHeight() / sprite.GetPixelPerUnit()));

        Vector2 start = camera.WorldToScreen(transMatrix * Vector2(0, 0));

        Vector2 newI = endI - start;
        Vector2 newJ = endJ - start;


        int down = -(*it).GetCenter().Y() / sprite.GetPixelPerUnit() * transform.Scale.Y();
        int up = sprite.GetHeight() / sprite.GetPixelPerUnit() * transform.Scale.Y() + down;
        int left = -(*it).GetCenter().X() / sprite.GetPixelPerUnit() * transform.Scale.X();
        int right = sprite.GetWidth() / sprite.GetPixelPerUnit() * transform.Scale.X() + left;

        int maxOffset = (std::max)({ std::abs(down), std::abs(up), std::abs(left),std::abs(right) });

        

        for (int i = -maxOffset + start.Y(); i < maxOffset + start.Y(); i++)
        {
            for (int j = -maxOffset + start.X(); j < maxOffset + start.X(); j++)
            {
                Vector2 pos = camera.ScreenToWorld(Vector2(j, i));
                pos = inversedTransMatrix * pos;
                pos.Y() *= -1;
                pos += (*it).GetCenter();
                int roundedX = Round(pos.X());
                int roundedY = Round(pos.Y());

                if (field.IsGreaterDepthAt(j,i, (*it).GetOrder())) {
                    if (roundedX >= 0 && roundedX < sprite.GetWidth()&& roundedY >= 0 && roundedY < sprite.GetHeight())
                    {
                        field.SetAt(j, i, sprite.GetData()[roundedY][roundedX]);
                        field.SetDepthAt(j, i, (*it).GetOrder());
                    }
                }
            }
        }
    }
}
