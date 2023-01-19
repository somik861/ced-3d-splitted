/*
 * thinning.h
 *
 * Interface to thinning function
 *
 * Marek Vinkler (xvinkl@mail.muni.cz) 2010
 * 
 */

#ifndef __THINNING_H__
#define __THINNING_H__

#include "image3d.h"
#include "algo_export.h"
#include <list>

namespace i3d
{
	void CreateLUT(std::vector<bool> &table);
	size_t IndexUD(const Image3d<unsigned char> &img, const Vector3d<size_t> &point);
	size_t IndexNS(const Image3d<unsigned char> &img, const Vector3d<size_t> &point);
	size_t IndexEW(const Image3d<unsigned char> &img, const Vector3d<size_t> &point);
	bool IsBorderPoint(const Image3d<unsigned char> &img, const Vector3d<size_t> &point);
	bool IsDeletable(const Image3d<unsigned char> &img, const Vector3d<size_t> &point,
		const std::vector<bool> &table);
	size_t ThinningIter(std::list<Vector3d<size_t> > &border, Image3d<unsigned char> &img,
		const std::vector<bool> &table);

	/**A 3D fully parallel surface-thinning algorithm by Kálmán Palágyi*/
	void I3D_ALGO_EXPORT Thinning(Image3d<bool> &img);

} // namespace i3d

#endif // __THINNING_H__

