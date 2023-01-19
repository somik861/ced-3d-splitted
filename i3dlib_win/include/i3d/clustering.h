/*
 * clustering.h
 *
 * k-means clustering.
 *
 * Pavel Matula (pam@fi.muni.cz) 2007
 */

#ifndef __CLUSTERING_H__
#define __CLUSTERING_H__

#include "basic.h"
#include "image3d.h"

namespace i3d {
	
	/** Supported methods for cluster initialization */
	enum InitClusterMethod {
		ClusterRandom,			///< assign pixels to clusters randomly
		ClusterEqualMass,		///< create clusters with equal mass and similar intensity
		ClusterAlternating,		///< pixels are assigned to clusters alternately (their position modulo k)
		ClusterMask,			///< output image is taken as initial partioning
		ClusterMultilevelOtsu	///< pixels are clustered according to multilevel Otsu method.
	};
/**
	\brief Segmentation using k-Mean clustering

		Partitions the image into k segments so that the variance of pixel intensity in each cluster is minimised.
		Clusters may be disconnected. Global optimum is not guaranteed because Lloyd's iterative algorithm is used.
		\param img          input image
		\param imgout		output image
		\param k			number of clusters required
		\param method		method used for initial partioning
		\param max_iters    maximal number of iterations allowed
		\param means        where to store means of clusters (if means = NULL then they are not returned)

		\returns true if max_iters is not reached (i.e. the process has converged) and false otherwise

		ClusterRandom ........ pixels are assignet to clusters randomly
		ClusterEqualMass ..... histogram of the input image is computed and then the pixels are divided 
								into segments with equal mass. This method is not implemented for float images.
		ClusterAlternating ... pixel membership to clusters is alternating as one go through the image buffer
		ClusterMask	.......... imgout is taken as the initial partioning. All pixels must have values 0, 1, ..., k - 1
*/
	template <class VOXEL> I3D_ALGO_EXPORT bool kMeans(const Image3d<VOXEL> &img, Image3d<GRAY8> &imgout, GRAY8 k, InitClusterMethod method, int max_iters = 50, std::vector<float> *means = NULL);
}

#endif
