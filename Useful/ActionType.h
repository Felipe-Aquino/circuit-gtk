#ifndef __ACTION_TYPE_H_
#define __ACTION_TYPE_H_

    #include <iostream>
    #include <string>
    
    using namespace std;

    class ActionType {
    public:
        virtual void Action(string) = 0;
        virtual ~ActionType(){};
    };

#endif

