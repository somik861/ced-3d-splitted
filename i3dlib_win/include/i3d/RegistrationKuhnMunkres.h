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
    @brief Kuhn-Munkres Algorithm

    (H. W. Kuhn, The Hungarian method for the assignment problem,
    Naval Research Logistics Quarterly, 2 (1955), pp. 83-97. )

    Based on description available from:
    http://www.math.uwo.ca/~mdawes/courses/344/kuhn-munkres.pdf

    @author Petr Matula (pem@fi.muni.cz)
    @author Ondrej Danek (xdanek2@fi.muni.cz)
    @date 2010
*/ 

#ifndef I3D_REGISTRATIONKUHNMUNKRES_H
#define I3D_REGISTRATIONKUHNMUNKRES_H

#include <vector>
#include <stdlib.h>
#include "algo_export.h"

namespace i3d
{
    namespace Registration
    {
        /** Find solution to optimal assignment problem using the Kuhn-Munkres algorithm.
    
            @param[in] n Size of the problem, i.e. the number of rows of the weight matrix.
            @param[in] weights Weight matrix of size <i>n x n</i> stored in a row major continuous array.
            @param[out] Optimal assignment. Res[i] is the vertex assigned to the vertex i in 
                the optimal matching.

            @tparam DT Data type of the weights.
        */
        template <class DT>
        void I3D_ALGO_EXPORT KuhnMunkres(size_t n, const std::vector<DT> &weights, std::vector<size_t> &res);
    }
}

#endif
