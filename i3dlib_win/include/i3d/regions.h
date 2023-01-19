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
 * FILE: regions.h
 *
 * labeled 3d image
 * region labeling algorithm (for symmetric neigbourhoods)
 *
 * Pavel Matula (pam@fi.muni.cz) 2001
 * Petr Mejzlík (mejzlik@fi.muni.cz) 2001
 */

  /*
    Basic definitions:
    ~~~~~~~~~~~~~~~~~~
    NEIGHBOURHOOD is a set of offsets. The offsets point to all neighbours
    of a voxel in Image3d. 
    
    SYMMETRIC NEIGHBOURHOOD is a neigbourhood N, which satisfies the
      following criterion:
      if (x, y, z) is in N then (-x, -y, -z) is also in N.
    
    PATH (with respect to neighbourhood N) is a sequence of voxels 
      v[1], v[2], ..., v[n] where v[i+1]-v[i] is in N for each i = 1, ..., n-1

    COMPONENT is a set of voxels of an image

    REGION or CONNECTED COMPONENT (with respect to neighbourhood N) is 
      a component C where for each voxels u and v there exists a path (with 
      respect to neighbourhood N) from u to v.

    LABELED IMAGE is an image where a voxel intensity indicates component
      index to which the voxel belongs

    REGION LABELING is a task to find all regions (connected components) of 
      the same intensity voxels in an image. The output is a labeled image
      where all components are regions
  */

//#define VERBOSE_DEBUG 

#ifndef __REGIONS_H__
#define __REGIONS_H__

#ifdef __GNUG__
#pragma interface
#endif

#include <limits>
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <iostream>
#include "image3d.h"
#include "neighbours.h"
#include "histogram.h"

namespace i3d 
{

/// Set of voxels forming the boundary.
using Boundary = std::vector<Vector3d<size_t>>;


  /*
    a structure describing properties of a component in an image
   */

template <class LABEL, class VOXEL>
class I3D_ALGO_EXPORT ComponentInfo {
public:

    using Container = std::map<LABEL, ComponentInfo>;

    VOI<UPIXELS> voi; // bounding VOI of component
    size_t volume;   // volume of component, i.e. number of voxels
    // size_t holes;  // number of holes in the object
    bool border; // is the object on the edge of the image?
    VOXEL voxel_value; // contents of each voxel of the component

    ComponentInfo() : voi(), volume(0), border(false) {}
    ComponentInfo(const VOI<UPIXELS> &voi_, const size_t volume_,
		    const VOXEL voxel_value_, const bool border_)
      : voi(voi_), volume(volume_), border(border_), voxel_value(voxel_value_)
    {}
    // Copy constructor:
    ComponentInfo(const ComponentInfo& c)
      : voi(c.voi), volume(c.volume), border(c.border),
        voxel_value(c.voxel_value)
    {}
    ComponentInfo &operator+= (const ComponentInfo &ri) {
      voi += ri.voi;
      volume += ri.volume;
      border = border || ri.border;
      return *this;
    };
	UPIXELS::T_size voi_volume(void) const {
		return voi.Size();
	};
};

template <class LABEL, class VOXEL>
std::ostream & operator <<(std::ostream &o, const ComponentInfo<LABEL, VOXEL> &ci) {
	o << "VOI: " << ci.voi << '\n'
	  << "Volume: " << ci.volume << '\n'
	  << "Is border: " << ci.border << '\n'
	  << "ID: " << int(ci.voxel_value) << '\n';
  return o;
};

  /* some predicates defined on ComponentInfo */

