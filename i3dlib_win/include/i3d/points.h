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

/** \file points.h
	\brief 3D point and point-sets representation - header

	This file defines 3D points and 3D point-sets. 

	i3dlib contains also similar class Vector3d in vector3d.h, which was added to 
	the library	slightly earlier. There will be an attempt to unify these two
	classes.

	\todo Better layout out of points.h and points.cc

	\author Petr Matula (pem@fi.muni.cz) 2001, 
	\author Petr Mejzlík (mejzlik@fi.muni.cz) 2001
 */


/*-*-c++-*-
 * FILE: points.h
 *
 * Points and point sets representations
 *
 * Petr Matula (pem@fi.muni.cz) 2002
 */

#ifndef __POINTS_H__
#define __POINTS_H__

#include "basic.h"
#include <vector>
#include <valarray>
#include <numeric>
#include <string.h>
#include <iostream>
#include <iomanip>
#include "algo_export.h"
#ifndef _MSC_VER
#include <cmath>
#endif

namespace i3d {

  template <class T> class I3D_ALGO_EXPORT Point3d
  {
    T coor[3];
  public:
    /////////////////////////////////////////////////
    // costructors / destructors
    /////////////////////////////////////////////////
    Point3d(T x = 0, T y = 0, T z = 0) { 
      coor[0] = x; coor[1] = y; coor[2] = z; };
    Point3d(T data[3]) {
      memcpy(coor, data, sizeof(T) * 3);
    }
    Point3d(const Point3d<T> &p) {
      memcpy(coor, p.coor, sizeof(T) * 3);
    }
    /////////////////////////////////////////////////
    // member functions 
    /////////////////////////////////////////////////
    T x() const {return coor[0];};
    T y() const {return coor[1];};
    T z() const {return coor[2];};
    T* data() { return coor; };
    const T* data() const { return coor; };
      
    /////////////////////////////////////////////////
    // member operators 
    /////////////////////////////////////////////////
    const T &operator[](size_t i) const { return coor[i]; };
    T &operator[](size_t i) {
#ifdef I3D_DEBUG
      if (i > 3)
        throw InternalException("Point3d: Out of Bounds");
#endif
      return coor[i];
    };

    Point3d<T> &operator +=(const Point3d<T> &p) {
      coor[0] += p.coor[0]; coor[1] += p.coor[1]; coor[2] += p.coor[2];
      return *this;
    };
    
    Point3d<T> &operator -=(const Point3d<T> &p) {
      coor[0] -= p.coor[0]; coor[1] -= p.coor[1]; coor[2] -= p.coor[2];
      return *this;
    };
    
    Point3d<T> &operator /=(const Point3d<T> &p) {
      coor[0] /= p.coor[0]; coor[1] /= p.coor[1]; coor[2] /= p.coor[2];
      return *this;
    };

    Point3d<T> &operator *=(const T &k) {
      coor[0] *= k; coor[1] *= k; coor[2] *= k;
      return *this;
    };

	Point3d<T> &operator *=(const Point3d<T> &p) {
      coor[0] *= p.coor[0]; coor[1] *= p.coor[1]; coor[2] *= p.coor[2];
      return *this;
    };

    Point3d<T> &operator /=(const T &k) {
      coor[0] /= k; coor[1] /= k; coor[2] /= k;
      return *this;
    };

    template <class T1> Point3d(const Point3d<T1> &p) {coor[0] = p[0];coor[1] = p[1];coor[2] = p[2]; }
    template <class T1> Point3d<T> &operator=(const Point3d<T1> &p) {
      coor[0] = p[0]; coor[1] = p[1]; coor[2] = p[2]; return *this; }
  };
//  <<<<<<< points.h

  //
  // non-member operators
  //
  ///////////////////////////////////////////
  // input/output operators 
  ///////////////////////////////////////////
  template <class T>
  inline std::ostream& operator<< (std::ostream & os, const Point3d<T> &p) {
	os << std::setw(8) << p[0] << "  " << std::setw(8) << p[1] << "  " << std::setw(8) << p[2];
    return os;
  };

  template <class T>
  inline std::istream& operator>> (std::istream & is, Point3d<T> &p) {
    is >> p[0] >> p[1] >> p[2];
    return is;
  };
  ///////////////////////////////////////////
  // unary operators 
  ///////////////////////////////////////////
  template <class T>
  inline T norm2(const Point3d<T> &p) {
    return p[0]*p[0] + p[1]*p[1] + p[2]*p[2];
  }
  //    =======
  // sprod renamed to dot_prod
  template <class T> T dot_prod(const Point3d<T> &p1, const Point3d<T> &p2) {
    return p1.x() * p2.x() + p1.y() * p2.y() + p1.z() * p2.z();
  };

  // vector product
  template <class T> Point3d<T> vec_prod(const Point3d<T> &p1, const Point3d<T> &p2)
  {
	  return Point3d<T>(
		  p1.y() * p2.z() - p1.z() * p2.y(),
		  p1.z() * p2.x() - p1.x() * p2.z(), 
		  p1.x() * p2.y() - p1.y() * p2.x() );
  }

