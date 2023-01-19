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

/**
 *  FILE: shape.h
 *
 *  definitions of functions for shape characterization on binary images
 *
 *  Zdenek Hrncir, 2004 (60514@mail.muni.cz)
 */

#ifndef __BINARYSHAPE_H__
#define __BINARYSHAPE_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <map>
#include <vector>
#include "image3d.h"
#include "regions.h"


namespace i3d {

  typedef std::vector< const Vector3d<size_t>* > BoundaryNeighbours;

  struct I3D_ALGO_EXPORT NetBoundaryNode
  {
    BoundaryNeighbours boundaryNeighbours;
    float curvature;
  };
  
  /* NetBoundary is graph - nodes are boundary voxels and edges are between
    neighbouring voxels
  */
  typedef  std::map< Vector3d<size_t>,  NetBoundaryNode> NetBoundary;

  /** axes and their values respectively,
     axes are orthonormal and val1 > val2 > val3,
     therefore axe1 is major axe, axe3 is minor axe
    */
  struct I3D_ALGO_EXPORT PrincipalAxes
  {
    Vector3d<float>  axe1, axe2, axe3;
    float            val1, val2, val3;
  };

 /** Shape is wrapping object for all shape characterisation functions.
     It is designed to work with binary Image3d as well as with all LabeledImage3d types.
	 Therefore it is necessary to specify
	 the same LABEL template class as the LABEL class of LabeledImage3d to be used.\n
     For use with binary images simply use Shape<bool>
    */
 template <class LABEL>
 class I3D_ALGO_EXPORT Shape 
 {
   const Image3d<LABEL> *img;
   LABEL label;
   bool is3D;
   bool isIsometric;
   size_t volume;  // area for 2D
   size_t surface; // perimeter for 2D
   float surfaceUm;// perimeter for 2D
   Vector3d<size_t> centroid;
   Boundary boundary;
   size_t curvatureDist;  //distance of voxels in curvature, 0 = curvature not computed
   std::vector< float > curvature;
   std::map<int, unsigned long> statMoments;
   std::map<int, long> cStatMoments;
   PrincipalAxes principalAxes;
   float rectangularity;
   float symmetry1, symmetry2, symmetry3;
   float fF, nEnergy;
   double bendingE;

   bool isVolume, isSurface,
        isSurfaceUm, isCentroid, isBoundary, isCurvature,
	isPrincipalAxes, isRectangularity,
	isPrincipalSymmetry,
	isNFDs2d, isBendingE;

   void SwitchAllIsIndicatorsOff();

  /** 2D version of boundary*/
  Boundary GetBoundary2d(const Neighbourhood& nbh);

  /** 3D version of boundary*/
  Boundary GetBoundary3d(const Neighbourhood& nbh);

  /** surface in micrometers - only for 3D*/
  float SurfaceUm3d();

  /** rectangularity - only for 2D*/
  float Rectangularity2d();

  /** rectangularity - only for 3D*/
  float Rectangularity3d();
 public:

   Shape() {}

  /**
  Constructor. \n  
  @param _img input image, you can use LabeledImag.
  @param _label label of object to be measured, for binary images use true
  */
   Shape(const Image3d<LABEL> *_img, LABEL _label = 0);

   /**Call this function if you have made changes in input image, otherwise measurments could be incorrect*/
   void EraseValues();

   /** To use Shape for another image 
       @param _img input image, you can use LabeledImag.
   */
   void SetImage(const Image3d<LABEL> *_img);

   /** To use Shape for another object in image with different label
       @param _label label of object to be measured, for binary images set true
   */
   void SetLabel(const LABEL _label);

/**Area of 2D object in pixels*/
   size_t Area();

 /**Volume of 3D object in voxels (For 2D images similar as calling Area)*/
 size_t Volume();

 /** Area of 2D object in micrometers^2*/
 float AreaUm();

 /** Volume of 3D object in micrometers^3 (um).
    (For 2D images similar as calling AreaUm)*/
 float VolumeUm();

 /** 2D/3D - Finds boundary with implicit neighbourhoods
        - nb2D_4 for 2D objects - boundary is 8-connected
        - nb3D_6 for 3D objects - boundary is 26-connected
        .
     For 2D images the boundary sequence is in chain,
     i.e. bdr[i+1] and bdr[i] are neighbours. \n
	 More precisely it finds "intermal boundary". Voxel belongs into this boundary
	 if it has non-object voxel in given neighbourhood*/
  Boundary GetBoundary();

