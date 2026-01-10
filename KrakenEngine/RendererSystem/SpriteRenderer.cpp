#include "SpriteRenderer.h"
#include <chrono>
#include <string>



int Round(double d) {
    int r = /*static_cast<int>(0.5 + d - (d < 0))*/ std::round(d + 0.5);
    return r /*  +((d - r) == .5)*/;
}

void SpriteRenderer::Render(ComPtr<SpriteRenderData> data, RenderField& field,ComPtr<Camera> camera)
{
    Sprite& sprite = data->GetSprite();
    Transform& transform = data->GetOwner().GetTransform();

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


    for (int i = 0; i < field.GetHeight(); i++)
    {
        for (int j = 0; j < field.GetWidth(); j++)
        {
            Vector2 normalizedField((double)j / field.GetWidth(), (double)i / field.GetHeight());

            Vector2 pos = camera->ScreenToWorld(Vector2(normalizedField.X() * camera->GetSize().X(), normalizedField.Y() * camera->GetSize().Y()));
            pos = inversedTransMatrix * pos;
            pos.Y() *= -1;
            pos += data->GetCenter();
            int roundedX = Round(pos.X());
            int roundedY = Round(pos.Y());

            if (field.IsGreaterDepthAt(j, i, data->GetOrder())) {
                if (roundedX >= 0 && roundedX < sprite.GetWidth() && roundedY >= 0 && roundedY < sprite.GetHeight() && sprite.GetData()[roundedY][roundedX] != ' ')
                {
                    field.SetAt(j, i, sprite.GetData()[roundedY][roundedX]);
                    field.SetDepthAt(j, i, data->GetOrder());
                }
            }

        }
    }
}
