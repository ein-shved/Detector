#############################################################################
# Makefile for building: bin/detector
# Generated by qmake (2.01a) (Qt 4.8.5) on: Fri Dec 20 22:19:20 2013
# Project:  Detector.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile Detector.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1,--sort-common,--as-needed,-z,relro -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -llinear -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/FeatureVector/FeatureVector.cpp \
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
		src/main.cpp moc_ResultView.cpp
OBJECTS       = FeatureVector.o \
		FeatureVectorImg.o \
		FeatureVectorStd.o \
		FeatureVectorHOG.o \
		HOGImage.o \
		Examples.o \
		ExamplesImg.o \
		ExamplesStd.o \
		Classifier.o \
		ClassifierImg.o \
		Trainer.o \
		Bootstraper.o \
		ResultView.o \
		main.o \
		moc_ResultView.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Detector.pro
QMAKE_TARGET  = detector
DESTDIR       = bin/
TARGET        = bin/detector

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_ResultView.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) bin/ || $(MKDIR) bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Detector.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile Detector.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile Detector.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/detector1.0.0 || $(MKDIR) .tmp/detector1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/detector1.0.0/ && $(COPY_FILE) --parents src/FeatureVector/FeatureVector.h src/FeatureVector/FeatureVectorImg.h src/FeatureVector/FeatureVectorStd.h src/FeatureVector/FeatureVectorHOG.h src/FeatureVector/HOGImage.h src/Examples/Examples.h src/Examples/ExamplesImg.h src/Examples/ExamplesStd.h src/Model/Classifier.h src/Model/ClassifierImg.h src/Model/Trainer.h src/Model/Bootstraper.h src/Graphics/ResultView.h src/main.h .tmp/detector1.0.0/ && $(COPY_FILE) --parents src/FeatureVector/FeatureVector.cpp src/FeatureVector/FeatureVectorImg.cpp src/FeatureVector/FeatureVectorStd.cpp src/FeatureVector/FeatureVectorHOG.cpp src/FeatureVector/HOGImage.cpp src/Examples/Examples.cpp src/Examples/ExamplesImg.cpp src/Examples/ExamplesStd.cpp src/Model/Classifier.cpp src/Model/ClassifierImg.cpp src/Model/Trainer.cpp src/Model/Bootstraper.cpp src/Graphics/ResultView.cpp src/main.cpp .tmp/detector1.0.0/ && $(COPY_FILE) --parents src/Graphics/ResultView.ui .tmp/detector1.0.0/ && (cd `dirname .tmp/detector1.0.0` && $(TAR) detector1.0.0.tar detector1.0.0 && $(COMPRESS) detector1.0.0.tar) && $(MOVE) `dirname .tmp/detector1.0.0`/detector1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/detector1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_ResultView.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_ResultView.cpp
moc_ResultView.cpp: ui_ResultView.h \
		src/Model/ClassifierImg.h \
		src/Model/Classifier.h \
		src/FeatureVector/FeatureVector.h \
		src/definitions.h \
		src/Graphics/ResultView.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) src/Graphics/ResultView.h -o moc_ResultView.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_ResultView.h
compiler_uic_clean:
	-$(DEL_FILE) ui_ResultView.h
ui_ResultView.h: src/Graphics/ResultView.ui
	/usr/lib/qt4/bin/uic src/Graphics/ResultView.ui -o ui_ResultView.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

FeatureVector.o: src/FeatureVector/FeatureVector.cpp src/FeatureVector/FeatureVector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FeatureVector.o src/FeatureVector/FeatureVector.cpp

FeatureVectorImg.o: src/FeatureVector/FeatureVectorImg.cpp src/FeatureVector/FeatureVectorImg.h \
		src/FeatureVector/FeatureVector.h \
		src/definitions.h \
		src/FeatureVector/HOGImage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FeatureVectorImg.o src/FeatureVector/FeatureVectorImg.cpp

