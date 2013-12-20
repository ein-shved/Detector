/*
 * HOGImage.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 19.10.2012
 */

#include <cmath>
#include <stdexcept>
#include <iostream>
#include "HOGImage.h"

#undef _ExceptionString
#define _ExceptionString "HOGImage:\t"

using namespace std;
using namespace Detector;


const size_t HOGPixel::s_HOGVectorLength = _HOGVectorLength;
HOGImage::HOGImage (const QImage &in_Image)
{
	constructor(in_Image);
}
HOGImage::HOGImage (const QString &in_sImage)
{
	constructor (QImage(in_sImage));
}
bool HOGImage::isNull () const
{
	return m_mImage.empty();
}
void HOGImage::constructor (const QImage &in_Image)
{
	if ( in_Image.isNull()) {
		return;
	}
	size_t in_iHeight = in_Image.height();
	size_t in_iWidth = in_Image.width();

	HOGPixel pixel;
	in_iHeight /= _Block_Size;
	in_iWidth /= _Block_Size;
	for ( size_t y = 0; y < in_iHeight; ++y ) {
		m_mImage.push_back(std::vector<HOGPixel>());
		for ( size_t x=0; x < in_iWidth; ++x) {
			pixel (in_Image, QPoint ( x*_Block_Size, y*_Block_Size ));
			m_mImage[y].push_back ( pixel );
		}
	}
}
const HOGPixel &HOGImage::operator () (size_t x, size_t y) const
{
	return m_mImage[y][x];
}
size_t HOGImage::width () const
{
	if ( m_mImage.empty() ) {
		throw logic_error ( _ExceptionString "Using of NULL" );
	}
	return m_mImage[0].size();
}
size_t HOGImage::height () const
{
	if ( m_mImage.empty() ) {
		throw logic_error ( _ExceptionString "Using of NULL" );
	}
	return m_mImage.size();
}
size_t HOGImage::naturalWidth () const
{
	if ( m_mImage.empty() ) {
		throw logic_error ( _ExceptionString "Using of NULL" );
	}
	return m_mImage[0].size()*_Block_Size;
}
size_t HOGImage::naturalHeight () const
{
	if ( m_mImage.empty() ) {
		throw logic_error ( _ExceptionString "Using of NULL" );
	}
	return m_mImage.size()*_Block_Size;
}
HOGPixel::HOGPixel ()
    : m_vGradient (_HOGVectorLength,0)
{}
HOGPixel::HOGPixel ( const HOGPixel& in_other )
    : m_vGradient (in_other.m_vGradient)
{}
HOGPixel::HOGPixel ( const QImage &in_Image, const QPoint &in_pPosition )
    : m_vGradient (_HOGVectorLength,0)
{
	if (in_Image.format() == QImage::Format_Indexed8) {
		grey_constructor (in_Image, in_pPosition);
	} else {
		constructor (in_Image, in_pPosition);
	}
}
size_t HOGPixel::length ()
{
	return s_HOGVectorLength;
}
void HOGPixel::operator () ( const QImage &in_Image, const QPoint &in_pPosition )
{
	if (in_Image.format() == QImage::Format_Indexed8) {
		grey_constructor (in_Image, in_pPosition);
	} else {
		constructor (in_Image, in_pPosition);
	}
}

static inline QRgb pixel ( const QImage &in_Image, int x, int y ){
	if ( x<0 ) x= -x;
	else if ( x >= in_Image.width() )
		x = 2 * in_Image.width() - x - 1;
	if ( y<0 ) y=-y;
	else if ( y >= in_Image.height() )
		y = 2 * in_Image.height() - y - 1;
	return in_Image.pixel(x,y);

}
static inline int pixelIndex ( const QImage &in_Image, int x, int y ){
	if ( x<0 ) x= -x;
	else if ( x >= in_Image.width() )
		x = 2 * in_Image.width() - x - 1;
	if ( y<0 ) y=-y;
	else if ( y >= in_Image.height() )
		y = 2 * in_Image.height() - y - 1;
	return in_Image.pixelIndex(x,y);

}

