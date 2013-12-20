/*
 * ExamplesImg.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#ifndef _Detector_EXAMPLES_PATH_H_
#define _Detector_EXAMPLES_PATH_H_

#include "ExamplesStd.h"
#include "../FeatureVector/FeatureVectorImg.h"
#include <QImage>
#include "../definitions.h"

namespace Detector {

	class ExamplesImg : public ExamplesStd {

#	ifndef _DefaultAreaWidth
#	 define _DefaultAreaWidth 80
#	endif //_DefaultAreaWidth
#	ifndef _DefaultAreaHeight
#	 define _DefaultAreaHeight 200
#	endif //_DefaultAreaHeight

	/* Constructors */
	public:
		~ExamplesImg ();
		ExamplesImg ( const ExamplesImg &in_Examples );
		ExamplesImg ( std::vector<QImage> in_vImg,
			      size_t in_uWidth = _DefaultAreaWidth,
			      size_t in_uHeight = _DefaultAreaHeight );
			/* throws std::logic_error */

	/* Interface (set-like)
	 * 
	 * Inherit:
	 * void Examples::resetIndexing () const;
	 * bool Examples::hasNext () const;
	 * const FeatureVector &Examples::getNext () const;
	 */
		 
	/* Interface (inheritance) */
	public:
		virtual ExamplesImg *clone () const;
		
	/* State */
	private:
		/* Inherit:
		 * std::vector<FeatureVector> Exmples::m_vFVectors;
		 * size_t Exmples::m_uIndex;
		 */
	};
}

#endif //_Detector_EXAMPLES_PATH_H_