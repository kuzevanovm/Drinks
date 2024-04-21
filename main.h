#ifndef MainH
#define MainH

#include <vector>
#include <list>
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

// Базовый класс семейства

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
    DrinkPtr GetCurrent() const {*It;};
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

// Декоратор для определения готовности напитка

class ReadyCheckIterator : public IteratorDecorator<DrinkPtr>
{
private:
    Iterator<DrinkPtr> *it;
    bool DrinkIsReady;
public:
    ReadyCheckIterator(Iterator<DrinkPtr> *it, bool DrinkIsReady):IteratorDecorator(it) {}
    void First()
    {
        it->First();
        while(!it->IsDone() && it->GetCurrent()->IsReady())
        {
            Next();
        }
    }
    void Next()
    {
        while(!it->IsDone() && it->GetCurrent()->IsReady() != DrinkIsReady)
        {
            it->Next();
        }
    }
};

// Декоратор для фильтрации напитков по температуре

class TemperatureFiltrIterator : public IteratorDecorator<DrinkPtr>
{
private:
    Iterator<DrinkPtr> *it;
    DrinkTemperature RightTemp;
public:
    TemperatureFiltrIterator(Iterator<DrinkPtr> *it, DrinkTemperature RightTemp) : IteratorDecorator(it) {}
    void First()
    {
        it->First();
        while (!it->IsDone() && it->GetCurrent()->GetTemperature() != RightTemp)
        {
            it->Next();
        }
    }
    void Next()
    {
        it->Next();
        while (!it->IsDone() && it->GetCurrent()->GetTemperature() != RightTemp)
        {
            it->Next();
        }
    }
};

// Декоратор изменеия объема напитка

class DrinkVolumeModifierIterator : public IteratorDecorator<DrinkPtr>
{
private:
    Iterator<DrinkPtr> *it;
    DrinkVolume newVolume;

public:
    DrinkVolumeModifierIterator(Iterator<DrinkPtr> *it, DrinkVolume volume) : IteratorDecorator(it), newVolume(volume) {}

    void First() {
        it->First();
    }

    void Next() {
        it->Next();
    }

    bool IsDone() const {
        return it->IsDone();
    }

    DrinkPtr GetCurrent() const
    {
        DrinkPtr current = it->GetCurrent();
        current->SetVolume(newVolume);
        return current;
    }
};

#endif // MainH

