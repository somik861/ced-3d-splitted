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

/** \file se.h
  \brief Structuring elements - header.

  Definition of various types of structuring elements 
 
  \author Petr Matula (pem@fi.muni.cz) 2009
  \author Jiri Kus (207578@mail.muni.cz) 2009
 
*/

#ifndef __I3D_SE_H__
#define __I3D_SE_H__

#include <iostream>
#include <vector>
#include "vector3d.h"
#include "algo_export.h"
#include "algo_export.h"

namespace se {

	//------------------------
	// ABSTRACT CLASSES
	//------------------------
	class I3D_ALGO_EXPORT StructuringElement {
	public:
	/** Fills given vector with neighbours of SE
			The origin is [0,0,0]
			2D structuring elements has coordinate z=0*/
		virtual void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const = 0;
	
		/** Fills given vector with decomposition of SE
			If decomposition is not possible, just the original SE is returned*/
		virtual void GetSequence(std::vector<StructuringElement*>&) const = 0;
		
			/** Reflects the SE
		    = Every point [u,v,w] is replaced by [-u,-v,-w] */
		virtual void Reflect() = 0;
		
		/** Translates the SE 
			every point [u,v,w] is replaced by [u+x,v+y,w+z] 
			The origin is still [0,0,0] */
		virtual void Translate(const i3d::Vector3d<int>) = 0;
		
		/// virtual destructor just to keep GCC quiet
		virtual ~StructuringElement() {}
	}; // StructuringElement 
	
	class NonFlatStructuringElement: public StructuringElement{
	public:
		/** Fills given vector with weights of SE.
			Weights are ordered from left to right, starting with point [min,min] and
			ending with [max,max]*/
		virtual void GetWeights(std::vector<double>&) const = 0;
	};

	//------------------------
	// NON-ABSTRACT CLASSES
	//------------------------

/********ARBITRARY*********/
	class I3D_ALGO_EXPORT Arbitrary : public StructuringElement{
	private:
		std::vector<i3d::Vector3d<int> > nhood;
	public:	
		/// Default constructor. Creates empty SE
		Arbitrary(){/*empty*/}
		
		/// Copy constructor. Creates a copy of the given SE
		Arbitrary(const Arbitrary &se){se.GetNeighbours(nhood);} 
		
		/** creates an ARBITRARY SE
			= a flat structuring element where nhood specifies the neighborhood. 
			\param nhood list of points with center in [0,0,0] */
		Arbitrary(const std::vector<i3d::Vector3d<int> > input){nhood=input;}
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&output) const{output=nhood;}
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect() ;
		void Translate(const i3d::Vector3d<int>);
		
		//arbitrary specific functions
		void SetNeighbours(const std::vector<i3d::Vector3d<int> >input){nhood=input;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Arbitrary &se);

	};
	
/********NON-FLAT ARBITRARY*********/	
	class I3D_ALGO_EXPORT NonFlatArbitrary : public NonFlatStructuringElement, public Arbitrary{
	private:
		std::vector<double> weights;
	public:	
		/** Default constructor. Creates empty SE.
		 */
		NonFlatArbitrary(){/*empty*/}
		
		/// Copy constructor. Creates a copy of the given SE
		NonFlatArbitrary(const NonFlatArbitrary &se); 
		
		/** creates an ARBITRARY SE
			= a non-flat structuring element where nhood specifies the neighborhood.
			throws i3d::InternalException if the size of nhood is not equal to the size of weights
			\param nhood list of points with center in [0,0,0] 
			\param weights list of weights in the same order as the nhood vector
			*/
		NonFlatArbitrary(const std::vector<i3d::Vector3d<int> > &nhood, const std::vector<double> weights); 
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&vec) const{Arbitrary::GetNeighbours(vec);}
		void SetNeighbours(const std::vector<i3d::Vector3d<int> >vec){Arbitrary::SetNeighbours(vec);}
		void GetSequence(std::vector<StructuringElement*>&vec) const;
		void Reflect(){Arbitrary::Reflect();}
		void Translate(const i3d::Vector3d<int>vec){Arbitrary::Translate(vec);}
		
		//NonFlatStructuringElement functions
		void GetWeights(std::vector<double> &out) const{out=weights;}

		//specific
		void SetWeights(const std::vector<double>input){weights=input;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const NonFlatArbitrary &se);
		
	};
/*********DISK***********/	
	class I3D_ALGO_EXPORT Disk: public StructuringElement{
	private:
		unsigned radius;
		unsigned n;
		i3d::Vector3d<int> shift;
	public:	
		/// Defaul constructor = Disk(1,4)
		Disk();
		
		/// Copy constructor.
		Disk(const Disk &se);
		
		/**
		\param radius non-negative radius of DISK
		\param n - must be 0, 4, 6, or 8. When N is greater than 0, the disk-shaped 
					structuring element is approximated by a sequence of N periodic-line structuring 
					elements. When N equals 0, no approximation is used, and the structuring element 
					members consist of all pixels whose centers are no greater than R away 
					from the origin. If N is not specified, the default value is 4.*/
		Disk(unsigned radius, unsigned n=4);
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const;
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect(){shift=-shift;}
		void Translate(const i3d::Vector3d<int>vec){shift+=vec;}

		//disk-specific
		unsigned GetRadius()const{return radius;}
		void SetRadius(unsigned r){radius=r;}
		unsigned GetN()const{return n;}
		void SetN(unsigned nn);
		i3d::Vector3d<int> GetShift()const{return shift;}
		void SetShift(i3d::Vector3d<int> vec){shift=vec;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Disk &se);	
	};	

