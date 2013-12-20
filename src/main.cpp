/*
 * Main.cpp
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#include <QApplication>
#include <cstring>
#include <string>
#include <iostream>
#include <QString>
#include <QImage>
#include <QDir>
#include <QFileInfo>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <stdexcept>
#include <algorithm>

#include "definitions.h"
#include "Examples/ExamplesImg.h"
#include "Model/Trainer.h"
#include "Model/Classifier.h"
#include "Graphics/ResultView.h"
#include "Model/Bootstraper.h"
#include "main.h"

#ifndef _MAIN_Train_Step
# define _MAIN_Train_Step 1
#endif //_MAIN_Train_Step

#ifndef _MAIN_Train_Threshold
# define _MAIN_Train_Threshold 0.2
#endif //_MAIN_Train_Threshold

#ifndef _MAIN_Classify_Step
# define _MAIN_Classify_Step 80
#endif //_MAIN_Classify_Step

#ifndef _MAIN_Classify_Threshold
# define _MAIN_Classify_Threshold 0.3
#endif //_MAIN_Classify_Threshold

using namespace std;
using namespace Detector;

#undef _InfoString
#define _InfoString " main:\t"

#undef _ExceptionString
#define _ExceptionString " main:\t"

template <class TImage>
void recursive_Image ( const QString &file, std::vector<TImage> &out_vImg, QVector<QString> &errors );

int noCatchMain (int argc, char *argv[]);
int main(int argc, char *argv[])
{
	try {
		return noCatchMain(argc,argv);
	} catch (const logic_error &exc) {
		cerr<<endl<<exc.what()<<endl;
		cerr<<_ExceptionString<<"Aborted."<<endl;
		return 1;
	}
	return 0;
}
int noCatchMain (int argc, char *argv[])
{
	std::vector<QImage> negatives;
	std::vector<QImage> positives;
	std::vector<QString> images;
	QVector<QString> errors;
	QString model ("");
	QString summaryFile ("");
	QString guiFile ("");
	QString sFScopeFile ("");

	bool bRecursive = false;
	bool bHelp = false;
	bool bModel = false;
	bool bForce = false;
	bool bReadModel = true;
	bool bSummary = false;
	bool bEchoBootstraper = false;
	bool bGuiFile = false;
	bool bFScopeFile = false;
	bool bSkipSelection = false;
	enum {
		main_Arguments
		, main_Negatives
		, main_Positives
		, main_Images
	} arg_mode = main_Arguments;

	/*************** Computing arguments ***************/
	for ( int i = 1; i < argc; ++i ) {
		switch (arg_mode) {
		case main_Arguments:{
				if ( argv[i][0] == '-' && argv[i][1] != '-' ) {
					size_t s_len = strlen ( argv[i]);
					for ( size_t j = 1; j < s_len; ++j ) {
						switch (argv[i][j]) {
						case 'r':
							bRecursive = true;
							break;
						case 'h':
							bHelp = true;
							goto lablePrintHelp;
							break;
						case 'c':
							bModel = true;
							break;
						case 'f':
							bForce = true;
							break;
						case 's':
							bSummary = true;
							break;
						case 'b':
							bEchoBootstraper = true;
							break;
						case 'i':
							bGuiFile = true;
							break;
						case 'F':
							bFScopeFile = true;
							break;
						case 'S':
							bSkipSelection = true;
							break;
						default:
							cerr<<_ExceptionString "Unknown option: -"<<argv[i][j];
							return 1;
							break;
						}
					}
					continue;
				}
				if ( bModel ) {
					if ( !model.isEmpty() ) {
						cerr<<_ExceptionString "You have already chosen a classifier file."<<endl;
						return 1;
					}
					model = QString (argv[i]);
					bModel = false;
					continue;
				}
				if ( bSummary ) {
					if ( !summaryFile.isEmpty() ) {
						cerr<<_ExceptionString "You have already chosen a summary file."<<endl;
						return 1;
					}
					summaryFile = argv[i];
					bSummary = false;
					continue;
				}
				if ( bGuiFile ) {
					if ( !guiFile.isEmpty() ) {
						cerr<<_ExceptionString "You have already chosen an image file."<<endl;
						return 1;
					}
					guiFile = argv[i];
					bGuiFile = false;
					continue;
				}
				if ( bFScopeFile ) {
					if ( !guiFile.isEmpty() ) {
						cerr<<_ExceptionString "You have already chosen an correct pedestrians positions file."<<endl;
						return 1;
					}
					sFScopeFile = argv[i];
					bFScopeFile = false;
					continue;
				}
				if ( !strcmp ( argv[i],"--recursive" ) ) {
					bRecursive = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--help" ) ) {
					bHelp = true;
					goto lablePrintHelp;
					continue;
				}
				if ( !strcmp ( argv[i],"--classifier" ) ) {
					bModel = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--force" ) ) {
					bForce = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--summary" ) ) {
					bSummary = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--bootecho" ) ) {
					bEchoBootstraper = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--image" ) ) {
					bGuiFile = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--f-scope" ) ) {
					bFScopeFile = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--skip-selection" ) ) {
					bSkipSelection = true;
					continue;
				}
				if ( !strcmp ( argv[i],"--" ) ) {
					if (bSkipSelection) {
						arg_mode = main_Images;
						cout << _InfoString "Reading test images." <<endl;
					} else {
						arg_mode = main_Negatives;
						cout << _InfoString "Reading negatives." <<endl;
					}
					bReadModel = false;
					continue;
				}
				cerr<<_ExceptionString "Unexpected argument: "<<argv[i]<<endl;
				return 1;
				break;
			}
		case main_Negatives: {
				if ( !strcmp ( argv[i],":" ) ) {
					arg_mode = main_Positives;
					cout << _InfoString "Reading positives." <<endl;
					continue;
				}
				QString file (argv[i]);
				if ( bRecursive ) {
					recursive_Image(file,negatives, errors);
				} else {
					QImage image (file);
					if (image.isNull() ) {
						errors.append (file);
					} else {
						negatives.push_back (image);
					}
				}
				break;
			}
		case main_Positives: {
				if ( !strcmp ( argv[i],":" ) ) {
					arg_mode = main_Images;
					cout << _InfoString "Reading test images." <<endl;
					continue;
				}
				QString file (argv[i]);
				if ( bRecursive ) {
					recursive_Image(file,positives, errors);
				} else {
					QImage image (file);
					if (image.isNull() ) {
						errors.append (file);
					} else {
						positives.push_back (image);
					}
				}
				break;
			}
		case main_Images: {
				QString file (argv[i]);
				if ( bRecursive ) {
					recursive_Image(file,images, errors);
				} else {
					images.push_back (file);
				}
				break;
			}

		}

	}

	if (bHelp) {
	lablePrintHelp:
		cout << helpString <<endl;
		return 0;
	}
	if ( arg_mode == main_Negatives ) {
		cerr << _ExceptionString "Please, indicate positives."<<endl;
		cerr << _ExceptionString "Aborted."<<endl;;
		return 1;
	}

	/*************** Reading errors ***************/
	if ( !errors.isEmpty() ) {
		cerr<<_ExceptionString "Can not open files:"<<endl;
		for ( int i =0; i<errors.size(); ++i ) {
			cerr<<_ExceptionString "\t" + errors[i].toStdString()<<endl;
		}
		if (bForce ) {
			cerr<<_ExceptionString "Continue."<<endl;
		} else {
			cerr<<_ExceptionString "Aborted."<<endl;
			return 1;
		}
	}
	/*************** Converting negatives to grayscale ***************/
	if ( !negatives.empty() ) {
		cout << _InfoString "Converting negatives. " <<endl;
		QVector<QRgb> colorTable;
		colorTable.resize(256);
		for (size_t i=0; i<256; ++i ) {
			colorTable[i] = qRgb(i,i,i);
		}
		for ( size_t i=0 ; i < negatives.size(); ++i ) {
			QImage imgNew (negatives[i].width(), negatives[i].height(), QImage::Format_Indexed8);
			imgNew.setColorTable (colorTable);
			for (int y = 0; y < negatives[i].height(); ++y){
				for (int x = 0; x < negatives[i].width(); ++x){
					QRgb rgb = negatives[i].pixel(x, y);
					uint uiGray = 0.2125*qRed(rgb) + 0.7154*qGreen(rgb) + 0.0721*qBlue(rgb);
					imgNew.setPixel(x, y, uiGray);
				}
			}
			negatives[i] = imgNew;
		}
	}

	ClassifierImg out_classifier;
	bModel = !model.isEmpty();
	if ( !bModel ) {
		model = "a.out";
	}
	if ( bModel && bSkipSelection ) {
		bReadModel = true;
	}

	QApplication a (argc,argv);
	ResultView formResultView;
	/*************** TRAINING ***************/
	if ( bModel || arg_mode != main_Arguments ) {
		QFileInfo modelFI (model);
		if ( !bSkipSelection && (!bModel || ( bModel && !bReadModel ) ) ) {
			cout << _InfoString "Training." <<endl;
			BootstraperImg trainer( Trainer(0.1), negatives, positives );
			trainer.train (_MAIN_Train_Step,_MAIN_Train_Threshold);

			cout << _InfoString "Saving classifier to '"<<model.toStdString()<<"'" <<endl;
			formResultView.setClassifier (trainer.getClassifier());
			formResultView.getClassifier().save (modelFI.absoluteFilePath().toStdString() );
			negatives.clear();
			positives.clear();
		} else {
			if ( bModel && bReadModel) {
				formResultView.onOpenClassifier (modelFI.absoluteFilePath());
			}
		}
	}
	/*************** SUMMARY ***************/
	if ( !images.empty() ) {
		cout<< _InfoString "Running in summary mode. "<<endl;
		if ( summaryFile.isEmpty() ) {
			cout << _InfoString "Using 'b.out' as out file."<<endl;
			summaryFile = "b.out";
		}
		const ClassifierImg &sum_classifier = formResultView.getClassifier();
		QFile fSummaryFile(summaryFile);
		if (!fSummaryFile.open(QIODevice::WriteOnly | QIODevice::Text ) ) {
			cerr << _ExceptionString "Can not open summary file '"<<summaryFile.toStdString()<<"'"<<endl;
			return 1;
		}
		QTextStream summaryDataStream(&fSummaryFile);
		bFScopeFile = !sFScopeFile.isEmpty();
		vector <ClassifyInfo> sTrueResults;
		if ( bFScopeFile ) {
			QFile fTrueResults(sFScopeFile);
			if (!fTrueResults.open(QIODevice::ReadOnly | QIODevice::Text ) ) {
				cerr << _ExceptionString "Can not open correct pedestrians positions file '"<<sFScopeFile.toStdString()<<"'"<<endl;
				return 1;
			}
			QTextStream correctDataStream(&fTrueResults);
			while ( correctDataStream.status() == QTextStream::Ok ) {
				ClassifyInfo currentCI;
				correctDataStream >> currentCI.filename;
				if ( correctDataStream.status() == QTextStream::ReadPastEnd )
					break;
				int x,y,w,h;
				currentCI.found = false;
				correctDataStream >> x >> y >> w >> h;
				if ( correctDataStream.status() != QTextStream::Ok ) {
					cerr << _ExceptionString "Can not read data from correct pedestrians positions file '"<<sFScopeFile.toStdString()<<"'"<<endl;
					return 1;
				}
				currentCI.rect = QRect (x,y,w,h);
				sTrueResults.push_back (currentCI);
			}
		}
		int iTruePedestrians = 0;
		int iTruePositions = 0;
		int iCorrectPedestrians = sTrueResults.size();
		int iAllPositions = 0;

		cout <<_InfoString "\tStatus [>                                                 ] 0%";
		cout.flush();
		for ( size_t i=0; i<images.size(); ++i ) {
			QImage currentImage (images[i]);
			if ( currentImage.isNull() ) {
				cerr <<endl<< _ExceptionString "Can not open image from '" <<images[i].toStdString() <<"'"<<endl;
				if (bForce ) {
					cerr<<_ExceptionString "Continue."<<endl;
				} else {
					cerr<<_ExceptionString "Aborted."<<endl;
					return 1;
				}
			} else {

				std::vector<QRect> result = sum_classifier.classify(currentImage,_MAIN_Classify_Step,_MAIN_Classify_Threshold);
				QFileInfo imageInfo (images[i]);
				QString sCurrentFilename = imageInfo.completeBaseName();

				for ( size_t j=0; j<result.size(); ++j ) {
					if ( bFScopeFile ) {
						++iAllPositions;
						vector<ClassifyInfo>::iterator it = sTrueResults.begin();
						while ( (it = std::find (it, sTrueResults.end(), sCurrentFilename ))
							!= sTrueResults.end() )
						{
							QRect square = it->rect.intersected(result[j]);
							double sSquare = square.width()*square.height();
							double sResultI = result[j].width()*result[j].height();
							if ( sSquare/sResultI  >= 0.6 ) {
								++iTruePositions;
								if ( !(it->found) ) {
									++iTruePedestrians;
									it->found=true;
								}
							}
							++it;
						}
					}
					summaryDataStream<<sCurrentFilename<<"\t";
					summaryDataStream<<result[j].x()<<"\t"<<result[j].y()<<"\t";
					summaryDataStream<<result[j].width()<<"\t"<<result[j].height()<<"\n";
					if (summaryDataStream.status() != QTextStream::Ok ) {
						cerr <<endl<< _ExceptionString "Can not write data to summary file '"<<summaryFile.toStdString()<<"'"<<endl;
						return 1;
					}
				}
			}
			size_t statusPoints = (i+1) * 50 / images.size();
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
			cout<<"] "<<((i+1)*100)/images.size()<<"%";
			cout.flush();
		}
		cout <<endl<<_InfoString "Summaring done." <<endl;
		if ( bFScopeFile ) {
			if ( iCorrectPedestrians == 0 || iCorrectPedestrians == 0 ) {
				cerr << _ExceptionString "Can not clculate recall and precision: zero devision."<<endl;
				return 1;
			}
			double recall = ((double)iTruePedestrians)/iCorrectPedestrians;
			double precision = ((double)iTruePositions)/iAllPositions;
			cout <<_InfoString "\tRecall: "<<recall<<endl;
			cout <<_InfoString "\tPrecision: "<<precision<<endl;
			cout <<_InfoString "\tF-Scope: "<<2*recall*precision/(recall+precision) <<endl;
		}
	}
	
	/*************** GUI ***************/
	if ( !guiFile.isEmpty() || images.empty() ) {
		cout << _InfoString "Running in GUI mode."<<endl;
		if ( !formResultView.onOpenImage ( guiFile ) ) {
			cerr << _ExceptionString "Can not open image from file '"<<guiFile.toStdString()<<"'"<<endl;
			if ( bForce ) {
				cerr<<_ExceptionString "Continue."<<endl;
			} else {
				cerr<<_ExceptionString "Aborted."<<endl;
				return 1;
			}
		}
		formResultView.show();
		return a.exec();
	}
	return 0;
}

template <class TImage>
void recursive_Image ( const QString &file, std::vector<TImage> &out_vImg, QVector<QString> &errors ) {
	QFileInfo fi (file);
	if ( fi.isDir () ) {
		QDir dir = fi.absoluteDir();
		dir.setFilter (QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
		for ( size_t i=0; i < dir.count(); ++i ) {
			recursive_Image (dir.absolutePath ()+'/'+dir[i], out_vImg, errors);
		}
	} else {
		TImage image (file);
		if ( image.isNull() ) {
			errors.push_back(file);
		} else {
			out_vImg.push_back (image);
		}
	}
}
