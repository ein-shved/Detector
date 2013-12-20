/*
 * FeatureVector.h
 * 
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 10.10.2012
 */


#ifndef _Detector_FEATURE_VECTOR_BASE_H_
#define _Detector_FEATURE_VECTOR_BASE_H_

#include <vector>

namespace Detector {

	class /* Interface */ FeatureVectorBase {
#	define FVectorBase FeatureVectorBase

	/* Destructor */
	public:
		virtual ~FeatureVectorBase();

	/* Vector-like */
	public:
		virtual double operator [] ( size_t in_iIndex) const =0;
		virtual size_t length () const =0;
		
	/* Inheritance */
	public:
		virtual FeatureVectorBase *clone() const =0;
	};
	class FeatureVector : public FeatureVectorBase {
#	define FVector FeatureVector

	/* Constructors */
	public:
		FeatureVector ();
		FeatureVector ( const FeatureVector &in_FVector );
	public:
		/* Intervace (vector-like) */
		double operator [] ( size_t in_iIndex) const;
		virtual double &operator [] ( size_t in_iIndex );
		size_t length () const;

		/* Interface (inheritance) */
		FeatureVector *clone() const;
		
	protected:
		/* State */
		std::vector<double> m_vFeatures;
	};

}


#endif //_Detector_FEATURE_VECTOR_BASE_H_
