/*
 * Classifier.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#include <stdexcept>
#include <iostream>
#include "Classifier.h"
#include "../locals.h"

using namespace std;
using namespace Detector;

#undef _ExceptionString
#define _ExceptionString " Classifier:\t"

Classifier::Classifier ( const struct model *in_pModel )
    : m_pModel ( NULL )
{
	if ( in_pModel != NULL ) {
		m_pModel = copyModel (in_pModel);
	}
}
Classifier::Classifier ( const Classifier &in_Classifier )
    : m_pModel ( NULL )
{
	if ( in_Classifier.m_pModel != NULL ) {
		m_pModel = copyModel (in_Classifier.m_pModel);
	}
}

Classifier &Classifier::operator = ( const Classifier &in_Classifier )
{
	if ( m_pModel != NULL ) {
		removeModel(m_pModel);
		m_pModel = NULL;
	}
	if ( in_Classifier.m_pModel != NULL ) {
		m_pModel = copyModel (in_Classifier.m_pModel);
	}
	return *this;
}
Classifier &Classifier::operator = ( const struct model *in_pModel )
{
	if ( m_pModel != NULL ) {
		removeModel(m_pModel);
		m_pModel = NULL;
	}
	if ( in_pModel != NULL ) {
		m_pModel = copyModel (in_pModel);
	}
	return *this;
}
Classifier::~Classifier()
{
	if ( m_pModel != NULL )
		removeModel(m_pModel);
}

bool Classifier::classify ( const FeatureVectorBase &in_FVector, double *in_dEstimates ) const
{
	if ( m_pModel == NULL ) {
		throw logic_error ( _ExceptionString "Using of NULL Classifier." );
	}
	size_t features = in_FVector.length();
	struct feature_node* x = Malloc(struct feature_node, features + 1);
	x[features].index = -1;
	for ( size_t j = 0; j < features; j++)
        {
		x[j].index = j+1;
		x[j].value = in_FVector[j];
	}
	double prob_estimates[1];
	int result = predict_values(m_pModel, x, prob_estimates);
	if ( in_dEstimates != NULL ) {
		*in_dEstimates = prob_estimates[0];
	}
	free(x);
	return result == 1;
}
bool Classifier::isNull () const {
	return m_pModel == NULL;
}
void Classifier::read ( const string &in_sFile ) {
	struct model *in_pModel = load_model ( in_sFile.c_str() );
	if (in_pModel == NULL) {
		throw logic_error (_ExceptionString "Can not load classifier from file '" + in_sFile + "'");
	}
	if ( m_pModel != NULL ) {
		removeModel(m_pModel);
		m_pModel = NULL;
	}
	m_pModel = copyModel (in_pModel);
}
void Classifier::save ( const string &in_sFile ) const {
	if ( m_pModel == NULL ) {
		throw logic_error (_ExceptionString "Can not safe NULL classifier.");
	}
	if ( save_model (in_sFile.c_str(),m_pModel) < 0 ) {
		throw logic_error (_ExceptionString "Can not safe classifier to file '" + in_sFile + "'");
	}
}

const struct model *Classifier::getModel() const {
	return m_pModel;
}

vector<Classifier::ModelPointer> Classifier::s_vModels;
struct model *Classifier::copyModel ( const struct model *in_pModel ) {
	size_t size = s_vModels.size();
	for (size_t i=0; i < size; ++i ) {
		ModelPointer &lPointer = s_vModels[i];
		if (lPointer.pointer == in_pModel ) {
			++(lPointer.count);
			return lPointer.pointer;
		}
	}
	s_vModels.push_back (ModelPointer (in_pModel));
	return (*(s_vModels.end() - 1)).pointer;
}
struct model *Classifier::removeModel ( const struct model *in_pModel )
{
	if ( in_pModel == NULL ) {
		throw logic_error ( _ExceptionString "Error in model inedxing. NULL." );
	}
	size_t size = s_vModels.size();
	for (size_t i=0; i < size; ++i ) {
		ModelPointer &lPointer = s_vModels[i];
		if (lPointer.pointer == in_pModel ) {
			if (lPointer.count == 0)
				throw logic_error ( _ExceptionString "Error in model inedxing. Zero." );
			--(lPointer.count);
			if ( lPointer.count == 0 ) {
				free_and_destroy_model(&(lPointer.pointer));
			}
			return lPointer.pointer;
		}
	}
	throw logic_error ( _ExceptionString "Error in model inedxing. Not found." );
}
Classifier::ModelPointer::ModelPointer ( const struct model *in_pModel )
    : count (1)
{
	if ( in_pModel == NULL ) {
		throw logic_error ( _ExceptionString "Error in model inedxing. NULL pointer." );
	}
	pointer = const_cast<struct model *> (in_pModel);
	if ( pointer == NULL ) {
		throw logic_error ( _ExceptionString "Error in model inedxing. Can not cast the constant pointer." );
	}
}
