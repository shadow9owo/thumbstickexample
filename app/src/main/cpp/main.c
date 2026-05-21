#include "raymob.h"
#include "raymath.h"

Vector2 CenterOfThumbstick;
Vector2 ThumbStickOffset;
bool Moving;
int MovingIndex;

void InitDynamicValues() {
    CenterOfThumbstick = (Vector2){
        256, GetScreenHeight() - 256
    };

    ThumbStickOffset = (Vector2){0,0};
    return;
}

void RenderThumbstick()
{
    DrawCircle(CenterOfThumbstick.x,CenterOfThumbstick.y,256,GRAY);
    DrawCircle(CenterOfThumbstick.x + ThumbStickOffset.x * 256,CenterOfThumbstick.y + ThumbStickOffset.y * 256,64,BLACK);
    return;
}

Vector2 GetOffsetPosition(Vector2 position)
{
    float radius = 256.0f;

    Vector2 offset = {
            (position.x - CenterOfThumbstick.x) / radius,
            (position.y - CenterOfThumbstick.y) / radius
    };

    float length = Vector2Length(offset);
    
    if (length > 1.0f)
    {
        offset = Vector2Scale(Vector2Normalize(offset), 1.0f);
    }

    ThumbStickOffset = offset;

    return offset;
}

int main(void)
{
    Moving = false;
    InitWindow(0, 0, "raylib [core] example - basic window");
    SetTargetFPS(300);

    InitDynamicValues();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        RenderThumbstick();

        for (size_t a = 0;a<GetTouchPointCount();a++)
        {
            if (CheckCollisionCircleRec(CenterOfThumbstick,256, (Rectangle){GetTouchPosition(a).x,GetTouchPosition(a).y,4,4}) && !Moving)
            {
                //use for movement
                GetOffsetPosition(GetTouchPosition(a));
                Moving = true;
                MovingIndex = a;
            }else {
                if (Moving && a == MovingIndex)
                {
                    GetOffsetPosition(GetTouchPosition(a));
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}