void HOGPixel::constructor ( const QImage &in_Image, const QPoint &in_pPosition )
{
	clean();
	int posX = in_pPosition.x();
	int posY = in_pPosition.y();
	for ( int y = 0; y < _Block_Size; ++y ) {
		for ( int x = 0; x < _Block_Size; ++x ) {

			//from qPaint/src/Filter/Sobel.cpp:Sobel::calcPixel
			#define _kernel(_x,_y) \
				(pixel (in_Image,(_x)+x+posX,(_y)+y+posY))
			#define _lightness(_rgb) \
				( 0.2125*qRed(_rgb) + 0.7154*qGreen(_rgb) + 0.0721*qBlue(_rgb) )
			QRgb 	rgb02 =	_kernel(0,2), rgb00 = _kernel(0,0),
				rgb12 = _kernel(1,2), rgb10 = _kernel(1,0),
				rgb22 = _kernel(2,2), rgb20 = _kernel(2,0),
				rgb21 = _kernel(2,1), rgb01 = _kernel(0,1);

			int xGrad =	_lightness(rgb02) - _lightness(rgb00) +
					2*_lightness(rgb12) - 2*_lightness(rgb10) +
					_lightness(rgb22) - _lightness(rgb20);

			int yGrad =	_lightness(rgb20) - _lightness(rgb00) +
					2*_lightness(rgb21) - 2*_lightness(rgb01) +
					_lightness(rgb22) - _lightness(rgb02);
			#undef _kernel
			#undef _lightness

			int cell = 0;
			if ( xGrad < 0 ) cell += 2;
			if ( yGrad < 0 ) cell += 4;
			if ( abs(xGrad) < abs(yGrad) ) ++cell;
			++m_vGradient[cell];
		}
	}
	nonLinearKernel ();
}

void HOGPixel::grey_constructor ( const QImage &in_Image, const QPoint &in_pPosition )
{
	clean();
	int posX = in_pPosition.x();
	int posY = in_pPosition.y();
	for ( int y = 0; y < _Block_Size; ++y ) {
		for ( int x = 0; x < _Block_Size; ++x ) {

			//from qPaint/src/Filter/Sobel.cpp:Sobel::calcPixel
			#define _kernel(_x,_y) \
				(pixelIndex (in_Image,(_x)+x+posX,(_y)+y+posY))
			int 	rgb02 =	_kernel(0,2), rgb00 = _kernel(0,0),
				rgb12 = _kernel(1,2), rgb10 = _kernel(1,0),
				rgb22 = _kernel(2,2), rgb20 = _kernel(2,0),
				rgb21 = _kernel(2,1), rgb01 = _kernel(0,1);

			int xGrad =	rgb02 - rgb00 +
					2*rgb12 - 2*rgb10 +
					rgb22 - rgb20;

			int yGrad =	rgb20 - rgb00 +
					2*rgb21 - 2*rgb01 +
					rgb22 - rgb02;
			#undef _kernel

			int cell = 0;
			if ( xGrad < 0 ) cell += 2;
			if ( yGrad < 0 ) cell += 4;
			if ( abs(xGrad) < abs(yGrad) ) ++cell;

			++m_vGradient[cell];
		}
	}
	nonLinearKernel ();
}

#ifndef PI
# define PI 3.14159265359
#endif //PI
static double _SechOrder = 1/cosh(_FeatureVectorNLK_Order*PI);
void HOGPixel::nonLinearKernel () {
	std::vector<double> copy;
	copy.reserve(_HOGVectorLength);
	for ( size_t i=0; i<_GradientCellNumber; ++i ) {
		double x = m_vGradient[i];
		for ( int n = -_FeatureVectorNLK_Step; n <= _FeatureVectorNLK_Step; ++n ) {
			if ( x != x ) {
				throw logic_error ( _ExceptionString "Not a number." );
			}
			if ( x == 0 ) {
				copy.push_back (0);
				copy.push_back (0);
			} else {
				copy.push_back (cos(_FeatureVectorNLK_Order*n*log(x))*sqrt(x*_SechOrder));
				copy.push_back (sin(_FeatureVectorNLK_Order*n*log(x))*sqrt(x*_SechOrder));
			}
		}
	}
	m_vGradient = copy;
}
HOGPixel &HOGPixel::operator = ( const HOGPixel &in_other )
{
	m_vGradient = in_other.m_vGradient;
	return *this;
}
void HOGPixel::clean ()
{
	m_vGradient.clear();
	m_vGradient.resize (_HOGVectorLength,0);
}
double HOGPixel::operator [] ( size_t index ) const
{
	return m_vGradient[index];
}
