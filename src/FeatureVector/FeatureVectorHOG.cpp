/*
 * FeatureVectorHOG.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 22.10.2012
 */

#include <stdexcept>
#include <iostream>
#include "FeatureVectorHOG.h"

using namespace Detector;
using namespace std;

#undef _ExceptionString
#define _ExceptionString " FeatureVectorHOG:\t"

FeatureVectorHOG::FeatureVectorHOG ( const FeatureVector &in_FVector )
    : FeatureVector (in_FVector)
{}
FeatureVectorHOG::FeatureVectorHOG ( const HOGImage &in_Image,
		   const QPoint &in_pPosition,
		   size_t in_iWidth,
		   size_t in_iHeight )
    : FeatureVector ()
{
	constructor(in_Image, QRect (in_pPosition.x()/_Block_Size,
				     in_pPosition.y()/_Block_Size,
				     in_iWidth/_Block_Size,
				     in_iHeight/_Block_Size ));
}
FeatureVectorHOG::FeatureVectorHOG ( const HOGImage &in_Image, const QRect &in_pRect)
    : FeatureVector ()
{
	constructor(in_Image, QRect (in_pRect.x()/_Block_Size,
				     in_pRect.y()/_Block_Size,
				     in_pRect.width()/_Block_Size,
				     in_pRect.height()/_Block_Size ));
}
FeatureVectorHOG::~FeatureVectorHOG ()
{}
void FeatureVectorHOG::constructor ( const HOGImage &in_Image, const QRect &in_pRect )
{
	size_t m_iWidth = in_pRect.x() + in_pRect.width();
	size_t m_iHeight = in_pRect.y() + in_pRect.height();
	m_vFeatures.clear();
	m_vFeatures.reserve (in_pRect.width()*in_pRect.height()*HOGPixel::length());
	for (size_t y = in_pRect.y(); y < m_iHeight; ++y ) {
		for (size_t x = in_pRect.x(); x < m_iWidth; ++x ) {
			size_t length = HOGPixel::length();
			for (size_t uHOGIndex = 0; uHOGIndex < length; ++uHOGIndex) {
				m_vFeatures.push_back ( in_Image(x,y)[uHOGIndex]);
			}
		}
	}
}
FeatureVectorHOG *FeatureVectorHOG::clone() const
{
	return new FeatureVectorHOG (*this);
}

FeatureVectorHOGlink::FeatureVectorHOGlink ( const FeatureVectorHOGlink &in_FVector )
    : m_Image (in_FVector.m_Image)
    , m_pPosition (in_FVector.m_pPosition)
    , m_iWidth (in_FVector.m_iWidth)
    , m_iHeight (in_FVector.m_iHeight)
{}
FeatureVectorHOGlink::FeatureVectorHOGlink ( const HOGImage &in_Image,
		   const QPoint &in_pPosition,
		   size_t in_iWidth,
		   size_t in_iHeight )
    : m_Image (in_Image)
    , m_pPosition (in_pPosition.x()/_Block_Size, in_pPosition.y()/_Block_Size)
    , m_iWidth (in_iWidth/_Block_Size)
    , m_iHeight (in_iHeight/_Block_Size)
{}
FeatureVectorHOGlink::FeatureVectorHOGlink ( const HOGImage &in_Image, const QRect &in_pRect)
    : m_Image (in_Image)
    , m_pPosition (in_pRect.x()/_Block_Size, in_pRect.y()/_Block_Size)
    , m_iWidth (in_pRect.width()/_Block_Size)
    , m_iHeight (in_pRect.height()/_Block_Size)
{}
FeatureVectorHOGlink::~FeatureVectorHOGlink ()
{}

double FeatureVectorHOGlink::operator [] ( size_t in_iIndex) const
{
	size_t uHOGIndex = in_iIndex % HOGPixel::length();
	in_iIndex /= HOGPixel::length();
	size_t x = m_pPosition.x() + in_iIndex % m_iWidth;
	size_t y = m_pPosition.y() + in_iIndex / m_iWidth;
	if ( y >= m_iHeight + m_pPosition.y() ) {
		throw logic_error ( _ExceptionString "Wrong indexing." );
	}
	const HOGPixel &pix = m_Image(x,y);
	return pix[uHOGIndex];
}
size_t FeatureVectorHOGlink::length () const
{
	return m_iWidth*m_iHeight*HOGPixel::length();
}
FeatureVectorHOGlink *FeatureVectorHOGlink::clone() const
{
	return new FeatureVectorHOGlink (*this);
}
