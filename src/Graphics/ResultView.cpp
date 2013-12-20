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

#include <stdexcept>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "ResultView.h"
using namespace std;
using namespace Detector;

#undef _ExceptionString
#define _ExceptionString " ResultView:\t"

#undef _InfoString
#define _InfoString " ResultView:\t"

ResultView::ResultView ( const Detector::Classifier &in_Classifier, const QImage &image,
			 const QString &in_sPath, const std::vector<QRect> &in_results )
    : m_Classifier (in_Classifier)
    , m_pScene (NULL)
    , m_sPath (QFileInfo(in_sPath).absoluteFilePath())
    , m_ClassifyThread (this,m_Classifier)
{
	ui.setupUi(this);
	if ( m_Classifier.isNull() ) {
		ui.btnOpen->setEnabled(false);
	}
	m_ClassifyThread.m_results = in_results;
	this->setMinimumSize ( this->geometry().width(), this->geometry().height() );
	this->setMaximumSize ( this->geometry().width(), this->geometry().height() );
	updateImage (image);
	if ( !in_results.empty() )
		QCoreApplication::postEvent( this, new DoneEvent);
}

void ResultView::updateImage ( const QImage &in_Image ) {
	if (in_Image.isNull()) {
		return;
	}
	enbleBtns (false);
	QPixmap pmNew = QPixmap::fromImage(in_Image);
	QGraphicsScene *pNewScene = new QGraphicsScene;
	pNewScene->addPixmap(pmNew);
	ui.mainView->setScene(pNewScene);

	QRect imageSize = in_Image.rect();
	QRect btnOpenGeometry = ui.btnOpen->geometry();
	QRect btnClassifierGeometry = ui.btnClassifier->geometry();
	QRect lblStatusGeometry = ui.lblStatus->geometry();
	
	if ( imageSize.width() < 20 + btnOpenGeometry.width() +
		btnClassifierGeometry.width() + lblStatusGeometry.width() )
	{
		imageSize.setWidth ( 20 + btnOpenGeometry.width() +
		btnClassifierGeometry.width() + lblStatusGeometry.width() );
	}
	imageSize.setWidth ( imageSize.width()+10);
	imageSize.setHeight ( imageSize.height()+10);
	imageSize.moveTopLeft(QPoint (5,10));
	ui.mainView->setGeometry (imageSize);

	QRect mainGeometry = this->geometry();
	mainGeometry.setWidth ( imageSize.width() + 10 );
	mainGeometry.setHeight ( imageSize.height() + 50 );
	
	this->setMinimumSize ( mainGeometry.width(), mainGeometry.height() );
	this->setMaximumSize ( mainGeometry.width(), mainGeometry.height() );

	int paragraph = btnOpenGeometry.width() + 5;
	btnOpenGeometry.moveTopLeft ( QPoint (mainGeometry.width() - paragraph,
				      mainGeometry.height() - btnOpenGeometry.height() - 5 ) );
	ui.btnOpen->setGeometry(btnOpenGeometry);

	paragraph += btnClassifierGeometry.width() + 5;
	btnClassifierGeometry.moveTopLeft ( QPoint (mainGeometry.width() - paragraph,
						    mainGeometry.height() - btnClassifierGeometry.height() - 5 ) );
	ui.btnClassifier->setGeometry(btnClassifierGeometry);

	lblStatusGeometry.moveTopLeft ( QPoint (5,mainGeometry.height() - lblStatusGeometry.height() - 5 ) );
	ui.lblStatus->setGeometry(lblStatusGeometry);
	
	if (m_pScene != NULL) {
		delete m_pScene;
	}
	m_pScene = pNewScene;
	ui.btnClassifier->setEnabled(true);
	if (!m_Classifier.isNull()) {
		ui.lblStatus->setStyleSheet ("color: blue");
		ui.lblStatus->setText ("Working");
		m_ClassifyThread.start(in_Image);
	}
}
bool ResultView::event ( QEvent *event ) {
	if (event->type() == (QEvent::Type)(QEvent::User + 1)) {
		QPen pen;
		pen.setColor ( QColor(0,255,0)); //qreen
		for ( size_t i=0; i<m_ClassifyThread.m_results.size(); ++i ) {
			m_pScene->addRect (m_ClassifyThread.m_results[i],pen);
		}
		ui.lblStatus->setStyleSheet ("color: green");
		ui.lblStatus->setText ("Done");
		enbleBtns (true);
        }
        return QDialog::event (event);
}
void ResultView::onOpenImage() {
	if ( m_Classifier.isNull() ) {
		return;
	}
	QString sPath = QFileDialog::getOpenFileName(this, "Open an image",
		m_sPath, "Images(*.jpg *.jpeg *.bmp *.png);;JPEG(*.jpg *.jpeg);;BMP(*.bmp);;PNG(*.png);;All files (*.*)");
	if (sPath.isEmpty()) return;

	QImage image (sPath);
	if (image.isNull() ) {
		QMessageBox::critical(this, "Error", "Can not to open the image.");
		return;
	};
	updateImage(image);
	m_sPath = sPath;
}
bool ResultView::onOpenImage ( const QString &imagePath)
{
	if (imagePath.isEmpty()) return true;
	QImage image (imagePath);
	if ( !image.isNull() ) {
		updateImage(image);
		m_sPath = QFileInfo(imagePath).absolutePath();
		return true;
	} else {
		return false;
	}

}
void ResultView::onOpenClassifier() {
	QString sPath = QFileDialog::getOpenFileName(this, "Open a classifier",
		"", "All files (*)");
	if (sPath.isEmpty()) return;

	try {
		m_Classifier.read ( sPath.toStdString() );
	} catch ( const logic_error &exc ) {
		QMessageBox::critical(this, "Error", exc.what() );
		return;
	};
	enbleBtns(true);
	updateImage(m_ClassifyThread.getImage());
}
void ResultView::onOpenClassifier(const QString &str) {
	m_Classifier.read ( str.toStdString() );
	enbleBtns(true);
}
void ResultView::setClassifier( const Detector::Classifier &classifier) {
	m_Classifier = classifier;
	enbleBtns(true);
	updateImage(m_ClassifyThread.getImage());
}
void ResultView::enbleBtns (bool in_bEnabled) {
	ui.btnOpen->setEnabled (in_bEnabled);
	ui.btnClassifier->setEnabled (in_bEnabled);
}
const Classifier &ResultView::getClassifier() {
	return m_Classifier;
}
ClassifyThread::ClassifyThread (ResultView *in_pResultView, const ClassifierImg &in_lClassifier)
    : m_pResultView (in_pResultView)
    , m_lClassifier (in_lClassifier)
{}

void ClassifyThread::run () {
	m_results = m_lClassifier.classify (m_Image,_MAIN_Classify_Step,_MAIN_Train_Threshold);
	QCoreApplication::postEvent( m_pResultView, new DoneEvent);
}
const QImage &ClassifyThread::getImage() const
{
	return m_Image;
}
void ClassifyThread::start (const QImage &in_Image) {
	m_Image = in_Image;
	if (in_Image.isNull() || m_lClassifier.isNull() ) {
		m_results.clear();
		QCoreApplication::postEvent( m_pResultView, new DoneEvent);
		return;
	}
	QThread::start();
}
