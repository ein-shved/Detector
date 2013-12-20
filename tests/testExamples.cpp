#include "../src/Examples/ExamplesImg.h"
#include <iostream>
#include <QImage>
#include <QDir>

using namespace std;
using namespace Detector;

int main () {
	QDir dir ( "Data/negative/","*.png" );
	if ( ! dir.exists() ) {
		cout<<"NULL dir\n";
		return 1;
	}
	vector<QImage> files;
	for ( uint i=0; i < dir.count(); ++i ) {
		files.push_back (QImage ("Data/negative/" + dir[i]) );
	}
	ExamplesImg exapmles(files);
	while ( exapmles.hasNext() ) {
		const FeatureVector &lCurrentFVector = exapmles.getNext();
		for ( size_t i =0; i < lCurrentFVector.length(); ++i ) {
			cout<<lCurrentFVector[i]<<" ";
		}
		cout<<endl;
	}
}