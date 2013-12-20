/*
 * Examples.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#include "Examples.h"

using namespace std;
using namespace Detector;

Examples::Examples ()
    : m_uIndex (0)
{}
Examples::Examples ( const Examples &in_Examples )
    : m_vFVectors ( in_Examples.m_vFVectors)
    , m_uIndex (0)
{
	/*for ( size_t i=0; i<in_Examples.m_vFVectors.size(); ++i ) {
		m_vFVectors[i] = in_Examples.m_vFVectors[i]->clone();
	}*/
}
Examples::~Examples()
{
	/*for ( size_t i=0; i<m_vFVectors.size(); ++i ) {
		delete m_vFVectors[i];
	}*/
}

void Examples::resetIndexing () const
{
	size_t &index = const_cast<size_t &> (m_uIndex);
	index = 0;
}
bool Examples::hasNext () const
{
	return m_uIndex < m_vFVectors.size();
}
const FeatureVector &Examples::getNext () const
{
	size_t &index = const_cast<size_t &> (m_uIndex);
	return m_vFVectors[index++];
}
size_t Examples::size () const
{
	return m_vFVectors.size();
}

Examples *Examples::clone () const
{
	return new Examples (*this);
}
