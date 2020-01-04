#include "entity.h"
#include "resource.h"
entity::entity(int W ,int H ,int X ,int Y)
	:  Width(W), Height(H), PosX(X), PosY(Y), DiffX(0), DiffY(0)
{
	type=ENTITY_TYPE_DEFALUT;
	Health=0;

}
entity::entity()
{
    //Default size of the object
    Width =10;
    Height = 10;
    //Original coordinates
    PosX = 0;
    PosY = 0;
}

void entity::offset(int Dx , int Dy)
{
    // Just like the move function but not modify the position difference.
    PosX += Dx;
    PosY += Dy;
}

bool entity:: checkCollision(const entity *another)
{
    int self_x_min = PosX;
    int self_x_max = PosX + Width;

    int another_x_min = another->PosX;
    int another_x_max = another->PosX + another->Width;

    bool x_collided = self_x_max >= another_x_min && self_x_min <= another_x_max;

    int self_y_min = PosY;
    int self_y_max = PosY + Height;

    int another_y_min = another->PosY;
    int another_y_max = another->PosY + another->Height;

    bool y_collided = self_y_max >= another_y_min && self_y_min <= another_y_max;

    return x_collided && y_collided;
}

