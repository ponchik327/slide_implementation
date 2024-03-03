#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "geometry.h"

// ------------------------- интерфейс объекта ------------------- 

class Object
{
public: 
    virtual ~Object() = default;
public:
    // помогает понять групповой ли это объект или нет, удобно использовать для работы с методами AddObject() и GetGroup()
    virtual bool IsGropuObject() const = 0;

    // возвращает прямоугльник описывающий все обьекты группы, для одиночного объекта возвращает прямоугольник данный при инициализации
    virtual const Rect& GetSize() const = 0;

    // перегрузка для примитивного объекта выбрасывает исключение
    virtual void AddObject(std::unique_ptr<Object>&& unq_ptr_obj) = 0;
    
    // для оюьекта возващает 1, для группы считает вложенные объекты 
    virtual size_t GetCountObjects() const = 0;
    
    // перемещает объект/группу
    virtual void MoveObject(int xOffset, int yOffset) = 0;

    // перегрузка для примитивного объекта выбрасывает исключение
    virtual std::vector<std::unique_ptr<Object>>& GetGroup() = 0;
    virtual const std::vector<std::unique_ptr<Object>>& GetGroup() const = 0;
};

// ------------------------ паттерн Composite ------------------- 

// ------------------------- одиночный объект ------------------
class PrimitiveObject : public Object 
{
public:
    PrimitiveObject(const Rect& r);

    bool IsGropuObject() const;

    void AddObject(std::unique_ptr<Object>&& unq_ptr_obj) override;

    const Rect& GetSize() const override;

    void MoveObject(int xOffset, int yOffset) override;

    size_t GetCountObjects() const override;

    std::vector<std::unique_ptr<Object>>& GetGroup() override;

    const std::vector<std::unique_ptr<Object>>& GetGroup() const override;
private:
    Rect rect;
};

// ------------------------- групповой объект ------------------
class GroupObject : public Object
{
public:
    bool IsGropuObject() const;

    void AddObject(std::unique_ptr<Object>&& unq_ptr_obj) override;

    const Rect& GetSize() const override;

    void MoveObject(int xOffset, int yOffset) override;

    size_t GetCountObjects() const override;

    std::vector<std::unique_ptr<Object>>& GetGroup() override;

    const std::vector<std::unique_ptr<Object>>& GetGroup() const override;
private:
    std::vector<std::unique_ptr<Object>> group;
    Rect rect;

    // Обновляет описывающий прямоугольник, так чтобы каждый обьект группы стал вложенным в него
    void UpdateRect(const Rect& size);
};