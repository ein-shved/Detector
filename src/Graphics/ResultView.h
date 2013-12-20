/*
 * ResultView.h
 *
 * Designed and written by
 * 	Shvedov Yury 321 group.
 *
 * Powered by
 * 	MediaLab, CMC MSU
 *
 * 14.10.2012
 */

#ifndef _RESULT_VIEW_H
#define _RESULT_VIEW_H

#include <QImage>
#include <QString>
#include <QGraphicsScene>
#include <QThread>
#include "ui_ResultView.h"
#include "../Model/ClassifierImg.h"
#include "../Model/Classifier.h"
#include "../definitions.h"

class ResultView;
class ClassifyThread : public QThread {
	Q_OBJECT
public:
	ClassifyThread (ResultView *in_pResultView, const Detector::ClassifierImg &in_lClassifier);
	void start (const QImage &in_Image);
	const QImage &getImage() const;
protected:
	void run();
private:
	ResultView *m_pResultView;
	const Detector::ClassifierImg &m_lClassifier;
	QImage m_Image;
public:
	std::vector<QRect> m_results;
};

class DoneEvent : public QEvent {
public:
        DoneEvent() : QEvent((QEvent::Type)(QEvent::User + 1)) {};
};

class ResultView: public QDialog {
	Q_OBJECT
	Ui_ResultView ui;
	
public:
	ResultView ( const Detector::Classifier &in_Classifier = Detector::Classifier(), const QImage &in_Iimage = QImage(),
		     const QString &in_sPath = QString(), const std::vector<QRect> &in_results = std::vector<QRect> ());
	const Detector::Classifier &getClassifier();
	void setClassifier( const Detector::Classifier &classifier);
		     
private:
	Detector::ClassifierImg m_Classifier;
	QGraphicsScene *m_pScene;
	QString m_sPath;
	ClassifyThread m_ClassifyThread;
	
protected:
	bool event(QEvent *event);
	
public slots:
	void onOpenImage();
	bool onOpenImage ( const QString &imagePath);
	void onOpenClassifier();
	void onOpenClassifier(const QString &str);
	
private:
	void updateImage ( const QImage &in_Image );
	void enbleBtns (bool in_bEnabled = true);
	
	friend class ClassifyThread;
};

#endif //_RESULT_VIEW_H
