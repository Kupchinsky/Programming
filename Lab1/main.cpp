#include "list.hpp"
#include <iostream>

using namespace std;

#define out(x) cout << x << endl

int main()
{
    List<int> *test1 = new List<int>(), *test2 = new List<int>();

    /* Test 1: [1 - 10] */
    out("::test1::" << endl);

    for (int i = 0; i < 5; i++)
        test1->pushLast(i + 1); // pushFirst

    for (int i = 5; i < 10; i++)
        test1->pushLast(i + 1);

    test1->print(&cout);
    out(endl << "test1 size: " << test1->calculateSize() << ", recursive size: " << test1->calculateSizeRecursive());
    /* End */

#define bla2
#ifdef bla2
    /* Test 2: [120 - 100] */
    out(endl << "::test2::" << endl);

    for (int i = 10; i < 40; i++)
        test2->pushFirst(i + 1); //pushFirst

    test2->print(&cout);
    out(endl << "test2 size: " << test2->calculateSize() << ", recursive size: " << test2->calculateSizeRecursive());
    /* End */
#endif

//#define bla
#ifdef bla
    /* Работа с test1 */
    /* Здесь должен удалиться последний элемент 10, размер уменьшиться на 1 */
    test1->deleteMostGreaterNode();

    /* Здесь должен удалиться последний элемент 9, размер уменьшиться на 1 */
    test1->deleteLast();

    /* Здесь должен удалиться первый элемент 5, размер уменьшиться на 1 */
    test1->deleteFirst();

    /* Здесь должен добавиться элемент 99 в конец, размер увеличиться на 1 */
    test1->pushLast(99);

    out(endl << "::test1 after::" << endl);

    test1->print(&cout);
    out(endl << "test1 size: " << test1->calculateSize() << ", recursive size: " << test1->calculateSizeRecursive());
    /* End */
#endif

#define bla3
#ifdef bla3
    /* Работа с test1, test2 */
    List<int> *test3 = test1->mergeLists(test2);

    out(endl << "::test3::" << endl);

    test3->print(&cout);
    out(endl << "test3 size: " << test3->calculateSize() << ", recursive size: " << test3->calculateSizeRecursive());
    /* End */

    //delete test3;
#endif

    delete test1;
    delete test2;

    out("Bye.");

    return 0;
}

