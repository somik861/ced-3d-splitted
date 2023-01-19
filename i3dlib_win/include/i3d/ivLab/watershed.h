#ifndef WATERSHED_H
#define WATERSHED_H

namespace ivLab
{
    template<class T>
    int* Watershed(const T* Gradient, const int Width, const int Height, const bool OrderInvariant, const int Connectivity);
}

#endif
