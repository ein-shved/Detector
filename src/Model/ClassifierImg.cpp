/*
 * ClassifierImg.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 14.10.2012
 */

#include "ClassifierImg.h"
#include "../FeatureVector/FeatureVectorImg.h"
#include <stdexcept>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
using namespace Detector;

#undef _ExceptionString
#define _ExceptionString " ClassifierImg:\t"


ClassifierImg::ClassifierImg ( const struct model *in_pModel )
    : Classifier ( in_pModel )
{
	if (s_colorTable.isEmpty()) {
		s_colorTable.resize(256);
		for (size_t i=0; i<256; ++i ) {
			s_colorTable[i] = qRgb(i,i,i);
		}
	}
}
ClassifierImg::ClassifierImg ( const Classifier &in_Classifier )
    : Classifier ( in_Classifier )
{
	if (s_colorTable.isEmpty()) {
		s_colorTable.resize(256);
		for (size_t i=0; i<256; ++i ) {
			s_colorTable[i] = qRgb(i,i,i);
		}
	}
}

Classifier &ClassifierImg::operator = ( const Classifier &in_Classifier )
{
	return Classifier::operator = (in_Classifier);
}
Classifier &ClassifierImg::operator = ( const struct model *in_pModel )
{
	return Classifier::operator = (in_pModel);
}

set<size_t> suppressDuplications ( vector<double> &vEstimates, size_t in_neighborhood, double in_threshold ) {
	in_neighborhood /= 2;
	set<size_t> result;
	if ( (in_threshold <0 ) || (vEstimates.empty() ) )
		return result;
	while (true) {
		vector<double>::iterator iBegin = vEstimates.begin(), iEnd = vEstimates.end();
		vector<double>::iterator max = max_element(iBegin,iEnd);
		if ( max == iEnd ) {
			return result;
		}
		if (*max < in_threshold )
			return result;
		if ( !(result.insert(max - iBegin).second) )
			return result;
		vector<double>::iterator end = max + in_neighborhood;
		if ( end > iEnd ) {
			end = iEnd;
		}
		max -= in_neighborhood;
		if ( max < iBegin ) {
			max = iBegin;
		}
		for ( ; max != end; ++max ) {
			*max = -1;
		}
	}
	return result;
}

std::vector<QRect> ClassifierImg::classify ( const QImage &in_Image, double in_stepPart, double in_dThreshold,
					     size_t in_iWidth, size_t in_iHeight ) const
{
	if ( isNull() ) {
		throw logic_error ( _ExceptionString "Using of NULL Classifier." );
	}
	if ( in_stepPart < 0 || in_stepPart > in_iWidth || in_stepPart > in_iHeight ) {
		throw logic_error ( _ExceptionString "Wrong shifting step." );
	}

	const QImage *pImage = &in_Image;
	QImage imgNew;

	if ( pImage->format() != QImage::Format_Indexed8 )
	{
		imgNew = QImage (in_Image.width(), in_Image.height(), QImage::Format_Indexed8);
		imgNew.setColorTable (s_colorTable);

		for (int y = 0; y < in_Image.height(); ++y){
			for (int x = 0; x < in_Image.width(); ++x){
				QRgb rgb = in_Image.pixel(x, y);
				uint uiGray = 0.2125*qRed(rgb) + 0.7154*qGreen(rgb) + 0.0721*qBlue(rgb);
				imgNew.setPixel(x, y, uiGray);
			}
		}
		pImage = &imgNew;
	}

	size_t step = ( (in_iWidth < in_iHeight) ? in_iWidth : in_iHeight ) / in_stepPart;
	std::vector<QRect> result;
	QRect shifter (0,0, in_iWidth, in_iHeight);
	while ( shifter.y() + shifter.height() <= in_Image.height() ) {
		vector<double> estimates;
		while ( shifter.x() + shifter.width() <= in_Image.width() ) {
			double estimate;
			if ( Classifier::classify ( FeatureVectorImg (*pImage, shifter), &estimate )
							&& -1*estimate > in_dThreshold )
			{
				//cout<<(-1*estimate)<<endl;
				estimates.push_back (-1*estimate);
			} else {
				estimates.push_back (-1);
			}
			bool close = ( shifter.x() + shifter.width() == in_Image.width() );
			shifter.moveLeft ( shifter.x() + step );
			if ( (shifter.x() + shifter.width() > in_Image.width()) && !close ) {
				shifter.moveLeft ( in_Image.width() - in_iWidth );
			}
		}
		set<size_t> suppresed = suppressDuplications (estimates,in_stepPart,0);
		for ( set<size_t>::iterator it = suppresed.begin(),
		      end = suppresed.end(); it != end; ++it)
		{
			shifter.moveLeft((*it)*step);
			result.push_back (shifter);
		}

		bool close = ( shifter.y() + shifter.height() == in_Image.height() );
		shifter.moveLeft (0);
		shifter.moveTop ( shifter.y() + step );
		if ( (shifter.y() + shifter.height() > in_Image.height()) && !close ) {
			shifter.moveLeft ( in_Image.height() - in_iHeight );
		}
	}
	return result;
}

QVector<QRgb> ClassifierImg::s_colorTable;