  /** 2D/3D - Finds boundary with given neighbourhood.\n
     for 2D images is allowed:
        - nb2D_8: boundary is 4-connected
        - nb2D_4: boundary is 8-connected
        .
	 All neighbourhoods for 3D images allowed. \n
     For 2D images the boundary sequence is in chain,
     i.e. bdr[i+1] and bdr[i] are neighbours. \n
	 More precisely it finds "intermal boundary". Voxel belongs into this boundary
	 if it has non-object voxel in given neighbourhood*/
  Boundary GetBoundary(const Neighbourhood& nbh);

  /** NetBoundary constructor, so far it is unuseful. It was ment
      for extremity (vertices) points finding */
  NetBoundary NetBoundary3d();

  /** Perimeter of 2D object in pixels by given neighbourhood
        - nb2D_4: 8-connected boundary
        - nb2D_8: 4-connected boundary
        .
      Perimeter is simply number of pixels in boundary.
  */
  size_t Perimeter(const Neighbourhood& nbh = nb2D_4);

  /** Surface of 3D object in voxels \n
	 It uses boundary constructor (GetBoundary) with implicit nb3D_6 neighbourhood.
	 Surface is simply number of voxels in boundary.
	 (For 2D images similar as calling Perimeter)	 
	 */
  size_t Surface();

  /** Surface of 3D object in voxels by given neighbourhood. \n
     It uses boundary constructor (GetBoundary) with given neighbourhood. 
	 Surface is simply number of voxels in boundary.
	 */
  size_t Surface(const Neighbourhood& nbh);

  /** Perimeter in micrometers (um) of 2D object \n
      Uses simple linear aproximation of 8-connected boundary*/
  float PerimeterUm();

  /** Surface of binary image in microns by
     3D-6 neighbourhood aproximation*/
  float SurfaceUm();

  /** 2D/3D Roundness is based on ratio between area and perimeter(volume and surface).
  It is normalized to be in range (0,1]. 1 stands for circle (ball). The less compact is the shape the lower is roundness. 
  */
  float Roundness();


 /**  Curvature of every boundary voxel of 2D object. \n
      Curvature(img).size() == Boundary(img).size()
      and Curvature(img)[i] is curvature of voxel Boundary(img)[i].\n
      Curvature is from interval <-1, 1> where -1 stands for straight boundary and
        1 stands for total tips (convex or concave).

      Radius must be >1. It influences how much the curvature measure
      is sensitive to noise. The higher the radius, the less sensitivity to noise
      but also to little details.
  */
 std::vector< float > Curvature2d( size_t dist);


 /**  computes curvature using 5 neighbouring voxels B-spline approximation. \n
     This curvature corresponds with connected (non-discrete) curve
     curvature definition.
     For boundary shorter than 5 voxels doesn't computation make sense.  
	 \sa Curvature2d*/
 std::vector< float > BSCurvature2d();


 /** Bending energy of 2D object. \n It is average of curvature^2 from all boundary points.
     BSCurvature2d is used. The higher the bending energy is the more curved and complicated is the shape.*/
 double BendingEnergy2d();

 /** center of mass. */
 Vector3d<size_t> Centroid();

 /**2D/3D Statistical moment. \n
     @param ex, ey, ez    exponent coeficients
     moment for 3D is defined as  Sum(x^ex * y^ey * z^ez * img3D(x,y,z))
         for all x,y,z values combinations. \n
     note that :
       - StatMoment(img, 1, 0, 0) / Volume(img)   ==   x value of center of object
       - StatMoment(img, 0, 1, 0) / Volume(img)   ==   y value of center of object
       - StatMoment(img, 0, 0, 1) / Volume(img)   ==   z value of center of object
       .
     It is suitable also for 2D object, just leave 'ez' zero.  
   */
  unsigned long StatMoment( unsigned short ex, unsigned short ey, unsigned short ez=0);

  /** statistical moments but in micrometers. \sa StatMoment*/
  float StatMomentUm( unsigned short ex, unsigned short ey, unsigned short ez=0);


