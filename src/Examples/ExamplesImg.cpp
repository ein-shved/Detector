/*
 * ExamplesImg.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#include "ExamplesImg.h"
#include <stdexcept>

using namespace std;
using namespace Detector;

#undef _ExceptionString
#define _ExceptionString " ExamplesImg:\t"

ExamplesImg::ExamplesImg ( const ExamplesImg &in_Examples )
    : ExamplesStd (in_Examples)
{}
ExamplesImg::ExamplesImg ( std::vector<QImage> in_vImages, size_t in_uWidth, size_t in_uHeight  )
    : ExamplesStd ()
{
	for ( size_t i = 0; i < in_vImages.size(); ++i )
	{
		//detalize
		m_vFVectors.push_back (FeatureVectorImg(in_vImages[i],QPoint(0,0),in_uWidth,in_uHeight));
	}
}
ExamplesImg ::~ExamplesImg ()
{}

ExamplesImg *ExamplesImg::clone () const
{
	return new ExamplesImg (*this);
}
