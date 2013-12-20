/*
 * Trainer.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#include <linear.h>
#include <stdexcept>
#include "Trainer.h"
#include "../locals.h"

using namespace std;
using namespace Detector;

#undef _ExceptionString
#define _ExceptionString " Trainer:\t"

Trainer::Trainer ( double in_dConstant )
    : m_dConstant (in_dConstant)
{}
void Trainer::train ( const Examples &negatives, const Examples &positives )
{
	struct problem prob;
	prob.l = negatives.size() + positives.size();
	prob.bias = -1;
	negatives.resetIndexing ();
	positives.resetIndexing ();

	prob.y = Malloc(int, prob.l);
	prob.x = Malloc(struct feature_node *, prob.l);
	size_t featuresNumber=0;

	bool hasFeatures = false;
	size_t uIndex = 0;

	while ( negatives.hasNext() ) {
		if ( uIndex > (size_t)prob.l ) {
			throw logic_error ( _ExceptionString "FATAL ERROR" );
		}
		const FeatureVectorBase &lCurrentFVector = negatives.getNext();
		if ( !hasFeatures ) {
			featuresNumber = lCurrentFVector.length();
			hasFeatures =true;
		} else {
			if ( featuresNumber != lCurrentFVector.length() ) {
				throw logic_error ( _ExceptionString "Unexpected instance length." );
			}
		}
		prob.x [uIndex] = Malloc(struct feature_node, featuresNumber+1);
		prob.x [uIndex][featuresNumber].index = -1;
		for (size_t i = 0; i < featuresNumber; ++i) {
			prob.x [uIndex][i].index = i+1;
			prob.x [uIndex][i].value = lCurrentFVector[i];
		}
		prob.y[uIndex] = -1;
		++uIndex;
	}

	while ( positives.hasNext() ) {
		if ( uIndex > (size_t)prob.l ) {
			throw logic_error ( _ExceptionString "FATAL ERROR" );
		}
		const FeatureVectorBase &lCurrentFVector = positives.getNext();
		if ( !hasFeatures ) {
			featuresNumber = lCurrentFVector.length();
			hasFeatures =true;
		} else {
			if ( featuresNumber != lCurrentFVector.length() ) {
				throw logic_error ( _ExceptionString "Unexpected instance length." );
			}
		}
		prob.x [uIndex] = Malloc(struct feature_node, featuresNumber+1);
		prob.x [uIndex][featuresNumber].index = -1;
		for (size_t i = 0; i < featuresNumber; ++i) {
			prob.x [uIndex][i].index = i+1;
			prob.x [uIndex][i].value = lCurrentFVector[i];
		}
		prob.y[uIndex] = 1;
		++uIndex;
	}

	prob.n = featuresNumber;
	
	struct parameter param;
	param.solver_type = L2R_L2LOSS_SVC_DUAL;
	param.C = m_dConstant;
	param.eps = 1e-4;
	param.nr_weight = 0;
	param.weight_label = NULL;
	param.weight = NULL;

	m_Classifier = ::train ( &prob, &param );
	destroy_param ( &param );
	free (prob.y);
	for (int i = 0; i < prob.l; ++i)
		free (prob.x[i]);
	free(prob.x);
}

const Classifier &Trainer::getClassifier () const
{
	return m_Classifier;
}