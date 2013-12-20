/*
 * HOGImage.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 19.10.2012
 */

#ifndef _Detector_HOG_IMAGE_H_
#define _Detector_HOG_IMAGE_H_

#include <QImage>
#include "../definitions.h"


namespace Detector {

	/*
	 * Contain gradient hystogramm of
	 * block with size _Block_Size x _Block_Size.
	 */
	class HOGPixel {

#	ifndef _Block_Size
#	 define _Block_Size 8 
#	endif //_Block_Size
#	ifndef _GradientCellNumber
#	 define _GradientCellNumber 8
#	endif //_GradientCellNumber

#	ifndef _FeatureVectorNLK_Step
#	 define _FeatureVectorNLK_Step 1
#	endif //_FeatureVectorNLK_Step
#	ifndef _FeatureVectorNLK_Order
#	 define _FeatureVectorNLK_Order 0.25
#	endif //_FeatureVectorNLK_Order

#	undef _HOGVectorLength
#	define _HOGVectorLength _GradientCellNumber*2*(_FeatureVectorNLK_Step*2 + 1)

	/* Constructors */
	public:
		HOGPixel ();
		HOGPixel ( const QImage &in_Image, const QPoint &in_pPosition );
		HOGPixel ( const HOGPixel& in_other );

	/* Reconstructor */
	public:
		void operator () ( const QImage &in_Image, const QPoint &in_pPosition );

	/* Interface */
	public:
		double operator [] ( size_t index ) const;
		HOGPixel &operator = ( const HOGPixel &in_other );
		void clean ();
		static size_t length ();

	/* Auxiliary methods */
	private:
		void constructor ( const QImage &in_Image, const QPoint &in_pPosition );
		void grey_constructor ( const QImage &in_Image, const QPoint &in_pPosition );
		void nonLinearKernel ();

	/* State */
	private:
		std::vector<double> m_vGradient; //Hystogramm

	/* Sise of hystogramm (_HOGVectorLength)*/
	private:
		const static size_t s_HOGVectorLength;

	};

	/*
	 * Image with HOGPixels instead of RGB pixels
	 */
	class HOGImage {

	/* Constructors */
	public:
		explicit HOGImage (const QImage &in_Image);
		explicit HOGImage (const QString &in_sImage);

	/* Interface */
	public:
		const HOGPixel &operator () (size_t x, size_t y) const; //pixel on [x][y]
		size_t width () const; //In mean of HOGPixel
		size_t height () const; //In mean of HOGPixel
		size_t naturalWidth () const; //In mean of source image
		size_t naturalHeight () const; //In mean of source image
		bool isNull () const;

	/* Auxiliary method */
	private:
		void constructor (const QImage &in_Image);

	/* State */
	private:
		std::vector<std::vector<HOGPixel> > m_mImage;
	};
}

#endif //_Detector_HOG_IMAGE_H_
