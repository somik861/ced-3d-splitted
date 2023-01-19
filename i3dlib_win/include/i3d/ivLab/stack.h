#ifndef STACK_H
#define STACK_H

#include "basic.h"

namespace ivLab
{
    template<class T>
    class TStack
    {
    private:
        const int MaxSize;
        T* Array;
        int sptr;

    public:
        void Push(const T value) {
#ifdef I3D_DEBUG
            if (sptr >= MaxSize)
            {
                throw i3d::InternalException("ivLab::Stack::Push => overflow");
            }
#endif
            Array[sptr++] = value;
        }
        void Pop(T& reference)  {
#ifdef I3D_DEBUG
            if (sptr <= 0)
            {
                throw i3d::InternalException("ivLab::Stack::Pop => empty stack");
            }
#endif
            reference = Array[--sptr];
        }
        bool IsEmpty() {
            return (sptr == 0);
        }
        void Reset() {
            sptr = 0;
        }

    public:
        TStack(const int Size):MaxSize(Size) {
            Array = new T[MaxSize];
            if(!Array) {
                throw i3d::InternalException("ivLab::Stack::Stack => cannot allocate memory");
            }
            Reset();
        }
        ~TStack() {
            if(Array) {
                delete[] Array;
            }
        }
    };
}

#endif
