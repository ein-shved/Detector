/*
 * FeatureVector.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 10.10.2012
 */

#include "FeatureVector.h"


using namespace Detector;
using namespace std;

#undef _ExceptionString
#define _ExceptionString " FeatureVector:\t" 

FeatureVectorBase::~FeatureVectorBase()
{}
FeatureVector::FeatureVector ()
{}
FeatureVector::FeatureVector ( const FeatureVector &in_FVector )
    : m_vFeatures ( in_FVector.m_vFeatures )
{}

double FeatureVector::operator [] ( size_t in_iIndex) const
{
	return m_vFeatures[in_iIndex];
}
double &FeatureVector::operator [] ( size_t in_iIndex )
{
	return m_vFeatures[in_iIndex];
}
size_t FeatureVector::length () const
{
	return m_vFeatures.size();
}
FeatureVector *FeatureVector::clone() const
{
	return new FeatureVector (*this);
}
