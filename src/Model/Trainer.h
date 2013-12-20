/*
 * Trainer.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#ifndef _Detector_TRAINER_H_
#define _Detector_TRAINER_H_

#include <vector>
#include "../Examples/Examples.h"

#include "Classifier.h"
#include "../definitions.h"

namespace Detector {

	class Trainer {
		
#	ifndef _DefaultTrainingConstant
#	 define _DefaultTrainingConstant 0.1
#	endif //_DefaultTrainingConstant

	/* Constructors */
	public:
		Trainer ( double in_dConstant = _DefaultTrainingConstant );

	/* Inerface */
	public:
		void train ( const Examples &negatives, const Examples &positives );
		const Classifier &getClassifier () const;
		
	private:
		double m_dConstant;
		Classifier m_Classifier;
	};
}

#endif //_Detector_TRAINER_H_