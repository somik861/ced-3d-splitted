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
 * FILE: illumination_correction.h, by Tomáš Šlimar
 *
 * illumination correction
 *
 * 
 * TODO: needs to be amended and translated!!!
 * 
 */

#ifndef __ILLUMINATION_CORRECTION_H__
#define __ILLUMINATION_CORRECTION_H__

#include <vector>
#include "histogram.h"
#include "bspline.h"
#include "image3d.h"

namespace i3d
{

/////	Pomocne funkce pro Gaussovo vyhlazeni

//	Vrati hodnotu normalniho rozdeleni v bode x pro stredni hodnotu 0 a rozptyl sigma^2
	inline double getGauss( const size_t x, const double sigma )
	{
		return ((1.0/(sigma*std::sqrt(M_PI*2)))*std::exp(-1*((x*x)/(2*sigma*sigma))));
	}

//	Aplikuje masku mask na histogram data v bode i a vrati vypocitanou hodnotu
	unsigned long aplicateMask( const Histogram &data, const size_t i, const std::vector<double> &mask );

//	Vygeneruje masku normovaneho Gaussova rozdeleni a vrati jako vector
	std::vector<double> generateGaussMask( const double sigma );



///// Pomocne funkce pro funkci correctIlluminationBsplineAprox()


//  Aproximuje bspline plochu na pozadi obrazku img a do surface ulozi kontrolni body teto plochy.
//  Bspline plochu nepocita. Pozadi obrazku je definovano binarnim obrazkem background - do aproximace
//	se pocitaji pouze body, ktere jsou b v background nastaveny na backgroudSign.
//	Img, background a surface museji mit stejnou velikost.
	template <	class T> I3D_ALGO_EXPORT bool fitBspline(
		const Image3d<T> &img, bSplineSurface &surface,
		const Image3d<bool> &background, bool backgroundSign = false );

	template <class T> I3D_ALGO_EXPORT double getRMS( T *data, size_t size );

//	Vrati hodnotu prahu daneho prvnim lokalnim maximem v druhe derivaci histogramu obrazku img
	template <class T> I3D_ALGO_EXPORT size_t getThreshold( Image3d<T> &img );

//	Prahuje obrazek in. Vysledek vraci jako binarni obrazek out. Prahovou hodnotu voli automaticky
//	funkci getThreshold()
	template <class T> I3D_ALGO_EXPORT void thresholdBackground( Image3d<T> &in, Image3d<bool> &out );

//	Pokusi se zjistit nerovnomerne podsviceni v obrazku o a toto vrati jako obrazek background.
//	Zbyle parametry urcuji vlastnosti bspline plochy - BSplineCpCountX pocet kontrolnich bodu v ose X,
//	bSplineCpCountY v ose Y a bSplineDegree urcuje stupen plochy. Jestlize vse probehlo v poradku vraci
//	true, jinak false
	template <class T> I3D_ALGO_EXPORT bool estimateBackground( 
		const Image3d<T> &o, Image3d<T> &out,
		int bSplineCpCountX, int bSplineCpCountY, int bSplineDegree );





//	Funkce se pokusi odstranit nerovnomerne podsviceni momoci aproximace B-spline plochy na pixely
//	pozadi a nasledne upravy. Parametr in je puvodni obrazek, do parametru out se ulozi jiz opraveny.
//	Parametr previewPercet urcuje, o kolik procet se zmensi obrazek na kterem se budou provadet vypocty.
//	To umoznuje zvyseni rychlosti na ukor presnosti. Zbyle parametry urcuji vlastnosti plochy, ktera
//	reprezentuje pozadi. Pocet kontrolnich bodu v ose X a Y a stupen plochy.
	template < class T > I3D_ALGO_EXPORT bool correctIlluminationBsplineAprox( 
		const Image3d<T> &in, Image3d<T> &out, int previewPercent=100,
		int bSplineCpCountX=4, int bSplineCpCountY=4, int bSplineDegree=3 );

	/** Filter parameters for a homomorphic filtering method. */
	struct I3D_ALGO_EXPORT HomomorphicFilterParams
	{
		double gamma_low;
		double gamma_high;
		double c;
		double D0;

		/** Constructor. */
		HomomorphicFilterParams() { SetIdentity(); };
		/** Destructor. */
		~HomomorphicFilterParams() {};
		/** Set parameters in such a way that represent an identical transformation. */
		void SetIdentity() { gamma_low = 1.0; gamma_high = 1.0; c = 1.0; D0 = 1.0; };
	};

/////	Homomorfni filtrovani

	template < class T > I3D_ALGO_EXPORT void homFilter(Image3d<T> &in, Image3d<T> &out, const HomomorphicFilterParams &params);

}

#endif