/*******BALL*******/
	// TODO: derives from flat equivalent?
	class I3D_ALGO_EXPORT Ball : public NonFlatStructuringElement, public Disk{
	private:
		double weight;
	public:
		/// Defaul constructor = Ball(1,4)
		Ball();
		
		/// Copy constructor.
		Ball(const Ball &se);

		
		/** creates a ball-shaped structuring element (actually an ellipsoid)
			\param radius non-negative radius of the ball
			\param n - must be 0, 4, 6, or 8. When N is greater than 0, the ball-shaped 
					structuring element is approximated by a sequence of N periodic-line structuring 
					elements. When N equals 0, no approximation is used, and the structuring element 
					members consist of all pixels whose centers are no greater than R away 
					from the origin. If N is not specified, the default value is 4.
			\param weights The corresponding height values are determined from the formula 
					of the ellipsoid specified by WEIGHTS and RADIUS. */
		Ball(unsigned radius, double weight,unsigned n=4);
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&out) const{Disk::GetNeighbours(out);}
		void GetSequence(std::vector<StructuringElement*>&out) const{Disk::GetSequence(out);}
		void Reflect(){Disk::Reflect();}
		void Translate(const i3d::Vector3d<int>vec){Disk::Translate(vec);}
		
		
		//NonFlatStructuringElement functions
		void GetWeights(std::vector<double>&out) const;

		//Ball specific
		double GetWeight() const{return weight;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Ball &se);
	};
/*********DIAMOND***********/		
	class I3D_ALGO_EXPORT Diamond : public StructuringElement{
	private:
		unsigned radius;
		i3d::Vector3d<int> shift;
	public:
		/// Defaul constructor = Diamond(1)
		Diamond();
		
		/// Copy constructor.
		Diamond(const Diamond &se);

		/**
		\param radius - the distance from the structuring element 
					origin to the points of the diamond. Non-negative
		*/
		Diamond(unsigned radius);
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const;
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect(){shift=-shift;}
		void Translate(const i3d::Vector3d<int>vec){shift += vec;}
		//diamond-specific functions
		unsigned GetRadius()const{return radius;}
		i3d::Vector3d<int> GetShift()const{return shift;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Diamond &se);
		
	};

/*******LINE********/	
	class I3D_ALGO_EXPORT Line : public StructuringElement{
	private:
		unsigned length;
		unsigned angle;
		i3d::Vector3d<int> shift; //used for translate
		i3d::Vector3d<int> sign; //used for reflect
	public:	
		/// Default constructor = Line(0,0)
		Line();
		
		/// Copy constructor.
		Line(const Line &se);
		
		/** creates a line shaped SE with its origin in the middle
			\param length of the line 
			\param angle of the line in degrees as measured in a counterclockwise 
				   direction from the horizontal axis. */
		Line(unsigned length, unsigned angle);
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const;
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect(){sign=-sign; shift=-shift;}
		void Translate(const i3d::Vector3d<int>vec){shift+=vec;}

		//line-specific
		unsigned GetLength()const{return length;}
		unsigned GetAngle()const{return angle;}
		i3d::Vector3d<int> GetShift()const{return shift;}
		i3d::Vector3d<int> GetSign()const{return sign;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Line &se);
		
		
	};
/*******PAIR********/	
	class I3D_ALGO_EXPORT Pair : public StructuringElement{
	private:
		i3d::Vector3d<int> first;
		i3d::Vector3d<int> second;
	public:	
		/// Defaul constructor = Pair(0,0,0)
		Pair(){/*empty*/}
		
		/// Copy constructor.
		Pair(const Pair &se);
		
		/** Creates a flat structuring element containing two members. 
			One member is located at the origin. 
			The second is lcoated at [a,b,c] */
		Pair(int a, int b, int c);
		Pair(const i3d::Vector3d<int>);
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const;
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect();
		void Translate(const i3d::Vector3d<int>);
		//pair specific
		i3d::Vector3d<int> GetFirst()const{return first;}
		i3d::Vector3d<int> GetSecond()const{return second;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Pair &se);
		
	
	};
