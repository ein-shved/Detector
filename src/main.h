/*
 * main.h
 *
 * Designed and written by
 *	 Shvedov Yury 321 group.
 *
 * Powered by
 * 	 MediaLab, CMC MSU
 *
 * 13.10.2012
 */

#ifndef _Detector_MAIN_H_
#define _Detector_MAIN_H_

#include <QRect>
#include <QString>

const char *helpString =
"USAGE: detector [OPTIONS ...] [-- [NEGATIVES ...] : [POSITIVES ...] [: [IMAGES ...]] ]\n\n"
"Training classifier from NEGATIVES and POSITIVES and searching pedestrians\n"
"in IMAGES. If there 1 or less images in IMAGES, gui will be launched.\n\n"
"OPTIONS:\n"
"\t-h --help\t\t"		"print this message and exit\n"
"\t-r --recursive\t\t"		"open NEGATIVES, POSITIVES and IMAGES recursively\n"
"\t-f --force\t\t"		"ignore some errors\n"
"\t-c --classifier <file>\t"	"load classifier from 'file'\n"
"\t-s --summary <file>\t"	"write summary to 'file' if there more then 1 image in IMAGES\n"
"\t-S --skip-selection\t"	"skip reading NEGATIVES and POSITIVES\n"
"\t-i --image <file>\t"		"open file in GUI\n"
"\t-F --f-scope <file>\t"	"calculate f-scope, using file as correct pedestrians positions\n";

struct ClassifyInfo {
	QString filename;
	QRect rect;
	bool found;
	bool operator == ( const ClassifyInfo &other ) const {
		return filename == other.filename;
	}
	bool operator == ( const QString &in_str ) const {
		return filename == in_str;
	}
};

#endif //_Detector_MAIN_H_