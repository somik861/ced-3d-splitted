#ifndef _COLOCALIZATION_
#define _COLOCALIZATION_
#include "image3d.h"
#include "regions.h"
#include <map>

namespace i3d {

template <class VOXEL> 
void Manders(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, 
						   Image3d<GRAY16> &o1, unsigned int threshold=0);
template <class VOXEL> 
void Pearson(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, 
						   Image3d<GRAY16> &o1);
template <class VOXEL> 
void Overlap(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, 
						   Image3d<GRAY16> &o1);
template <class VOXEL> 
double OverlapC(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, const LabeledImage3d<GRAY16, bool> &mask, int label=-1);
template <class VOXEL> 
double MandersC(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, const LabeledImage3d<GRAY16, bool> &mask, int label=-1, unsigned int threshold=0);
template <class VOXEL> 
double PearsonC(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, const LabeledImage3d<GRAY16, bool> &mask, int label=-1);
template <class VOXEL> 
double OverlapC(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2);
template <class VOXEL> 
double MandersC(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, unsigned int threshold=0);
template <class VOXEL> 
double PearsonC(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2);

template <class VOXEL> 
std::map<unsigned short,double> PearsonM(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, const LabeledImage3d<GRAY16, bool> &mask);
template <class VOXEL> 
std::map<unsigned short,double> MandersM(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, const LabeledImage3d<GRAY16, bool> &mask, unsigned int threshold=0);
template <class VOXEL> 
std::map<unsigned short,double> OverlapM(const Image3d<VOXEL> &i1, const Image3d<VOXEL> &i2, const LabeledImage3d<GRAY16, bool> &mask);



};


#endif
