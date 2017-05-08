#ifndef __REMOVE_TEMPLATE_
#define __REMOVE_TEMPLATE_

#include <vector>

using namespace std;

template<class T>
void Remove(vector<T*>& elements, T* element) {
    int i = 0;
    for(auto e : elements){
        if(element == e) {
            elements.erase(elements.begin() + i);
            break;
        }
        i++;
    }
}

#endif