#include "object.h"

// -------------------------- реализация PrimitiveObject -----------------------------
PrimitiveObject::PrimitiveObject(const Rect& r)
    : rect(r)
{}

bool PrimitiveObject::IsGropuObject() const
{
    return false;
}

void PrimitiveObject::AddObject(std::unique_ptr<Object>&& unq_ptr_obj)
{
    throw std::runtime_error("Incorrect use AddObject()");
}

const Rect& PrimitiveObject::GetSize() const
{
    return rect;
} 

void PrimitiveObject::MoveObject(int xOffset, int yOffset)
{
    rect.x += xOffset;
    rect.y += yOffset;
}

size_t PrimitiveObject::GetCountObjects() const
{
    return 1;
}

std::vector<std::unique_ptr<Object>>& PrimitiveObject::GetGroup()
{
    throw std::runtime_error("Is primitive object");
}

const std::vector<std::unique_ptr<Object>>& PrimitiveObject::GetGroup() const
{
    throw std::runtime_error("Is primitive object");
}

// -------------------------- реализация GroupObject -----------------------------
bool GroupObject::IsGropuObject() const
{
    return true;
}

void GroupObject::AddObject(std::unique_ptr<Object>&& unq_ptr_obj)
{
    UpdateRect(unq_ptr_obj->GetSize());
    group.push_back(std::move(unq_ptr_obj));
}

const Rect& GroupObject::GetSize() const
{
    if (group.empty())
    {
        throw std::runtime_error("GroupObject is empty");
    }
    return rect;
}

void GroupObject::MoveObject(int xOffset, int yOffset)
{
    for (auto& object : group)
    {
        object->MoveObject(xOffset, yOffset);
    }
    rect.x += xOffset;
    rect.y += yOffset;
}

size_t GroupObject::GetCountObjects() const
{
    return group.size();
}

std::vector<std::unique_ptr<Object>>& GroupObject::GetGroup()
{
    return group;
}

const std::vector<std::unique_ptr<Object>>& GroupObject::GetGroup() const
{
    return group;
}

// ----------- приватный метод -------------
void GroupObject::UpdateRect(const Rect& size)
{
    if (group.empty())
    {
        rect = size;
    }
    else
    {
        if (!rect.IsFeatsInside(size))
        {
            rect.ResizeToBigger(size);
        }
    }
}