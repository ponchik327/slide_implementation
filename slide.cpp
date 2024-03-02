#include "slide.h"

// -------------------------- реализация Slide -----------------------------

void ImplementationSlide::addRect(const Rect& geometry)
{
    objects.push_back(std::make_unique<PrimitiveObject>(geometry));
}

void ImplementationSlide::group(const std::vector<std::size_t>& indexesToGroup)
{
    // создаём пустой групповой объект  
    std::unique_ptr<Object> group_object = std::make_unique<GroupObject>();
    
    // перемещаем в него обьекта из слайда с нужными индексами
    for (size_t index_object : indexesToGroup)
    {
        group_object->AddObject(std::move(objects[index_object]));
    }

    // помещаем нашу группу на слайд
    // на место, где был последний обьект группы на слайде 
    size_t last_index = indexesToGroup[indexesToGroup.size() - 1];
    objects[last_index].swap(group_object);

    // удаляем свободные места на слайде, где раньше были элементы группы
    for (size_t i = indexesToGroup[0]; i < indexesToGroup.size(); ++i)
    {
        removeObject(i);
    }
}

void ImplementationSlide::ungroup(std::size_t groupIndex)
{
    // для удобства сохраняем ссылку на группу 
    auto& group = objects[groupIndex]->GetGroup();

    // добавляем пустые обьекты на места, где будут находиться объекты разгруппированной группы 
    for (size_t i = 0; i < group.size(); ++i)
    {
        objects.insert(objects.begin() + groupIndex, std::move(std::make_unique<PrimitiveObject>(Rect{})));
    }

    // переносим объекты из группы на слайд
    size_t index = groupIndex;
    for (auto& object : group)
    {
        objects[index++].swap(object);
    }

    // удаляем группированный обьект
    removeObject(groupIndex + group.size());  
}

void ImplementationSlide::removeObject(std::size_t objectIndex)
{
    objects.erase(objects.begin() + objectIndex);
}

void ImplementationSlide::moveObject(std::size_t objectIndex, int xOffset, int yOffset)
{
    objects[objectIndex]->MoveObject(xOffset, yOffset);
}

std::size_t ImplementationSlide::getObjectsCount() const
{
    size_t count_objects = 0;
    for (auto& object : objects)
    {
        if (object)
        {
            count_objects += object->GetCountObjects();
        }
    }
    return count_objects;
}

const Object& ImplementationSlide::getObject(std::size_t objectIndex) const
{
    return *objects.at(objectIndex);
}