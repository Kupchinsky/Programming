#include "queue.hpp"
#include <iostream>

using namespace std;

#define out(x) cout << x << endl

int main()
{
    Queue *q1 = new Queue();

    for (int i = 0; i < 5; i++)
        q1->add(i);

    for (int i = 0; i < 5; i++)
        out(i << ": " << q1->poll());

    return 0;
}