  // dist deleted, it is equivalent to norm
  //  template <class T> double dist(Point3d<T> &p) {return std::sqrt(dist2(p));};

  //  dist2 deleted, it is equivalent to norm2
  //    template <class T> T dist2(Point3d<T> &p) {return sprod(p, p);};
  //  >>>>>>> 1.4
  
	template <class T>
		inline Point3d<T> operator- (const Point3d<T> &p)
	{
		return Point3d<T>(-p.x(), -p.y(), -p.z());
	}

  template <class T>
  inline double norm(const Point3d<T> &p) {
    return std::sqrt(norm2(p));
  }
  
  template <class T>
  inline double dist(const Point3d<T> &p1,const Point3d<T> &p2) {
    return norm(p2 - p1);
  }
  
  template <class T>
  inline Point3d<T> min(const Point3d<T> &p1,const Point3d<T> &p2) {
	return Point3d<T>(std::min(p1[0], p2[0]), std::min(p1[1], p2[1]), std::min(p1[2], p2[2]));
  }
  
  template <class T>
  inline Point3d<T> max(const Point3d<T> &p1,const Point3d<T> &p2) {
	  return Point3d<T>(std::max(p1[0], p2[0]), std::max(p1[1], p2[1]), std::max(p1[2], p2[2]));
  }
  
  template <class T>
  inline Point3d<T> abs(const Point3d<T> &p) {
    return Point3d<T>( std::abs(p[0]), std::abs(p[1]), std::abs(p[2]) );
  }
  
  ///////////////////////////////////////////
  // operators Point3d<T> op Point3d<T>
  ///////////////////////////////////////////
  template <class T>
  inline Point3d<T> operator+ (const Point3d<T> &p1, const Point3d<T> &p2) {
    Point3d<T> tmp(p1); tmp += p2; return tmp; };

  template <class T>
  inline Point3d<T> operator- (const Point3d<T> &p1, const Point3d<T> &p2) {
    Point3d<T> tmp(p1); tmp -= p2; return tmp; };

  template <class T>
  inline Point3d<T> operator/ (const Point3d<T> &p1, const Point3d<T> &p2) {
    Point3d<T> tmp(p1); tmp /= p2; return tmp; };

  /////////////////////////////////////////////////////
  // operators T op Point3d<T> and Point3d<T> op T
  /////////////////////////////////////////////////////

  template <class T>
  inline Point3d<T> operator* (const T &k, const Point3d<T> &p) {
    Point3d<T> tmp(p); tmp *= k; return tmp; };

  template <class T>
  inline Point3d<T> operator* (const Point3d<T> &p, const T &k) {
    Point3d<T> tmp(p); tmp *= k; return tmp; };

  template <class T>
  inline Point3d<T> operator/ (const T &k, const Point3d<T> &p) {
    Point3d<T> tmp(p); tmp /= k; return tmp; };

  template <class T>
  inline Point3d<T> operator/ (const Point3d<T> &p, const T &k) {
    Point3d<T> tmp(p); tmp /= k; return tmp; };

  ///////////////////////////////////////////////////////////////////////////
  //
  // Point Set representation
  //
  ///////////////////////////////////////////////////////////////////////////
  
