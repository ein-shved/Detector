#include "../src/FeatureVector/FeatureVectorImg.h"
#include "../src/FeatureVector/FeatureVectorHOG.h"
#include <iostream>
#include <QImage>

using namespace std;
using namespace Detector;

int main () {
	QImage image ( "Data/positive/0000.png" );
	if ( image.isNull() ) {
		cout<<"NULL image\n";
		return 1;
	}
	FeatureVectorImg vImg (image);
	HOGImage imageHOG (image);
	FeatureVectorHOG vHOG (imageHOG);
	cout << vImg.length() <<" "<<vHOG.length()<< endl;
	for (size_t i=0; i< vImg.length(); ++i ) {
		cout<<i<<": "<<vImg[i]<<" "<<vHOG[i]<<endl;
		vHOG[i];
	}
	cout<<endl;
}