  template <class LABEL, class VOXEL>
  struct volume_less: 
    public std::function<bool(typename ComponentInfo<LABEL, VOXEL>::Container, size_t)> {
    bool operator() (const std::pair<const size_t, ComponentInfo<LABEL, VOXEL> >& x, const std::pair<const size_t, ComponentInfo<LABEL, VOXEL> > & y) const 
    {return x.second.volume < y.second.volume;}
  };
  
template <class LABEL, class VOXEL>
struct component_volume_less: 
	public std::function<bool(ComponentInfo<LABEL, VOXEL>, size_t)> {
    bool operator() (const ComponentInfo<LABEL, VOXEL>& x, const size_t y) const 
    {return x.volume < y;}
};

template <class LABEL, class VOXEL>
struct component_volume_greater: 
	public std::function<bool(ComponentInfo<LABEL, VOXEL>, size_t)> {
    bool operator() (const ComponentInfo<LABEL, VOXEL>& x, const size_t y) const 
    {return x.volume > y;}
};
  
template <class LABEL, class VOXEL>
struct density_less: 
	public std::function<bool(ComponentInfo<LABEL, VOXEL>, size_t)> {
    bool operator() (const ComponentInfo<LABEL, VOXEL>& x, const size_t y) const 
    {return (x.volume / x.voi_volume() < y);}
};

template <class LABEL, class VOXEL>
struct component_touch_border:
        public std::function<bool(ComponentInfo<LABEL, VOXEL>)> {
	    bool operator() (const ComponentInfo<LABEL, VOXEL>& x) const
			        {return x.border;}
	};

template <class T>
struct true1:
        public std::function<bool(T)> {
	    bool operator() (const T& x) const
			        {return true;}
	};



/* Remove() removes all components (stored in an indexed container), for 
 * which the predicate is true.
*/

template <class Index, class Container, class Predicate>
void Remove(std::map<Index, Container>& cont, Predicate pred) {
    typename std::map<Index, Container>::iterator i;
    std::map<Index, Container> tmp = cont;
    cont.clear();
    for (i = tmp.begin(); i != tmp.end(); ++i) {
    #ifdef VERBOSE_DEBUG 
      cout <<"Remove: " <<  i->first << " " << i->second.volume << " " << pred(i->second) << endl;
    #endif
      if (!pred(i->second)) {
        cont[i->first] = i->second;
      }
    }
}

/* RemoveBlack() removes all components (stored in an indexed container), 
 * which are formed by black (==0) voxels.
*/

template <class Container>
void RemoveBlack(std::map<size_t, Container>& cont) {
    typename std::map<size_t, Container>::iterator i;
    std::map<size_t, Container> tmp = cont;
    cont.clear();
    for (i = tmp.begin(); i != tmp.end(); ++i) {
      if (i->second.voxel_value != 0) {
        cont[i->first] = i->second;
      }
    }
}

/* CreateObjectsFromComponents() takes two input variables
 * of types Image and LImage and an indexed container with
 * elements of type Component and constructs a new indexed
 * container containing Objects as follows:
 *
 * The Objects container is cleared and for every i, 
 * objects[i] is set to Object(img, limg, components[i], i), 
 * if components[i] satisfies the predicate pred(), 
 * where pred() takes one argument of type Component.
 *
 * Obviously, the operator[] must be available in both containers and 
 * the constructor Object(const Image&, const Component&) must be defined.
 */

template <class Image, class LImage, class Component, class Object, class Predicate>
void CreateObjectsFromComponents(const Image& img, const LImage& limg,
                                 const std::map<size_t, Component>& components,
                                 std::map<size_t, Object>& objects,
                                 Predicate pred)
{
	objects.clear();
	typename std::map<size_t, Component>::const_iterator i;
	for (i = components.begin(); i != components.end(); i++) {
		#ifdef VERBOSE_DEBUG 
		cout << "label=" << i->first << " volume=" << i->second.volume \
			<< " predicate=" << pred(i->second) << endl;
		#endif
		if (pred(i->second))
			objects[i->first] = \
				Object(img, limg, i->second, i->first);
	}
}


/************************************************************************/
/*			 	LabeledImage3d 				*/
/************************************************************************/