FeatureVectorStd.o: src/FeatureVector/FeatureVectorStd.cpp src/FeatureVector/FeatureVectorStd.h \
		src/FeatureVector/FeatureVector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FeatureVectorStd.o src/FeatureVector/FeatureVectorStd.cpp

FeatureVectorHOG.o: src/FeatureVector/FeatureVectorHOG.cpp src/FeatureVector/FeatureVectorHOG.h \
		src/FeatureVector/FeatureVector.h \
		src/FeatureVector/HOGImage.h \
		src/definitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FeatureVectorHOG.o src/FeatureVector/FeatureVectorHOG.cpp

HOGImage.o: src/FeatureVector/HOGImage.cpp src/FeatureVector/HOGImage.h \
		src/definitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HOGImage.o src/FeatureVector/HOGImage.cpp

Examples.o: src/Examples/Examples.cpp src/Examples/Examples.h \
		src/FeatureVector/FeatureVector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Examples.o src/Examples/Examples.cpp

ExamplesImg.o: src/Examples/ExamplesImg.cpp src/Examples/ExamplesImg.h \
		src/Examples/ExamplesStd.h \
		src/Examples/Examples.h \
		src/FeatureVector/FeatureVector.h \
		src/FeatureVector/FeatureVectorImg.h \
		src/definitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ExamplesImg.o src/Examples/ExamplesImg.cpp

ExamplesStd.o: src/Examples/ExamplesStd.cpp src/Examples/ExamplesStd.h \
		src/Examples/Examples.h \
		src/FeatureVector/FeatureVector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ExamplesStd.o src/Examples/ExamplesStd.cpp

Classifier.o: src/Model/Classifier.cpp src/Model/Classifier.h \
		src/FeatureVector/FeatureVector.h \
		src/definitions.h \
		src/locals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Classifier.o src/Model/Classifier.cpp

ClassifierImg.o: src/Model/ClassifierImg.cpp src/Model/ClassifierImg.h \
		src/Model/Classifier.h \
		src/FeatureVector/FeatureVector.h \
		src/definitions.h \
		src/FeatureVector/FeatureVectorImg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ClassifierImg.o src/Model/ClassifierImg.cpp

Trainer.o: src/Model/Trainer.cpp src/Model/Trainer.h \
		src/Examples/Examples.h \
		src/FeatureVector/FeatureVector.h \
		src/Model/Classifier.h \
		src/definitions.h \
		src/locals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Trainer.o src/Model/Trainer.cpp

Bootstraper.o: src/Model/Bootstraper.cpp src/FeatureVector/HOGImage.h \
		src/definitions.h \
		src/FeatureVector/FeatureVectorHOG.h \
		src/FeatureVector/FeatureVector.h \
		src/Model/Bootstraper.h \
		src/Model/Trainer.h \
		src/Examples/Examples.h \
		src/Model/Classifier.h \
		src/Examples/ExamplesStd.h \
		src/Examples/ExamplesImg.h \
		src/FeatureVector/FeatureVectorImg.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Bootstraper.o src/Model/Bootstraper.cpp

ResultView.o: src/Graphics/ResultView.cpp src/Graphics/ResultView.h \
		ui_ResultView.h \
		src/Model/ClassifierImg.h \
		src/Model/Classifier.h \
		src/FeatureVector/FeatureVector.h \
		src/definitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ResultView.o src/Graphics/ResultView.cpp

main.o: src/main.cpp src/definitions.h \
		src/Examples/ExamplesImg.h \
		src/Examples/ExamplesStd.h \
		src/Examples/Examples.h \
		src/FeatureVector/FeatureVector.h \
		src/FeatureVector/FeatureVectorImg.h \
		src/Model/Trainer.h \
		src/Model/Classifier.h \
		src/Graphics/ResultView.h \
		ui_ResultView.h \
		src/Model/ClassifierImg.h \
		src/Model/Bootstraper.h \
		src/FeatureVector/FeatureVectorHOG.h \
		src/FeatureVector/HOGImage.h \
		src/main.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

moc_ResultView.o: moc_ResultView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ResultView.o moc_ResultView.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
