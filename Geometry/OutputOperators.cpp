/***********************************************************************
OutputOperators - Basic iostream output operators for templatized
geometry objects.
Copyright (c) 2009 Oliver Kreylos

This file is part of the Templatized Geometry Library (TGL).

The Templatized Geometry Library is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Templatized Geometry Library is distributed in the hope that it will
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with the Templatized Geometry Library; if not, write to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA
***********************************************************************/

#define GEOMETRY_OUTPUTOPERATORS_IMPLEMENTATION

#ifndef METHODPREFIX
	#ifdef NONSTANDARD_TEMPLATES
		#define METHODPREFIX inline
	#else
		#define METHODPREFIX
	#endif
#endif

#include <Geometry/OutputOperators.h>

#include <iomanip>
#include <Geometry/ComponentArray.h>
#include <Geometry/Box.h>
#include <Geometry/Plane.h>
#include <Geometry/Matrix.h>
#include <Geometry/Rotation.h>
#include <Geometry/OrthonormalTransformation.h>
#include <Geometry/OrthogonalTransformation.h>
#include <Geometry/AffineTransformation.h>
#include <Geometry/ProjectiveTransformation.h>

namespace std {

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::ComponentArray<ScalarParam,dimensionParam>& ca)
	{
	streamsize width=os.width();
	os<<setw(1)<<'('<<setw(width)<<ca[0];
	for(int i=1;i<dimensionParam;++i)
		os<<", "<<setw(width)<<ca[i];
	os<<')';
	return os;
	}

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::Box<ScalarParam,dimensionParam>& b)
	{
	streamsize width=os.width();
	os<<setw(1)<<'{'<<setw(width)<<b.min<<", "<<setw(width)<<b.max<<'}';
	return os;
	}

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::Plane<ScalarParam,dimensionParam>& p)
	{
	streamsize width=os.width();
	os<<setw(1)<<'{'<<setw(width)<<p.getNormal()<<", "<<setw(width)<<p.getOffset()<<'}';
	return os;
	}

template <class ScalarParam,int numRowsParam,int numColumnsParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::Matrix<ScalarParam,numRowsParam,numColumnsParam>& m)
	{
	streamsize width=os.width();
	os<<setw(1)<<'{';
	for(int i=0;i<numRowsParam;++i)
		{
		if(i>0)
			os<<", ";
		os<<'{'<<setw(width)<<m(i,0);
		for(int j=1;j<numColumnsParam;++j)
			os<<", "<<setw(width)<<m(i,j);
		os<<'}';
		}
	os<<'}';
	return os;
	}

namespace {

/************
Helper class:
************/

template <class ScalarParam,int dimensionParam>
class RotationPrinter
	{
	};

template <class ScalarParam>
class RotationPrinter<ScalarParam,2>
	{
	/* Methods: */
	public:
	static ostream& print(ostream& os,const Geometry::Rotation<ScalarParam,2>& r)
		{
		os<<r.getAngle();
		return os;
		}
	};

template <class ScalarParam>
class RotationPrinter<ScalarParam,3>
	{
	/* Methods: */
	public:
	static ostream& print(ostream& os,const Geometry::Rotation<ScalarParam,3>& r)
		{
		streamsize width=os.width();
		os<<setw(1)<<'{'<<setw(width)<<r.getAxis()<<", "<<setw(width)<<r.getAngle()<<'}';
		return os;
		}
	};

}

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::Rotation<ScalarParam,dimensionParam>& r)
	{
	return RotationPrinter<ScalarParam,dimensionParam>::print(os,r);
	}

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::OrthonormalTransformation<ScalarParam,dimensionParam>& t)
	{
	streamsize width=os.width();
	os<<setw(1)<<'{'<<setw(width)<<t.getTranslation();
	os<<", "<<setw(width)<<t.getRotation();
	return os;
	}

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::OrthogonalTransformation<ScalarParam,dimensionParam>& t)
	{
	streamsize width=os.width();
	os<<setw(1)<<'{'<<setw(width)<<t.getTranslation();
	os<<", "<<setw(width)<<t.getRotation();
	os<<", "<<setw(width)<<t.getScaling()<<'}';
	return os;
	}

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::AffineTransformation<ScalarParam,dimensionParam>& t)
	{
	os<<t.getMatrix();
	return os;
	}

