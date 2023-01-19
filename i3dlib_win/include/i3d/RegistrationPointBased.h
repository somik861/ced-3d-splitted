/*
 * i3dlib - image manipulation library
 *
 * Copyright (C) 2000-2006   Centre for Biomedical Image Analysis (CBIA)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/** @file 
    @brief Point-based image registration methods.

    Based on the original code by Petr Matula.

    @author Ondrej Danek (xdanek2@fi.muni.cz)
    @date 2010
*/ 

#ifndef I3D_REGISTRATIONPOINTBASED_H
#define I3D_REGISTRATIONPOINTBASED_H

#include <vector>
#include "algo_export.h"
#include "vector3d.h"

namespace i3d
{
    namespace Registration
    {
        // List of 3d points
        typedef std::vector<Vector3d<double> > PointSet;
        // Matching between two PointSets
        typedef std::vector<std::pair<size_t,size_t> > PointMatching;
        // Transformation matrix
        typedef double PointTransformation[4][4];

        /** Register point sets and find matching points. 
        
            Based on: Petr Matula, Pavel Matula, Michal Kozubek, Vladimir Dvorak. Fast 
                Point-Based 3D Alignment of Live Cells. IEEE Transactions on Image 
                Processing, 15(8), 2388-2396, 2006.
        */
        void I3D_ALGO_EXPORT FindPointMatching(const PointSet &a, const PointSet &b, 
            PointMatching &m, double max_dist = 20.0, double bin_width = 5.0, 
            double scale_eps = 0.1, double zdiff_eps = 5.0);

        /** Compute transformation matrix for given two point sets and matching.

            Solves the Absolute Orientation Problem between given two point sets, 
            i.e. finds a transformation (scale factor, rotation and translation
            vector) of the set \c q minimizing the sum of squared errors.

            Based on the following paper:
            Berthold K.P. Horn: <em>Closed-from solution of absolute orientation 
            using unit quaternions</em>

            @param[in] p First point set.
            @param[in] q Second point set.
            @param[in] m Matching between the point sets.
            @param[out] t Transformation of the set \c q minimizing the sum of 
                squared errors.
        */
        void I3D_ALGO_EXPORT FindPointTransformation(const PointSet &p, const PointSet &q, 
            const PointMatching &m, PointTransformation &t);
    }
}

#endif

