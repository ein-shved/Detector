/*
 * Classifier.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#ifndef _Detector_CLASSIFIER_H_
#define _Detector_CLASSIFIER_H_

#include <linear.h>
#include <vector>
#include <string>
#include "../FeatureVector/FeatureVector.h"
#include "../definitions.h"

namespace Detector {

	class Classifier {

#	ifndef _DefaultClassifyStep
#	 define _DefaultClassifyStep 40
#	endif //_DefaultClassifyStep

	/* Constructors */
	public:
		Classifier ( const struct model *in_pModel = NULL );
		Classifier ( const Classifier &in_Classifier );
	/* Destructor */
		~Classifier ();

	/* Interface (Assigment) */
	public:
		Classifier &operator = ( const Classifier &in_Classifier );
		Classifier &operator = ( const struct model *in_pModel );

	/* Interface */
	public:
		bool classify ( const FeatureVectorBase &in_FVector, double *in_dEstimates = NULL ) const;
		    /* trows std::logic_error */
		bool isNull () const;
		void read /*from file*/ ( const std::string &in_sFile );
		void save /*to file*/ ( const std::string &in_sFile ) const;

	/* Interface (Inheritance) */
	protected:
		const struct model *getModel() const;

	/* State */
	private:
		struct model *m_pModel;
		
	/* Model indexing */
	private:
		struct ModelPointer {
			struct model *pointer;
			size_t count;
			ModelPointer ( const struct model *in_pModel);
		};
		static struct model *copyModel ( const struct model *in_pModel );
		static struct model *removeModel ( const struct model *in_pModel );
		static std::vector<ModelPointer> s_vModels;
	};
}

#endif //_Detector_CLASSIFIER_H_