template <class ScalarParam,int dimensionParam>
METHODPREFIX
ostream&
operator<<(
	ostream& os,
	const Geometry::ProjectiveTransformation<ScalarParam,dimensionParam>& t)
	{
	os<<t.getMatrix();
	return os;
	}

#if !defined(NONSTANDARD_TEMPLATES)

/****************************************************
Force instantiation of all standard output operators:
****************************************************/

template ostream& operator<<(ostream&,const Geometry::ComponentArray<int,2>&);
template ostream& operator<<(ostream&,const Geometry::Box<int,2>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<int,2,2>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<int,2,3>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<int,3>&);
template ostream& operator<<(ostream&,const Geometry::Box<int,3>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<int,3,3>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<int,3,4>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<int,4>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<int,4,4>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<float,2>&);
template ostream& operator<<(ostream&,const Geometry::Box<float,2>&);
template ostream& operator<<(ostream&,const Geometry::Plane<float,2>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<float,2,2>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<float,2,3>&);
template ostream& operator<<(ostream&,const Geometry::Rotation<float,2>&);
template ostream& operator<<(ostream&,const Geometry::OrthonormalTransformation<float,2>&);
template ostream& operator<<(ostream&,const Geometry::OrthogonalTransformation<float,2>&);
template ostream& operator<<(ostream&,const Geometry::AffineTransformation<float,2>&);
template ostream& operator<<(ostream&,const Geometry::ProjectiveTransformation<float,2>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<float,3>&);
template ostream& operator<<(ostream&,const Geometry::Box<float,3>&);
template ostream& operator<<(ostream&,const Geometry::Plane<float,3>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<float,3,3>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<float,3,4>&);
template ostream& operator<<(ostream&,const Geometry::Rotation<float,3>&);
template ostream& operator<<(ostream&,const Geometry::OrthonormalTransformation<float,3>&);
template ostream& operator<<(ostream&,const Geometry::OrthogonalTransformation<float,3>&);
template ostream& operator<<(ostream&,const Geometry::AffineTransformation<float,3>&);
template ostream& operator<<(ostream&,const Geometry::ProjectiveTransformation<float,3>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<float,4>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<float,4,4>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<double,2>&);
template ostream& operator<<(ostream&,const Geometry::Box<double,2>&);
template ostream& operator<<(ostream&,const Geometry::Plane<double,2>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<double,2,2>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<double,2,3>&);
template ostream& operator<<(ostream&,const Geometry::Rotation<double,2>&);
template ostream& operator<<(ostream&,const Geometry::OrthonormalTransformation<double,2>&);
template ostream& operator<<(ostream&,const Geometry::OrthogonalTransformation<double,2>&);
template ostream& operator<<(ostream&,const Geometry::AffineTransformation<double,2>&);
template ostream& operator<<(ostream&,const Geometry::ProjectiveTransformation<double,2>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<double,3>&);
template ostream& operator<<(ostream&,const Geometry::Box<double,3>&);
template ostream& operator<<(ostream&,const Geometry::Plane<double,3>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<double,3,3>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<double,3,4>&);
template ostream& operator<<(ostream&,const Geometry::Rotation<double,3>&);
template ostream& operator<<(ostream&,const Geometry::OrthonormalTransformation<double,3>&);
template ostream& operator<<(ostream&,const Geometry::OrthogonalTransformation<double,3>&);
template ostream& operator<<(ostream&,const Geometry::AffineTransformation<double,3>&);
template ostream& operator<<(ostream&,const Geometry::ProjectiveTransformation<double,3>&);

template ostream& operator<<(ostream&,const Geometry::ComponentArray<double,4>&);
template ostream& operator<<(ostream&,const Geometry::Matrix<double,4,4>&);

#endif

}
