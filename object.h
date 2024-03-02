#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "common.h"

// ------------------------- интерфейс объекта ------------------- 

class Object
{
public: 
    virtual ~Object() = default;
public:
    virtual const Rect& GetSize() const = 0;
    virtual void AddObject(std::unique_ptr<Object>&& unq_ptr_obj) = 0;
    virtual size_t GetCountObjects() const = 0;
    virtual void MoveObject(int xOffset, int yOffset) = 0;
    virtual std::vector<std::unique_ptr<Object>>& GetGroup() = 0;
    virtual const std::vector<std::unique_ptr<Object>>& GetGroup() const = 0;
};

// ------------------------ паттерн Composite ------------------- 

// ------------------------- одиночный объект ------------------
class PrimitiveObject : public Object 
{
public:
    PrimitiveObject(const Rect& r);

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