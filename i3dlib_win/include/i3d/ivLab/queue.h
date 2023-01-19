#ifndef QUEUE_H
#define QUEUE_H

#include "basic.h"

namespace ivLab
{
    template<class T>
    class TQueue
    {
    private:
        const int MaxSize;
        T* Array;
        int head, tail;

    public:
        void In(const T value) {
#ifdef I3D_DEBUG
            if (tail >= MaxSize)
            {
                throw i3d::InternalException("ivLab::Queue::In => overflow");
            }
#endif
            Array[tail++] = value;
        }
        void Out(T& reference)  {
#ifdef I3D_DEBUG
            if (head >= tail)
            {
                throw i3d::InternalException("ivLab::Queue::Out => empty queue");
            }
#endif
            reference = Array[head++];
        }
        bool IsEmpty() {
            return (head >= tail);
        }
        void Reset() {
            head = tail = 0;
        }

    public:
        TQueue(const int Size):MaxSize(Size) {
            Array = new T[MaxSize];
            if(!Array) {
                throw i3d::InternalException("ivLab::Queue::Queue => cannot allocate memory");
            }
            Reset();
        }
        ~TQueue() {
            if(Array) {
                delete[] Array;
            }
        }
    };
}

#endif