  /**
    class LabeledImage3d implements a labeled image 
   */

template <class LABEL, class VOXEL>
class I3D_ALGO_EXPORT LabeledImage3d : public Image3d<LABEL> {
private:
  LABEL max_label;
  /** Displacement in voxels according to the original image. We can have
     an indexed image for a part of the original image or even an indexed
     image which is not fully covered by the original image (for instance,
     if it has black voxels added at borders to allow fast binary functions). 
  */
  Vector3d<int> displacement; 

public:
  /** container of ComponentInfo structures: */
  typename ComponentInfo<LABEL, VOXEL>::Container components;

  using Image3d<LABEL>::MakeRoom;
  using Image3d<LABEL>::CopyMetaData;
  using Image3d<LABEL>::SetVoxel;
  using Image3d<LABEL>::SetOffset;
  using Image3d<LABEL>::SetResolution;
  
  /* Constructors : */ 
 
  /** Empty image: */ 
  explicit LabeledImage3d(const Offset* off_ = 0, const Resolution* res_ = 0)
      : Image3d<LABEL>(off_, res_), max_label(0), displacement(0,0,0) {};

  /** 
     CreateRegions performs region labeling algorithm on an input Image3d<VOXEL> 
     image. Size of *this LabeledImage3d will be same as of the input image.
     Information about regions is stored into this->components container.
     Neigbourhood nb is expected to be symetric. If it is not, the algorithm 
     create symetric neigbourhood from offsets (x, y, z) of nb where
      (x <= 0 && y == 0 && z == 0) || (y < 0 && z == 0) || (y <= 0 && z < 0)
    */

  void CreateRegionsOld(Image3d<VOXEL>&, const Neighbourhood &nb = nb3D_6);

  /** The function CreateRegions performs Rosenfeld's region labelling algortihm
  on an input image. This implementation is done in more effective way than 
  the above one and gives the same results. In contrast to CreateRegionsOld function,
  the output sequence of labels is in ascending order (without spaces) and starts with
  label 1. */
  void CreateRegions(Image3d<VOXEL> &img, const Neighbourhood &nb = nb3D_6);

  /** The results are same as for CreateRegions function. 
	* Different algorithm (based  on FloodFill) is used. 
	* Neighbourhood nb3D_6 is imlicitly assumed */
  void CreateRegionsFF(const Image3d<VOXEL> &img, const Neighbourhood &nb = nb3D_6);

  /** If we know the background needn't be labeled we can speed up 
		the labeling process. The foreground is formed by nonzero pixels. */
  void CreateForegroundRegionsFF(const Image3d<VOXEL>& img, const Neighbourhood &nb = nb3D_6);

//    template <class Predicate> 
//    void MergeComponents(Predicate &pred) {
//      typename ComponentInfo<VOXEL>::Container::iterator i;
//      for (i = components.begin(); i != components.end(); ++i) {
//        if (pred(i->second)) {
//          /*DODELAT*/
//          MergeComponents();
//        }
//      }
//    }

  /** Remove component with given label. If such a component does not exist, the i3d::InternalException is thrown. */
  void RemoveComponent(LABEL label);

  /**
    Component comp is merged with all components for which pred holds.
   */
  template <class Predicate> 
  void MergeComponents(LABEL comp, Predicate pred) {
    typename ComponentInfo<LABEL, VOXEL>::Container::iterator i;
    for (i = components.begin(); i != components.end();) {
#ifdef VERBOSE_DEBUG 
        cout << "merging " << comp << " and " << i->first
             << " of volume " << i->second.volume << endl;
#endif
      if (pred(i->second)) {
#ifdef VERBOSE_DEBUG 
        cout << "YES" << endl;
#endif
        LABEL rmlab = i->first;
        ++i;
        MergeComponents(comp, rmlab);
      } else {
        ++i;
      }
    }
  }

  /**
    components comp1 and comp2 are merged
   */
  void MergeComponents(LABEL comp1, LABEL comp2);