  template <class T> class I3D_ALGO_EXPORT PointSet
  {
	size_t capacity;
    size_t sz;
    Point3d<T> *data_;

    mutable T **ptrs_; //array of pointers on data points
    // initialized when ptrs function is used for the first time

    void InitPtrs(void) const {
      ptrs_ = new T* [sz+1];
      for (size_t i = 0; i < sz; ++i)
        ptrs_[i] = data_[i].data();
    };
    
  public:
    typedef Point3d<T> *iterator;
    typedef const Point3d<T> * const_iterator;
    
    size_t size() const { return sz; };
    void resize(size_t n) {
		sz = n;
		if (n <= capacity)
			return;
      capacity = n;
      if (ptrs_) { delete [] ptrs_; ptrs_ = NULL; }
      if (data_) delete [] data_;
      data_ = new Point3d<T>[sz+1];
    };
    
    PointSet(): capacity(0), sz(0), data_(0), ptrs_(0) {};
  // sz+1 changed to sz 
    PointSet(size_t n): capacity(n), sz(n), data_(0), ptrs_(0) { data_ = new Point3d<T>[sz]; };
    
    PointSet(T *d, size_t n): capacity(n), sz(n), data_(0), ptrs_(0) {
  // sz+1 changed to sz 
      data_ = new Point3d<T>[sz];
      memcpy(data_,d,sizeof(Point3d<T>)*sz);
    };
    
    PointSet(std::vector< Point3d<T> > &p): capacity(p.size()), sz(p.size()) {
      data_ = new Point3d<T>[sz];
      for (size_t i = 0; i < p.size(); ++i)
        data_[i] = p[i]; 
    }
    
    PointSet(const PointSet &ps): capacity(0), sz(0), data_(0), ptrs_(0) { *this = ps;};
    ~PointSet() {
      if (data_) delete [] data_; if (ptrs_) delete [] ptrs_;
    };

    PointSet<T> &operator=(const PointSet<T> &ps) {
      if (data_) delete [] data_; if (ptrs_) delete [] ptrs_;
      sz = ps.sz;
	  capacity = ps.sz;
      ptrs_=0;
      data_ = new Point3d<T>[ps.sz+1];
      memcpy(data_, ps.data_, sizeof(Point3d<T>) * sz);
      return *this;
    }
    
    Point3d<T> &operator[] (size_t idx) {
#ifdef I3D_DEBUG
      if (idx > sz)
        throw InternalException("PointSet: Out of Bounds");
#endif
      return data_[idx];
    }
    
    const Point3d<T> &operator[] (size_t idx) const {
#ifdef I3D_DEBUG
      if (idx > size())
        throw InternalException("PointSet: Out of Bounds");
#endif
      return data_[idx];
    }
    
    PointSet & operator+= (const Point3d<T> &p) {
      for (size_t i = 0; i < size(); ++i)
        { data_[i] += p; }
      return *this;
    }

	PointSet & operator-= (const Point3d<T> &p) {
      for (size_t i = 0; i < size(); ++i)
        { data_[i] -= p; }
      return *this;
    }

	PointSet & operator*= (const Point3d<T> &p) {
      for (size_t i = 0; i < size(); ++i)
        { data_[i] *= p; }
      return *this;
    }

	iterator begin() { return data_; }
    iterator end() { return data_ + sz; }
    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_ + sz; }
    T *data() { return data_[0].data(); }
    const T *data() const { return data_[0].data(); }

    // return data points as T** (e.g. required by ANN library)
    T **ptrs() { if (!ptrs_) InitPtrs(); return ptrs_; }
    T **ptrs() const { if (!ptrs_) InitPtrs(); return ptrs_; }
  };

  // Call this function to be sure that your compiler
  // stores points in PointSets continuously in memory (i.e.
  // no alignment is performed in class Point3d<T>)
  template <class T> inline bool PointSetIsContinuous(void) {
    return sizeof(Point3d<T>)==sizeof(T)*3;
  }

  template <class T> std::ostream& operator<< (std::ostream &os, const PointSet<T> &ps) {
    for (size_t i = 0; i < ps.size(); ++i)
      os << ps[i] << std::endl;;
    return os;
  }

  ////////////////////////////////////////////////////////
  //
  // Functions
  //
  ////////////////////////////////////////////////////////

  template <class T> inline Point3d<T> CenterOfGravity(const PointSet<T> &ps) {
    return accumulate(ps.begin(), ps.end(), Point3d<T>()) / T(ps.size());
  };

#ifdef WITH_BLAS
// Points in point set p_in are multiplied by affine transformation matrix
// and are stored to p_out. The last row of affine transformation matrix
// mat should have the form [0 0 0 1]' (its real values are ignored)
  I3D_ALGO_EXPORT void ApplyTransMat(const PointSet<double> &p_in, PointSet<double> &p_out,
                                   double mat[4][4]);

#endif

  enum Direction {AXIS_X = 0, AXIS_Y = 1, AXIS_Z = 2}; 
  
  // convert polar coordinates to cartesian coordinates
  // coordinate axis is simply copied: p_out[i][axis] = p_in[i][axis];
  // and let A = {a1, a2} = {0, 1, 2} \ {axis}
  // then remaining coordinates are set as 
  // p_out[i][a1] = r * sin(phi), where phi = pin[i][a1] is angle
  // p_out[i][a2] = r * cos(phi),   and r   = pin[i][a2] is radius
  // p_out is appropriately resized.
  I3D_ALGO_EXPORT void Pol2Cart(const PointSet<double> &p_in, PointSet<double> &p_out,
                              Direction axis = AXIS_Z);

  // Inverse function to PolToCart
  //   p_out[i][axis] = p_in[i][axis];
  //   p_out[i][a1] = atan2(x,y),      where x = pin[i][a1] is angle
  //   p_out[i][a2] = sqrt(x^2 + y^2),   and r = pin[i][a2] is radius
  I3D_ALGO_EXPORT void Cart2Pol(const PointSet<double> &p_in, PointSet<double> &p_out,
                              Direction axis = AXIS_Z);
  
  // convert spherical coordinates to cartesian coordinates
  // pin[i][0] is radius
  // pin[i][1] is azimuthal angle in radians
  // pin[i][2] is polar angle in radians
  I3D_ALGO_EXPORT void Spherical2Cart(const PointSet<double> &p_in, PointSet<double> &p_out);

  // Inverse function to SphericalToCart
  I3D_ALGO_EXPORT void Cart2Spherical(const PointSet<double> &p_in, PointSet<double> &p_out);
  
} // of i3d namespace

#endif
