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

/** \file neigbours.h
  \brief Definition of neighbourhood - header.

  \todo

  \author Pavel Matula (pam@fi.muni.cz) 2001

*/

#ifndef __NEIGHBOURS_H__
#define __NEIGHBOURS_H__

#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include "algo_export.h"
#include "image3d.h"
#include "vector3d.h"

#ifdef __GNUG__
#	pragma interface
#endif

namespace i3d {
	/***************************************************************************\
	*
	*                               Typedefs
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// VectContainer
	//--------------------------------------------------------------------------
	typedef std::vector< Vector3d<int> > VectContainer;

	/***************************************************************************\
	*
	*                               Neighbourhood
	*
	\***************************************************************************/
    /** \brief The main structure representing the neighbourhood of an image voxel.
    
	Neighbourhood is a sequence of offsets. The offsets point to neighbours of 
	a voxel in Image3d
	*/
	struct I3D_ALGO_EXPORT Neighbourhood {
		//--------------------------------------------------------------------------
		// Members of structure
		//--------------------------------------------------------------------------
		/** The sequence of offsets. */
		VectContainer offset;

		//--------------------------------------------------------------------------
		// Constructors and destructors
		//--------------------------------------------------------------------------
		/** Default constructor. */
		Neighbourhood() 
			: offset() 
		{};
        
        #ifdef __APPLE__
        ~Neighbourhood() {};
        
        Neighbourhood(const Neighbourhood& src) {
            offset = src.offset;
        }
        #endif

        /** Constructor takes array of length 3*n_. Offsets have to be stored in order
		{ offset1_x, offset1_y, offset1_z, offset2_x, offset2_y, offset2_z, ...}. */
		Neighbourhood(const int offset_[], int n_);
		
		/** Create neighbourhood containing points i * v where i \in {0,..., p} */
		Neighbourhood(Vector3d<int> v, size_t p);
		
		/** Create elipsoidal neighbourhood. */
		Neighbourhood(double r1, double r2, double r3);

		//--------------------------------------------------------------------------
		// Operators
		//--------------------------------------------------------------------------
		/** Comparison of two neighbourhoods. */
		bool operator== (const Neighbourhood &N) const;

		/** Union of two neighbourhoods. */
		const Neighbourhood operator+ (const Neighbourhood &N) const;

		/** Difference of two neighbourhoods. */
		const Neighbourhood operator- (const Neighbourhood &N) const;

		/** Inversion of neighbourhood. */
		Neighbourhood operator-() const;

		//--------------------------------------------------------------------------
		// Get neighbourhood properties
		//--------------------------------------------------------------------------
		/** Get size of neighbourhood. Return the number of neighbours.*/
		size_t size() const
		{
			return offset.size();
		};

		/** Returns "maximum extent" of the neighbourhood - largest absolute 
		value of any of the coordinates stored in any dimension. It can be 
		useful when padding the image for working with this neighbourhood. */
		size_t GetMaxExtent() const;

		//--------------------------------------------------------------------------
		// Create child neighbourhoods
		//--------------------------------------------------------------------------
		/** 
		Splits this neighbourhood into two other neighbourhoods - positive and negative. 
		If "0" is present, it will not be part of the created neighbourhoods.
		Previous contents of nbhPos and nbhNeg will be destroyed.
		\param nbhPos output parameter with the positive neighbourhood
		\param nbhNeg output parameter with the negative neighbourhood
		*/
		void Split(Neighbourhood &nbhPos, Neighbourhood &nbhNeg) const;

	}; // Neighbourhood

	/***************************************************************************\
	*
	*                         External neighbourhood constants
	*
	\***************************************************************************/
	//--------------------------------------------------------------------------
	// nb2D_4
	//--------------------------------------------------------------------------
	/** We define nb2D_4 neighbourhood of point P=[x,y,z] as:
	(1, 0, 0), (0, 1, 0), (-1, 0, 0), (0, -1, 0)
	i.e:
                ___       
            __ /_ /__    
           /__/_ /_ /|     
          |  /__/|  ||    
          | _|  ||__|/    
             |__/        

	*/
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb2D_4;

	//--------------------------------------------------------------------------
	// nb2D_o4
	//--------------------------------------------------------------------------
	/** Same as nb2D_4, but origin, i.e. point (0,0,0) is included. */
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb2D_o4;


