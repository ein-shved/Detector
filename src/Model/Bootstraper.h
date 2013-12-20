/*
 * BootstraperImg.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 16.10.2012
 */

#ifndef _Detector_BOOTSTRAPER_IMG_H_
#define _Detector_BOOTSTRAPER_IMG_H_

#include <iostream>
#include <QImage>
#include <vector>
#include "Trainer.h"
#include "../Examples/ExamplesStd.h"
#include "../Examples/ExamplesImg.h"
#include "../FeatureVector/FeatureVectorHOG.h"
#include "../definitions.h"

namespace Detector {

	class HandledExmples : public ExamplesStd {
	public:
		HandledExmples ();
		HandledExmples ( const Examples &other);
		void removePrevious();
		void clear();
		HandledExmples &operator = ( const Examples &in_other );
	};
	
	class BootstraperImg {
		
#	ifndef _DefaultImgPartStep
#	 define _DefaultImgPartStep 2
#	endif //_DefaultImgPartStep
#	ifndef _DefaultAreaWidth
#	 define _DefaultAreaWidth 80
#	endif //_DefaultAreaWidth
#	ifndef _DefaultAreaHeight
#	 define _DefaultAreaHeight 200
#	endif //_DefaultAreaHeight

	public:
		BootstraperImg ( const Trainer &in_trainer,
				 const std::vector<QImage> &in_vNegatives,
				 const std::vector<QImage> &in_vPositives,
				 std::ostream &in_OutStream = std::cout );

		void train ( double in_stepPart = _DefaultImgPartStep, //step accuracy
			     double in_dThreshold = 0,
			     size_t in_iWidth = _DefaultAreaWidth,
			     size_t in_iHeight = _DefaultAreaHeight );
		    /* trows std::logic_error */
		const Classifier &getClassifier () const;
	
	private:

		Trainer trainer;
		const std::vector<QImage> &m_vNegatives;
		const std::vector<QImage> &m_vPositives;

		HandledExmples m_eNegatives;
		ExamplesImg m_ePositives;

		std::ostream &m_OutStream;

		Classifier m_Classifier;
	};
}

#endif //_Detector_BOOTSTRAPER_IMG_H_
