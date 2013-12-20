/*
 * FeatureVector.h
 * 
 * Designed and written by
 *	Shvedov Yury 321 group.
 *
 * Powered by
 *	MediaLab, CMC MSU
 *
 * 12.10.2012 
 */

#ifndef _Detector_FEATURE_VECTOR_STD_H_
#define _Detector_FEATURE_VECTOR_STD_H_

#include "FeatureVector.h"
#include <vector>
namespace Detector {
	
	class FeatureVectorStd /* std::vector */ : public FeatureVector {
	#define FVectorStd FeatureVctorStd

	/* Constructors */
	public:
		FeatureVectorStd ( const FeatureVector &in_FVector );
		FeatureVectorStd ( const std::vector<double> &in_vFeatures = std::vector<double> () );

	/* Intervace (vector-like) */
	public:
		void append ( double in_fValue );
		/* Inherit from FeatureVector:
		 * 	operator []
		 * 	length ()
		 */

	/* Interface (inheritance) */
	public:
		virtual FeatureVectorStd *clone() const; //I think, it is unnecessary

	/* State
	 * inherit std::vector<double> FeatureVector::m_vFeatures;
	 */

	};
};

#endif //_Detector_FEATURE_VECTOR_STD_H_
