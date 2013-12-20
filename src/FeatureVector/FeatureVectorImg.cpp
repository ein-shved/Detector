/*
 * FeatureVectorImg.cpp
 * 
 * Designed and written by
 *	Shvedov Yury 321 group.
 *
 * Powered by
 *	MediaLab, CMC MSU
 *
 * 12.10.2012 
 */

#include <stdexcept>
#include <cmath>
#include <iostream>
#include "FeatureVectorImg.h"
#include "HOGImage.h"

using namespace std;
using namespace Detector;

#undef _ExceptionString
#define _ExceptionString " FeatureVectorImg:\t" 

#define _Blocks_Number ((_AreaHeight/_Block_Size)*(_AreaWidth/_Block_Size))


FeatureVectorImg::FeatureVectorImg ( const QImage &in_Image, 
				     const QPoint &in_pPosition,
	       			     size_t in_iWidth, 
				     size_t in_iHeight )
{
	m_constructor ( in_Image, QRect (in_pPosition.x(), in_pPosition.y(), in_iWidth, in_iHeight) );
}
FeatureVectorImg::FeatureVectorImg ( const QImage &in_Image,
				     const QRect &in_Rect )
{
	m_constructor ( in_Image, in_Rect );
}
FeatureVectorImg::FeatureVectorImg ( const FeatureVectorImg &in_FVector )
	: FeatureVector ( in_FVector )
{}
FeatureVectorImg *FeatureVectorImg::clone() const
{
	return new FeatureVectorImg (*this);
}

void FeatureVectorImg::m_constructor ( const QImage &in_Image, const QRect &in_Rect )
{
	if ( ! in_Image.rect().contains( in_Rect ) )
	{
		throw logic_error ( _ExceptionString
				"Wrong interest rectangle" );
	}
	HOGPixel gradient;
	size_t in_iWidth = in_Rect.width();
	size_t in_iHeight = in_Rect.height();
	m_vFeatures.clear();
	m_vFeatures.reserve ( (in_iHeight/_Block_Size)*(in_iWidth/_Block_Size)*gradient.length());

	int posX = in_Rect.x();
	int posY = in_Rect.y();

	for ( size_t y = 0; y <= in_iHeight - _Block_Size; y+=_Block_Size ) {
		for ( size_t x=0; x <= in_iWidth - _Block_Size; x+=_Block_Size ) {
			gradient ( in_Image, QPoint ( posX + x, posY + y ) );
			for ( size_t i =0; i < gradient.length(); ++i ){
				m_vFeatures.push_back(gradient[i]);
			}
		}
	}
}