	//--------------------------------------------------------------------------
	// nb2D_8
	//--------------------------------------------------------------------------
	/** We define nb2D_8 neighbourhood of point P=[x,y,z] as: 
    (1, 0, 0), (0, 1, 0), (1, 1, 0), (-1, 0, 0), (-1, 1, 0), (0, -1, 0), 
	(1, -1, 0), (-1, -1, 0)
     i.e:
             ________    
           /_ /_ /__/|  
          /__/_ /_ /||    
         /__/__/__/||/   
         |  |  |  ||/    
         |__|__|__|/    
                              
	*/  
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb2D_8;

	//--------------------------------------------------------------------------
	// nb2D_o8
	//--------------------------------------------------------------------------
	/** Same as nb2D_8, but origin, i.e. point (0,0,0) is included. */
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb2D_o8;

	//--------------------------------------------------------------------------
	// nb3D_6
	//--------------------------------------------------------------------------
	/** We define nb3D_6 neighbourhood of point P=[x,y,z] as:
	(1, 0, 0), (0, 1, 0), (0, 0, 1), (-1, 0, 0), (0, -1, 0), (0, 0, -1)
	i.e:
               ___         
              /__/|       
            _|  | |__     
           /_|__|/_ /|     
          | /__/|  | |    
          |_|  ||__|/    
            |__/| |     
             |__|/  
    */
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb3D_6;

	//--------------------------------------------------------------------------
	// nb3D_o6
	//--------------------------------------------------------------------------
	/** Same as nb3D_o6, but origin, i.e. point (0,0,0) is included. */
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb3D_o6;

	//--------------------------------------------------------------------------
	// nb3D_18
	//--------------------------------------------------------------------------
	/** We define nb3D_18 neighbourhood of point P=[x,y,z] as:
	nb3D_6 + (1, 1, 0), (0, 1, 1), (1, 0, 1), (-1, 1, 0), (0, -1, 1), (1, 0, -1), 
    (1, -1, 0), (0, 1, -1), (-1, 0, 1), (-1, -1, 0), (0, -1, -1), (-1, 0, -1)
    i.e:         
                ___   
            ___/__/_   
          /__/__/__/|_   
         | /__/|  | |/|
         ||  | |__|/| |
        /_|__|/_ /| |/  
       |  |  |  | |/|  
       |__|__|__|/| | 
          |  | |__|/
          |__|/  
	*/
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb3D_18;

	//--------------------------------------------------------------------------
	// nb3D_o18
	//--------------------------------------------------------------------------
	/** Same as nb3D18, but origin, i.e. point (0,0,0) is included. */
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb3D_o18;
	
	//--------------------------------------------------------------------------
	// nb3D_26
	//--------------------------------------------------------------------------
	/** We define nb3D_26 neighbourhood of point P=[x,y,z] as:
	nb3D_18 + (1, 1, 1), (-1, 1, 1), (1, -1, 1), (1, 1, -1), 
	(-1, -1, -1), (1, -1, -1), (-1, 1, -1), (-1, -1, 1)
    i.e:      
               ________
             /__/__/__/|
           /__/__/__/| |  
         /__/__/__/| |/|
        |  |  |  | |/| |
        |__|__|__|/| |/| 
        |  |  |  | |/| |
        |__|__|__|/| |/
        |  |  |  | |/
        |__|__|__|/

	*/
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb3D_26;

	//--------------------------------------------------------------------------
	// nb3D_o26
	//--------------------------------------------------------------------------
	/** Same as nb3D_26, but origin, i.e. point (0,0,0) is included. */
	I3D_ALGO_EXPORT_DATA(extern const Neighbourhood) nb3D_o26;

