/*
 * FeatureVectorHOG.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 22.10.2012
 */

#ifndef _Detector_FEATURE_VECTOR_HOG_H_
#define _Detector_FEATURE_VECTOR_HOG_H_

#include "FeatureVector.h"
#include "HOGImage.h"
#include "../definitions.h"

namespace Detector {

	/*
	 * Class for constructing Feature Vectors from 
	 * HOGImage.
	 */
	class FeatureVectorHOG : public FeatureVector {

#	ifndef _DefaultAreaWidth
#	 define _DefaultAreaWidth 80
#	endif //_DefaultAreaWidth
#	ifndef _DefaultAreaHeight
#	 define _DefaultAreaHeight 200
#	endif //_DefaultAreaHeight

	/* Constructors */
	public:
		FeatureVectorHOG ( const FeatureVector &in_FVector );
		FeatureVectorHOG ( const HOGImage &in_Image,
				   const QPoint &in_pPosition = QPoint(0,0),
				   size_t in_iWidth = _DefaultAreaWidth,
				   size_t in_iHeight = _DefaultAreaHeight );
		FeatureVectorHOG ( const HOGImage &in_Image, const QRect &in_pRect);

	/* Destructor */
	public:
		~FeatureVectorHOG();

	/* Interface (vector-like)
	 *
	 * Inherit from FeatureVector:
	 * 	operator []
	 * 	length ()
	 */

	/* Interface (inheritance) */
	public:
		FeatureVectorHOG *clone() const;

	/* Auxiliary method */
	private:
		void constructor ( const HOGImage &in_Image, const QRect &in_pRect );

	/* State
	 *
	 * inherit std::vector<double> FeatureVector::m_vFeatures;
	 */
	};

/*
	 * Class for constructing Feature Vectors from
	 * HOGImage.
	 * USE CAREFULLY!
	 * Objects takes its data from existing HOGImage without copying.
	 */
	class FeatureVectorHOGlink : public FeatureVectorBase {

	/* Constructors */
	public:
		FeatureVectorHOGlink ( const FeatureVectorHOGlink &in_FVector );
		FeatureVectorHOGlink ( const HOGImage &in_Image,
				       const QPoint &in_pPosition = QPoint(0,0),
				       size_t in_iWidth = _DefaultAreaWidth,
				       size_t in_iHeight = _DefaultAreaHeight );
		FeatureVectorHOGlink ( const HOGImage &in_Image, const QRect &in_pRect);

	/* Destructor */
	public:
		~FeatureVectorHOGlink();

	/* Interface (vector-like) */
	public:
		double operator [] ( size_t in_iIndex) const;
		size_t length () const;
		
	/* Interface (inheritance) */
	public:
		FeatureVectorHOGlink *clone() const;

	/* State */
	private:
		const HOGImage &m_Image;
		const QPoint m_pPosition;
		const size_t m_iWidth;
		const size_t m_iHeight;
	};
}

#endif//_Detector_FEATURE_VECTOR_HOG_H_