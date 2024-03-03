#pragma once

#include <utility>
#include <iostream>

struct Rect
{
    // в моей реализации x, y это координаты верхнего левого угла угла прямоугольника
    // координата (0, 0) находится, также в верхнем левом углу
    // ось X направлена влево, ось Y направлена вниз 
    int x;
    int y;
    // ширина и высота фигуры отсчитываются по направлению осей X, Y от точки (x, y) 
    int width;
    int height;
 
    // Проверяет содержиться ли переданный прямоугольник в текущем
    bool IsFeatsInside(const Rect& other)
    {
        return (other.x >= x) && (other.x + other.width <= x + width)
            && (other.y >= y) && (other.y + other.height <= y + height); 
    }

    // Расширеяет текущий прямоугольник до размеров, таких, что переданный становиться вложенным в текущий
    void ResizeToBigger(const Rect& other)
    {
        SetMaxWidth(other);
        SetMaxHeight(other);
        x = std::min(x, other.x);
        y = std::min(y, other.y);
    }

    // перегрузили для проверки
    bool operator ==(const Rect& other) const
    {
        return (other.height == height)  
            && (other.width == width)
            && (other.x == x)
            && (other.y == y);
    }
private:
    // Устанавливает для текущего прямоугольника наибольший размер ширины 
    void SetMaxWidth(const Rect& other)
    {
        int abs_x = x + width;
        int abs_other_x = other.x + other.width;
        width = FindMax(abs_x, abs_other_x, width, other.width, std::min(x, other.x));
    }

    // Устанавливает для текущего прямоугольника наибольший размер высоты
    void SetMaxHeight(const Rect& other)
    {
        int abs_y = y + height;
        int abs_other_y = other.y + other.height;
        height = FindMax(abs_y, abs_other_y, height, other.height, std::min(y, other.y));
    }

    // Вспомогательная функция для посика размеров 
    int FindMax(int abs, int abs_other,
                int length, int length_other,
                int offset)
    {
        if (abs > abs_other) 
        {
            return abs - offset;
        }
        else if (abs < abs_other)
        {
            return abs_other - offset;    
        }
        else {
            return std::max(length, length_other);
        }
    }
};