  /** function converts LabeledImage3d to Image3d if it is possible (i.e 
     number of components < max value of Image3d type) List of components 
     is lost. Returned value indicate whether conversion was successful.
  */
  template <class T> bool Convert(Image3d<T> &img)
  {
    if (NumberOfComponents() < std::numeric_limits<T>::max()) 
    {
      img.MakeRoom(this->GetSize());
		img.SetOffset(this->GetOffset());
		img.SetResolution(this->GetResolution());

      if (NumberOfComponents() > 0) 
      {
		size_t i;
        std::vector<T> mv(max_label + 1);  // map vector of length max_label
        typename std::map<LABEL, ComponentInfo<LABEL, VOXEL> >::const_iterator label = 
							components.begin();
        for (i = 0; i < NumberOfComponents(); ++i)
        {
          mv[label->first] = static_cast<T>(i + 1);
          ++label;
        }
        
        LABEL *src = this->GetFirstVoxelAddr();
        T *desc = img.GetFirstVoxelAddr();
        for (i = 0; i < img.GetImageSize(); ++i, ++desc, ++src)
          *desc = mv[*src];
      }
      return true;
    }
    return false;
  }

  /** return number of components */
  size_t NumberOfComponents() const {return components.size();};

//    const ComponentContainer &Regions() const {return regions; };

  /// get the image displacement
  Vector3d<int> GetDisplacement() const {return displacement;}

  /// set the image displacement
  void SetDisplacement(const Vector3d<int> &d) {displacement = d;}

  // return max_label
  LABEL get_max_label(void) const { return max_label; };

  // find and set max label - returns max_label
  size_t FindAndSetMaxLabel ();

  /** Add a new component to this labelled image. The new component is
	* defined using mask in the given input image
	*/
  LABEL AddNewComponent(const Image3d<bool> &mask);

  /** Update component of the labelled image. The new component is
	* defined using mask in the given input image. It is assumed that the mask was 
	 created by GetComponentMask, especially that the voi of the mask is the same.
	 Warning: function can replace labels of other components and create inconsistency. 
	 If mask grasped only background voxels it should be safe. 
	*/
  void UpdateComponent(LABEL lbl, const Image3d<bool> &mask);

  /** Create the binary mask of given component */
  void GetComponentMask(LABEL lbl, Image3d<bool> &mask) const;

  /** Save LabeledImage3d to a given file - creates filename.l3d containing the name
      of a file with the 3d data and list of components. 3d data is converted to
      GRAY8 or GRAY16 image (depending on the number of components) and saved in usual way. 
      Throws an IOException on error.
      l3d file format:
        3d image filename
        displacement vector
        number of components - n
        max_label
        components list 1..n (label voi volume border voxel_value)
      */
  void SaveImage (const char *filename, i3d::FileFormat format = IMG_ICSv2) const;

