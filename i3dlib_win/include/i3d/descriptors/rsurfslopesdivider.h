/*
 * i3dlib - image manipulation library
 *
 * Copyright (C) 2000-2015   Centre for Biomedical Image Analysis (CBIA)
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
 * License along with this library; if not, write to the Freere
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
/** 
 * \file rsurfslopesdivider.h
   \brief 2D & 3D RSurf features.
	
	This file contains functions for calculating 2D/3D RSurf features.

	T. Majtner, R. Stoklasa, D. Svoboda. RSurf – The Efficient Texture-based
	Descriptor for Fluorescence Microscopy Images of HEp-2 Cells. In 22nd
	International Conference on Pattern Recognition (ICPR). Los Alamitos, California,
	USA: IEEE Computer Society, 2014. Pages 1194–1199, ISBN 978-1-
	4799-5208-3.
	
	\author Roman Stoklasa <139873@mail.muni.cz>
	\date 2015
*/

#ifndef _SLOPES_DIVIDER_H
#define _SLOPES_DIVIDER_H

#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std; 

class Slope
{
private: 
	int trend; 
	vector<float> values; 

public: 
	Slope();
	int GetTrend();

	bool IsIncreasing();
	bool IsDecreasing(); 

	bool PushBack(float value);
	vector<float> GetValues();

	float GetMinValue();
	float GetMaxValue();

	int GetLength();
	float GetHeight();

	bool IsEmpty(); 

	void Reset();
};


class SlopesDivider 
{
private: 
	vector<Slope> slopes; 
	Slope currentSlope; 

	vector<float> currentFlatZone; 

	void StartNewSlope();
	void StartNewSlope(float value);

public:
	SlopesDivider(); 

	void PushNextPixel(float pixelValue);

	void FinishCurrentSlope();

	vector<Slope> GetSlopes();
}; 
#endif

SlopesDivider::SlopesDivider()
{
	this->currentSlope.Reset();
	this->slopes.clear();
	this->currentFlatZone.clear();
}

void SlopesDivider::StartNewSlope() 
{
	if ( !this->currentSlope.IsEmpty() ) {
		this->slopes.push_back(this->currentSlope); 
	}

	this->currentSlope.Reset();
}

void SlopesDivider::StartNewSlope(float value) 
{
	this->StartNewSlope();
	this->currentSlope.PushBack(value);
}

void SlopesDivider::PushNextPixel(float pixelValue)
{
	if (this->currentFlatZone.size() == 0 || this->currentFlatZone[0] == pixelValue) {
		this->currentFlatZone.push_back(pixelValue);
	}

	bool b = this->currentSlope.PushBack(pixelValue);
	if (!b) {
		this->StartNewSlope(); 

		if (this->currentFlatZone.size() > 0) {
			for (unsigned i = 0; i < this->currentFlatZone.size(); i++) {
				this->currentSlope.PushBack(this->currentFlatZone[i]); 
			}
		}

		this->currentSlope.PushBack(pixelValue);
	}

	if (this->currentFlatZone.size() > 0 && this->currentFlatZone[0] != pixelValue) {
		this->currentFlatZone.clear();
		this->currentFlatZone.push_back(pixelValue);
	}

}

void SlopesDivider::FinishCurrentSlope()
{
	if ( !this->currentSlope.IsEmpty() ) {
		this->slopes.push_back(this->currentSlope); 
	}

	this->currentSlope.Reset(); 
}

vector<Slope> SlopesDivider::GetSlopes()
{
	return this->slopes;
}


Slope::Slope()
{
	this->trend = 0;
	this->values.clear();
}

bool Slope::PushBack(float value)
{
	if (this->trend == 0) {
		if (this->values.size() == 0) {
			this->values.push_back(value);
			return true; 
		} else {
			if (this->GetMaxValue() < value) {
				this->trend = 1;
			}
			if (value < this->GetMinValue()) {
				this->trend = -1;
			}

			this->values.push_back(value); 
			return true; 
		}
	} 

	if (this->trend > 0) {
		if (value < this->GetMaxValue()) {
			return false; 
		} else {
			this->values.push_back(value);
			return true; 
		}
	}

	if (this->trend < 0) {
		if (value > this->GetMinValue()) {
			return false; 
		} else {
			this->values.push_back(value);
			return true; 
		}
	}

	return false;
}

float Slope::GetMaxValue()
{
	float result = (float)INT_MIN; 
	for (vector<float>::iterator it = this->values.begin(); it != this->values.end(); ++it) {
		result = std::max(result, *it);
	}
	return result; 
}

float Slope::GetMinValue()
{
	float result = (float)INT_MAX; 
	for (vector<float>::iterator it = this->values.begin(); it != this->values.end(); ++it) {
		result = min(result, *it);
	}
	return result; 
}

bool Slope::IsIncreasing()
{
	return (this->trend > 0); 
}

bool Slope::IsDecreasing()
{
	return (this->trend < 0); 
}

int Slope::GetLength()
{
	return this->values.size(); 
}

float Slope::GetHeight()
{
	return (this->GetMaxValue() - this->GetMinValue()); 
}

bool Slope::IsEmpty()
{
	return (this->GetLength() <= 0); 
}

void Slope::Reset()
{
	this->trend = 0;
	this->values.clear();
}

vector<float> Slope::GetValues()
{
	return this->values; 
}
