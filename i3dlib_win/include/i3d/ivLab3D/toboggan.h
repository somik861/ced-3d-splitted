#ifndef TOBOGGAN3D_H
#define TOBOGGAN3D_H

namespace ivLab3D 
{
    template<class T>
    int* Toboggan(const T* Gradient, const int Width, const int Height, const int Depth, 
        const bool OrderInvariant, const int Connectivity, const bool DrawLines);
}
#endif
