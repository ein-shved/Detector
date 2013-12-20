TARGET = bin/detector
TEMPLATE = app
SOURCES += 	src/FeatureVector/FeatureVector.cpp \
		src/FeatureVector/FeatureVectorImg.cpp \
		src/FeatureVector/FeatureVectorStd.cpp \
		src/FeatureVector/FeatureVectorHOG.cpp \
		src/FeatureVector/HOGImage.cpp \
		src/Examples/Examples.cpp \
		src/Examples/ExamplesImg.cpp \
		src/Examples/ExamplesStd.cpp \
		src/Model/Classifier.cpp \
		src/Model/ClassifierImg.cpp \
		src/Model/Trainer.cpp \
		src/Model/Bootstraper.cpp \
		src/Graphics/ResultView.cpp \
		src/main.cpp

HEADERS += 	src/FeatureVector/FeatureVector.h \
		src/FeatureVector/FeatureVectorImg.h \
		src/FeatureVector/FeatureVectorStd.h \
		src/FeatureVector/FeatureVectorHOG.h \
		src/FeatureVector/HOGImage.h \
		src/Examples/Examples.h \
		src/Examples/ExamplesImg.h \
		src/Examples/ExamplesStd.h \
		src/Model/Classifier.h \
		src/Model/ClassifierImg.h \
		src/Model/Trainer.h \
		src/Model/Bootstraper.h \
		src/Graphics/ResultView.h \
		src/main.h

FORMS += 	src/Graphics/ResultView.ui

LIBS += -llinear
#CONFIG += debug