 /**2D/3D Central statistical moment. \n
    these are important to obtain translation invariance - useful for calculating eigenaxes and symmetry
     ex, ey, ez  - are exponent coeficients
     moment for 3D is defined as  Sum((x -x')^ex * (y-y')^ey * (z-z')^ez * img3D(x,y,z))
         for all x,y,z values combinations, x',y',z' denotes x,y,z center coordinates
     Suitable for 2D objects. \sa StatMoment.
   */
  long CStatMoment( unsigned short ex, unsigned short ey,
                   unsigned short ez=0);


  /**Computes central statistical moment in micrometers, takes into account resolution
    These are important to obtain translation invariance - useful for calculating eigenaxes and symmetry.
     ex, ey, ez  - are exponent coeficients
     moment for 3D is defined as  Sum((x -x')^ex * (y-y')^ey * (z-z')^ez * img3D(x,y,z))
         for all x,y,z values combinations, x',y',z' denotes x,y,z center coordinates
		 Suitable for 2D objects. \sa StatMomentUm.
   */
  float CStatMomentUm( unsigned short ex, unsigned short ey,
                   unsigned short ez=0);


  /**minimal, maximal and mean radius. Result is in micrometers. Euclidean metric is used.*/
  void Radius(float &min, float &max, float &mean);


  /** computes principal axes and their values
     using LAPACK ssyev (single(real) - symmetric - eigen vectors) function
     if input image isn't isometric (i.e. in Resolution  x ,y ,z  aren't the same ),
     than resolution is taken into account and statistical moments
     and eigen axes/values are computed in micrometers.
     */
  PrincipalAxes GetPrincipalAxes();

  /** Elongation, defined as ratio of eigenvalues, for 2D objects. 
      Elongation is in range <1,inf), the higher is the value the more elongated is
	  the shape.	  
    */  
  void Elongation2d( float& elongation);

  /** Elongation, defined as ratio of eigenvalues, for 3D objects. Both majorElongation and minorElongation values
      are in range <1,inf). Some typical shape values:
      - major == 1, minor == 1 : ball shape
      - major >> 1, minor == 1 : pole shape
      - major == 1, minor >> 1 : disc shape
      - major >> 1, minor >> 1 : generic shape
    */
  void Elongation3d( float& majorElongation, float& minorElongation);

  /** 2D/3D Elongation. Deprecated function, for 2D returns minorElongation=infinity.
      Please use Elongation2d or Elongation3d.
    */
  void Elongation( float& majorElongation, float& minorElongation);

  /** 2D/3D Symmetry with respect to given plane or ray.     
     @param normVect
	 - normal vector in case of plane symmetry
	 - direction vector in case of ray symmetry

	 @param center point in plane or ray.   

	 @param symType 
	 - 'P' ... symmetry with respect to plane given by normal vector and one point ( center )
     - 'R' ... symmetry with respect to ray given by it's direction vector nad one point ( center )

	 symmetry is defined as ratio  Sym / ( Sym + 2*Asym), where
     - Sym .... sum of voxels having their symmetric mirrors in object
     - Asym ... sum of voxels without their symmetric mirrors in object

	 Symmetry is in range (0,1>, 1 means full symmetry.
  */
  float  Symmetry( Vector3d<float> normVect, Vector3d<size_t> center, char symType);


  /** 2D/3D Symmetry with respect to principal planes (those are defined by
     principal axes as normal vectors and center)
     sym1 is defined by axe1 etc.
	 All values are from range (0,1>. Symmetric objects has higher values.
	 For 2D objects sym3 is always 1.
	 \sa Symmetry.*/
  void  PrincipalSymmetry( float &sym1, float &sym2, float &sym3);

   /** Rectangularity is based on recognizing MEP (minimum enclosing prism),
     MEP can be defined as minimal prism containing whole object, having
     edges perpendicular with object main axes.
	 Rectangularity is in range (0,1>. Rectangles has value 1.
  */
  float Rectangularity();

  /**energy of first koeficients obtained by Fast Fourier Transform,
     it means that only low frequencies are assumed.
	 @param  koefNumber number of coefficients taken into account (usually something
	 about ten coefficients are important)
	 */
  float LPEnergy2d(size_t coefNumber);

  /**Normalized Fourier Descriptors : FF and Normalized Energy. These are object size
    independent.*/
  void NFDs2d(float& FF, float& NEnergy);

  };
}
#endif
