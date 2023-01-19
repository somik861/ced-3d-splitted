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
    @brief Basic voxel-based image registration methods.

    @warning This code is BETA and it may change significantly

    @author Ondrej Danek (xdanek2@fi.muni.cz)
    @date 2010
*/ 

#ifndef I3D_REGISTRATION_H
#define I3D_REGISTRATION_H

#include <string>
#include "algo_export.h"
#include "basic.h"
#include "image3d.h"

namespace i3d
{
    namespace Registration
    {
        //////////////////////////////////////////////////////////////////////////
        //
        // AUXILIARY CLASSES
        //
        //////////////////////////////////////////////////////////////////////////

        /** Class describing image transformation. */
        template <class T>
        class Transformation
        {
        public:
            Vector3d<T> m_shift;
        };

        /** Region specification class. */
        class Region
        {
        public:
            /** Top left corner of the region. */
            Vector3d<size_t> m_ofs;
            /** Region size. */
            Vector3d<size_t> m_sz;

            /** Setup the region as intersection of given transformation on given image. */
            template <class T, class VOXEL>
            void SetIntersection (const Image3d<VOXEL> &img, const Transformation<T> &tmin,
                const Transformation<T> &tmax)
            {
                VOI<PIXELS> v1(Vector3d<PIXELS::T_offset> (tmin.m_shift), img.GetSize());
                VOI<PIXELS> v2(Vector3d<PIXELS::T_offset> (tmax.m_shift), img.GetSize());
                VOI<PIXELS> v3(Vector3d<PIXELS::T_offset> (0), img.GetSize());

                v1 *= v2;
                v1 *= v3;

                m_ofs = Vector3d<size_t> (v1.offset);
                m_sz = v1.size;
            }
        };

        //////////////////////////////////////////////////////////////////////////
        //
        // SIMILARITY METRICS
        //
        //////////////////////////////////////////////////////////////////////////

        /** Generic similarity metric class interface.
            Implementations of this class measure how much two images are similar.
        */
        template <class T, class VOXEL>
        class ISimilarityMetric
        {
        protected:
            /** Reference image. */
            const Image3d<VOXEL> &m_ref_img;
            /** Region specification. */
            Region m_region;

        public:
            /** Constructor.

                @param[in] ref_img The reference image.
                @param[in] region Specification of the region in which the similarity function will
                    be computed. The region should be a subset of intersection of all possible 
                    transformations of the second registered image.
                */
            ISimilarityMetric(const Image3d<VOXEL> &ref_img, const Region &region);

            /** Virtual destructor. */
            virtual ~ISimilarityMetric()
            {}

            /** Compute the similarity between the given image and the reference image.

                @param[in] img Input image to be registered with the reference image (already transformed).
                @param[in] shift Additional integral shift of the input image. Compensating integral 
                    shift is extremely easy, so this parameter can be used to speed up the registration, 
                    because the minimizing method doesn't have to transform the input image itself when 
                    trying different integral shifts.
                @return Value of the similarity metric.
                */
            virtual T Compute(const Image3d<VOXEL> &img, const Vector3d<int> &shift) = 0;

            /** Get the name of the similarity metric. */
            virtual std::string GetName() const = 0;
        };

