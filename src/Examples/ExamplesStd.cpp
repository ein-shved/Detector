/*
 * ExamplesStd.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#include "ExamplesStd.h"

using namespace std;
using namespace Detector;

ExamplesStd::ExamplesStd ()
    : Examples ()
{}
ExamplesStd::ExamplesStd ( const Examples &in_Examples )
    : Examples (in_Examples)
{}
ExamplesStd::ExamplesStd ( std::vector<FeatureVector> in_vFVectors )
    : Examples ()
{
	m_vFVectors = in_vFVectors;
	/*for ( size_t i=0; i<in_vFVectors.size(); ++i ) {
		m_vFVectors.push_back(in_vFVectors[i]->clone());
	}*/
}
ExamplesStd::~ExamplesStd ()
{};

void ExamplesStd::add ( const FeatureVector &in_FVector )
{
	m_vFVectors.push_back(in_FVector);
}

ExamplesStd *ExamplesStd::clone () const
{
	return new ExamplesStd (*this);
}
