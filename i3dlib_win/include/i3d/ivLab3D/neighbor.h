#ifndef NEIGHBOR3D_H
#define NEIGHBOR3D_H

#include "basic.h"

namespace ivLab3D 
{
    template<int Connectivity>
    class TNeighbor
    {
    private:
        int Offset[Connectivity];
        int Index;

    public:
        TNeighbor(const int xOffset, const int yOffset, const int zOffset) {
            // the order of offsets is important for iterating in forward and backward neighborhoods. Forward pixels are the first	
            // we asume that xOffset < yOffset and xOffset * yOffset < zOffset
            switch(Connectivity) { 
            case 4:
                Offset[0] = xOffset;
                Offset[1] = yOffset;
                Offset[2] = - xOffset;
                Offset[3] = - yOffset;
                break;
            case 8:
                Offset[0] = xOffset;
                Offset[1] = xOffset + yOffset;
                Offset[2] = yOffset;
                Offset[3] = - xOffset + yOffset;
                Offset[4] = - xOffset;
                Offset[5] = - xOffset - yOffset;
                Offset[6] = - yOffset;
                Offset[7] = xOffset - yOffset;
                break;
                /** Tento kod jsem pridal */ 
            case 6: 
                Offset[0] = xOffset;
                Offset[1] = yOffset;
                Offset[2] = zOffset;
                Offset[3] = - xOffset;
                Offset[4] = - yOffset;
                Offset[5] = - zOffset;
                break;
            case 18:
                Offset[0]  = xOffset;
                Offset[1]  = xOffset + yOffset;
                Offset[2]  = yOffset;
                Offset[3]  = - xOffset + yOffset;
                Offset[4]  = zOffset;
                Offset[5]  = zOffset + xOffset;
                Offset[6] = zOffset + yOffset;
                Offset[7] = zOffset - xOffset;
                Offset[8] = zOffset - yOffset;
                Offset[9]  = - xOffset;
                Offset[10]  = - xOffset - yOffset;
                Offset[11]  = - yOffset;
                Offset[12]  = xOffset - yOffset;
                Offset[13] = - zOffset;
                Offset[14] = - zOffset + xOffset;
                Offset[15] = - zOffset + yOffset;
                Offset[16] = - zOffset - xOffset;
                Offset[17] = - zOffset - yOffset;
                break;
            case 26:
                Offset[0]  = xOffset;
                Offset[1]  = xOffset + yOffset;
                Offset[2]  = yOffset;
                Offset[3]  = - xOffset + yOffset;
                Offset[4]  = zOffset;
                Offset[5]  = zOffset + xOffset;
                Offset[6] = zOffset + xOffset + yOffset;
                Offset[7] = zOffset + yOffset;
                Offset[8] = zOffset - xOffset + yOffset;
                Offset[9] = zOffset - xOffset;
                Offset[10] = zOffset - xOffset - yOffset;
                Offset[11] = zOffset - yOffset;
                Offset[12] = zOffset + xOffset - yOffset;
                Offset[13]  = - xOffset;
                Offset[14]  = - xOffset - yOffset;
                Offset[15]  = - yOffset;
                Offset[16]  = xOffset - yOffset;
                Offset[17] = -zOffset;
                Offset[18] = -zOffset + xOffset;
                Offset[19] = -zOffset + xOffset + yOffset;
                Offset[20] = -zOffset + yOffset;
                Offset[21] = -zOffset - xOffset + yOffset;
                Offset[22] = -zOffset - xOffset;
                Offset[23] = -zOffset - xOffset - yOffset;
                Offset[24] = -zOffset - yOffset;
                Offset[25] = -zOffset + xOffset - yOffset;
                break;
            default:
                throw i3d::InternalException("Neighbor::Neighbor => invalid value of the connectivity");
            }
        }
        void Begin() {
            Index = 0;
        }
        bool End() {
            return Index >= Connectivity;
        }
        void BeginForward() {
            Index = 0;
        }
        bool EndForward() {
            return Index >= Connectivity/2;
        }
        void Next() {
            Index++;
        }
        int Where(const int Center) {
            return Center + Offset[Index];
        }
        int Where(const int Center, const int JumpIndex) {
            return Center + Offset[JumpIndex];
        }
        int Backtrack(const int Where) {
            return Where - Offset[Index];
        }
        int Backtrack(const int Where, const int JumpIndex) {
            return  Where - Offset[JumpIndex];
        }
        int Direction() {
            return Index;
        }
    };
}

#endif
