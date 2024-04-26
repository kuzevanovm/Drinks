#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <list>

using namespace std;

#include "main.h"



// Фабричный метод

Drink *CreateDrink( const DrinkType type)
{
    switch(type)
    {
        case DrinkType::Coffee:return new Coffee(static_cast<DrinkTemperature>(rand()%3+1));
        case DrinkType::Matcha:return new Matcha(static_cast<DrinkTemperature>(rand()%3+1));
        case DrinkType::Water:return new Water(static_cast<DrinkTemperature>(rand()%3+1));
        case DrinkType::Milk:return new Milk(static_cast<DrinkTemperature>(rand()%3+1));
        default: return NULL;
    }
}

wstring PrintDrinkType(DrinkType type)
{
    switch(type)
    {
        case DrinkType::Coffee: return L"Coffee";
        case DrinkType::Matcha: return L"Matcha";
        case DrinkType::Water: return L"Water";
        case DrinkType::Milk: return L"Milk";
        default: return L"Unknown drink";
    }
}

wstring PrintDrinkTemperature(DrinkTemperature temp)
{
    switch(temp)
    {
        case DrinkTemperature::Cold: return L"Cold";
        case DrinkTemperature::Hot: return L"Hot";
        case DrinkTemperature::Normal: return L"Normal";
        default: return L"Unknown temperature";
    }
}

//№1 Отбор напитка  по tемпературе

void Task_1(Iterator<DrinkPtr> * Iterator)
{
	for(Iterator->First(); !Iterator->IsDone(); Iterator->Next())
	{
		const DrinkPtr CurrentDrink = Iterator->GetCurrent();
        wcout << PrintDrinkType(CurrentDrink->GetType()) << " " << PrintDrinkTemperature(CurrentDrink->GetTemperature()) << endl;
    }
}


// №2 Выпить  все готовые холодные напитки

void Task_2(Iterator<DrinkPtr> * Iterator)
{
    for(Iterator->First(); !Iterator->IsDone(); Iterator->Next())
    {
        const DrinkPtr CurrentDrink = Iterator->GetCurrent();
        CurrentDrink->Sip();
    }
}

int main()
{
    srand(time(0));

// Заполнение контейнеров объектами

    VectorDrinkContainer ContainerVector;

    for (int i = 0; i < rand()%400 + 500; i++)
    {
        ContainerVector.AddDrink(CreateDrink(static_cast<DrinkType>(rand()%4+1)));
    };

    ListDrinkContainer ContainerList;

    for (int i = 0; i < rand()%400 + 500; i++)
    {
        ContainerList.AddDrink(CreateDrink(static_cast<DrinkType>(rand()%4+1)));
    };


    // Для первого задания
    Iterator<DrinkPtr> *Iterator = new DrinkTemperatureDecorator(ContainerList.GetIterator(),DrinkTemperature::Hot);
    Task_1(Iterator);

    // Для второго задания
    //Iterator<DrinkPtr> *Iterator = new DrinkTemperatureDecorator(new DrinkReadyDecorator(ContainerVector.GetIterator(),true), DrinkTemperature::Cold);
    //Task_2(Iterator);


    return 0;
}
