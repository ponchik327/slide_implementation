#include <iostream>
#include <memory>
#include <cassert>

#include "slide.h"

using namespace std;

ostream& operator <<(ostream& out, const Rect& r)
{
    out << "(x, y) : (" << r.x << ", " << r.y << ")\n";
    out << "width: " << r.width << '\n';
    out << "height: " << r.height;
    return out;
}

int main()
{
    unique_ptr<Slide> slide = make_unique<ImplementationSlide>(); 
    
    // создали прямоугольники для слайда
    Rect r0{0, 0, 200, 200};
    Rect r1{100, 100, 200, 200};
    Rect r2{150, 50, 200, 200};
    Rect r3{50, 150, 200, 200};
    vector<Rect> vec_rec{r0, r1, r2, r3};

    // добавли на слайд 4 простых объекта
    size_t count_object = 4;
    for (size_t i = 0; i < count_object; ++i)
    {
        slide->addRect(vec_rec[i]);
    }

    // проверили getObjectsCount()
    assert(slide->getObjectsCount() == count_object);

    // сгруппировали 2-ой и 3-ий объекты
    slide->group(vector<size_t>{1, 2}); 

    // проверили, что коректно сработала группировка
    assert(slide->getObject(0).GetSize() == vec_rec[0]);
    assert(slide->getObject(1).GetGroup()[0]->GetSize() == vec_rec[1]);
    assert(slide->getObject(1).GetGroup()[1]->GetSize() == vec_rec[2]);
    assert(slide->getObject(2).GetSize() == vec_rec[3]);

    // проверили, что выбрасывается исключение при обращении к невалидному индексу
    bool exception_appeared = false;
    try {
        cout << slide->getObject(3).GetSize() << endl;
    }
    catch(const std::exception& e)
    {
        exception_appeared = true;
    }
    assert(exception_appeared);

    // проерили, что выбрасывается исключение попытке вызвать GetGroup() у простого объекта
    exception_appeared = false;
    try {
        cout << slide->getObject(3).GetSize() << endl;
    }
    catch(const std::exception& e)
    {
        exception_appeared = true;
    }
    assert(exception_appeared);

    // сдвинули обьект
    size_t offest = 15;
    slide->moveObject(0, offest, offest);

    // проверили, что объект сдвинулся
    assert(slide->getObject(0).GetSize().x == vec_rec[0].x + offest); 
    assert(slide->getObject(0).GetSize().y == vec_rec[0].y + offest);

    // вернули обратно
    slide->moveObject(0, -offest, -offest);

    Rect old_group = slide->getObject(1).GetSize(); 

    // сдвинули группу объектов 
    slide->moveObject(1, offest, offest);

    // проверили, что обькеты, как и сама группа сдвинулись
    assert(slide->getObject(1).GetSize().x == old_group.x + offest); 
    assert(slide->getObject(1).GetSize().y == old_group.y + offest);
    assert(slide->getObject(1).GetGroup()[0]->GetSize().x == vec_rec[1].x + offest);
    assert(slide->getObject(1).GetGroup()[0]->GetSize().y == vec_rec[1].y + offest);

    assert(slide->getObject(1).GetGroup()[1]->GetSize().x == vec_rec[2].x + offest);
    assert(slide->getObject(1).GetGroup()[1]->GetSize().y == vec_rec[2].y + offest);

    // вернули обратно
    slide->moveObject(1, -offest, -offest);

    // разбили группу обратно на 2 объекта
    slide->ungroup(1);

    // проверили, что коректно сработала разгруппировка
    for (size_t i = 0; i < count_object; ++i)
    {
        assert(slide->getObject(i).GetSize() == vec_rec[i]);
    }

    // удалили последний объект со слайда
    count_object -= 1;
    slide->removeObject(3);
    assert(slide->getObjectsCount() == count_object);

    // удалили группированный объект со слайда
    slide->group(vector<size_t>{1,2});
    count_object -= slide->getObject(1).GetCountObjects();
    slide->removeObject(1);
    assert(slide->getObjectsCount() == count_object);

    cout << "All ok!" << endl;
}
