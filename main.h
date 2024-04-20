#ifndef MainH
#define MainH

#include <vector>
#include "Patterns.h"

using namespace std;

// Характеристики объектов

enum class DrinkType: int
{
    Coffee,
    Matcha,
    Water,
    Milk,
    Unknown = -1
};

enum class DrinkTemperature: int
{
    Cold,
    Hot,
    Normal
};

enum class DrinkColor: int
{
    Green,
    Black,
    White,
    Clear,
    Unknown = -1
};

enum class DrinkVolume: int
{
    Large,
    Medium,
    Small
};

// Базовый класс

class Drink
{
protected:
    bool DrinkIsReady;
    DrinkType type;
    DrinkTemperature temp;
    DrinkColor color;
    DrinkVolume volume;
    Drink();
public:
    bool IsReady() const { return DrinkIsReady; }
    virtual DrinkType GetType() const = 0;
    DrinkColor GetColor() const { return color; };
    DrinkTemperature GetTemperature() const { return temp; };
    DrinkVolume GetVolume() const { return volume; };
    virtual void Sip() const;

    virtual void Cool()
    {
        cout << "Напиток охлажден" << endl;
    }
    virtual void heat()
    {
        cout << "Напиток подогрет" << endl;
    }

};

typedef Drink * DrinkPtr;

// Семейство объектов

class Coffee : public Drink
{
public:
    Coffee() : Drink()
    {
        color = DrinkColor::Black;
        temp = DrinkTemperature::Hot;
        volume = DrinkVolume::Medium;
        type = DrinkType::Coffee;
    }
    DrinkType GetType () const { return DrinkType::Coffee; }
    void Sip() { wcout << L"Выпили кофе"; };
};

class Matcha : public Drink
{
public:
    Matcha() : Drink()
    {
        color = DrinkColor::Green;
        temp = DrinkTemperature::Hot;
        volume = DrinkVolume::Small;
        type = DrinkType::Matcha;
    }
    DrinkType GetType () const { return DrinkType::Matcha; }
    void Sip() { wcout << L"Выпили матчу"; }
};

class Water : public Drink
{
public:
    Water() : Drink()
    {
        color = DrinkColor::Clear;
        temp = DrinkTemperature::Normal;
        volume = DrinkVolume::Large;
        type = DrinkType::Water;
    }
    DrinkType GetType () const { return DrinkType::Water; }
    void Sip() { wcout << L"Выпили воду"; }
};

class Milk : public Drink
{
public:
    Milk() : Drink()
    {
        color = DrinkColor::White;
        temp = DrinkTemperature::Cold;
        volume = DrinkVolume::Medium;
        type = DrinkType::Milk;
    }
    DrinkType GetType () const { return DrinkType::Milk; }
    void Sip() { wcout << L"Выпили молоко"; }
};


#endif // MainH

