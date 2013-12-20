/*
 * Examples.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#ifndef _Detector_EXAMPLES_BASE_H_
#define _Detector_EXAMPLES_BASE_H_

#include <vector>
#include "../FeatureVector/FeatureVector.h"

namespace Detector {

	/*
	 * Contains a set of featire vector what needs for training
	 * Provids a simple interface of accecing to its elements.
	 */
	class /* pseudo-abstarct */ Examples {

	/* Constructors */
	protected:
		Examples ();
	public:
		~Examples();
		Examples ( const Examples &in_Examples );

	/* Interface (set-like) */
	public:
		void resetIndexing () const;
		bool hasNext () const;
		const FeatureVector &getNext () const;
		size_t size () const;

	/* Interface (inheritance) */
	public:
		virtual Examples *clone () const;

	/* State */
	protected:
		std::vector<FeatureVector> m_vFVectors;
		size_t m_uIndex;
	};
}


#endif //_Detector_EXAMPLES_BASE_H_