  /** Load LabeledImage3d from .l3d file */
  void ReadImage (const char *filename, const VOI<PIXELS> *voi = NULL, bool isregexp=0, size_t channel = -1);
};

/**   WeightedCenter computes the center (in microns) of a component with 
 *   label lbl weighted by intensities in image img (img is the original 
 *   - usually grayscale - image, from which the indexed image limg was 
 *   formed). Coordinates of the center are given with respect to image img 
 *   (the labeled image can be shifted with respect to img).
 *   The function returns false if the component is empty or 
 *   contains only zero voxels. Otherwise it returns true and the center 
 *   is returned in center. The voxel resolution is obtained from the
 *   labeled image.
 */
template <class ORIGVOXEL, class LABEL, class VOXEL> 
  I3D_ALGO_EXPORT bool WeightedCenter(const Image3d<ORIGVOXEL> &img,
                                    const LabeledImage3d<LABEL, VOXEL> &labels, LABEL label, 
                                    Vector3d<float>& center);

/**   Center computes the center (in microns) of a component with label lbl.
 *   Coordinates of the center are given in coordinates of the (grayscale)
 *   image from which the labeled image has been formed (displacement in voxels
 *   from the original image can be obtained by labels.GetDisplacement()).
 *   The function returns false if the component is empty. Otherwise it 
 *   returns true and the center is returned in center.
 */
template <class LABEL, class VOXEL> 
  I3D_ALGO_EXPORT bool Center(const LabeledImage3d<LABEL, VOXEL> &labels, LABEL label, 
                            Vector3d<float>& center);

/** Estimate surface (or perimeter for 2D) for a component with the given label. 
 * Computes also volume of the component in voxels.
 */
template <class LABEL, class VOXEL>
  I3D_ALGO_EXPORT double Surface(const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label, size_t& volume);

/** Function Roundness computes the roundness of a component with the label lbl. The value of roundness
 *  is based on ratio between volume and surface (area and perimeter for 2D). It is normalized to be in 
 *  range (0,1]. 1 stands for circle (ball). The less compact is the component the lower is its roundness. 
 *  In fact, it calculates exactly Circularity for 2D components and Sphericity for 3D components.
 */
template <class LABEL, class VOXEL>
  I3D_ALGO_EXPORT double Roundness(const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label);

/** The roundness factor \f[ f_r = \frac{d_s}{d_o} \f] is the average distance d_s of any point
 *  in a sphere to the centre of gravity divided by the same parameter d_o in a chromosomal
 *  domain with identical volume. 
 *  \param limg - labeled image
 *  \param label - label of the selected component
 *  \param wcenter - weighted center of the selected component
 *  \param volume - volume of component (in um^3), this can be set to -1 to be computed automatically
 */
template <class LABEL, class VOXEL>
  I3D_ALGO_EXPORT double RoundnessFactor(const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label, 
                                       const Vector3d<float> &wcenter, double volume = -1);

/** Function returns the boundary voxels of a component with label lbl. It uses neighbourhood nb2D_4 for 2D and
 *  neighbourhood nb3D_6 for 3D images.
 */
template <class LABEL, class VOXEL>
  I3D_ALGO_EXPORT Boundary GetComponentBoundary(const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label);

/** Function computes minimal, maximal and mean radius of a component with the label lbl. Radius is computed
 *  from the component center of mass in micrometers. Results are in micrometers. Euclidean metric is used.
 */
template <class LABEL, class VOXEL>
  I3D_ALGO_EXPORT void Radius(const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label, const Vector3d<float> &center,
                            float &min, float &max, float &mean);

/** Function computes histogram of a component with the label lbl. The intensity values 
 *  are given from original image.
 */
template <class ORIGVOXEL, class LABEL, class VOXEL> 
  I3D_ALGO_EXPORT void IntensityHist(const Image3d<ORIGVOXEL> &img,
                                   const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label, 
                                   Histogram &hist);

/** Function computes minimal and maximal intensity value of a component with the label lbl. The intensity values 
 *  are given from original image.
 */
template <class ORIGVOXEL, class LABEL, class VOXEL> 
  I3D_ALGO_EXPORT void MinMaxComponentValue(const Image3d<ORIGVOXEL> &img,
                                          const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label, 
                                          ORIGVOXEL &min, ORIGVOXEL &max);

/** Remove all components from the original image for which the predicate is true. The new value of voxels 
 *  of these components is toggled from original value using ColorInversion function.
 */
template <class ORIGVOXEL, class LABEL, class VOXEL, class Predicate>
  I3D_ALGO_EXPORT void RemoveComponents(Image3d<ORIGVOXEL> &img, const LabeledImage3d<LABEL, VOXEL> &limg, Predicate &pred); 

/** Remove all components from the original image for which the predicate is true. The new value of voxels 
 *  of these components is toggled from original value using ColorInversion function.
 *  Also the voxels (labels) in labeled image belonging to the deleted components are set to 0 and the
 *  component is removed from component list.
 */
template <class ORIGVOXEL, class LABEL, class VOXEL, class Predicate>
  I3D_ALGO_EXPORT void EraseComponents(Image3d<ORIGVOXEL> &img, LabeledImage3d<LABEL, VOXEL> &limg, Predicate &pred); 

/** Function returns true if the object represented as its voi touchs the voi of the image.
 *  Intersections are computed only for given border (third, fourth and fifth parameter). 
 *  If no border is given function returns false. 
 */
I3D_ALGO_EXPORT bool HasIntersection(const VOI<UPIXELS> &img_voi, const VOI<UPIXELS> &obj_voi, bool bdr_x, bool bdr_y, bool bdr_z);

/** Class ComponentToRemove represents the predicate for RemoveComponents function.
 *  If the operator() returns true the component will be removed.
 */
template <class LABEL, class VOXEL> class I3D_ALGO_EXPORT ComponentToRemove {
  private:
	VOXEL value;                           // the value of component voxels
    bool bdr_x, bdr_y, bdr_z;              // touch the component x,y,z border ?
	bool use_bdr_min_sz, use_bdr_max_sz;   // remove the border component with minimal, maximal volume
	size_t bdr_min_sz, bdr_max_sz;         // minimal and maximal volume of the border component
	bool use_min_sz, use_max_sz;           // remove the component with minimal, maximal volume
	size_t min_sz, max_sz;                 // minimal and maximal volume of the component
    bool use_value;                        // check the component voxel value?
    bool full_voi;                         // remove component with voi containing the whole image (typically background)
	bool use_voi_volume;				   // use voi_volume instead of volume?	

  public: 
	ComponentToRemove(VOXEL v, bool x, bool y, bool z, bool ubmin, bool ubmax, size_t bmin, size_t bmax, 
	                  bool umin, bool umax, size_t min, size_t max, bool uval = true, bool ufvoi = false, 
					  bool use_voi_vol = false) :
      value(v), bdr_x(x), bdr_y(y), bdr_z(z), use_bdr_min_sz(ubmin), use_bdr_max_sz(ubmax), 
	  bdr_min_sz(bmin), bdr_max_sz(bmax), use_min_sz(umin), use_max_sz(umax), min_sz(min), max_sz(max),
      use_value(uval), full_voi(ufvoi), use_voi_volume(use_voi_vol) {};
	
	bool operator()(const ComponentInfo<LABEL, VOXEL> &c, Image3d<VOXEL> &img);

  private:
	/** Function returns true if the component volume is greater or less than minimal or maximal volume
	 *  or if the component volume is between minimal and maximal volume. 
	 *  If we don't use both minimal and maximal volume the function returns true.
     */
	bool ComponentSize(const ComponentInfo<LABEL, VOXEL> &c, bool use_min, bool use_max, size_t min, size_t max);

};


/** Added by Vladimir Ulman (xulman@fi.muni.cz), 14.11.2004
 *
 * Structure containing 2D table of doubles and get, set functions
 * (position x,y <-> double value_at_x,y). Originally ment to store
 * mutual distances between regions/components from given two LabeledImage3d.
*/
struct I3D_ALGO_EXPORT components_distance_matrix {
  private:
	size_t x_dimension,y_dimension;
	//it holds: x_dimension * y_dimension = length of matrix_data array