	/***************************************************************************\
	*
	*                         Neigbourhood related operators
	*
	\***************************************************************************/
	/** Output operator. Writes information about the neighbourhood into the stream. */
	I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &out, const Neighbourhood &n);

	/***************************************************************************\
	*
	*                         Neigbourhood related functions
	*
	\***************************************************************************/
	/** This function will construct a boxed neighbourhood in 2 or 3 dimensions.
	Examples: 
	ConstructBoxNeighbourhood(nb,1.0,1.0,0.0) will give classic 8-neighbourhood in 2 dimensions 
	ConstructBoxNeighbourhood(nb,1.0,1.0,1.0) will give classic 26-neighbourhood in 3 dimensions
	ConstructBoxNeighbourhood(nb,2.0,2.0,2.0) will give classic 124-neighbourhood in 3 dimensions. */
	I3D_ALGO_EXPORT void ConstructBoxNeighbourhood(Neighbourhood &nb, double r1, double r2, double r3, bool include_origin = false);

	/***************************************************************************\
	*
	*							  Other functions
	*
	\***************************************************************************/
	/// \todo All other functions should be moved to the another file.

    /** GetNbh computes valid neighbours of point [x,y,z], which must be inside 
	the image img (otherwise, the InternalException is raised). The function 
	returns how long computed neigbourhood will be valid, if you will go through
	voxels using ++i (i = index[x,y,z] ie. like in GetWindow).

    One version of the overloaded GetNbh() function stores the resulting valid 
	neigbourhood points in an output neighbourhood (rnb), the other version produces
	tags stored in the boolean array isvalid, in which 
	isvalid[i] == true <=> nb.offset[i] + [x,y,z] is inside the image img. */
	template <class T> I3D_ALGO_EXPORT size_t GetNbh(
		const Image3d<T> &img,
		size_t x, 
		size_t y, 
		size_t z, 
		const Neighbourhood &nb, 
		Neighbourhood &rnb);

	template <class T> I3D_ALGO_EXPORT size_t GetNbh(
		const Image3d<T> &img, 
		size_t x, 
		size_t y, 
		size_t z, 
		const Neighbourhood &nb, 
		std::vector<bool> &isvalid);

	/**  MakeWindow computes vector of pointers to img's voxels, i.e. window to image. 
    Neighbourhood nb MUST be computed by GetNbh to avoid invalid pointers. */
	template <class T> I3D_ALGO_EXPORT void MakeWindow(
		Image3d<T> &img, 
		size_t x, 
		size_t y, 
		size_t z, 
		const Neighbourhood &nb, 
		std::vector<T *> &valid);

    template <class T> I3D_ALGO_EXPORT void MakeWindow(
		const Image3d<T> &img,
        size_t x, 
		size_t y, 
		size_t z, 
		const Neighbourhood &nb, 
		std::vector<const T *> &valid);

	/** GetWindow computes vector of pointers to valid neighbours of point [x,y,z]
    Vector of pointers can be viewed like a window to the Image3d. The function 
	returns an integer value giving the a distance, how far one can move the window
	(i.e use ++ for each pointer in computed vector) without recomputation of valid
	neigbours (i.e new call of GetWindow). Vector valid will not be larger than 
	nb.size() => you can use valid.reserve(nb.size()). */
	template <class T> I3D_ALGO_EXPORT size_t GetWindow(
		Image3d<T> &img, 
		size_t x, 
		size_t y, 
		size_t z,
        const Neighbourhood &nb, 
		std::vector<T *> &valid);
    
	template <class T> I3D_ALGO_EXPORT size_t GetWindow(
		const Image3d<T> &img, 
		size_t x, 
		size_t y, 
		size_t z, 
		const Neighbourhood &nb,
		std::vector<const T *> &valid);

	/** GetFullWindow acts like GetWindow, except that it produces a pointer for *each*
	neighbourhood point. If a point is out of the image, the corresponding pointer is 0. */
	template <class T> I3D_ALGO_EXPORT size_t GetFullWindow(
		Image3d<T> &img,
		size_t x, 
		size_t y, 
		size_t z,
        const Neighbourhood &nb,
		std::vector<T*> &valid);
	
	template <class T> I3D_ALGO_EXPORT size_t GetFullWindow(
		const Image3d<T> &img,
		size_t x, 
		size_t y, 
		size_t z, 
		const Neighbourhood &nb,
		std::vector<const T *> &valid);

	/** Get median of intensities in the specified window. */
	template <class T> T GetMedian(const std::vector<const T *> &win);
	
	/** use this function to move window computed by GetFullWindow 
	to the next voxel. 
	\todo There is no check - Is the move possible?. */
	template <class T> inline void MoveFullWindow(std::vector<T*>& v)
	{
		typename std::vector<T*>::iterator i;
		for (i = v.begin(); i != v.end(); ++i) 
		{
			if (*i) 
			{
				*i++;
			}
		}
	}

	/** use this function to move window computed by GetWindow or MakeWindow
	to the next voxel. 
	\todo There is no check - Is the move possible?. */
	template <class T> inline void MoveWindow(std::vector<T*>& v)
	{
		typename std::vector<T*>::iterator i;
		for (i = v.begin(); i != v.end(); ++i) {
			++(*i);
		}
	}
	
	/** \todo Can be united with function above. 
	\todo There is no check - Is the move possible?. */
	template <class T> inline void MoveWindow(std::vector<T*>& v, int shift)
	{
		typename std::vector<T*>::iterator i;
		for (i = v.begin(); i != v.end(); ++i) 
		{
			*i += shift;
		}
	}

	/***************************************************************************\
	*
	*                         Neighbourhood related classes
	*
	\***************************************************************************/
	/// Class that border-unsafely walks the neighbourhood
	class I3D_ALGO_EXPORT NeighbourhoodWalkerU
	{
	public:
		/// constructor that initializes the walker for some image and neighbourhood
		NeighbourhoodWalkerU(const Vector3d<size_t> &imageSize, const Neighbourhood &neigbourhood);
		/// destructor that frees all the allocated resources
		~NeighbourhoodWalkerU();

		/// prepares walker for walking - in this unsafe version it always succeeds
		void Begin(size_t index)
		{ this->index = index; offsetsIndex = 0; }
		/// returns whether is walker prepared for retrieving index
		bool Valid() const
		{ return offsetsIndex < offsetsSize; }
		/// returns walking index 
		size_t GetIndex() const
		{ return index + offsets[offsetsIndex]; }
		/// moves to the next index
		void Next()
		{ ++offsetsIndex; }
	private:
		/// current index of the central voxel
		size_t index;
		/// all the index offsets
		int *offsets;
		/// current index into the offsets vector
		size_t offsetsIndex;
		/// size of the offsets array
		size_t offsetsSize;
	};

	/// Class that border-safely walks the neighbourhood
	class I3D_ALGO_EXPORT NeighbourhoodWalker
	{
	public:
		/// Structure that holds the current neighbourhood walker state - allows to use the walker recursively (thanks to the save and load state methods)
		struct State
		{
			/// current index of the central voxel
			size_t index;
			/// all the index offsets for current beginning
			const int *offsets;
			/// current index into the offsets vector
			size_t offsetsIndex;
			/// size of the offsets vector
			size_t offsetsSize;
		};

		/// constructor that initializes the walker for some image size and neighbourhood
		NeighbourhoodWalker(const Vector3d<size_t> &imageSize, const Neighbourhood &neigbourhood, bool precompute);
		/// destructor that frees all the allocated resources
		~NeighbourhoodWalker();

		/// prepares walker for walking - in this safe version it is necessary to check Valid before calling GetIndex
		void Begin(size_t index);
		/// returns whether is walker prepared for retrieving index
		bool Valid() const
		{ return state.offsetsIndex < state.offsetsSize; }
		/// returns walking index 
		size_t GetIndex() const
		{ return state.index + state.offsets[state.offsetsIndex]; }
		/// moves to the next index
		void Next()
		{ ++state.offsetsIndex; }

		/// saves the current state so that it can be retrieved in the future
		void SaveState(State &tmpState) const
		{ memcpy(&tmpState, &state, sizeof(State)); }
		/// restores the current stat from the given one
		void LoadState(const State &tmpState)
		{ memcpy(&state, &tmpState, sizeof(State)); }
	private:
		/// state of the walker
		State state;
		/// mapping of distance codes to the vectors with index offsets
		std::vector<int> ******offsetsTree;
		/// size of the images this walker is set up to
		Vector3d<size_t> imageSize;
		/// negative extent of the represented neighbourhood
		i3d::Vector3d<size_t> negExtent;
		/// positive extent of the represented neighbourhood
		i3d::Vector3d<size_t> posExtent;
		/// array of the precomputed pointers to proper offset vectors
		std::vector<int> **precomputed;
	};

} // i3d namespace

#endif
