/*
 * definitions.h
 *
 * Designed and written by
 *	 Shvedov Yury 321 group.
 *
 * Powered by
 * 	 MediaLab, CMC MSU
 *
 * 24.10.2012
 */

#ifndef _Detector_DEFINITIONS_H_
#define _Detector_DEFINITIONS_H_

// Define params


//**** MAIN ****
#ifndef _MAIN_Train_Step
# define _MAIN_Train_Step 1
#endif //_MAIN_Train_Step

#ifndef _MAIN_Train_Threshold
# define _MAIN_Train_Threshold 0.35
#endif //_MAIN_Train_Threshold

#ifndef _MAIN_Classify_Step
# define _MAIN_Classify_Step 80
#endif //_MAIN_Classify_Step

#ifndef _MAIN_Classify_Threshold
# define _MAIN_Classify_Threshold 0.1
#endif //_MAIN_Classify_Threshold


//**** HOG ****
#ifndef _Block_Size
# define _Block_Size 8
#endif //_Block_Size

#ifndef _FeatureVectorNLK_Step
# define _FeatureVectorNLK_Step 1
#endif //_FeatureVectorNLK_Step

#ifndef _FeatureVectorNLK_Order
# define _FeatureVectorNLK_Order 0.5
#endif //_FeatureVectorNLK_Order


#endif //_Detector_DEFINITIONS_H_