  public:
	//public because of fast direct access, nevertheless get/set functions still provided...
	double *matrix_data;

	//constructor
	components_distance_matrix(size_t x,size_t y) {
		matrix_data=new double[x*y];
		if (matrix_data == NULL)
      		  throw InternalException("comp._dist_matrix: Not enough memory to store the matrix.");

		size_t a;
		for (a=0; a < x*y; a++) matrix_data[a]=0.0;

		x_dimension=x;
		y_dimension=y;
	}

	//destructor
	~components_distance_matrix(void) {
		delete[] matrix_data;
	}

	//indexes begin from zero!
	double get_value(int x,int y) {
		if ((x < 0) || (x >= (int)x_dimension) || 
			 (y < 0) || (y >= (int)y_dimension))
      		  throw InternalException("comp._dist_matrix: Wrong index(es) to access matrix.");

		return(matrix_data[y*x_dimension +x]);
	}

	void set_value(int x,int y,double value) {
		if ((x < 0) || (x >= (int)x_dimension) || 
			 (y < 0) || (y >= (int)y_dimension))
      		  throw InternalException("comp._dist_matrix: Wrong index(es) to access matrix.");

		matrix_data[y*x_dimension +x]=value;
	}

	size_t get_x_dimension(void) { return(x_dimension); };
	size_t get_y_dimension(void) { return(y_dimension); };

