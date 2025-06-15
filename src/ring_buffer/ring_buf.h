#ifndef RING_BUF_H
#define RING_BUF_H

#include <vector>

template<typename A> struct ringbuf
{

    //arraysize and data array
    size_t length;
    std::vector<A> data;

    //next writing position
    A* head;
    //next reading position
    A* tail;

    ringbuf(size_t l)
    {
        if(l == 0){
            return;
        }

        length = l;

        //create a vector, reserve enough space and create a inition value for the pointers to point to
        std::vector<A> data{};
        data.resize(l, A{});

        head = &data[0];
        tail = &data[0];
    }


};





#endif