/********PERIODIC LINE************/	
	class I3D_ALGO_EXPORT PeriodicLine : public StructuringElement{
	private:
		int p;
		int rowOffset;
		int colOffset;
		i3d::Vector3d<int> shift;
		i3d::Vector3d<int> sign;
		// even is true if periodicLine was created by PeriodicLine(p,n,col,row)
		bool even;
		int n;

	public:	
		/// Defaul constructor = PeriodicLine(0,0,0)
		PeriodicLine();
		
		/// Copy constructor.
		PeriodicLine(const PeriodicLine &se);
		
		/** Creates a flat structuring element containing 2*P+1 members. 
		    V is a vector(ROW_OFFSET,COLUMNG_OFFSET). 
			One structuring element member is located at the origin. 
			The other members are located at 1*V, -1*V, 2*V, -2*V */
		PeriodicLine(int p, int columnOffset,int rowOffset);
		
		/** Creates a periodic line with even count of members
			use this constructor to create periodic lines of even size
			\param p member count
			\param n marks nth point as origin (first point has n==0)*/
		PeriodicLine(int p,int n, int columnOffset,int rowOffset);

		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const;
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect(){shift=-shift; sign=-sign;}
		void Translate(const i3d::Vector3d<int>vec){shift+=vec;}
		//periodicline-specific functions
		unsigned GetP()const{return p;}
		int GetRowOffset()const{return rowOffset;}
		int GetColOffset()const{return colOffset;}
		i3d::Vector3d<int> GetShift()const{return shift;}
		i3d::Vector3d<int> GetSign()const{return sign;}
		//returns true if size is even
		bool IsEven()const{return even;}
		// returns index of origin
		int GetN()const{return n;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const PeriodicLine &se);
		
	};

/***********RECTANGLE*****************/
	class I3D_ALGO_EXPORT Rectangle : public StructuringElement{
	private:
		unsigned cols;
		unsigned rows;
		i3d::Vector3d<int> shift; //where to shift rectangle
		i3d::Vector3d<int> sign; //used for reflect
	public:	
		/// Defaul constructor = Rectangle(3,3)
		Rectangle();
		
		/// Copy constructor.
		Rectangle(const Rectangle &se);
		
		/** Creates a rectangular SE*/
		Rectangle(unsigned cols, unsigned rows);
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const;
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect();
		void Translate(const i3d::Vector3d<int>vec){shift += vec;}
		//rectangle specific
		unsigned GetRows()const{return rows;}
		unsigned GetCols()const{return cols;}
		void SetRows(unsigned r){rows=r;}
		void SetCols(unsigned c){cols=c;}
		i3d::Vector3d<int> GetShift()const{return shift;}
		i3d::Vector3d<int> GetSign()const{return sign;}
		void SetShift(i3d::Vector3d<int> v){shift=v;}
		void SetSign(i3d::Vector3d<int> v){sign=v;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Rectangle &se);
		
	};
/***********SQUARE*****************/
	class I3D_ALGO_EXPORT Square : public Rectangle{
	private:
	public:	
		/// Defaul constructor = Square(3)
		Square();
		
		/// Copy constructor.
		Square(const Square &se);
		
		/** Creates a square shaped SE*/
		Square(unsigned size);
		
		//square specific
		unsigned GetSize()const{return GetCols();}

		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Square &se);
		
	};
/***********OCTAGON*****************/
	class I3D_ALGO_EXPORT Octagon : public StructuringElement{
	private:
		int radius;
		i3d::Vector3d<int> shift;
	public:	
		/// Defaul constructor. TODO: Default values
		Octagon();
		
		/// Copy constructor.
		Octagon(const Octagon &se);
		
		/** creates a flat, octagonal structuring element
			\param radius distance from the structuring element origin to the sides 
					of the octagon, as measured along the horizontal and vertical axes.
					Nonnegative multiple of 3.*/
		Octagon(int radius);
		
		//StructuringElement functions
		void GetNeighbours(std::vector<i3d::Vector3d<int> >&) const;
		void GetSequence(std::vector<StructuringElement*>&) const;
		void Reflect(){shift=-shift;}
		void Translate(const i3d::Vector3d<int>vec){shift+=vec;}
		//octagon-specific
		unsigned GetRadius()const{return radius;}
		i3d::Vector3d<int> GetShift()const{return shift;}
		friend I3D_ALGO_EXPORT std::ostream& operator<<(std::ostream &os, const Octagon &se);

	};

	//------------------------
	// GLOBAL FUNCTIONS
	//------------------------
	void I3D_ALGO_EXPORT printNeighbours(std::ostream &os, const std::vector<i3d::Vector3d<int> >);
	void I3D_ALGO_EXPORT printSequence(std::ostream &os, const std::vector<StructuringElement*>);
	/*Returns true if vector vec contains vector3d v*/
	bool I3D_ALGO_EXPORT contains(const i3d::Vector3d<int> v,const std::vector<i3d::Vector3d<int> >vec);
	/** Dilates  neighbourhood in with se (arbitrary structuring element) 
	    and saves result into out */
	void I3D_ALGO_EXPORT simpleDilate(const std::vector<i3d::Vector3d<int> >in,const Arbitrary se,std::vector<i3d::Vector3d<int> >&out);
}; // se
#endif // #ifndef __I3D_SE_H__
