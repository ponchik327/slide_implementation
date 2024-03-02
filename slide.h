#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "common.h"
#include "object.h"

class Slide
{
public:
    Slide() = default;
    virtual ~Slide() = default;
public:
    virtual void addRect(const Rect& geometry) = 0;

    virtual void group(const std::vector<std::size_t>& indexesToGroup) = 0;
    virtual void ungroup(std::size_t groupIndex) = 0;

    virtual void removeObject(std::size_t objectIndex) = 0;

    virtual void moveObject(std::size_t objectIndex, int xOffset, int yOffset) = 0;

    virtual std::size_t getObjectsCount() const = 0;
    virtual const Object& getObject(std::size_t objectIndex) const = 0;
};

// ---------------- реализация интерфейса Slide --------------------------
class ImplementationSlide : public Slide
{
public:
    void addRect(const Rect& geometry) override;

    void group(const std::vector<std::size_t>& indexesToGroup) override;
    void ungroup(std::size_t groupIndex) override;

    void removeObject(std::size_t objectIndex) override;

    void moveObject(std::size_t objectIndex, int xOffset, int yOffset) override;

    std::size_t getObjectsCount() const override;
    const Object& getObject(std::size_t objectIndex) const override;
private:
    std::vector<std::unique_ptr<Object>> objects;
};
