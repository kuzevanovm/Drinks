#ifndef MainH
#define MainH

#include <vector>
#include <list>
#include "Patterns.h"

using namespace std;

// Характеристики объектов

enum class DrinkType: int
{
    Coffee = 1,
    Matcha = 2,
    Water = 3,
    Milk = 4,
    Unknown = -1
};

enum class DrinkTemperature: int
{
    Cold = 1,
    Hot = 2,
    Normal = 3
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

// Базовый класс семейства

class Drink
{
protected:
    bool DrinkIsReady;
    DrinkType type;
    DrinkTemperature temp;
    DrinkColor color;
    DrinkVolume volume;
    Drink()
    {
         DrinkIsReady = bool(rand()%2);
    };
public:
    bool IsReady() const { return DrinkIsReady; }
    virtual DrinkType GetType() const = 0;
    DrinkColor GetColor() const { return color; };
    DrinkTemperature GetTemperature() const { return temp; };
    DrinkVolume GetVolume() const { return volume; };
    virtual void Sip() = 0;
    virtual void SetVolume(DrinkVolume NewVolume) {volume = NewVolume;}

    virtual void Cool()
    {
        cout << "Напиток охлажден" << endl;
        temp = DrinkTemperature::Cold;
    }
    virtual void heat()
    {
        cout << "Напиток подогрет" << endl;
        temp = DrinkTemperature::Hot;
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
    Coffee(DrinkTemperature Temp) : Drink() { temp = Temp; }
    DrinkType GetType () const { return DrinkType::Coffee; }
    void Sip() { wcout << L"Drink coffee" << endl; }
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
    Matcha(DrinkTemperature Temp) : Drink() { temp = Temp; }
    DrinkType GetType () const { return DrinkType::Matcha; }
    void Sip() { wcout << L"Drink matcha" << endl; }
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
    Water(DrinkTemperature Temp) : Drink() { temp = Temp; }
    DrinkType GetType () const { return DrinkType::Water; }
    void Sip() { wcout << L"Drink water" << endl; }
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
    Milk(DrinkTemperature Temp) : Drink() { temp = Temp; }
    DrinkType GetType () const { return DrinkType::Milk; }
    void Sip() { wcout << L"Drink milk" << endl; }
};

// Базовый класс контейнера
class Container
{
public:
    virtual void AddDrink (DrinkPtr NewDrink)=0;
    virtual int GetCount() const = 0;
    virtual Iterator<DrinkPtr> *GetIterator()=0;
};


// Итератор для vector

class VectorDrinkIterator : public Iterator<DrinkPtr>
{
private:
    const vector<DrinkPtr> *VectorDrink;
    vector<DrinkPtr>::const_iterator it;
public:
    void First() {it = VectorDrink->begin();}
    void Next() {it++;}
    bool IsDone() const {it == VectorDrink->end();}
    DrinkPtr GetCurrent() const {return *it;}
    VectorDrinkIterator(const vector<DrinkPtr> *vectorDrink)
    {
        VectorDrink = vectorDrink;
        it = VectorDrink->begin();
    }

};


// Первый контейнер - vector

class VectorDrinkContainer : public Container
{
private:
    vector<DrinkPtr> VectorDrink;
public:
    void AddDrink(DrinkPtr NewDrink){VectorDrink.push_back(NewDrink);}
    int GetCount() const {return VectorDrink.size();}

    Iterator<DrinkPtr> *GetIterator ()
    {
        return new VectorDrinkIterator(&VectorDrink);
    };
};


// Итератор для list

class ListDrinkIterator : public Iterator<DrinkPtr>
{
private:
    const list<DrinkPtr> *ListDrink;
    list<DrinkPtr>::const_iterator It;
public:
    void First() {It = ListDrink->begin();}
    void Next() {It++;}
    bool IsDone() const {It == ListDrink->end();}
    DrinkPtr GetCurrent() const {return *It;};
    ListDrinkIterator(const list<DrinkPtr> *listDrink)
    {
        ListDrink = listDrink;
        It = ListDrink->begin();
    }
};

// Второй контейнер - list

class ListDrinkContainer : public Container
{
private:
    list<DrinkPtr> ListDrink;
public:
    void AddDrink(DrinkPtr NewDrink){ListDrink.push_back(NewDrink);}
    int GetCount() const {return ListDrink.size();}
    Iterator<DrinkPtr> *GetIterator ()
    {
        return new ListDrinkIterator(&ListDrink);
    };

};

// Декоратор фильтр по типу напитка

class DrinkTypeDecorator : public IteratorDecorator<DrinkPtr>
{
private:
    DrinkType TargetType;
public:
    DrinkTypeDecorator(Iterator<DrinkPtr> *Iterator, DrinkType targetType): IteratorDecorator(Iterator)
    {
        TargetType = targetType;
    }
    void First()
    {
        Decorator -> First();
        while (!Decorator -> IsDone()&& Decorator->GetCurrent()->GetType() != TargetType)
        {
            Decorator->Next();
        }
    }
    void Next()
    {
        do
        {
            Decorator->Next();
        }
        while(!Decorator->IsDone()&&Decorator->GetCurrent()->GetType() != TargetType);
    }
};

// Декоратор по температуре напитка

class DrinkTemperatureDecorator : public IteratorDecorator<DrinkPtr>
{
private:
    DrinkTemperature TargetTemperature;
public:
    DrinkTemperatureDecorator(Iterator<DrinkPtr> *Iterator, DrinkTemperature targetTemperature): IteratorDecorator(Iterator)
    {
        TargetTemperature = targetTemperature;
    }
    void First()
    {
        Decorator -> First();
        while (!Decorator -> IsDone()&& Decorator->GetCurrent()->GetTemperature() != TargetTemperature)
        {
            Decorator->Next();
        }
    }
    void Next()
    {
        do
        {
            Decorator->Next();
        }
        while(!Decorator->IsDone()&&Decorator->GetCurrent()->GetTemperature() != TargetTemperature);
    }
};

// Декоратор по определению готовности напитка

class DrinkReadyDecorator : public IteratorDecorator<DrinkPtr>
{
private:
    bool TargetReady;
public:
    DrinkReadyDecorator(Iterator<DrinkPtr> *Iterator, bool targetReady): IteratorDecorator(Iterator)
    {
        TargetReady = targetReady;
    }
    void First()
    {
        Decorator -> First();
        while (!Decorator -> IsDone()&& Decorator->GetCurrent()->IsReady() != TargetReady)
        {
            Decorator->Next();
        }
    }
    void Next()
    {
        do
        {
            Decorator->Next();
        }
        while(!Decorator->IsDone()&&Decorator->GetCurrent()->IsReady() != TargetReady);
    }
};



#endif // MainH
