#include <iostream>

using namespace std;

#include "main.h"

Drink::Drink()
{
    DrinkIsReady = bool(rand() % 2);
}

// Фабричный метод

Drink *CreateDrink(DrinkType type)
{
    switch(type)
    {
        case DrinkType::Coffee:return new Coffee;
        case DrinkType::Matcha:return new Matcha;
        case DrinkType::Water:return new Water;
        case DrinkType::Milk:return new Milk;
        default: return NULL;
    }
}

int main()
{
// Заполнение контейнеров объектами

    VectorDrinkContainer ContainerVector;

    for (int i = 0; i < rand()%300 + 200; i++)
    {
        ContainerVector.AddDrink(CreateDrink(static_cast<DrinkType>(rand()%4+1)));
    };

    ListDrinkContainer ContainerList;

    for (int i = 0; i < rand()%300 + 200; i++)
    {
        ContainerList.AddDrink(CreateDrink(static_cast<DrinkType>(rand()%4+1)));
    };

    cout << "Hello world!" << endl;
    return 0;
}
