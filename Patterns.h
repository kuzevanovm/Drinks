#ifndef PatternsH
#define PatternsH

// Шаблон итератора

template<class Type> class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Type GetCurrent() const = 0;
};

// Интерфейс Декоратора

template<class Type>
class IteratorDecorator : public Iterator<Type>
{
protected:
    Iterator<Type> *Decorator;

public:
    IteratorDecorator(Iterator<Type> *it)
    {
        Decorator = it;
    }
    virtual ~IteratorDecorator() { delete Decorator; }
    virtual void First() {Decorator->First();}
    virtual void Next() {Decorator->Next();}
    virtual bool IsDone() const {return Decorator->IsDone();}
    virtual Type GetCurrent() const {return Decorator->GetCurrent();}

};

#endif // PatternsH

