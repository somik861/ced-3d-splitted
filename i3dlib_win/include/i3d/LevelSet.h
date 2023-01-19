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

/*
 * FILE : LevelSet.h
 *
 * Jan Hubeny <xhubeny@fi.muni.cz> 2005
 *
 */

#ifndef __LEVELSET_H__
#define __LEVELSET_H__

/** \defgroup if Image preprocessing filters */
/** \defgroup sm PDE based image segmentation methods */

#define MINDIVIDER 1e-06

#ifdef __GNUG__
#pragma interface "LevelSet.h"
#endif

/* STL includes */
#include <limits>
#ifndef _MSC_VER
#include <cmath>
#endif
#include <valarray>
#include <vector>
#include "basic.h"
#include "image3d.h"
#include "filters.h"
#include "edge.h"
#include "points.h"

#define ORIGINALPM 0
#define ALTERNATIVEPM 1
#define TUKEY 2
/* Forward declarations */
class LSNeighbourhood;

namespace i3d{
/** \ingroup sm
  in this vector type  are stored Vector3d points, which can be used as the 
  */
typedef std::vector< i3d::Vector3d<size_t> > SeedPointsVector;

/** \ingroup sm
  \brief Computes the speed of the moving interface on whole input image.
  
  This function computes the standard Speed function  
  \f[ F = \frac{1}{1 + |\nabla G_{\sigma} I | } \f]
  which is used to as a driving force to deform the moving boundary with Fast Marching or Level Set methods. The values of 
  the speed are in the <0,1> interval. The greater the gradient is the slower the moving of the interface is.
  
  The parameters are:
  \arg \c Image3d<VOXELIN>& \c ImgIn - reference to input image from which is the Speed computed.
  \arg \c Image3d<VOXELOUT>& \c SpeedImg - reference to output image. In this image is the computed speed saved.
  \arg \c double \c sigmax, \c sigmay, \c sigmaz, \c width - parameters of the gaussian filter.
  
  This Function should be used in collaboration with i3d::FastMarchingMethod function. 
  \image html df1.gif "Speed of the interface is dependent on the gradient magnitude"

  The implementation of this function is based on chapter 8 from the book <br>
  J. A. Sethian, <em> Level Set Methods and Fast Marching Methods </em>, Cambridge University Press 1999.

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005  */
template <class VOXELIN, class VOXELOUT> I3D_ALGO_EXPORT void SpeedFunctionStandard(Image3d<VOXELIN>& ImgIn, Image3d<VOXELOUT>& SpeedImg, double sigmax = 1.2, double sigmay = 1.2, double sigmaz = 1.2, double width = 1.5);


/** \ingroup sm
  \brief Computes the speed of the moving interface on whole input image.

  This function computes the standard Speed function  
  \f[ F = e^{-\alpha (|G_{\sigma}I|)} \f]
  which is used to as a driving force to deform the moving boundary with Fast Marching or Level Set methods. The values of 
  the speed are in the <0,1> interval. The greater the gradient is the slower the moving of the interface is.
  
  The parameters are:
  \arg \c Image3d<VOXELIN>& \c ImgIn - reference to input image from which is the Speed computed.
  \arg \c Image3d<VOXELOUT>& \c SpeedImg - reference to output image. In this image is the computed speed saved.
  \arg \c double \c sigmax, \c sigmay, \c sigmaz, \c width - parameters of the gaussian filter.
  \arg \c double \c alpha  the steepness of stopping. Default value is 0.02. Meaningfull values are between 0.001 and 0.06.
  
  This Function should be used in collaboration with i3d::FastMarchingMethod function. 
  \image html df2.gif "Speed of the interface is dependent on the gradient magnitude"

  The implementation of this function is based on chapter 8 from the book <br>
  J. A. Sethian, <em> Level Set Methods and Fast Marching Methods </em>, Cambridge University Press 1999.


  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
  */

template <class VOXELIN, class VOXELOUT> void SpeedFunctionExponential (Image3d<VOXELIN>& ImgIn,Image3d<VOXELOUT> & SpeedImg,double sigmax = 1.0, double sigmay= 1.0, double sigmaz= 1.0, double width= 1.5,double alpha = 0.02);


/** \ingroup sm
 \brief  This function computes Fast Marching method, which can be used for image segmentation. 
 
 The Fast marching solves following eikonal equation
 \f[
 F|\nabla T| = 1,
 \f]
 where <em>F</em> is the speed function of the interface, <em>T</em> is the time of arrival of the moving interface and \f$ \{ (x,y,z) | T(x,y,z) = 0\}\f$ 
 is the initial interface. This equation describes evolving of such interface in time.
 
  The input parameters of the method are: 
  \arg \c i3d::Image3d<VOXELIN>& \c SpeedImg - typically float 2D or 3D image (the SpeedImg is computed from input GRAY8 image by function i3d::SpeedFunctionStandard defined above), which is then used to compute arrival times of the wave in Fast Marching method. This image should not be empty. 
  \arg \c  SeedPointsVector& \c SeedPoints  - reference to \c std::vector of \c i3d::Vector3d type in which are saved the seeds for the fast marching method (the starting points of the wave). The should be at least one seed in the vector.
  
  \arg  \c i3d::Image3d<VOXELOUT>& \c ImgOut - the only output parameter is reference to ImgOut (for now the VOXELOUT template can be float only). In this image are saved the arrival times of the wave (evolving boundary) computed by Fast Marching method from the input parameters.
 
  The implementation of this function is based on chapter 8 from the book <br>
  J. A. Sethian, <em> Level Set Methods and Fast Marching Methods </em>, Cambridge University Press 1999.

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005

 */
template <class VOXELIN, class VOXELOUT> I3D_ALGO_EXPORT void FastMarchingMethod (i3d::Image3d<VOXELIN> & SpeedImg, i3d::Image3d<VOXELOUT> & ImgOut, SeedPointsVector & SeedPoints);



/** \ingroup sm
  \brief Computes the right arrival time of the moving contour. This value should correct separate the image to interior and exterior region.
  
  This function compute the value of the time on which lies the assumed iso contour line. I.E. when is the fast marching method used to segmentation of 2D image, this function returns in the value parameter the value of the time on which lies the boundary between the interior (the goal of segmentation) and exterior (the rest of the image). 

  For the user, who is not deep informated about FM method, there are only 2 parameters:
  
  \arg \c Image3d<VOXEL>& \c Img - input image (this should be the output of i3d::FastMarchingMethod -- Arrival times) Img.
  \arg \c VOXEL& \c value - variable, in which is saved the result.
  
  Advanced user can modify the other implicit parameters. The brief description of the computing procedure follows.<br>
  1) First we make a histogram from the input arrival times image.<br>
        This histogram has the \c size_t \c Bins number of bins and the step between bins is equal to \c size_t \c Step. i.e. when we have the arrival times image \c Img with values between 0-577.8 the implicit parameters of the procedure \c Bins = 100 \c Step = 1, denotes that we compute histogram with 100 bins with step equal to one, so only the values between 0 - 99 from the input image are saved in the histogram (for details see histogram.cc)
  2) We smooth this histogram with 1D standard gaussian filter. with parameters \c Sigma and \c Radius.<br>
  3) We compute the finite diference aproximation of second derivation of the smoothed histogram. the kernel of the derivation operator is 1 -2 1 (central diference operator)<br>
  4) we want to find the values of this second derivation which is close to zero (This means that the boundary of FM method stops for a while)<br>
        so we go sequentially from the \c size_t \c Start bin of the histogram until we find a bin, in which the abs value of the second derivation is lower than \c VOXEL \c Threshold.  <br>
 
  The implementation of this function is based on article<br>
  P. Matula, J. Hubený, M. Kozubek <em> Fast Marching 3D Reconstruction of Interphase Chromosomes </em>, CVAMIA-MMBIA 2004, LNCS 3117.

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005

 */
template <class VOXEL> I3D_ALGO_EXPORT void FindContourLevel(Image3d<VOXEL> & Img, VOXEL& value,size_t Start = 3, VOXEL Threshold = 2.0, size_t Bins = 100, size_t Step = 1, double Sigma = 1.0, double Radius = 3.0);

/** \ingroup sm
  \brief This function computes shortest Geodesic Distances in the mask object from seed points. 

  Let <em> A </em> be a set which is first supposed to be connected. The <em> geodesic distance</em> \f$ d_A(p,q) \f$ between two pixels (voxels) \f$ p \f$ and \f$ q \f$ in <em>
  A </em> is the minimum of the length <b>L</b> of the path(s) \f$ P=(p_1,p_2,\dots,p_l) \f$ joining \f$ p \f$ and \f$ q \f$ and included in <em> A </em>:
  \f[
  d_A(p,q) = \min \{\mathbf{L}(P) | p_1 = p, p_l = q,  P \subseteq A\}.
  \f]
  
  This function computes such defined Geodesic Distance for the pixels in mask object from seed points. The mask object is the first parameter \c ImgIn. The Geodesic Distance is saved in the output image \c ImgOut. The seed points are given as input in the first parameter \c SeedPoints.

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005

  */
template <class VOXELIN, class VOXELOUT> I3D_ALGO_EXPORT void GeodesicDistance (Image3d<VOXELIN> & ImgIn, Image3d<VOXELOUT> & ImgOut, SeedPointsVector & SeedPoints);


/** \ingroup sm
  \brief This function computes Local Radius of the pixels  in the mask object from seed point. 

  <b>Definition of Local Radius:</b><br>
   Let <em> A </em> be a set which is first supposed to be connected. The <em> local radius </em> \f$ r_l(p,q) \f$  between two pixels (voxels)  \f$p \f$ and \f$ q\f$ in  
 <em> A </em>, where \f$ p \f$ is the given center is defined as the ratio of Geodesic Distance \f$ d_A(p,q) \f$  and sum of Geodesic Distance \f$ d_A(p,q) \f$  and the Geodesic distance of point \f$ q \f$ to the object boundary (\f$ d_A(q,boundary)\f$) multiplied by 100 to get the percents..
 \f[
   r_l(p,q) = \frac{ d_A(p,q) }{ d_A(p,q) +  d_A(q,boundary)} \cdot 100
 \f]
This function computes such defined Local Radius for the pixels in mask object from seed points. The mask object is the first parameter \c ImgIn. The Local Radius is saved in the output image \c ImgOut. The seed points are given as input in the first parameter \c SeedPoints.

 \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005


  */

template <class VOXELIN, class VOXELOUT> I3D_ALGO_EXPORT void LocalRadius (const Image3d<VOXELIN> & ImgIn, Image3d<VOXELOUT> & ImgOut, SeedPointsVector & SeedPoints);


template <class VOXELIN, class VOXELOUT> I3D_ALGO_EXPORT void FastMarchingSignedDistance(VOXELIN  Speed, Image3d<VOXELOUT> & ImgOut,  std::vector<size_t> & indexes, std::vector<VOXELOUT> & values);


/**
  \brief This class is together with class PDESolver the root abstract class for wide family of classes which implements 
  segmentation methods and image preprocessing filters. All these offsprings of this base class have one common feature.
  The key idea of those methods or filters is described by partial differential equation, which is evolving in time. 
  This class serves to compute the difference between two timesteps.

  The partial differential equation, which is the core off all offsprings of \c PDESolver class, has 
  following "general form":
  \f[
  u_t = F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...),
  \f]
  where <em>F</em> is some function of spatial derivatives. 
  The temporal derivation can be for example discretised by the forward Euler operator.
   \f[
  \frac{u^{n+1}- u^{n}}{\tau} = F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...),
  \f]
  This leads to following explicit scheme:
    \f[
  u^{n+1} = u^{n} + \tau F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...),
  \f]
  From this follows, that we have some initial state (input image, initial state of the segmentation, etc. )
  we iteratively modify this state (we compute the filter on the image, we try to find correct segmentation)
  and after some time we find the solution of the equation.
  
  Class \c PDESolverFunction computes only the 
  \f$  F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...) \f$ part of the equation. Due to the 
  limitations of the numerical schema (time step requirements, neighbourhood computations, etc.)
  it is convenient to compute the update (\f$ \tau F \f$ part) to independent buffer and after the computation  add the buffer to the solution.
  Therefore  all offsprings of this class have some buffer structure (which can differ) and all implement
  the ComputeUpdateData() method, which updates this buffer every time step. 
  There is no need to instantiate  a "Function" object (i. e. \c PDESolverFunction class) from the user point of view. 
  The user should only instantiate some offspring of \c PDESolver class. The "Function" object is instantiated automatically by 
  the "Solver" object.

  See also following schema and the documentation of \c PDESolver class.
  
  
  \image html diag.png "Diagram of Data and Control flow between Solver object (\c PDESolver offspring) and Function Object (\c PDESolverFunction offsprint)" 

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
*/

template <class VOXEL> class I3D_ALGO_EXPORT PDESolverFunction
{
    public:
	///This function computes the \f$\tau F\f$ part of the PDE equation, if fills the buffer with the update.
	virtual void ComputeUpdateData();
	///Returns the global time step which was computed by ComputeUpdateData function().
	VOXEL GetGlobalTimeStep();
	/// Set the fixed global time step.
	void SetGlobalTimeStep(VOXEL ts);
	///Set the Speed image. This image is used in some Level set methods.
	void SetSpeedImage(Image3d<VOXEL> * data);
	Image3d<VOXEL> * GetSpeedImage();

	///Set Spacing between voxels.
	virtual void SetSpacing(float x,float y, float z);
	///Set Spacing between voxels.
	virtual void SetSpacing(Vector3d<float> vec);
	///Get Spacing between voxels.
	Vector3d<float> GetSpacing();
	///Get Spacing between voxels.
	void GetSpacing(float *x, float *y, float *z);
	///Set the epsilon parametr. If is greater than zero the curvature part of some Level Set methods will be take into the account in the computations
	void SetEpsilon(VOXEL e);
	///Get the epsilon parametr. If is greater than zero the curvature part of some Level Set methods will be take into the account in the computations
	VOXEL GetEpsilon();
	//Contructors
	PDESolverFunction(Image3d<VOXEL> & data);
	//Destructor
	virtual ~PDESolverFunction();
    protected:
	///Global time step
	VOXEL GlobalTimeStep;
	///Reference to the Data image (to the changing solution of the equation)
	Image3d<VOXEL> & Data;
	///Reference to the Data image valarray (to the changing solution of the equation)
	std::valarray<VOXEL> & DataArray;
	///Pointer to Speed image (it is needed to some Level Set methods)
	Image3d<VOXEL> * SpeedImage;
	 /// Spacing of the LevelSet lattice
	Vector3d<float> Spacing;	
	/// Number of dimensions (2 or 3)
	size_t Dimensions;
	/// True, if the time step should be fixed during the computation.
	bool FixedTimeStep;
	VOXEL Epsilon;
    private:
};

/**
  \brief This class is together with class \c ExplicitSchemeFunction the abstract class for segmentation methods and image preproccessing
  filters, which compute the solution of underlying PDE on the whole domain (i.e. whole image). The explicit scheme in time is implemented in these two sister classes.   The finite difference solver implemented in these two "sister" classes computes the update to the solution and the "ideal" (possible maximal) time step in every iteration. The computed update is then added to the solution. These two "sister" classes implements only the solver, the user should instantiate some offspring to get the full functional filter or segmentation method.

  Thre finite difference solver which is implemented in these two "sister" classes primarilly serves to find solutions 
  in the whole domain (update every voxel in every timestep), the implemented numerical scheme is explicit, so there are some typical
  limitation to the time step (the CFL condition and so on).
  The finite difference solver implemented in this class and in class \c ExplicitScheme computes the update first in
  the interior image (not taking into account the boundary voxels). The update in boundary voxels is computed separately.
  This design allows to compute the filter as fast as possible.  The neighbourhood of the voxel is in the 
  interior image computed only for one pixel, the other neighbourhoods are computed only with incrementation.
  The neighbourhoods on boundary voxels are computed to fulfill the Zero-Flux Neumann boundary condition.
  The provided neighbourhood can differ. The Four or Six-Neighbourhood is provided for discretisations of 
  some "simple" equations. If these neighbourhoods are not sufficient, the user can by setting Epsilon > 0.0 turn to 
  computations with Eight or Eighteen neighbourhoods.

  Method \c ComputeUpdateData() calls for every voxel the \c ComputeUpdate() method in every time step. The method \c ComputeUpdate() computes the 
  update for the particular voxel and save it in the buffer array and returns the maximum possible value of the timestep for the particular voxel. 
  This time step value is compared to the up to now maximum possible time step by \c UpdateTimeStep() method and if the new timestep is lower than the
  up to now time step, the new value is the new global time step. 
  
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
*/

template <class VOXEL> class I3D_ALGO_EXPORT ExplicitSchemeFunction : 
    public PDESolverFunction<VOXEL>
{
    public:
        /// Computes the update to the buffer valarray. 
	virtual void ComputeUpdateData();
	/// Compute the update value for one voxel, returns the ideal timestep for the particular voxel.
	virtual VOXEL ComputeUpdate(size_t * neighbors,size_t center);
	/// Udates the Globaltime step  from the value returned by \c ComputeUpdate() method.
	virtual void UpdateTimeStep (size_t * neighbors, size_t index, VOXEL tempTimeStep);
	///Set the conductance parameter. This parameter is used in the anisotropic diffusion filters
	void SetConductance (VOXEL c);
	///Get the conductance parameter.
	VOXEL GetConductance ();
	virtual void SetNeighbourhood(LSNeighbourhood * D2, LSNeighbourhood * D3);
	//Contructor
	ExplicitSchemeFunction(Image3d<VOXEL> & data);
	//Destructor
	virtual ~ExplicitSchemeFunction();
	/// in this val array is saved the update buffer.
	std::valarray<VOXEL>  BufferArray;
	using PDESolverFunction<VOXEL>::GlobalTimeStep;
	using PDESolverFunction<VOXEL>::Data;
	using PDESolverFunction<VOXEL>::FixedTimeStep;
    protected:
	VOXEL Conductance;
	 LSNeighbourhood * D2Neighbourhood;
	 LSNeighbourhood * D3Neighbourhood;
    private:
};


/**
  \brief This class implements together with class MCFFilter the Curvature Flow anisotropic diffusion filter, which was published by
  Alvarez, Lions and Morel.  As the other anisotropic filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. Moreover it generates the so called morphological scale space.
  In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = \mathrm{div} ( \nabla u / |\nabla u|)  |\nabla u|\f$. The particular implemantion 
  is based on explicit finite difference solver and therefore there exist some limitations to the time step.
   There is no need to instantiate this class in the user program. This class is instantiated automatically in the MCFFilter class.
  
  
  The image is smoothed by finding solution of partial differential
  equation
  \f[
   u_t =  \mathrm{div} ( \nabla u / |\nabla u|)  |\nabla u|
  \f]
  where \f$ u_0\f$ is the input image (boundary condition of the PDE).
  In the context of level set equations, the above equation can be written as
   \f[
   u_t = \kappa  |\nabla u|
  \f]

  The idea of this equation is to smooth the image in regions with high curvature (i.e. noise) and do not diffuse the image near significant edges.
  The advantage of the filter is that there are no parameters to adjust the behaviour of the filter. The only value, which 
  can the user adjust is the stopping time (time step + number of iterations) of the diffusion. If we we diffuse the image to the 
  infinity we get the constantly valued grey image.
  
  This class completely inherits the imple explicit numerical scheme from class \c ExplicitSchemeFunction.
  It only reimplements the ComputeUpdate() and the UpdateTimestep() 
  methods.

  
  The implementation of this class is based on the chapter 16 from book <br>

  J. A. Sethian, <em> Level Set Methods and Fast Marching Methods </em>, Cambridge University Press 1999.

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */


template <class VOXEL> class I3D_ALGO_EXPORT MCFFilterFunction : 
    public ExplicitSchemeFunction<VOXEL>
{
    public:
	virtual VOXEL ComputeUpdate(size_t * neighbors,size_t center);
	virtual void UpdateTimeStep (size_t * neighbors, size_t index, VOXEL tempTimeStep);
	//Contructor
	MCFFilterFunction(Image3d<VOXEL> & data);
	//Destructor
	virtual ~MCFFilterFunction();
	using ExplicitSchemeFunction<VOXEL>::GlobalTimeStep;
	using ExplicitSchemeFunction<VOXEL>::Dimensions;
	using ExplicitSchemeFunction<VOXEL>::FixedTimeStep;
	using ExplicitSchemeFunction<VOXEL>::DataArray;
	using ExplicitSchemeFunction<VOXEL>::Spacing;
	using ExplicitSchemeFunction<VOXEL>::BufferArray;
    protected:
    private:
};

/**

 \ingroup if
  \brief This class implements simple Estimator of the gradient magnitude. The Gradient is estimated by simple central differences in 
  the direction of each axe. The Magnitude is computed as the square root of the sum of individual derivatives.

 The gradient magnitude is computed in a following way.
 \f[
 |\nabla u_{i,j,k}| = \sqrt{\left(\frac{\partial u_{i,j,k}}{\partial x}\right)^2 + \left(\frac{\partial u_{i,j,k}}{\partial y}\right)^2 + \left(\frac{\partial u_{i,j,k}}{\partial z}\right)^2}
 \f]
 The derivatives are discretised by simple central differences. The pixel on boundary are served in the sense of zero flux neumann boundary conditions. The Magnitude is estimated by calling the ComputeUpdateData() method.

 The example of use in the program:
  \verbatim
  .............
  Image3d<float> Img;
  GradientMagnitudeEstimator<float> GME(Img);
  GME->ComputeUpdateData();
  .............
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */
template <class VOXEL> class I3D_ALGO_EXPORT GradientMagnitudeEstimator : 
    public ExplicitSchemeFunction<VOXEL>
{
    public:
	//Contructor
	GradientMagnitudeEstimator(Image3d<VOXEL> & data);
	//Destructor
	virtual ~GradientMagnitudeEstimator();
	/// Compute the gradient magnitude
	virtual VOXEL ComputeUpdate(size_t * neighbors,size_t center);
	virtual void UpdateTimeStep (size_t * neighbors, size_t index, VOXEL tempTimeStep);
	virtual void SetLowerAndUpperDim(size_t L,size_t U);
	/// Apply the square root on the sum of squares of the derivatives?
	virtual void ApplySqrt();
	/// Copy the results to some other image.
	virtual void CopyToImage(Image3d<VOXEL> & Img);

	using ExplicitSchemeFunction<VOXEL>::Dimensions;
	using ExplicitSchemeFunction<VOXEL>::DataArray;
	using ExplicitSchemeFunction<VOXEL>::Spacing;
	using ExplicitSchemeFunction<VOXEL>::BufferArray;
    protected:
	size_t LowerDim, UpperDim;
    private:
};

/**
 \ingroup if
  \brief This class implements spatial derivatives operator neede for optical flow comp. Documentation TBA

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2006
 */

template <class VOXEL> class I3D_ALGO_EXPORT SpatialDerivatives :
    public GradientMagnitudeEstimator<VOXEL>
{
    public:
	//Contructor
	SpatialDerivatives(Image3d<VOXEL> & data);
	//Destructor
	virtual ~SpatialDerivatives();
	virtual VOXEL ComputeUpdate(size_t * neighbors,size_t center);
	void SetArrayPointers( std::valarray<VOXEL>* x = NULL,std::valarray<VOXEL>* y = NULL, std::valarray<VOXEL>* z = NULL);
	
	using GradientMagnitudeEstimator<VOXEL>::LowerDim;
	using GradientMagnitudeEstimator<VOXEL>::DataArray;
	using GradientMagnitudeEstimator<VOXEL>::Spacing;
	using GradientMagnitudeEstimator<VOXEL>::BufferArray;
	using GradientMagnitudeEstimator<VOXEL>::Data;
	using GradientMagnitudeEstimator<VOXEL>::UpperDim;
    protected:
	Vector3d< std::valarray<VOXEL>* > SDeriv;
    private:
};


/**
  \brief This class implements together with class \c PMFilter the Perona-Malik anisotropic diffusion filter, which was published by
  Perona and Malik. This filter was historical first published anisotropic diffusion filter and therefore is fundamental.
  As the other anisotropic filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = \mathrm{div} (g(|\nabla u|) \nabla u)\f$
   There is no need to instantiate this class in the user program. This class is instantiated automatically in the PMFilter class.


  This class completely inherits the imple explicit numerical scheme from class \c ExplicitSchemeFunction.
  It only reimplements the ComputeUpdate() and the UpdateTimestep() 
  methods. The discretisation of the equation is not accurate (as in the Perona Malik article), there are some simplifications. 
   \f[
    \begin{array}[b]{l}
     u_t = \mathrm{div} (g(|\nabla u|) \nabla u) \\ 
     u_t =  \sum \limits_{Dir \in \{N,S,E,W\}} g_{Dir}|\nabla_{Dir} u|||\\
    \end{array}
   \f]
   where \f$ u_W = u_{i-1,j} - u_{i,j} \f$ and so on, \f$ g_{Dir} = g(|\nabla u_{Dir}|)\f$.
   
   The implementation of this class is based on the articles <br>
  Pietro Perona and Jitendra Malik, <em> Scale-Space and Edge Detection Using Anisotropic Diffusion</em> IEEE Transactions on Pattern Analysis and Machine Intelligence. Vol. 12. No. 7. July 1990.
  Michael J. Black, Guilermo Sapiro, David H. Marimont, David Heeger, <em>Robust Anisotropic Diffusion </em>, IEEE Transactions on Image Processing, Vol. 7. No. 3. March 1998
  
   \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */


template <class VOXEL> class I3D_ALGO_EXPORT PMFilterFunction : 
    public ExplicitSchemeFunction<VOXEL>
{
    public:

	virtual VOXEL ComputeUpdate(size_t * neighbors,size_t center);
	virtual void UpdateTimeStep (size_t * neighbors, size_t index, VOXEL tempTimeStep);
	//Contructor
	PMFilterFunction(Image3d<VOXEL> & data); 
	//Destructor
	virtual ~PMFilterFunction();
	void SetNorm( VOXEL (*Func) (VOXEL , VOXEL) );
	using ExplicitSchemeFunction<VOXEL>::GlobalTimeStep;
	using ExplicitSchemeFunction<VOXEL>::FixedTimeStep;
	using ExplicitSchemeFunction<VOXEL>::Dimensions;
	using ExplicitSchemeFunction<VOXEL>::DataArray;
	using ExplicitSchemeFunction<VOXEL>::Spacing;
	using ExplicitSchemeFunction<VOXEL>::Conductance;
	using ExplicitSchemeFunction<VOXEL>::BufferArray;
    protected:
	VOXEL (* ptToNormFunction ) (VOXEL , VOXEL);
	
    private:
};

/**
  \brief This class implements together with class MCDEFilter the Modified Curvature Diffusion Flow anisotropic diffusion filter, which was published by
  Whitaker and Xue.  As the other anisotropic filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. Moreover it generates the so called morphological scale space.
  In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = |\nabla u| \cdot \mathrm{div} \left( g(| \nabla u|)\frac{ \nabla u }{ |\nabla u|} \right) \f$. The particular implementation 
  is based on explicit finite difference solver and therefore there exist some limitations to the time step.
   There is no need to instantiate this class in the user program. This class is instantiated automatically in the MCDEFilter class.
 
  The idea of this equation is to smooth the image in regions with high curvature (i.e. noise) and do not diffuse the image near significant edges.
  The diffusion is more agresive in the interior of objects and there is almost no diffusion on the objects boundaries due to the conductance function.
  For the detailed description of the conductance function \f$ g(|\nabla u|) \f$ see the documentation if the class PMFilter.

  The typical setting of coefficients for biomedical images produced in LOM should be: <br> 
  A few of iterations (1 to 10) should be sufficient to to smooth the image. 
  due to the limitation of used explicit numerical discretisation should be the time step
  lower than 0.25 for 2D images and lower than 0.125 for 3D images (See also the example code).
  If there is no time step set, the possible largest is set automatically.
  
  The numerical scheme which finds the solution of the equation is implemented in \c ExplicitScheme class. This class inherits the solution.

 
  The implementation of this class is based on the article <br>

  R. T. Whitaker, X. W. Xue, <em> Variable Conductance , Level Set Curvature For Image Denoising</em>


  
  The implementation of this class is based on the chapter 16 from book <br>

  J. A. Sethian, <em> Level Set Methods and Fast Marching Methods </em>, Cambridge University Press 1999.

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */


template <class VOXEL> class I3D_ALGO_EXPORT MCDEFilterFunction :
    public ExplicitSchemeFunction<VOXEL>
{
    public:

	virtual VOXEL ComputeUpdate(size_t * neighbors,size_t center);
	virtual void UpdateTimeStep (size_t * neighbors, size_t index, VOXEL tempTimeStep);
	//Contructor
	MCDEFilterFunction(Image3d<VOXEL> & data); 
	//Destructor
	virtual ~MCDEFilterFunction();
	void SetNorm( VOXEL (*Func) (VOXEL , VOXEL) );

	using ExplicitSchemeFunction<VOXEL>::GlobalTimeStep;
	using ExplicitSchemeFunction<VOXEL>::Dimensions;
	using ExplicitSchemeFunction<VOXEL>::FixedTimeStep;
	using ExplicitSchemeFunction<VOXEL>::DataArray;
	using ExplicitSchemeFunction<VOXEL>::Spacing;
	using ExplicitSchemeFunction<VOXEL>::BufferArray;
	using ExplicitSchemeFunction<VOXEL>::Conductance;

    protected:
	VOXEL (* ptToNormFunction ) (VOXEL , VOXEL);

    protected:
    private:
};




/**
  \brief This class is together with class PDESolverFunction the root abstract class for wide family of classes which implements 
  segmentation methods and image preprocessing filters. All these offsprings of this base class have one common feature.
  The key idea of those methods or filters is described by partial differential equation. 
  The execution of the methods or application of the filters has in the background the
  solution of the underlying PDE. 

  The partial differential equation, which is the core off all offsprings of this class, has 
  following "general form":
  \f[
  u_t = F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...),
  \f]
  where <em>F</em> is some function of spatial derivatives. 
  The temporal derivation can be for example discretised by the forward Euler operator in following way.
   \f[
  \frac{u^{n+1}- u^{n}}{\tau} = F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...),
  \f]
  This leads to following explicit scheme:
    \f[
  u^{n+1} = u^{n} + \tau F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...),
  \f]
  From this follows, that we have some initial state (input image, initial state of the segmentation, etc. )
  we iteratively modify this state (we compute the filter on the image, we try to find correct segmentation)
  and after some time we find the solution of the equation.

  This class together with class \c PDESolverFunction implements above suggested functionality.
  The \c PDESolver class (and their offsprings) take control of the iteration proccess, 
  it handles the input and the output (memory allocation, etc.) and it implements the iterative solver of PDE equation.
  It has also an pointer to the "Function" object (\c PDESolverFunction and offsprings), which is responsible 
  for computation of the \f$\tau F(...)\f$ part of the equation. 
  There is no need to instantiate  a "Function" object (i. e. \c PDESolverFunction class) from the user point of view. 
  The user should only instantiate some offspring of \c PDESolver class. The "Function" object is instantiated automatically by 
  the "Solver" object.


  <b>More detailed description</b><br>
  The constructor  of every offspring of this class has two parameters -- references to Input and Output image (Image3d objects).
  The user should only supply correctly initialised (allocated and loaded) Input image. The output image is 
  automatically initialised to the correct state. There are some methods which should the user use to adjust the  default settings 
  (Spacing between voxels, maximum number of the iterations, the time step \f$ \tau \f$ and so on).
   The core functionality (iterative proccess of solution finding) is implemented in the method \c PDESolver::Execute().
  The code listing of this method is shown bellow. 
  In first the Input is copied to Output by the \c InitializeOutput() method. Second the virtual method \c Initialize() is called to 
  allow some necessary initialization steps, which are not common for all inherited classes. The iterative process starts  after that.
  The method \c ComputeChange() calls method PDESolverFunction::ComputeUpdateData(), which computes the 
  \f$  F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...) \f$ part of the equation. This method also computes the posible maximum
  time step \f$ \tau \f$ which can be used to add the \f$  F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...) \f$  part to \f$u^n \f$.
  The addition of \f$ \tau F(u_x,u_y,u_z,u_{xx},u_{yy},u_{zz},u_{xxx},...) \f$  to \f$ u^n \f$ provides the \c ApplyChange() method.
  The loop ends if the \c Convergence() method returns true. 

  \verbatim
  template <class VOXELIN, class VOXELOUT> void PDESolver<VOXELIN, VOXELOUT>::Execute()
  {
    InitializeOutput();
    Initialize();
    while (! Convergence())
    {
	InitializeIteration();
	ComputeChange();
	ApplyChange();
	++ElapsedIteration;
    }
  }
  \endverbatim

  
  \image html diag.png "Diagram of Data and Control flow between Solver object (\c PDESolver offspring) and Function Object (\c PDESolverFunction offsprint)" 
  
  <b>Simple example of usage</b><br>
  In the code sequence bellow is shown the simple example how should be used the offsprings of the \c PDESolver
  class. After instantiation with two parameters, where the input parameter is correctly allocated and the ouput is
  only declared, some adjustment is done (setting the spacing and timestep). After that the main \c Execute() method is called.
  The last two lines are used only for converting the float output to gray leveels image.
  
  \verbatim 
  #include <LevelSet.h>
  #include <image3d.h>
  .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   AOSTVFilter<GRAY8,float> TV(i,fimg); // instantiate  the filter  
   TV.SetMaximumNumberOfIterations(3); // Set the number of iterations to 2
   TV.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   TV.SetGlobalTimeStep(5.0); // Set the global time step
   TV.Execute(); // Perform the work of the filter
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim

  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
*/

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT PDESolver
{
    public:
	PDESolverFunction<VOXELOUT> * Function;
	/// Initialize the output image (Memory allocation, Resolution settings, etc.).
	void InitializeOutput();
	/// If returns true the iteration proccess stops.
	virtual bool Convergence();
	/// Initialize the computation.
	virtual void Initialize();
	/// Initialize computation for one iteration step.
	virtual void InitializeIteration();
	/// Compute the \f$ \tau \f$ part of the equation.
	virtual void ComputeChange();
	/// Add the  \f$ \tau \f$ part of the equation to the solution.
	virtual void ApplyChange();
	/// This method implements the main iterative proccess of solution finding
	virtual void Execute();
	//This method will reset the internal counter of elapsed iterations to zero.
	virtual void ZeroElapsedIteration();
	size_t GetNumberOfElapsedIterations();
	bool EstimateDistanceInOnePoint (size_t index, size_t * neighbors, VOXELOUT * offset);
	void SetInputIsoValue (VOXELOUT value) ;
	VOXELOUT GetInputIsoValue () ;
	/// Set the maximum number of iterations.
	void SetMaximumNumberOfIterations (size_t max) ;
	/// Get the maximum number of iterations.
	size_t GetMaximumNumberOfIterations () ;
	///Set the spacing between voxels.
	void SetSpacing(float x,float y, float z);
	///Set the spacing between voxels.
	void SetSpacing(Vector3d<float> vec);
	Vector3d<float> GetSpacing();
	///Get the spacing between voxels.
	void GetSpacing(float *x, float *y, float *z);
	///Set the fixed global time step (\f$ \tau\f$).
	virtual void SetGlobalTimeStep(VOXELOUT t) ;
	///Get the fixed global time step (\f$ \tau\f$).
	VOXELOUT GetGlobalTimeStep();
	//Constructor
	PDESolver(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~PDESolver();
    protected:
	void CopyInputToOutput();
///Input image	
	Image3d<VOXELIN> & Input;
	///Output Image
	Image3d<VOXELOUT> & Output;
//	Image3d<VOXELOUT> & FeatureImage;
/// Number of Elapsed Iteration during computations
	size_t ElapsedIteration;
 /// Maximum number of iterations
	size_t MaximumIteration;
/** Value of the isoline(surface), which will
  be taken as the zero level set, from the input image
*/
	VOXELOUT InputIsoValue;
 /// Spacing of the LevelSet lattice
	Vector3d<float> Spacing;	
	/// Number of dimensions (2 or 3)
        size_t Dimensions; 
	VOXELOUT GlobalTimeStep;
    private:
};



/**
  \brief This class is together with class \c ExplicitSchemeFunction the abstract class for segmentation methods and image preproccessing
  filters, which compute the solution of underlying PDE on the whole domain (i.e. whole image). The explicit scheme in time is implemented in these two sister classes.   The finite difference solver implemented in these two "sister" classes computes the update to the solution and the "ideal" (possible maximal) time step in every iteration. The computed update is then added to the solution. These two "sister" classes implements only the solver, the user should instantiate some offspring to get the full functional filter or segmentation method.

  The finite difference solver which is implemented in these two "sister" classes primarilly serves to find solutions 
  in the whole domain (update every voxel in every timestep), the implemented numerical scheme is explicit, so there are some typical
  limitation to the time step (the CFL condition and so on).
  The finite difference solver implemented in this class and in class \c ExplicitSchemeFunction computes the update first in
  the interior image (not taking into account the boundary voxels). The update in boundary voxels is computed separately.
  This design allows to compute the filter as fast as possible.  The neighbourhood of the voxel is in the 
  interior image computed only for one pixel, the other neighbourhoods are computed only with incrementation.
  The neighbourhoods on boundary voxels are computed to fulfill the Zero-Flux Neumann boundary condition (also called reflecting neumann boundary conditions).
  The provided neighbourhood can differ. The Four or Six-Neighbourhood is provided for discretisations of 
  some "simple" equations. If these neighbourhoods are not sufficient, the user can by setting Epsilon > 0.0 turn to 
  computations with Eight or Eighteen neighbourhoods.
  
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
*/

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT ExplicitScheme : public PDESolver<VOXELIN,VOXELOUT>
{
    public:
        ///Compute the update to the buffer.
	virtual void ComputeChange();
	///Add the buffer to the solution.
	virtual void ApplyChange();
	//Constructor
	ExplicitScheme(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~ExplicitScheme();
	using PDESolver<VOXELIN,VOXELOUT>::Function;
	using PDESolver<VOXELIN,VOXELOUT>::Output;
    protected:
    private:
};



#ifdef WITH_LAPACK
/**
  \brief This class is root abstract class for wide family of nonlinear diffusion filters. 
  This class implements the skeleton of numerical semi-implicit AOS scheme. Instances of this class 
  will not produce any usable output. To obtain fully functional nonlinear diffusion filter 
  try to instantiate some offspring of this class.

  The main idea of nonlinear diffusion filtering is to smooth the image inside relatively continuous regions and do not smooth 
  the image near edges.  Nonlinear diffusion filtering is ussualy performed with explicit schemes (see ExplicitScheme and PMFilter class for examples).
  This schemes are stable only for small time steps (i.e. \f$\tau < 0.25\f$ 
  for 2D images, see documentation of MCFFilter class). This limits their practical use
  and leads to poor efficiency. This abstract class implements the skeleton of
  numerical semi-implicit AOS (additive oerator splitting). 
  The AOS scheme is absolute stable fo all time steps, but there is
  one limitation to the size of time step \f$ \tau \f$. The scheme tends 
  to produce larger and larger  errors for time step \f$ \tau > 5.0 \f$ 
  (considering that the distance between grid points is \f$ h  = 1\f$ for all dimensions). The offsprings 
  of this abstract class modificate the input image by solving following partial differential equation:
  \f[
  u_t = {\mathrm {div}} (g(|\nabla u|)  \nabla u),
  \f]
  where \f$ g(s) \f$ is decreasing function of the image gradient, and \f$ u_0\f$ is the input image. 
  The equation is discretised on cartesian grid, the time is discretized by forward Euler operator. The image gradient is discretised
  by central differences. The divergence operator is discretised also with central differences. The semi-implicit scheme leads to following 
  discretisation of the equation:
    \f[
  \frac {u_{i,j}^{n+1} - u_{i,j}^n}{\tau} = {\mathrm {div}} (g(|\nabla u_{i,j}^n|) \nabla u_{i,j}^{n+1}) \\
\f]
The AOS schemes solves this discretisation dimension by dimension, so following equations will be shown only for the direction of <em>x</em> axe.
    \f[
\begin{array}[b]{l}
  \frac {u_{i}^{n+1} - u_{i}^n}{\tau} = {\mathrm {div}} (g(|\nabla u_{i}^n|)  \nabla u_{i}^{n+1}) \\
  \\
  \frac {u_{i}^{n+1} - u_{i}^n}{\tau}  =\frac{g_{i+1}^n + g_{i}^{n}}{2h^2}(u^{n+1}_{i+1} - u^{n+1}_{i}) - \frac{g_{i-1}^n + g_{i}^{n}}{2h^2}(u^{n+1}_{i} - u^{n+1}_{i-1}) \\
\end{array}
  \f]
 This can be written in more compact form:
   \f[
\begin{array}[b]{l}
  \frac {u_{i}^{n+1} - u_{i}^n}{\tau}  =\frac{g_{i+1}^n + g_{i}^{n}}{2h^2}(u^{n+1}_{i+1} - u^{n+1}_{i}) + \frac{g_{i-1}^n + g_{i}^{n}}{2h^2}(u^{n+1}_{i-1} - u^{n+1}_{i}) \\
  \\
  \frac {u_{i}^{n+1} - u_{i}^n}{\tau}  =\sum \limits_{j \in N(i)} \frac{g_{j}^n + g_{i}^{n}}{2h^2}(u^{n+1}_{j} - u^{n+1}_{i}) \\
\end{array}
  \f]
  which in matrix-vector notation becomes to 
   \f[
\begin{array}[b]{l}
  \frac {u^{n+1} - u^n}{\tau}  =A(u^n)u^{n+1} \\
  \\
  (I - \tau A(u^n)) u^{n+1} =   u^n \\
\end{array}
  \f]
  with \f$ A(u^n) = (a_{ij}(u^n))\f$ and
   \f[
\begin{array}[b]{l}
   a_{ij}(u^n) =   \frac{g_{j}^n + g_{i}^{n}}{2h^2}  \quad (j \in N(i)) \\ 
   \\
   a_{ij}(u^n) =   - \sum \limits_{k \in N(i)} \frac{g_{k}^n + g_{i}^{n}}{2h^2}  \quad (j  = i) \\ 
   \\
   a_{ij}(u^n) =   0   \quad {\mathrm {else}}\\
   \\
   \\
   g_i^n = g(\sqrt {u_x^2 + u_y^2})  \quad {\mathrm {discretised \, with \, central \, differences}}\\

\end{array}
  \f]

  The AOS scheme solves this equation dimension by dimension by adding solutions of the folowing equation in particular directions (x,y,z)  to the aggregate final solution.
   \f[
  u^{n+1} = \frac{1}{m} (I - m \tau A(u^n))^{-1}  u^n 
  \f]
  where <em>m</em> is number of dimensions. 
  The solution of above equation in each direction leads to solving the linear system of equations in one iteration step. 
  If we order the voxels extra for each direction, the matrix <em> A </em> becomes threediagonal and there exist fast methods for 
  finding solutions of such matrices. This class uses <b> LAPACK </b> routines to find solutions of three diagonal linear system. 
  The i3d library must be linked with lapack library to obtain fully functionality of this class.


  The implementation of this class is based on the article <br>
  Joachim Weickert, Bart M. ter Haar Romeny, Max A. Viergever, <em> Efficient and Reliable Schemes for Nonlinear Diffusion Filtering </em>, IEEE TRANSACTIONS ON IMAGE PROCESSING, VOL. 6, NO. 3, PP. 398-410, MARCH 1998.

  The typical code for using the anisotropic diffusion filters, which are offsprings of this class, is shown bellow. 
  The example code uses the AOS implementation of CLMC diffusion filter (class AOSCLMCFilter).
  \verbatim
    .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   AOSCLMCFilter<GRAY8,float> CLMC(i,fimg); // instantiate  the filter  (the two parameters are the input and the output image)
   CLMC.SetMaximumNumberOfIterations(2); // Set the number of iterations to 2
   CLMC.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   CLMC.SetSigma(1.0); // Set the sigma of the gaussian blur to 1.0
   CLMC.SetConductance(3.0); // Set the conductance parameter to 3.0
   CLMC.Execute(); // Perform the work of the filter
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005

 <b> Example input and output: </b>
  \image html ad.png "Left: Input to anisotropic diffusion, Right: Output of Total variation filter (AOSTVFilter class), 10 iterations with delta t = 5.0" 
 */
template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT ImplicitAOSScheme : public PDESolver<VOXELIN,VOXELOUT>
{
    public:
	virtual bool Convergence();
        virtual float Globality();
	/** One iteration of the AOS scheme will be performed after calling this method. 
	  */
	virtual void ComputeChange();
	/** This method copies the content of the internal ImplicitAOSScheme::BufferArray in the output image (Data member).*/
	virtual void ApplyChange();
	virtual void SetMaxGlobality(float g);
        virtual float ComputeLambdaFromQuantile(float quantile);
	//Constructor
	/** The constructor tooks two arguments, the input image <b> i3d::Image<VOXELIN> in </b> 
	  together with the output image  <b>i3d::Image<VOXELIN> out</b>*/
	ImplicitAOSScheme(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~ImplicitAOSScheme();
	/// Computes the coefficients in the diagonals of the matrix.
        virtual void PrepareDiagonals (size_t start, size_t incr, Vector3d<size_t> & size, size_t axe);
        //virtual void PrepareZDiagonals (size_t start, size_t incr, Vector3d<size_t> & size, size_t axe);
	/// This function computes the diffusivity function <em> g </em> for each voxel of the image. 
	virtual void ComputeDiffusivity();
	/// If Set to <b>true</b>, the threediagonal matrix A is considered to be symetric and the faster routines to solve this systems will be used. 
	void SetSymetric(bool s = true);
	/// Get the symetric flag. 
	bool GetSymetric();
	/// Set spacing of the cartesian grid. Typical values are (1.0,1.0,1.0 * z)
	virtual void SetSpacing(float x,float y, float z);
	/// Set spacing of the cartesian grid. Typical values are (1.0,1.0,1.0 * z)
	virtual void SetSpacing(Vector3d<float> vec);
	/** Allocate valarrays, in which are saved the coefficients of the matrix. (The matrix has different size for each direction). The input parameter
	  is the size of the main diagonal, which is equal to the size of image in each direction. */
	void AllocateDiagonals(size_t Max);

/** Pointer to GradientMagnitudeEstimator class, which serves to estimate the gradient of the image with central differences.
	  The instance of this class is automatically allocated in the constructor
	  */
	GradientMagnitudeEstimator<VOXELOUT> * GradMag;
	/// Pointer to valarray with values of gradient estimation.
	std::valarray<VOXELOUT> * GradMagData;


	using PDESolver<VOXELIN,VOXELOUT>::ElapsedIteration;
	using PDESolver<VOXELIN,VOXELOUT>::MaximumIteration;
	using PDESolver<VOXELIN,VOXELOUT>::Output;
	using PDESolver<VOXELIN,VOXELOUT>::Input;
	using PDESolver<VOXELIN,VOXELOUT>::Function;
	using PDESolver<VOXELIN,VOXELOUT>::Spacing;
	using PDESolver<VOXELIN,VOXELOUT>::Dimensions;
	using PDESolver<VOXELIN,VOXELOUT>::GlobalTimeStep;

    protected:
/// The solution of the AOS scheme is saved in this array 
	std::valarray<VOXELOUT>  BufferArray;
	std::valarray<VOXELOUT>  & OutputArray;
	/// The coefficients of the main diagonal are saved in this valraay
	std::valarray<VOXELOUT> Diag;
	/// The coefficients of the upper diagonal are saved in this valraay
	std::valarray<VOXELOUT> UDiag;
	/// The coefficients of the lower diagonal are saved in this valraay
	std::valarray<VOXELOUT> LDiag;
	/// The right hand side of the linear system is saved in this valarray
	std::valarray<VOXELOUT> row;

	float MaxGlobality;
	float InputMoment;
	float AverageGrey;
	bool Symetric;
    private:

};



template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT LODGaussianBlur;

/**
  \ingroup if
  \brief This class implements the nonlinear diffusion filter, which was published by
  Catte, Lions, Morel and Coll. As the other nonlinear filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = \mathrm{div} (g(|\nabla u_{\sigma}|^2) \nabla u)\f$
  
  The CLMC filter is improved version of the classic filter of Perona and Malik (see AOSPMFilter class). The image is smoothed by finding solution of
  equation
  \f[
   u_t = \mathrm{div} (g(|\nabla u_{\sigma}|^2) \nabla u)
  \f]
  where \f$ u_{\sigma}\f$ denotes the image convolved with gaussian of standard deviation \f$\sigma\f$,
   \f$ g(s^2) \f$ is decreasing function of the smoothed image gradient, and \f$ u_0\f$ is the input image (boundary condition of the PDE). The idea of this equation is to 
   smooth the image in regions with almost no gradient and do not diffuse the image near significant edges. The strength of the diffusion is controled by the diffusivity function <em>g</em>.
  This class completely inherits the AOS numerical scheme from class ImplicitAOSScheme. It only reimplements the ComputeDiffusivity() function, which first 
  convolves the inpute image with the Gaussian of standard deviation \f$\sigma\f$ (see documentation of LODGaussianBlur) and then computes 
  <em>g</em> diffusivity function for all voxels in the image \f$u^n\f$.
   \f[
   g(s^2) = 1 - \mathrm{exp}\left(\frac{-Cm}{(s^2/ \lambda^2)^m}\right )
   \f]
   For the meaning of the parameters see documentation of the AOSCLMCFilter class. 
 
   The diffusivity <em> g </em> function is computed by:
   \f[
   g(s^2) = 1 - \mathrm{exp}\left(\frac{-Cm}{(s^2/ \lambda^2)^m}\right )
   \f]
   The only free variable in this expression is the \f$s^2\f$, which is the squared gradint magnitude. The coefficients conductance \f$\lambda\f$ and exponent <em> m </em> 
   are selected by the user. The size of conductance lambda directly influences the smoothing. On can say, that the voxel will be smoothed, 
   if the gradient magnitude in it is less or equal than \f$\lambda\f$ and on the contrary not smoothed if the gradient magnitude in the voxel is greater 
   than \f$\lambda\f$ parameter. The size of <em> m </em> influences the steepness of the cross-over between "smoothing" and "not smoothing".
   The coefficient <em>Cm</em> is computed automatically. For having the idea of what is the diffusivity function exactly doing see following picture.
  
  \image html diffusivity.gif "Diffusivity g function: lambda = 10.0, m = 4.0, Cm = 4.22977"
  The typical setting of coefficients of <em> g</em> function for biomedical images produced in LOM should be: <br> 
  \f$\lambda\f$ between 1 and 10, <em>m</em> between 2 and 16.<br>
  The \f$\sigma\f$ should be at least 1.0 to suppress noise.<br>
  A few of iterations (1 to 10) should be sufficient to to smooth the image. The meaningful time step should be between 0.1 and 5.0 (See also the example code).
  The numerical scheme which finds the solution of the equation is implemented in ImplicitAOSScheme class. This class inherits the solution.
 
  The implementation of this class is based on the articles <br>
  Joachim Weickert, Bart M. ter Haar Romeny, Max A. Viergever, <em> Efficient and Reliable Schemes for Nonlinear Diffusion Filtering </em>, IEEE TRANSACTIONS ON IMAGE PROCESSING, VOL. 6, NO. 3, PP. 398-410, MARCH 1998. <br>
  Francine Catte, Piere-Louis Lions, Jean-Michel Morel and Tomeu Coll,<em>Image Selective Smoothing and Edge Detection by nonlinear diffusion</em>, SIAM Journal of Numer. Anal., Vol. 29, 182 - 193, 1992.

  The example code uses the AOS implementation of CLMC diffusion filter.
  \verbatim
   .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   AOSCLMCFilter<GRAY8,float> CLMC(i,fimg); // instantiate  the filter  (the two parameters are the input and the output image)
   CLMC.SetMaximumNumberOfIterations(3); // Set the number of iterations to 2
   CLMC.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   CLMC.SetSigma(1.0); // Set the sigma of the gaussian blur to 1.0
   CLMC.SetConductance(3.0); // Set the conductance parameter to 3.0
   CLMC.SetGlobalTimeStep(5.0); // Set the global time step
   CLMC.Execute(); // Perform the work of the filter
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT AOSCLMCFilter : public ImplicitAOSScheme<VOXELIN,VOXELOUT>
{
    public:
	//Constructor
	AOSCLMCFilter(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~AOSCLMCFilter();
	///Set the conductance coefficient lambda
	void SetConductance (VOXELOUT c);
	///Get the value of the conductance lambda coefficient
	VOXELOUT GetConductance ();
	///Set the sigma, standard deviation of the gaussian filter
	void SetSigma(VOXELOUT sig); 
	///Get the sigma, standard deviation of the gaussian filter
	VOXELOUT GetSigma() ; 
	///Set the value of the <em>m</em> exponent 
	void SetExponent(VOXELOUT exp);
	///Get the value of the <em>m</em> exponent 
	VOXELOUT GetExponent();
	/// computes the \f$g(s^2)\f$ function for the whole image.
	virtual void ComputeDiffusivity();
	/// Set the spatial spacing. Typical values are (1.0,1.0,1.0*z)
	virtual void SetSpacing(float x,float y, float z);
	/// Set the spatial spacing. Typical values are (1.0,1.0,1.0*z)
	virtual void SetSpacing(Vector3d<float> vec);


	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Function;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Output;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Spacing;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::GradMag;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::GradMagData;
	
    protected:
	///The conductance parameter of the diffusion function
	VOXELOUT Conductance;
	///The Exponent parameter of the diffusion function
	VOXELOUT Exponent;
	///Pointer to the LODGaussianBlur instance. This object performs the gaussian blur of the input image, before computing the gradient.
	LODGaussianBlur<VOXELOUT,VOXELOUT> * GaussEstimator;

    private:
};


/**
  \ingroup if
  \brief This class implements the Total Variations nonlinear diffusion filter and the Ballanced Forward Backward filter, which were published by
  Andreu et al. and Keeling et al. As the other nonlinear filters, these filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = \mathrm{div}(\frac{\nabla u}{|\nabla u|}) \f$.
  
  The well known Total Variation restoration (Rudin et al.) technique tries to to reconstruct the true image <em>u</em> from the observation <em>f</em>. Given an image function \f$ f \in L^2(\Omega)\f$, 
  with \f$ \Omega \subset R^2\f$ an open and bounded domain, the problem is to extract <em>u</em> from <em>f</em>. 
  The observation <em>f</em> is usually noised version of <em>u</em>.So Rudin, Osher and Fatemi have proposed following minimization problem:
  
  \f[
   \inf_u F(u) = \int_{\Omega} |\nabla u| + \lambda \int_{\Omega} |f - u|^2 dx dy
  \f]
  where \f$ \lambda > 0\f$ is weight parameter, \f$ \int_{\Omega} |f-u|^2 dxdy\f$ is fidelity term, which holds image <em>u</em> "near" image <em>f</em>, and 
  \f$ \int_{\Omega} |\nabla u|\f$ is the noise removing regularizing term. This minimization problem leads to solving the Euler-Lagrange equation:
   \f[
   u = f + \frac{1}{2 \lambda} \mathrm{div} \left ( \frac{\nabla u } { | \nabla u | } \right ) 
  \f]
  
  If we omit the fidelity term, we get in the context of nonlinear diffusion filtering following equation 
    \f[
   u_t = \mathrm{div} \left ( \frac{\nabla u } { | \nabla u | } \right ) 
  \f]
  Some authors add some regularising constant to the equation
   \f[
   u_t =  \mathrm{div} \left ( \frac{\nabla u } { (\sqrt { | \nabla u |^2 + \beta })^e } \right ) 
  \f]
  ,where  \f$ \beta > 0\f$ is the user selected constant. The exponent <em>e</em> should be greater or equal than 1. For the exponent <em>e=1</em> we get the Total variation diffusion filter (Andreu et al.) and for exponent <em>e = 2.0</em>  we get the Ballanced Forward Backward filter of Keeling et al.. If we set exponent <em>e</em> between 1 and 2, we get the combination of both filters.
  
  The implementation of this class is based on the articles <br>
  Joachim Weickert, Bart M. ter Haar Romeny, Max A. Viergever, <em> Efficient and Reliable Schemes for Nonlinear Diffusion Filtering </em>, IEEE TRANSACTIONS ON IMAGE PROCESSING, VOL. 6, NO. 3, PP. 398-410, MARCH 1998. <br>
  F. Andreu, V. Caselles, J. I. Diaz, J. M. Mazón,<em> Qualitative properties of the total variation flow</em>, Journal of Functional Analysis, Vol. 188, No. 2, 516-547, Febr. 2002.<br>
   Stephen L. Keeling and Rudolf Stollberger,<em>Nonlinear anisotropic diffusion filtering for multiscale edge enhancement</em>,Inverse Problems, Vol. 18, 2002, 175--190 <br>            
  L. Rudin, S. Osher, and E. Fatemi, <em>Nonlinear total variation based noise removal algorithms</em>, Physica D, vol. 60, pp. 259-268,1992.
  
  The example code for using the  TV diffusion filter.
  \verbatim
   .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   AOSTVFilter<GRAY8,float> TV(i,fimg); // instantiate  the filter  (the two parameters are the input and the output image)
   TV.SetMaximumNumberOfIterations(3); // Set the number of iterations to 2
   TV.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   TV.SetGlobalTimeStep(5.0); // Set the global time step
   TV.Execute(); // Perform the work of the filter
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT AOSTVFilter : public ImplicitAOSScheme<VOXELIN,VOXELOUT>
{
    public:
	//Constructor
	AOSTVFilter(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~AOSTVFilter();
	///Set the Exponent parameter
	void SetExponent(VOXELOUT exp);
	///Get the value of the exponent parameter
	VOXELOUT GetExponent();
	///Set the Beta parameter
        void SetBeta(VOXELOUT B);
	///get the value of the beta parameter
	VOXELOUT GetBeta();
	///This function computes the diffusivity <em>g </em> function
	virtual void ComputeDiffusivity();

	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Function;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Output;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Spacing;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::GradMag;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::GradMagData;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::SetSpacing;

    protected:
	VOXELOUT Exponent;
	VOXELOUT Beta;
    private:
};


/**
  \ingroup if
  \brief This class implements the Perona-Malik anisotropic diffusion filter, which was published by
  Perona and Malik. This filter was historical first published nonlinear diffusion filter and therefore is fundamental.
  As the other anisotropic filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = \mathrm{div} (g(|\nabla u|) \nabla u)\f$
  
  The Perona Malik Filter  is the historical first anisotropic diffusion filter. The image is smoothed by finding solution of partial differential
  equation
  \f[
   u_t = \mathrm{div} (g(|\nabla u|) \nabla u)
  \f]
  where \f$ g(s) \f$ is decreasing function of the image gradient, and \f$ u_0\f$ is the input image (boundary condition of the PDE).
  The idea of this equation is to smooth the image in regions with almost no gradient and do not diffuse the image near significant edges. 
  The strength of the diffusion is controled by the diffusivity function <em>g</em>.
   The diffusivity <em> g </em> is in original work of Perona and Malik computed by:
   \f[
   g(s) = \frac{1}{1+\left(\frac{s}{ \lambda}\right )^2}
   \f]
   Perona and Malik considered also an alternative diffusion function:
    \f[
   g(s) = \mathrm{exp}(-(s/\lambda)^2)
   \f]
   An consequently Black, Sapiro, Marimont, Heeger proposed the usage of Tukey Biweight norm:
    \f[
\begin{array}[b]{l}
   g(s) = [1 - 0.25((s/\lambda))^2]^2 \quad |s| \le \lambda\sqrt{5} \\
   g(s) = 0 \quad \rm{otherwise} \\
   \end{array}
   \f]
   See the image bellow, there are displayed all three norms. The meaning of those norms is following: All three enables the diffusion 
   on pixels with the gradient lower than \f$\lambda \f$. All three stops the diffusion on pixels with image gradient higher than \f$\lambda\f$, but they
   differ on the strictness of the stopping.
   
   \image html diffusivitypm.gif "Diffusivity g function: lambda = 5.0, left: original PM norm, middle: alternative PM Norm, right: Tukey Biweight Norm"

   This class completely inherits the AOS numerical scheme from class ImplicitAOSScheme. It only reimplements the ComputeDiffusivity() and the PrepareDiagonals() 
  functions. The discretisation of the equation is not accurate (as in the Perona Malik article), there are some simplifications. 
   \f[
    \begin{array}[b]{l}
     u_t = \mathrm{div} (g(|\nabla u|) \nabla u) \\ 
     u_t =  \sum \limits_{Dir \in \{N,S,E,W\}} g_{Dir}|\nabla_{Dir} u|||\\
    \end{array}
   \f]
   where \f$ u_W = u_{i-1,j} - u_{i,j} \f$ and so on, \f$ g_{Dir} = g(|\nabla u_{Dir}|)\f$. In contrast to the AOSCLMCFilter is this discretisation quite symplified.
   Therefore the above mentioned method are reimplemented in this class.

  The typical setting of coefficients of <em> g</em> function for biomedical images produced in LOM should be: <br> 
  \f$\lambda\f$ between 1 and 10.<br>
  All three norms can be used to produce meaningfull output.<br>
  A few of iterations (1 to 10) should be sufficient to to smooth the image. The meaningful time step should be between 0.1 and 5.0 (See also the example code).
  The numerical scheme which finds the solution of the equation is implemented in ImplicitAOSScheme class. This class inherits the solution.
 
  The implementation of this class is based on the articles <br>
  Joachim Weickert, Bart M. ter Haar Romeny, Max A. Viergever, <em> Efficient and Reliable Schemes for Nonlinear Diffusion Filtering </em>, IEEE TRANSACTIONS ON IMAGE PROCESSING, VOL. 6, NO. 3, PP. 398-410, MARCH 1998. <br>
  Pietro Perona and Jitendra Malik, <em> Scale-Space and Edge Detection Using Anisotropic Diffusion</em> IEEE Transactions on Pattern Analysis and Machine Intelligence. Vol. 12. No. 7. July 1990.
  Michael J. Black, Guilermo Sapiro, David H. Marimont, David Heeger, <em>Robust Anisotropic Diffusion </em>, IEEE Transactions on Image Processing, Vol. 7. No. 3. March 1998
  The example code uses the AOS implementation of PM diffusion filter.
  \verbatim
   .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   AOSPMFilter<GRAY8,float> PM(i,fimg); // instantiate  the filter  (the two parameters are the input and the output image)
   PM.SetMaximumNumberOfIterations(3); // Set the number of iterations to 2
   PM.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   PM.SetConductance(3.0); // Set the conductance parameter to 3.0
   PM.SetNorm(ORIGINALPM); // Set norm to original PM norm
   PM.SetGlobalTimeStep(5.0); // Set the global time step
   PM.Execute(); // Perform the work of the filter
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */
 
template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT AOSPMFilter : public ImplicitAOSScheme<VOXELIN,VOXELOUT>
{
    public:
	//Constructor
	AOSPMFilter(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~AOSPMFilter();
	/// Set the conductance parameter
	void SetConductance (VOXELOUT c) ;
	///Get the conductance parameter
	VOXELOUT GetConductance () ;
	///Set the Norm. The int parameter type can vary in {ORIGINALPM, ALTERNATIVEPM, TUKEY}
	int SetNorm (int type);
	///Compute the coefficients on the diagonals of the tridiagonal linear system.
        virtual void PrepareDiagonals (size_t start, size_t incr, Vector3d<size_t> & size, size_t axe);
///Compute the diffusivity (Here it only approximates the image gradient)
	virtual void ComputeDiffusivity();


	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Function;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Output;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Spacing;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::GradMag;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::GradMagData;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Dimensions;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::Diag;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::UDiag;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::OutputArray;
	using ImplicitAOSScheme<VOXELIN,VOXELOUT>::GlobalTimeStep;
        using ImplicitAOSScheme<VOXELIN,VOXELOUT>::SetSpacing;

    protected:
	VOXELOUT Conductance;
	VOXELOUT (* ptToNormFunction ) (VOXELOUT , VOXELOUT);
    private:
};





/**
  \brief This class is root abstract class for filters, which can be computed by simple LOD numerical scheme. 
  This class implements the skeleton of numerical semi-implicit LOD (locally one dimensional) scheme. Instances of this class 
  will not produce any usable output. To obtain fully functional filter 
  try to instantiate some offspring of this class. As an example can serve the LODGaussianBlur class.

  There are some linear filters (i.e. Gaussian blur) which have following features: 
  \li They can be computed dimension by dimension
  \li The dimension by dimension computation can be serialised
  (i.e. output of computation in X axe is input of computation in Y axe)
  \li The dimension by dimension computation are commutative
  \li They can be described by partial differential equation
  For computing this filters fast there is posibility to use this multiplicative LOD scheme.
  
  This abstract class implements the skeleton of
  numerical semi-implicit LOD (locally one dimensional) scheme. 
  There is no sister function class like for the (ExplicitScheme,ExplicitSchemeFunction) and (PDESolver, PDESolverFunction) pairs. All the functionality of the implicit numerical scheme is implemented in this class.
  The LOD scheme is absolute stable fo all time steps, there is
  no limitation to the size of time step \f$ \tau \f$.
  The main <b>advantage</b> of solving linear filters with LOD scheme is the <b>constant</b> amount of time which they need
  to convolve the image with convolution <b>kernel of arbitrary size</b>.
  The offsprings of this abstract class modificate the input image by solving following partial differential equation:
  \f[
  u_t = F(u),
  \f]
  where \f$ F(u) \f$ is some linear function of spatial derivatives of <em>u</em>.
  
  The discretisation of the equation is usually written in the vector matrix form:
  \f[

  \prod \limits_{l=1}^{m} (I - \tau A_l(u^{n})) u^{n+1} = u^{n} ,
  
  \f]
  where <em>m</em> is the number of dimensions, \f$\tau\f$ is the time step.
  Solving of one forward iteration of this equation leads to finding the solution of the linear system of equations.

  The LOD scheme solves this equation dimension by dimension by taking solutions of the folowing equation in particular direction (x,y) 
  as input for finding soluton in following direction (y,z).
   \f[
  u^{n+1} =  (I -  \tau A(u^n))^{-1}  u^n 
  \f]
  The solution of above equation in each direction leads to solving the linear system of equations in one iteration step. 
  If we order the voxels extra for each direction, the matrix <em> A </em> becomes threediagonal and there exist fast methods for 
  finding solutions of such matrices. This class uses <b> LAPACK </b> routines to find solutions of three diagonal linear system. 
  The i3d library must be linked with lapack library to obtain fully functionality of this class.


  The implementation of this class is based on the article <br>
  Joachim Weickert, Bart M. ter Haar Romeny, Max A. Viergever, <em> Efficient and Reliable Schemes for Nonlinear Diffusion Filtering </em>, IEEE TRANSACTIONS ON IMAGE PROCESSING, VOL. 6, NO. 3, PP. 398-410, MARCH 1998.

  The typical code for using the linear filters, which are offsprings of this class, is shown bellow. 
  The example code uses the LOD implementation of Gaussian Blur filter (class LODGaussianBlur).
  \verbatim
    .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   LODGaussianBlur<GRAY8,float> G(i,fimg);
   G.SetSigma(4.0);
   G.SetMaximumNumberOfIterations(1);
   G.SetSpacing(1.0,1.0,3.0); // optional if we want to set spacing different from the default settings.
   G.Execute();
   
   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT ImplicitLODScheme : public PDESolver<VOXELIN,VOXELOUT>
{
    public:
	/** One iteration of the LOD scheme will be performed after calling this method. 
	  */
	virtual void ComputeChange();
	ImplicitLODScheme(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	virtual ~ImplicitLODScheme();
	virtual void PrepareDiagonals(int dim);
	using PDESolver<VOXELIN,VOXELOUT>::Function;
	using PDESolver<VOXELIN,VOXELOUT>::Output;
	using PDESolver<VOXELIN,VOXELOUT>::Dimensions;
    protected:
	std::valarray<VOXELOUT> & OutputArray;
	/// The coefficients of the main diagonal are saved in this valraay
	std::valarray<VOXELOUT> Diag;
	/// The coefficients of the supper diagonal are saved in this valraay
	std::valarray<VOXELOUT> SDiag;
	/// Temporal variable
	std::valarray<VOXELOUT> PDiag;
	/// Temporal variable
	std::valarray<VOXELOUT> PSDiag;

    private:
};


/**
  \ingroup if
  \brief This class implements the classical Gaussian Blur filter by solving the following PDE \f$ u_t = \Delta u = (u_{xx} + u_{yy}) \f$.
  The main advantage is the constant speed of computation for any size of standard deviation \f$ \sigma \f$. 
  The speed is comparable to the speed of Fourier transform based filters.
  The second advantage is that this filter preserve the average grey value of the blurred image.
  
  It is well-known that Gaussian convolution with standard deviation \f$\sigma \f$ is equivalent 
  to linear diffusion filtering  (solving the equation \f$ u_t = \Delta u = (u_{xx} + u_{yy}) \f$) for some \f$ T = \sigma^2/2\f$.
  This class implements this filter. For solving it uses the LOD scheme which is fully implemented in the super class ImplicitLODScheme.
  The user must only set the standard deviation and numger of iterations. The time step is computed automatically. 
 
  The implementation of this class is based on the article <br>
  Joachim Weickert, Bart M. ter Haar Romeny, Max A. Viergever, <em> Efficient and Reliable Schemes for Nonlinear Diffusion Filtering </em>, IEEE TRANSACTIONS ON IMAGE PROCESSING, VOL. 6, NO. 3, PP. 398-410, MARCH 1998.

  The example code of Gaussian Blur filter (class LODGaussianBlur).
  \verbatim
    .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   LODGaussianBlur<GRAY8,float> G(i,fimg);
   G.SetSigma(4.0); // Set the standard deviation
   G.SetMaximumNumberOfIterations(1); // Set number of applications of the gaussian
   G.SetSpacing(1.0,1.0,3.0); // Set the spacing
   G.Execute(); // Perform the work of the filter
   
   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT LODGaussianBlur : public ImplicitLODScheme<VOXELIN,VOXELOUT>
{
    public:
	LODGaussianBlur(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	///Set the standard deviation of the gaussian blur
	void SetSigma(VOXELOUT s);
	///Get the standard deviation of the gaussian blur
	VOXELOUT GetSigma();
	virtual void PrepareDiagonals(int dim);
	virtual ~LODGaussianBlur();
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::Function;
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::Output;
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::GlobalTimeStep;
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::Spacing;
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::SDiag;
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::PDiag;
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::PSDiag;
	using ImplicitLODScheme<VOXELIN,VOXELOUT>::Diag;
        using ImplicitLODScheme<VOXELIN,VOXELOUT>::SetSpacing;
        using ImplicitLODScheme<VOXELIN,VOXELOUT>::SetGlobalTimeStep;
	
    protected:
	VOXELOUT sigma;
    private:
};


#endif

/**
  \ingroup if
  \brief This class implements together with class MCFFilterFunction the Curvature Flow anisotropic diffusion filter, which was published by
  Alvarez, Lions and Morel.  As the other anisotropic filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. Moreover it generates the so called morphological scaale space.
  In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = \mathrm{div} ( \nabla u / |\nabla u|)  |\nabla u|\f$. The particular implemantion 
  is based on explicit finite difference solver and therefore there exist some limitations to the time step.
  
  
  The image is smoothed by finding solution of partial differential
  equation
  \f[
   u_t =  \mathrm{div} ( \nabla u / |\nabla u|)  |\nabla u|
  \f]
  where \f$ u_0\f$ is the input image (boundary condition of the PDE).
  In the context of level set equations, the above equation can be written as
   \f[
   u_t = \kappa  |\nabla u|
  \f]

  The idea of this equation is to smooth the image in regions with high curvature (i.e. noise) and do not diffuse the image near significant edges.
  The advantage of the filter is that there are no parameters to adjust the behaviour of the filter. The only value, which 
  can the user adjust is the stopping time (time step + number of iterations) of the diffusion. If we we diffuse the image to the 
  infinity we get the constantly valued grey image.

  The typical setting of coefficients for biomedical images produced in LOM should be: <br> 
  A few of iterations (1 to 10) should be sufficient to to smooth the image. 
  due to the limitation of used explicit numerical discretisation should be the time step
  lower than 0.25 for 2D images and lower than 0.125 for 3D images (See also the example code).
  If there is no time step set, the possible largest is set automatically.
  
  The numerical scheme which finds the solution of the equation is implemented in \c ExplicitScheme class. This class inherits the solution.
 
  The implementation of this class is based on the chapter 16 from book <br>

  J. A. Sethian, <em> Level Set Methods and Fast Marching Methods </em>, Cambridge University Press 1999.

  Example code for using this filter: 

  \verbatim
   .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   MCFFilter<GRAY8,float> CF(i,fimg); // instantiate  the filter  (the two parameters are the input and the output image)
   CF.SetMaximumNumberOfIterations(3); // Set the number of iterations to 2
   CF.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   CF.Execute(); // Perform the work of the filter
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */


template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT MCFFilter : public ExplicitScheme<VOXELIN,VOXELOUT>
{
    public:
	//Constructor
	MCFFilter(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~MCFFilter();
	using ExplicitScheme<VOXELIN,VOXELOUT>::Function;
	using ExplicitScheme<VOXELIN,VOXELOUT>::GlobalTimeStep;
	using ExplicitScheme<VOXELIN,VOXELOUT>::Dimensions;
	using ExplicitScheme<VOXELIN,VOXELOUT>::Output;
	using ExplicitScheme<VOXELIN,VOXELOUT>::SetSpacing;
    protected:
    private:
};

/**
  \ingroup if
  \brief This class implements together with class PMFilterFunction the Perona-Malik anisotropic diffusion filter, which was published by
  Perona and Malik. This filter was historical first published anisotropic diffusion filter and therefore is fundamental.
  As the other anisotropic filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = \mathrm{div} (g(|\nabla u|) \nabla u)\f$. The particular implemantion 
  is based on explicit finite difference solver and therefore there exist some limitations to the time step. If
  you want to use the schema with no timestep limitation take a look to the documentation of AOSPMFilter. 
  
  
  The Perona Malik Filter  is the historical first anisotropic diffusion filter. The image is smoothed by finding solution of partial differential
  equation
  \f[
   u_t = \mathrm{div} (g(|\nabla u|) \nabla u)
  \f]
  where \f$ g(s) \f$ is decreasing function of the image gradient, and \f$ u_0\f$ is the input image (boundary condition of the PDE).
  The idea of this equation is to smooth the image in regions with almost no gradient and do not diffuse the image near significant edges. 
  The strength of the diffusion is controled by the diffusivity function <em>g</em>.
   The diffusivity <em> g </em> is in original work of Perona and Malik computed by:
   \f[
   g(s) = \frac{1}{1+\left(\frac{s}{ \lambda}\right )^2}
   \f]
   Perona and Malik considered also an alternative diffusion function:
    \f[
   g(s) = \mathrm{exp}(-(s/\lambda)^2)
   \f]
   An consequently Black, Sapiro, Marimont, Heeger proposed the usage of Tukey Biweight norm:
    \f[
\begin{array}[b]{l}
   g(s) = [1 - (2(s/\lambda))^2]^2 \quad |s| \le \lambda/\sqrt{2} \\
   g(s) = 0 \quad \rm{otherwise} \\
   \end{array}
   \f]
   See the image bellow, there are displayed all three norms. The meaning of those norms is following: All three enables the diffusion 
   on pixels with the gradient lower than \f$\lambda \f$. All three stops the diffusion on pixels with image gradient higher than \f$\lambda\f$, but they
   differ on the strictness of the stopping.
   
   \image html diffusivitypm.gif "Diffusivity g function: lambda = 5.0, left: original PM norm, middle: alternative PM Norm, right: Tukey Biweight Norm"

  The typical setting of coefficients of <em> g</em> function for biomedical images produced in LOM should be: <br> 
  \f$\lambda\f$ between 1 and 10.<br>
  All three norms can be used to produce meaningfull output.<br>
  A few of iterations (1 to 10) should be sufficient to to smooth the image. 
  due to the limitation of used explicit numerical discretisation should be the time step
  lower than 0.25 for 2D images and lower than 0.125 for 3D images (See also the example code).
  If there is no time step set, the possible largest is set automatically.
  
  The numerical scheme which finds the solution of the equation is implemented in \c ExplicitScheme class. This class inherits the solution.
 
  The implementation of this class is based on the articles <br>
  Pietro Perona and Jitendra Malik, <em> Scale-Space and Edge Detection Using Anisotropic Diffusion</em> IEEE Transactions on Pattern Analysis and Machine Intelligence. Vol. 12. No. 7. July 1990.
  Michael J. Black, Guilermo Sapiro, David H. Marimont, David Heeger, <em>Robust Anisotropic Diffusion </em>, IEEE Transactions on Image Processing, Vol. 7. No. 3. March 1998
  The example code uses the AOS implementation of PM diffusion filter.

  \verbatim
   .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   PMFilter<GRAY8,float> PM(i,fimg); // instantiate  the filter  (the two parameters are the input and the output image)
   PM.SetMaximumNumberOfIterations(3); // Set the number of iterations to 2
   PM.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   PM.SetConductance(3.0); // Set the conductance parameter to 3.0
   PM.SetNorm(ORIGINALPM); // Set norm to original PM norm
   PM.Execute(); // Perform the work of the filter
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT PMFilter : public ExplicitScheme<VOXELIN,VOXELOUT>
{
    public:
	PMFilter(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	virtual ~PMFilter();
	/// Set the norm function. Possible values are ORIGINALPM, ALTERNATIVEPM and TUKEY.
	int SetNorm (int type);
	/// Set the \f$\lambda \f$ conductance parameter.
	void SetConductance(VOXELOUT c);
	/// Get the \f$\lambda \f$ conductance parameter.
	VOXELOUT GetConductance();
	using ExplicitScheme<VOXELIN,VOXELOUT>::Function;
	using ExplicitScheme<VOXELIN,VOXELOUT>::GlobalTimeStep;
	using ExplicitScheme<VOXELIN,VOXELOUT>::Dimensions;
	using ExplicitScheme<VOXELIN,VOXELOUT>::Output;
	using ExplicitScheme<VOXELIN,VOXELOUT>::SetSpacing;

    protected:
    private:
};


/**
  \ingroup if
  \brief This class implements together with class MCDEFilterFunction the Modified Curvature Diffusion Flow anisotropic diffusion filter, which was published by
  Whitaker and Xue.  As the other anisotropic filters, this filter smooths the image in the relatively continuos region
  and do not smooth the significante edges. Moreover it generates the so called morphological scale space.
  In the typical output image is suppresed the noise and the edges remain sharp and well localised.
  The diffused image is the solution of the equation \f$ u_t = |\nabla u| \cdot \mathrm{div} \left( g(| \nabla u|)\frac{ \nabla u }{ |\nabla u|} \right) \f$. The particular implementation 
  is based on explicit finite difference solver and therefore there exist some limitations to the time step.
  
  
  The image is smoothed by finding solution of partial differential
  equation
  \f[
  u_t = |\nabla u| \cdot \mathrm{div} \left( g(| \nabla u|)\frac{ \nabla u }{ |\nabla u|} \right)
  \f]
  where \f$ u_0\f$ is the input image (boundary condition of the PDE).

  The idea of this equation is to smooth the image in regions with high curvature (i.e. noise) and do not diffuse the image near significant edges.
  The diffusion is more agresive in the interior of objects and there is almost no diffusion on the objects boundaries due to the conductance function.
  For the detailed description of the conductance function \f$ g(|\nabla u|) \f$ see the documentation if the class PMFilter.

  The typical setting of coefficients for biomedical images produced in LOM should be: <br> 
  A few of iterations (1 to 10) should be sufficient to to smooth the image. 
  due to the limitation of used explicit numerical discretisation should be the time step
  lower than 0.25 for 2D images and lower than 0.125 for 3D images (See also the example code).
  If there is no time step set, the possible largest is set automatically.
  
  The numerical scheme which finds the solution of the equation is implemented in \c ExplicitScheme class. This class inherits the solution.
 
  The implementation of this class is based on the article <br>

  R. T. Whitaker, X. W. Xue, <em> Variable Conductance , Level Set Curvature For Image Denoising</em>

  Example code for using this filter: 

  \verbatim
   .....
   
   Image3d<GRAY8> i;
   Image3d<float> fimg;
   i.ReadImage('input.tif'); // read input image
   MCDEFilter<GRAY8,float> CF(i,fimg); // instantiate  the filter  (the two parameters are the input and the output image)
   MCDE.SetMaximumNumberOfIterations(3); // Set the number of iterations to 2
   MCDE.SetSpacing(1.0,1.0,2.0); // Set the spacing of spatial discretisation to 1,1,2
   MCDE.Execute(); // Perform the work of the filter
   MCDE.SetNorm(ORIGINALPM); // Set norm to original PM norm
   FloatToGrayNoWeight(fimg,i); //Convert the output float image to gray8 image
   i.SaveImage('output.tif'); // save the output of the filter

   ......
  \endverbatim
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2005
 */



template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT MCDEFilter : public ExplicitScheme<VOXELIN,VOXELOUT>
{
    public:
	MCDEFilter(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	virtual ~MCDEFilter();
	/// Set the norm function. Possible values are ORIGINALPM, ALTERNATIVEPM and TUKEY.
	int SetNorm (int type);
	/// Set the \f$\lambda \f$ conductance parameter.
	void SetConductance(VOXELOUT c);
	/// Get the \f$\lambda \f$ conductance parameter.
	VOXELOUT GetConductance();
	using ExplicitScheme<VOXELIN,VOXELOUT>::Function;
	using ExplicitScheme<VOXELIN,VOXELOUT>::GlobalTimeStep;
	using ExplicitScheme<VOXELIN,VOXELOUT>::Dimensions;
	using ExplicitScheme<VOXELIN,VOXELOUT>::Output;
	using ExplicitScheme<VOXELIN,VOXELOUT>::SetSpacing;

    protected:
    private:
};

/**
\ingroup sm
  \brief This class implements simple the Kmeans segmentation algorithm for two means. Documentation TBA
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2006
 */



template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT KMeansLS : public PDESolver<VOXELIN,VOXELOUT>
{
    public:
	// 
	virtual void Initialize();
	virtual void InitializeIteration();
	virtual void ComputeChange();
	virtual bool Convergence();
	//Constructor
	KMeansLS(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	void SetLambda(VOXELOUT l1, VOXELOUT l2);
//	void SetCompMask (Image3d<bool> & i);
	void SetMask (Image3d<bool> * m);
	void SetThreshold(VOXELIN t);
	void SetInitValues(VOXELOUT l, VOXELOUT h);
	void SetInitBoundaryParams(VOXELOUT r, VOXELOUT g);
	//Destructor
	virtual ~KMeansLS();


	virtual void ComputeMeans();
	void GetMeans (VOXELOUT & m1, VOXELOUT & m2);

	using PDESolver<VOXELIN,VOXELOUT>::Function;
	using PDESolver<VOXELIN,VOXELOUT>::Output;
	using PDESolver<VOXELIN,VOXELOUT>::Input;
	using PDESolver<VOXELIN,VOXELOUT>::ElapsedIteration;
	using PDESolver<VOXELIN,VOXELOUT>::MaximumIteration;
	VOXELOUT c1sum, c2sum;

    protected:
	VOXELOUT lambda1, lambda2;
	VOXELOUT InitLow, InitHigh;
	double c1, c2, lastc1sum, lastc2sum;
	Image3d<bool> * InitMask;
	VOXELIN Thres;
    private:
	VOXELOUT initradius, initgap;
	
};

#ifdef WITH_LAPACK
/**
\ingroup sm
  \brief This class implements the threshold dynamics approximation of the Chan-Vese functional. Documentation TBA
  \author Jan Hubený xhubeny@fi.muni.cz
  \date 2006
 */

template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT ThresholdActiveContours : public KMeansLS<VOXELIN,VOXELOUT>
{
    public:
	virtual void ComputeChange();
	virtual bool Convergence();
	virtual void SetGlobalTimeStep(VOXELOUT t);

	ThresholdActiveContours(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	virtual ~ThresholdActiveContours();
	void Threshold(VOXELOUT t);
	void SetLambda(VOXELOUT l);
	void SetInnerSteps(size_t s);
	void PrepareDiagonals(int dim); 
        void ComputeTauLambda();
	void CallLinearSystemSolver(int rad, int vec, VOXELOUT * Diag, VOXELOUT * SDiag, VOXELOUT * rowU, int info);
	void RightHandSide(std::valarray<VOXELIN> & rf, std::valarray<VOXELOUT> & ru, size_t maxi);
	void RightHandSideY(std::valarray<VOXELIN> & rf, std::valarray<VOXELOUT> & ru, size_t maxi, size_t offsetY);
	void RightHandSideX(std::valarray<VOXELIN> & rf, std::valarray<VOXELOUT> & ru, size_t maxi, size_t sizeX, size_t sizeY);

        void SetWithThreshold(bool t);
	bool Enough (Image3d<VOXELOUT> & input, bool WithThreshold);
	void ComputeCConst();

	virtual void ComputeMeans();

	using KMeansLS<VOXELIN,VOXELOUT>::Output;
	using KMeansLS<VOXELIN,VOXELOUT>::GlobalTimeStep;
	using KMeansLS<VOXELIN,VOXELOUT>::lambda1;
	using KMeansLS<VOXELIN,VOXELOUT>::Input;
	using KMeansLS<VOXELIN,VOXELOUT>::c1;
	using KMeansLS<VOXELIN,VOXELOUT>::c1sum;
	using KMeansLS<VOXELIN,VOXELOUT>::c2sum;
	using KMeansLS<VOXELIN,VOXELOUT>::lastc1sum;
	using KMeansLS<VOXELIN,VOXELOUT>::lastc2sum;
	using KMeansLS<VOXELIN,VOXELOUT>::c2;
	using KMeansLS<VOXELIN,VOXELOUT>::InitLow;
	using KMeansLS<VOXELIN,VOXELOUT>::InitHigh;
	using KMeansLS<VOXELIN,VOXELOUT>::ElapsedIteration;
	using KMeansLS<VOXELIN,VOXELOUT>::Spacing;
	using KMeansLS<VOXELIN,VOXELOUT>::Dimensions;
	using KMeansLS<VOXELIN,VOXELOUT>::MaximumIteration;
	using KMeansLS<VOXELIN,VOXELOUT>::SetSpacing;

    protected:
	bool WithThreshold;
	VOXELOUT TimeStep, TauLambda;
	size_t InnerSteps;
	std::valarray<VOXELOUT> Diag, SDiag, PDiag, PSDiag;
	std::valarray<VOXELOUT> Buffer;
	
    private:
	double sigma1;
	double sigma2;
	VOXELOUT CConst;
	size_t lastVolume, Volume;
};

template <class VOXEL> i3d::Vector3d<float> ComputeNormedSpacing (i3d::Image3d<VOXEL> & img);
/*
template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT AOSChanVese :  public KMeansLS<VOXELIN,VOXELOUT>

{
    public:
	virtual void Initialize();
	//Constructor
	AOSChanVese(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out);
	//Destructor
	virtual ~AOSChanVese();
	///This function computes the diffusivity <em>g </em> function
	virtual void ComputeDiffusivity();
	///Set the value of the exponent
	void SetExponent(VOXELOUT exp);
	///Get the value of the exponent
	VOXELOUT GetExponent();
	///Set the value of beta coefficient
	void SetBeta(VOXELOUT B);
	///Get the value of beta coefficient
	VOXELOUT GetBeta();
	void SetMu (VOXELOUT m);
	void SetEpsilon(VOXELOUT e);
	
	void ComputeHeavisideAndDelta();
	void RightHandSide(valarray<VOXELIN> & rf, valarray<VOXELOUT> & ru, valarray<VOXELOUT>& rd, size_t maxi);
        virtual void PrepareDiagonals (size_t start, size_t incr, Vector3d<size_t> & size, size_t axe);
	virtual void ComputeChange();
	virtual void ComputeMeans();
	
	valarray <VOXELOUT> * HeavisideData;
	valarray <VOXELOUT> * DeltaData;

	GradientMagnitudeEstimator<VOXELOUT> * GradMag;
	/// Pointer to valarray with values of gradient estimation.
	valarray<VOXELOUT> * GradMagData;

    protected:
	VOXELOUT Exponent;
	VOXELOUT Beta;
	VOXELOUT Epsilon;
	valarray<VOXELOUT> Diag, SDiag;
	valarray<VOXELOUT> Buffer;
	VOXELOUT Mu;
	
    protected:
    private:
};
*/

#endif
/*
template < class VOXEL > class I3D_ALGO_EXPORT FastActiveContoursFunction:public
        ExplicitSchemeFunction<VOXEL>
    {
      public:
        /// Udates the Globaltime step  from the value returned by \c ComputeUpdate() method.
        virtual void UpdateTimeStep(size_t * neighbors, size_t index,VOXEL tempTimeStep);
      FastActiveContoursFunction(Image3d < VOXEL > &data);
        virtual ~ FastActiveContoursFunction();
        void SetLambda(VOXEL l1, VOXEL l2);
        void SetMu(VOXEL m);
      private:
        VOXEL mu, lambda1, lambda2;
        VOXEL c1, c2;
        size_t n, m;
        VOXEL length;
    };

template < class VOXELIN, class VOXELOUT > class I3D_ALGO_EXPORT FastActiveContours:public ExplicitScheme < VOXELIN, VOXELOUT>
    {
      public:
      FastActiveContours(Image3d < VOXELIN > &in, Image3d < VOXELOUT > &out);
        virtual ~ FastActiveContours();
        void SetLambda(VOXELOUT lambda1, VOXELOUT lambda2);
        void SetMu(VOXELOUT mu);
        void SetMask (Image3d<bool> * m);
	void SetThreshold(VOXELIN t);
	virtual void ApplyChange();
	virtual bool Convergence();
	/// Initialize the computation.
	virtual void Initialize();

      protected:
      private:
	VOXELOUT Thres;
	Image3d<bool> * InitMask;
    };

*/


/*
template <class INDEXTYPE, class DATATYPE> struct I3D_ALGO_EXPORT NarrowBandNode
{
    INDEXTYPE index; 
    DATATYPE data;
    unsigned char flags;
};
*/


/*
template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT LevelSetNarrowBand : public PDESolver<VOXELIN,VOXELOUT>
{
    
    public:
	LevelSetNarrowBand(Image3d<VOXELIN> & in, Image3d<VOXELOUT> & out);
	~LevelSetNarrowBand(){};
	void SetInnerRadius(float in){InnerRadius = in;};
	void SetRadius(float in){Radius = in;};
	void SetRadius(float inner, float rad){InnerRadius = inner; Radius = rad;};
    protected:
	vector<NarrowBandNode<size_t, VOXELOUT> > nodes;
	float InnerRadius;
	float Radius;
    private:
	
};
*/
/*
template <class VOXEL> class I3D_ALGO_EXPORT ExplicitSchemeFunctionSegmentation : 
    public ExplicitSchemeFunction<VOXEL>
{
    public:

	virtual VOXEL ComputeUpdate(size_t * neighbors,size_t center);
	//Contructor
	ExplicitSchemeFunctionSegmentation(Image3d<VOXEL> & data);
	//Destructor
	virtual ~ExplicitSchemeFunctionSegmentation();
    protected:
    private:
};
*/

/*
template <class VOXELIN, class VOXELOUT> class I3D_ALGO_EXPORT LSFullSegmentation : public ExplicitScheme<VOXELIN,VOXELOUT>
{
    public:
	// 
	virtual void Initialize();
	virtual void InitializeIteration(){};
	//Constructor
	//Destructor
	LSFullSegmentation(Image3d<VOXELIN>& in, Image3d<VOXELOUT> & out):
	    ExplicitScheme<VOXELIN,VOXELOUT>(in,out){};
	virtual ~LSFullSegmentation(){};

    protected:
    private:
};
*/


//template <class VOXELIN, class VOXELOUT> void HonzovaFce (Image3d<VOXELIN> & ImgIn, Image3d<VOXELOUT> & ImgOut, Image3d<VOXELOUT> & Speed);
};

#endif

