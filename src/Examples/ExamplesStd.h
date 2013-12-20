/*
 * ExamplesStd.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#ifndef _Detector_EXAMPLES_STD_H_
#define _Detector_EXAMPLES_STD_H_

#include "Examples.h"

namespace Detector {
	
	class ExamplesStd : public Examples {

	/* Constructors */
	public:
		~ExamplesStd ();
		ExamplesStd ();
		ExamplesStd ( const Examples &in_Examples );
		ExamplesStd ( std::vector<FeatureVector> in_vFVectors );
		
	/* Interface (set-like) */
	public:
		void add ( const FeatureVector &in_FVector );
		/* Inherit:
		 * void Examples::resetIndexing () const;
		 * bool Examples::hasNext () const;
		 * const FeatireVector &Examples::getNext () const;
		 */
		
	/* Interface (inheritance) */
	public:
		virtual ExamplesStd *clone () const;
	/*
	 * State
	 * 
	 * Inherit:
	 * std::vector<FeatureVector> Exmples::m_vFVectors;
	 * size_t Exmples::m_uIndex;
	 */
	};
}

#endif //_Detector_EXAMPLES_STD_H_
