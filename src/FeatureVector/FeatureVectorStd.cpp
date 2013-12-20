/*
 * FeatureVectorStd.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 12.10.2012
 */

#include "FeatureVectorStd.h"

#undef _ExceptionString
#define _ExceptionString " FeatureVectorStd:\t" 

using namespace Detector;
using namespace std;

FeatureVectorStd::FeatureVectorStd ( const std::vector<double> &in_vFeatures )
{
	m_vFeatures = in_vFeatures;
}

void FeatureVectorStd::append ( double in_fValue )
{
	m_vFeatures.push_back (in_fValue);
}
FeatureVectorStd *FeatureVectorStd::clone() const
{
	return new FeatureVectorStd (*this);
}
