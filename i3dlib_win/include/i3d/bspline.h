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
 * FILE: bspline.h, by Tomáš Šlimar
 *
 * 
 * TODO: needs to be amended and translated!!!
 * 
 */


#ifndef BSPLINE_H_
#define BSPLINE_H_

#include <cstdlib>

class bSplineSurface
{
	private:
		size_t numCpX, numCpY;
		size_t sizeX, sizeY, degree;
		double *cp;
		double *surface;
		bool paramOK;
		bool allocateSurface( void )
		{
			if( sizeX < 1 || sizeY < 1 ) return false;
			if( surface ) return true;
			surface = new double[ sizeX*sizeY ];
			return true;			
		}
//		double deBoor( int degree, const int i, const double t, const double *knotVector );
	public:
//		bSplineSurface( ):cp(0), surface(0){};
		bSplineSurface( const size_t sizeX, const size_t sizeY, const size_t numCpX, const size_t numCpY, const size_t degree )
		{
			cp=NULL;
			surface=NULL;
			paramOK=false;
			setSurfaceParams( sizeX, sizeY, numCpX, numCpY, degree );
		}
		bool setControlPoints( const double *points );
		bool setSurfaceParams( const size_t sizeX, const size_t sizeY, const size_t cpX, const size_t cpY, size_t const degree )
		{
			if( degree<1 || cpX<=degree || cpY<=degree || sizeX<cpX || sizeY<cpY )
			{
				return false;
			}
			paramOK = true;
			if( cp && ( this->sizeX!=sizeX || this->sizeY!=sizeY ) ) delete[] cp;
			if( surface ) delete[] surface;
			numCpX=cpX;
			numCpY=cpY;
			this->degree=degree;
			this->sizeX=sizeX;
			this->sizeY=sizeY;

			return true;
		}
		double getPoint( size_t x, size_t y ) const { return cp?surface[y*sizeX+x]:0; }
		double getPoint( size_t i ) const  { return cp?surface[i]:0; }

		size_t getCpCountX( void ) const { return paramOK?numCpX:0; }
		size_t getCpCountY( void ) const { return paramOK?numCpY:0; }
		size_t getDegree( void ) const { return paramOK?degree:0; }
		size_t getSizeX( void ) const { return paramOK?sizeX:0; }
		size_t getSizeY( void ) const { return paramOK?sizeY:0; }

		double baseFce( size_t degree, const double t, const size_t i, const double *knotVector );

		double *computeKnotVector( const size_t degree );
		double computeIncrementY( void ) const { return paramOK?(double)( numCpY - degree ) / (double)sizeY:0.0f; }
		double computeIncrementX( void ) const { return paramOK?(double)( numCpX - degree ) / (double)sizeX:0.0f; }

		bool compute( void );

		~bSplineSurface()
		{
			if( cp ) delete[] cp;
			if( surface ) delete[] surface;
		}
};

#endif /*BSPLINE_H_*/
