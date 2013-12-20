/*
 * ClassifierImg.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 14.10.2012
 */


#ifndef _Detector_CLASSIFIER_IMG_H_
#define _Detector_CLASSIFIER_IMG_H_

#include <vector>
#include <QImage>
#include "Classifier.h"
#include "../definitions.h"

namespace Detector {

	class ClassifierImg : public Classifier {

#	ifndef _DefaultImgPartStep
#	 define _DefaultImgPartStep 2
#	endif //_DefaultImgPartStep
#	ifndef _DefaultAreaWidth
#	 define _DefaultAreaWidth 80
#	endif //_DefaultAreaWidth
#	ifndef _DefaultAreaHeight
#	 define _DefaultAreaHeight 200
#	endif //_DefaultAreaHeight

	/* Constructors */
	public:
		ClassifierImg ( const struct model *in_pModel = NULL );
		ClassifierImg ( const Classifier &in_Classifier );
	/* Interface */
	public:
		std::vector<QRect> classify ( const QImage &in_Image,
					      double in_dThreshold = 0,
					      double stepPart = _DefaultImgPartStep,
					      size_t in_iWidth = _DefaultAreaWidth,
					      size_t in_iHeight = _DefaultAreaHeight
					      ) const;
		    /* trows std::logic_error */
	/* Interface (Assigment) */
	public:
		Classifier &operator = ( const Classifier &in_Classifier );
		Classifier &operator = ( const struct model *in_pModel );

	private:
		static QVector<QRgb> s_colorTable;
	};
}

#endif //_Detector_CLASSIFIER_IMG_H_