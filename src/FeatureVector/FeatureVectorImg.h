/*
 * FeatureVectorImg.h
 * 
 * Designed and written by
 *	Shvedov Yury 321 group.
 *
 * Powered by
 *	MediaLab, CMC MSU
 *
 * 12.10.2012 
 */

#ifndef _Detector_FEATURE_VECTOR_IMG_H_
#define _Detector_FEATURE_VECTOR_IMG_H_

#include "FeatureVector.h"
#include <vector>
#include <QImage>
#include "../definitions.h"

namespace Detector {

	class FeatureVectorImg : public FeatureVector {
#	define FVectorImg FeatureVectorImg

#	ifndef _DefaultAreaWidth
#	 define _DefaultAreaWidth 80
#	endif //_DefaultAreaWidth
#	ifndef _DefaultAreaHeight
#	 define _DefaultAreaHeight 200
#	endif //_DefaultAreaHeight

	/* Constructors */
	public:
		FeatureVectorImg ( const QImage &in_Image, const QPoint &in_pPosition = QPoint(0,0),
					size_t in_iWidth = _DefaultAreaWidth, size_t in_iHeight = _DefaultAreaHeight );
		    /* throws std::logic_error */
		FeatureVectorImg ( const QImage &in_Image, const QRect &in_Rect);
		    /* throws std::logic_error */
		FeatureVectorImg ( const FeatureVectorImg &in_FVector );

	/* Interface (vector-like)
	 *
	 * Inherit from FeatureVector:
	 * 	operator []
	 * 	length ()
	 */

	/* Interface (inheritance) */
	public:
		virtual FeatureVectorImg *clone() const;
		
	/* Auxiliary method */
	private:
		void m_constructor ( const QImage &in_Image, const QRect &in_Rect );

	/* State
	 * 
	 * inherit std::vector<double> FeatureVector::m_vFeatures;
	 */
	};
}

#endif //_Detector_FEATURE_VECTOR_IMG_H_
