/*
 * Bootstraper.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 14.10.2012
 */

#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "../FeatureVector/HOGImage.h"
#include "../FeatureVector/FeatureVectorHOG.h"
#include "Bootstraper.h"

using namespace std;
using namespace Detector;

#undef _ExceptionString
#define _ExceptionString " Bootstraper:\t"

#undef _InfoString
#define _InfoString " Bootstraper:\t"


BootstraperImg::BootstraperImg ( const Trainer &in_trainer,
				 const std::vector<QImage> &in_vNegatives,
				 const std::vector<QImage> &in_vPositives,
				 std::ostream &out)
    : trainer ( in_trainer )
    , m_vNegatives ( in_vNegatives )
    , m_vPositives ( in_vPositives )
    , m_ePositives ( in_vPositives )
    , m_OutStream ( out )
{}

struct FVectorInfo {
	double estimate;
	FVectorBase *pFVector;
	inline bool operator < ( const FVectorInfo &in_FVector ) const {
		return estimate > in_FVector.estimate;
	}
};

void BootstraperImg::train ( double in_stepPart, double in_dThreshold, size_t in_iWidth, size_t in_iHeight )
{
	size_t sNegatives = m_vNegatives.size();
	size_t sPositives = m_vPositives.size();

	if (sNegatives == 0 || sPositives == 0) {
		return;
	}
	if ( in_stepPart < 0 || in_stepPart > in_iWidth || in_stepPart > in_iHeight ) {
		throw logic_error ( _ExceptionString "Wrong shifting step." );
	}

	m_OutStream << _InfoString "Preparing negatives "<<endl;
	{
		for ( size_t i = 0; i < sNegatives; ++i ) {
			size_t x = (in_iWidth/in_stepPart)/2;
			size_t y = (in_iHeight/in_stepPart)/2;
			QRect first_pos ( x, y , in_iWidth, in_iHeight);
			if ( x + in_iWidth > (size_t) m_vNegatives[i].width() ) {
				x=0;
			}
			if ( y + in_iHeight > (size_t) m_vNegatives[i].height() ) {
				x=0;
			}
			m_eNegatives.add (FeatureVectorImg(m_vNegatives[i],first_pos));
		}
	}
	
	//size_t stepSize = ( (in_iWidth < in_iHeight) ? in_iWidth : in_iHeight ) / in_stepPart;

	m_OutStream << _InfoString "Training "<<endl;
	trainer.train (m_eNegatives, m_ePositives );
	m_Classifier = trainer.getClassifier();
	size_t faults = 0;
	size_t added_faults = 0;

	m_OutStream << _InfoString "Scanning negative images."<<endl;
	m_OutStream << _InfoString "\tThreshold: "<<in_dThreshold<<endl;
	HandledExmples eNegatives = m_eNegatives;
	HandledExmples ePositives = m_ePositives;
	m_ePositives.resetIndexing();

	cout <<_InfoString "\tStatus [>                                                 ] 0% 0 faults added";
	cout.flush();
	for ( size_t i = 0; i < sNegatives; ++i ) {
		size_t imgFaults = 0;
		const QImage &in_Image=m_vNegatives[i];
		size_t iHeight = in_Image.height();
		size_t iWidth = in_Image.width();
		QRect shifter (0,0, in_iWidth, in_iHeight);
		while ( shifter.y() + shifter.height() <=  (int)iHeight ) {
			while ( shifter.x() + shifter.width() <= (int)iWidth ) {
				FeatureVectorImg currentFVector (in_Image, shifter );
				double estimate;
				if ( m_Classifier.classify (currentFVector,&estimate) ) {
					if ( -estimate >= in_dThreshold ) {
						eNegatives.add (currentFVector);
						added_faults++;
						if ( !m_ePositives.hasNext() ) {
							m_ePositives.resetIndexing();
						}
						ePositives.add (m_ePositives.getNext());
					}
					++imgFaults;
				}
				bool close = ( shifter.x() + shifter.width() == (int)iWidth );
				shifter.moveLeft ( shifter.x() + shifter.width()/in_stepPart );
				if ( (shifter.x() + shifter.width() > (int)iWidth ) && !close ) {
					shifter.moveLeft ( iWidth - in_iWidth );
				}
			}
			bool close = ( shifter.y() + shifter.height() == (int)iHeight );
			shifter.moveLeft (0);
			shifter.moveTop ( shifter.y() + shifter.height()/in_stepPart );
			if ( (shifter.y() + shifter.height() > (int)iHeight) && !close ) {
				shifter.moveLeft ( iHeight - in_iHeight );
			}
		}
		faults += imgFaults;
		
		size_t statusPoints = (i+1) * 50 / sNegatives;
		cout<<"\r"_InfoString "\tStatus [";
		for ( size_t j=0; j<statusPoints; ++j) {
			cout<<"=";
		}
		if ( statusPoints != 50 ) {
			cout<<">";
		}
		for ( size_t j=statusPoints; j<49; ++j) {
			cout<<" ";
		}
		cout<<"] "<<((i+1)*100)/sNegatives<<"% "<<added_faults<<" faults added";
		cout.flush();
	}
	m_OutStream <<endl<< _InfoString "Summary:"<<endl;
	m_OutStream << _InfoString "\t"<<faults<<" faults found"<<endl;
	m_OutStream << _InfoString "\t"<<added_faults<<" faults added"<<endl;
	m_OutStream << _InfoString "\t"<<eNegatives.size()<<" negatives and ";
	m_OutStream << ePositives.size()<<" positives used."<<endl;
	m_OutStream << _InfoString "Retraining."<<endl;

	trainer.train (eNegatives, m_ePositives );
	m_Classifier = trainer.getClassifier();
}

const Classifier &BootstraperImg::getClassifier () const
{
	return m_Classifier;
}

HandledExmples::HandledExmples ()
    : ExamplesStd()
{}
HandledExmples::HandledExmples (const Examples &other)
    : ExamplesStd (other)
{}
void HandledExmples::removePrevious ()
{
	--m_uIndex;	
	m_vFVectors.erase ( m_vFVectors.begin()+m_uIndex );
}
HandledExmples &HandledExmples::operator = (const Examples &in_other )
{
	m_vFVectors.clear();
	m_vFVectors.reserve (in_other.size());
	in_other.resetIndexing();
	while (in_other.hasNext()) {
		m_vFVectors.push_back ( in_other.getNext());
	}
	return *this;
}
