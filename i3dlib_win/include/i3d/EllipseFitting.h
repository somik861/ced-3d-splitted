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
    @brief Ellipse fitting routines.

    @author Matus Kotry (Ko3@mail.muni.cz), Ondrej Danek (xdanek2@fi.muni.cz)
    @date 2011
*/ 

#ifndef I3D_ELLIPSEFITTING_H
#define I3D_ELLIPSEFITTING_H

#include <vector>
#include "algo_export.h"
#include "image3d.h"

namespace i3d
{
    /** Ellipse fitting code. Namespace used to separate typedefs from the rest of i3d. 
    
        Example:
        @code
        i3d::Image3d<bool> seg; // Binary mask of the foreground

        // Approximate binary mask by polygons
        i3d::EllipseFitting::PolygonSystem ps;
        i3d::EllipseFitting::makePolygons(seg, 3.2, ps);

        // Fit ellipses
        std::vector<i3d::EllipseFitting::Ellipse> ellipses;
        i3d::EllipseFitting::fitEllipses(ps, 50, 70, seg.GetSizeX(), seg.GetSizeY(), ellipses);
        @endcode    
    */
    namespace EllipseFitting
    {
        ////////////////////////////////////////////////////////////////////////
        //
        // APPROXIMATION OF REGIONS BY POLYGONS - AUXILIARY METHODS
        //
        ////////////////////////////////////////////////////////////////////////

        /** Precision of the fitting code. */
        typedef double VertexPrec;
        /** Vertex data type. */
        typedef i3d::Vector3d<VertexPrec> Vertex;
        /** List of vertexes. */
        typedef std::vector<Vertex> VertexList;

        /** Array of points. */
        struct Polygon
        {
            /** Polygon ID. */
            size_t m_id;
            /** Polygon vertexes. */
            VertexList m_vertex_list;
            /* Flag determining if the polygon is a hole of another polygon. */
            bool m_is_hole;
        };

        /** Set of polygons.
        * Each polygon may have holes (a polygon that lies inside of other polyon). Those share
        * ID with polygon in which they are contained. Every non-hole polygon has it's unique ID.  
        */
        typedef std::vector<Polygon> PolygonSystem;

        /** Conversion of contours to polygons.
          *	Converts binary image of contours to polygons. It is recomended to use contours returned
          * by getContours(). All polygons are automaticaly approximated by approxPolygon() function.
          *
          * @param[in] contours The binary image containing the contours.
          * @param[in] dTh Level of approximation for approxPolygon() function. Recommended range [3,4].
          *
          *	@retval PolygonSystem The distance.
          */
        I3D_ALGO_EXPORT void makePolygons(const i3d::Image3d<bool> &input, double dTh, PolygonSystem &polygons);

        ////////////////////////////////////////////////////////////////////////
        //
        // ELLIPSE FITTING
        //
        ////////////////////////////////////////////////////////////////////////

        /** Ellipse representation class. */
        class Ellipse 
        {
        private:
            Vertex center;
            double a, b;
            double angle;

        public:
            /** Default constructor. */
            Ellipse()
            {}

            /** Copy constructor. */
            Ellipse(const Ellipse &el)
            {
                *this = el;
            }

            /** Assignment operator. */
            Ellipse& operator= (const Ellipse &el)
            {
                center = el.center;
                a = el.a;
                b = el.b;
                angle = el.angle;
                return *this;
            }

            /** Constructor 1.
            * Constructs an ellipse given by several parameters listed below.
            *
            * @param[in] x X coordinate of the center.
            * @param[in] y Y coordinate of the center.
            * @param[in] a Length of semi-major axis.
            * @param[in] b Length of semi-minor axis.
            * @param[in] angle Angle of the ellipse in radians.
            */
            void Set(const Vertex &center, double a, double b, double angle) 
            {
                this->center = center;
                this->a = a;
                this->b = b;
                this->angle = angle;
            }

            /** Constructor 2.
              * Constructs an ellipse given by general conic equation:
              * ax^2 + bxy + cy^2 + dx + fy + g
              * (shx, shy) is a translation of the coordinate system
              */
            bool Set(double a, double b, double c, double d, double f, double g, double shx, double shy);

            /** Get ellipse center. */
            const Vertex &getCenter() const { return center; }
            /** Length of the longer semi-axis. */
            double getMajor() const { return a > b ? a : b; }
            /** Length of the shorter semi-axis. */
            double getMinor() const { return a > b ? b : a; }
            /** Length of the semi-axis stored as "A". */
            double getA() const { return a; }
            /** Length of the semi-axis stored as "B". */
            double getB() const { return b; }
            double getAngle() const { return angle; }

            void setCenter(const Vertex &center) 
            { 
                this->center = center; 
            }

            void setA(double a) { this->a = a; }
            void setB(double b) { this->b = b; }
            void setAngle(double angle) { this->angle = angle; }

            /** Tests if a point lies in an ellipse.
              * 
              * @param[in] pt The point.
              * @param[in] tolerance Distance of point from edge of ellipse that will be still considered as
              *						 if the point was in the ellipse (or out of the ellipse, if negative). 
              */
            bool containsPoint(const Vertex &pt, double tolerance=0) const;
        };

        /** Multiple ellipse fitting into a polygon system.
          * Same as fitEllipses(Polygon &poly,...) but for a set of polygons. It also respects holes
          * in the polygons, if there are some.
          *
          * It is recomended to use a polygon system generated by makePolygons() function.
          *
          * @param[in] polys The set of polygons.
          * @param[in] lowDist Constant used to determine the scale of image. It should approximately
          *					   equal the size of the smalest ellipse's minor axis.
          * @param[in] hiDist Constant used to determine the scale of image. It should approximately
          *					   equal the size of the largest ellipse's semi-major axis.
          * @param[in] w Width of image
          * @param[in] h Height of image
          * @param[out] ellipses vector<Ellipse> The set of newly fitted ellipses.
          */
        I3D_ALGO_EXPORT void fitEllipses(PolygonSystem &polys, double lowDist, double hiDist, size_t w, size_t h, std::vector<Ellipse> &ellipses);
            
        /** Draws the ellipse into chosen image.
          *
          * @param[in,out] canvas The image where the ellipse will be drawn.
          * @param[in] color Color of the ellipse.
          * @param[in] showCenter A cross marking the center of ellipse will be drawn if set to true.
          * @param[in] steps Level of detail. (Numbers of points of ellipse that will be calculated.
          *     These are connected by straight lines.)
          */
        template <class VOXEL>
        I3D_ALGO_EXPORT void drawEllipse(const Ellipse &el, i3d::Image3d<VOXEL> &canvas, VOXEL color, bool showCenter=false, int steps=36);
    }
}

#endif