	void print_matrix(void) {
		size_t x,y,offset=0;
		if ((x_dimension <= 0) || (y_dimension <= 0)) std::cout << "Matrix empty!\n";
		else {
			std::cout << "\t|| 0";
			for (x=1; x < x_dimension; x++) std::cout << "\t| " << x; std::cout << "\n========";
			for (x=0; x < x_dimension; x++) std::cout << "========"; std::cout << "\n";

			for (y=0; y < y_dimension; y++) {
				std::cout << y << "\t|| " << matrix_data[offset++];
				for (x=1; x < x_dimension; x++) std::cout << "\t| " << matrix_data[offset++];
				std::cout << "\n";
			}
		}
	}
};


#define DMAX	100		//if the bounding box distance is above this default threshold
				//then the distance between underlying regions/components
#define DMAX_FAR_AWAY	32767	//is claimed to be DMAX_FAR_AWAY

/** Creates and fills the structure representing the matrix of distances,
 * returns pointer to this structure. In matrix, row axis contains components
 * from limgA, column axis contains comp. from limgB, row/column index of
 * given component is its label. If the distance of bounding boxes of respective
 * components is above max_dist parameter (which defaults to DMAX constant) the
 * distance is claimed to be DMAX_FAR_AWAY. max_dist parameter is in microns units.
 * It is also expected that upper left corner of both images is the same point
 * in 3d space, i.e. images are aligned.
*/
template <class LABEL, class VOXEL>
  I3D_ALGO_EXPORT components_distance_matrix* CreateDistMatrix(const LabeledImage3d<LABEL,VOXEL> &limgA,const LabeledImage3d<LABEL,VOXEL> &limgB,const double max_dist=DMAX);


/* Creates list (implemented as vector) of points which are supposed to be
 * at the boundary of given image. Input image is first eroded, the result
 * is saved into some temporary image. Boundary points are determined as those
 * points laying in the original image while not present in the temporary (eroded)
 * image. Pointer to the vector is returned.
*/
template <class VOXEL>
  I3D_ALGO_EXPORT std::vector< Vector3d<float> >* ExtractBorderPoints(const Image3d<VOXEL> &img,const Vector3d<size_t> &offset);

/***********************************************************************
*
*	Surface/volume estimation based on marching cubes/squares algorithnm 
*  
************************************************************************/

/** Two estimation types used in the MC_Estimate procedure */
enum McEstimateType
{
    MC_ESTIMATE_SURFACE,
    MC_ESTIMATE_VOLUME
};

/** Estimation of component characteristics based on the marching cubes/squares algorithm.
  * \param limg - input image
  * \param label - component label
  * \param type - can be either MC_ESTIMATE_SURFACE or MC_ESTIMATE_VOLUME. The former gives
  *     surface estimation of 3D images or perimeter estimation of 2D images (XY plane only!).
  *     By analogy, the latter specifies volume(3D)/area(2D) estimation.
  * \return Returned value is either surface/perimeter or volume/area depending on the type parameter.
  * \author Ondrej Danek (xdanek2@fi.muni.cz)
  */
template <class LABEL, class VOXEL>
  I3D_ALGO_EXPORT double MC_Estimate (const LabeledImage3d<LABEL, VOXEL> &limg, LABEL label, McEstimateType type);

} // end of namespace i3d
#endif

#undef VERBOSE_DEBUG 