        /** Generic similarity metric based on mutual information. */
        template <class T, class VOXEL>
        class I3D_ALGO_EXPORT IGenericMutualInformation 
            : public ISimilarityMetric<T,VOXEL>
        {
        protected:
            /** Number of intensity levels present in the images. */
            size_t m_levels;
            /** Histograms. */
            size_t *m_hist_im, *m_hist_joint;
            /** Precalculated entropy of the reference image. */
            T m_Hx;

            using ISimilarityMetric<T,VOXEL>::m_ref_img;
            using ISimilarityMetric<T,VOXEL>::m_region;

        public:
            /** Constructor. 
            
                @param[in] ref_img Reference image.
                @param[in] region Specification of the region in which the similarity metric will
                    be computed. The region should be a subset of intersection of all possible 
                    transformations of the second registered image.
                @param[in] levels Number of intensity levels present in the registered images.
                    This parameter greatly influences the speed of the computation!
            */
            IGenericMutualInformation (const Image3d<VOXEL> &ref_img, const Region &region, 
                size_t levels = std::numeric_limits<VOXEL>::max());

            /** Destructor. */
            virtual ~IGenericMutualInformation()
            {
                delete m_hist_im;
                delete m_hist_joint;
            }

            T Compute(const Image3d<VOXEL> &img, const Vector3d<int> &shift);

        protected:
            /** Calculate the marginal entropy of given image. */
            T MarginalEntropy (const Image3d<VOXEL> &img, const Vector3d<size_t> &ofs);

            /** Calculate the entropy of given histogram. 
            
                @param[in] hist Histogram.
                @param[in] levels Size of the histogram.
                @return Entropy.
            */
            virtual T Entropy(size_t *hist, size_t levels) const = 0;
        };

        /** Mutual information similarity metric. */
        template <class T, class VOXEL>
        class I3D_ALGO_EXPORT MutualInformation 
            : public IGenericMutualInformation<T,VOXEL>
        {
        protected:
            using IGenericMutualInformation<T,VOXEL>::m_ref_img;
            using IGenericMutualInformation<T,VOXEL>::m_region;
            using IGenericMutualInformation<T,VOXEL>::m_hist_im;
            using IGenericMutualInformation<T,VOXEL>::m_hist_joint;
            using IGenericMutualInformation<T,VOXEL>::m_Hx;

        public:
            /** Constructor. 
            
                @param[in] ref_img Reference image.
                @param[in] region Specification of the region in which the similarity metric will
                    be computed. The region should be a subset of intersection of all possible 
                    transformations of the second registered image.
                @param[in] levels Number of intensity levels present in the registered images.
                    This parameter greatly influences the speed of the computation!
            */
            MutualInformation (const Image3d<VOXEL> &ref_img, const Region &region, 
                size_t levels = std::numeric_limits<VOXEL>::max())
                : IGenericMutualInformation<T,VOXEL>(ref_img, region, levels)
            {
                m_Hx = this -> MarginalEntropy(m_ref_img, m_region.m_ofs);
            }

            virtual std::string GetName() const
            {
                return std::string("Mutual information");
            }

        protected:
            /** Calculate the Shannon entropy of given histogram. 
            
                @param[in] hist Histogram.
                @param[in] levels Size of the histogram.
                @return Shannon entropy.
            */
            T Entropy(size_t *hist, size_t levels) const;
        };

        /** Generalized mutual information similarity metric. */
        template <class T, class VOXEL>
        class I3D_ALGO_EXPORT GeneralizedMutualInformation 
            : public IGenericMutualInformation<T,VOXEL>
        {
        protected:
            using IGenericMutualInformation<T,VOXEL>::m_ref_img;
            using IGenericMutualInformation<T,VOXEL>::m_region;
            using IGenericMutualInformation<T,VOXEL>::m_hist_im;
            using IGenericMutualInformation<T,VOXEL>::m_hist_joint;
            using IGenericMutualInformation<T,VOXEL>::m_Hx;

        public:
            /** Constructor. 
            
                @param[in] ref_img Reference image.
                @param[in] region Specification of the region in which the similarity metric will
                    be computed. The region should be a subset of intersection of all possible 
                    transformations of the second registered image.
                @param[in] levels Maximal intensity that is present in the registered images.
                    This parameter greatly influences the speed of the computation!
            */
            GeneralizedMutualInformation (const Image3d<VOXEL> &ref_img, const Region &region, 
                size_t levels = std::numeric_limits<VOXEL>::max())
                : IGenericMutualInformation<T,VOXEL>(ref_img, region, levels)
            {
                m_Hx = this -> MarginalEntropy(m_ref_img, m_region.m_ofs);
            }

            virtual std::string GetName() const
            {
                return std::string("Generalized mutual information");
            }

        protected:
            /** Calculate the second-order Renyi entropy of given histogram. 
            
                @param[in] hist Histogram.
                @param[in] levels Size of the histogram.
                @return Renyi entropy.
            */
            T Entropy(size_t *hist, size_t levels) const;
        };

        /** Normalized cross-correlation (NCC) similarity metric. */
        template <class T, class VOXEL>
        class NormalizedCorrelation
            : public ISimilarityMetric<T,VOXEL>
        {
        protected:
            using ISimilarityMetric<T,VOXEL>::m_ref_img;
            using ISimilarityMetric<T,VOXEL>::m_region;

        private:
            /** Mean value of the reference image. */
            T m_ref_mean;

        public:
            /** Constructor.

                @param[in] ref_img The reference image.
                @param[in] region Specification of the region in which the similarity metric will
                    be computed. The region should be a subset of intersection of all possible 
                    transformations of the second registered image.
                */
            NormalizedCorrelation(const Image3d<VOXEL> &ref_img, const Region &region);

            virtual T Compute(const Image3d<VOXEL> &img, const Vector3d<int> &shift);

            /** Get the name of the similarity metric. */
            virtual std::string GetName() const
            {
                return std::string("Normalized cross-correlation.");
            }

        protected:
            T GetMeanValue(const Image3d<VOXEL> &im, const Vector3d<size_t> &ofs);
        };

        //////////////////////////////////////////////////////////////////////////
        //
        // MINIMIZATION ALGORITHMS
        //
        //////////////////////////////////////////////////////////////////////////

        /** Generic function minimization class interface. */
        template <class T, class VOXEL>
        class IFuncMinimizer
        {
            public:
	        /** Virtual destructor. */
	        virtual ~IFuncMinimizer()
	        {}
	    
            /** Find best registration using given similarity metric and space of 
                possible transformations.

                @param[in] img Image to be registered.
                @param[in] sim Similarity metric (contains the reference image).
                @param[in] tmin Specification of the space of transformations.
                @param[in] tmax Specification of the space of transformations.
                @param[out] opt Optimal registration found.
            */
            virtual void Minimize(const Image3d<VOXEL> &img, ISimilarityMetric<T,VOXEL> &sim,
                const Transformation<T> &tmin, const Transformation<T> &tmax, 
                Transformation<T> &opt) = 0;
        };

        /** Brute force/exhaustive search minimization method. */
        template <class T, class VOXEL>
        class I3D_ALGO_EXPORT BruteForceSearch
            : public IFuncMinimizer<T,VOXEL>
        {
        protected:
            /** Search step size. */
            Transformation<T> m_step;

        public:
            /** Constructor. */
            BruteForceSearch()
            {
                m_step.m_shift = Vector3d<T>(1,1,1);
            }

            virtual void Minimize(const Image3d<VOXEL> &img, ISimilarityMetric<T,VOXEL> &sim,
                const Transformation<T> &tmin, const Transformation<T> &tmax, 
                Transformation<T> &opt);

            /** Set the step size of the full search algorithm. */
            void SetStep(const Transformation<T> &tstep)
            {
                m_step = tstep;
            }

            /** Get the step size of the full search algorithm. */
            Transformation<T> GetStep() const
            {
                return m_step;
            }
        };

        /** @todo doc, zacina vzdy uprostred intervalu         
            @todo Zatim to neni pravy gradient descent, ale mozna jednou bude :)
        */
        template <class T, class VOXEL>
        class I3D_ALGO_EXPORT GradientDescent
            : public IFuncMinimizer<T,VOXEL>
        {
        public:
            virtual void Minimize(const Image3d<VOXEL> &img, ISimilarityMetric<T,VOXEL> &sim,
                const Transformation<T> &tmin, const Transformation<T> &tmax, 
                Transformation<T> &opt);
        };
    }
}

#endif

