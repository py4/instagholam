#############################################################################
# Makefile for building: instagholam
# Generated by qmake (2.01a) (Qt 4.8.4) on: Wed May 21 20:11:36 2014
# Project:  instagholam.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile instagholam.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Iparser -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
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

SOURCES       = api.cpp \
		cli.cpp \
		clickableimage.cpp \
		comment.cpp \
		commentswindow.cpp \
		db.cpp \
		favoriteswindow.cpp \
		fellowwindow.cpp \
		friend_request.cpp \
		hashtag.cpp \
		main.cpp \
		mainwindow.cpp \
		post.cpp \
		postwindow.cpp \
		profile_table.cpp \
		requestbutton.cpp \
		user.cpp \
		user_report.cpp \
		users_table.cpp \
		parser/node.cpp \
		parser/parser.cpp \
		parser/XML.cpp moc_clickableimage.cpp \
		moc_commentswindow.cpp \
		moc_favoriteswindow.cpp \
		moc_fellowwindow.cpp \
		moc_mainwindow.cpp \
		moc_postwindow.cpp \
		moc_profile_table.cpp \
		moc_requestbutton.cpp \
		moc_users_table.cpp
OBJECTS       = api.o \
		cli.o \
		clickableimage.o \
		comment.o \
		commentswindow.o \
		db.o \
		favoriteswindow.o \
		fellowwindow.o \
		friend_request.o \
		hashtag.o \
		main.o \
		mainwindow.o \
		post.o \
		postwindow.o \
		profile_table.o \
		requestbutton.o \
		user.o \
		user_report.o \
		users_table.o \
		node.o \
		parser.o \
		XML.o \
		moc_clickableimage.o \
		moc_commentswindow.o \
		moc_favoriteswindow.o \
		moc_fellowwindow.o \
		moc_mainwindow.o \
		moc_postwindow.o \
		moc_profile_table.o \
		moc_requestbutton.o \
		moc_users_table.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
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
		instagholam.pro
QMAKE_TARGET  = instagholam
DESTDIR       = 
TARGET        = instagholam

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

$(TARGET): ui_commentswindow.h ui_favoriteswindow.h ui_fellowwindow.h ui_mainwindow.h ui_postwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: instagholam.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
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
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile instagholam.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
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
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile instagholam.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/instagholam1.0.0 || $(MKDIR) .tmp/instagholam1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/instagholam1.0.0/ && $(COPY_FILE) --parents api.h cli.h clickableimage.h comment.h commentswindow.h db.h exception.h favoriteswindow.h fellowwindow.h friend_request.h hashtag.h mainwindow.h photo.h post.h postwindow.h profile_table.h requestbutton.h user.h user_report.h users_table.h parser/node.h parser/parser.h parser/XML.h .tmp/instagholam1.0.0/ && $(COPY_FILE) --parents api.cpp cli.cpp clickableimage.cpp comment.cpp commentswindow.cpp db.cpp favoriteswindow.cpp fellowwindow.cpp friend_request.cpp hashtag.cpp main.cpp mainwindow.cpp post.cpp postwindow.cpp profile_table.cpp requestbutton.cpp user.cpp user_report.cpp users_table.cpp parser/node.cpp parser/parser.cpp parser/XML.cpp .tmp/instagholam1.0.0/ && $(COPY_FILE) --parents commentswindow.ui favoriteswindow.ui fellowwindow.ui mainwindow.ui postwindow.ui .tmp/instagholam1.0.0/ && (cd `dirname .tmp/instagholam1.0.0` && $(TAR) instagholam1.0.0.tar instagholam1.0.0 && $(COMPRESS) instagholam1.0.0.tar) && $(MOVE) `dirname .tmp/instagholam1.0.0`/instagholam1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/instagholam1.0.0


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

compiler_moc_header_make_all: moc_clickableimage.cpp moc_commentswindow.cpp moc_favoriteswindow.cpp moc_fellowwindow.cpp moc_mainwindow.cpp moc_postwindow.cpp moc_profile_table.cpp moc_requestbutton.cpp moc_users_table.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_clickableimage.cpp moc_commentswindow.cpp moc_favoriteswindow.cpp moc_fellowwindow.cpp moc_mainwindow.cpp moc_postwindow.cpp moc_profile_table.cpp moc_requestbutton.cpp moc_users_table.cpp
moc_clickableimage.cpp: clickableimage.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) clickableimage.h -o moc_clickableimage.cpp

moc_commentswindow.cpp: commentswindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) commentswindow.h -o moc_commentswindow.cpp

moc_favoriteswindow.cpp: favoriteswindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) favoriteswindow.h -o moc_favoriteswindow.cpp

moc_fellowwindow.cpp: fellowwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) fellowwindow.h -o moc_fellowwindow.cpp

moc_mainwindow.cpp: api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		mainwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_postwindow.cpp: postwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) postwindow.h -o moc_postwindow.cpp

moc_profile_table.cpp: api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		profile_table.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) profile_table.h -o moc_profile_table.cpp

moc_requestbutton.cpp: requestbutton.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) requestbutton.h -o moc_requestbutton.cpp

moc_users_table.cpp: users_table.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) users_table.h -o moc_users_table.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_commentswindow.h ui_favoriteswindow.h ui_fellowwindow.h ui_mainwindow.h ui_postwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_commentswindow.h ui_favoriteswindow.h ui_fellowwindow.h ui_mainwindow.h ui_postwindow.h
ui_commentswindow.h: commentswindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic commentswindow.ui -o ui_commentswindow.h

ui_favoriteswindow.h: favoriteswindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic favoriteswindow.ui -o ui_favoriteswindow.h

ui_fellowwindow.h: fellowwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic fellowwindow.ui -o ui_fellowwindow.h

ui_mainwindow.h: mainwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_postwindow.h: postwindow.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic postwindow.ui -o ui_postwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

api.o: api.cpp api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		user.h \
		post.h \
		friend_request.h \
		user_report.h \
		comment.h \
		hashtag.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o api.o api.cpp

cli.o: cli.cpp cli.h \
		db.h \
		exception.h \
		api.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cli.o cli.cpp

clickableimage.o: clickableimage.cpp clickableimage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o clickableimage.o clickableimage.cpp

comment.o: comment.cpp comment.h \
		post.h \
		user.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o comment.o comment.cpp

commentswindow.o: commentswindow.cpp commentswindow.h \
		ui_commentswindow.h \
		api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o commentswindow.o commentswindow.cpp

db.o: db.cpp db.h \
		user.h \
		post.h \
		hashtag.h \
		friend_request.h \
		user_report.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o db.o db.cpp

favoriteswindow.o: favoriteswindow.cpp favoriteswindow.h \
		ui_favoriteswindow.h \
		requestbutton.h \
		api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		fellowwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o favoriteswindow.o favoriteswindow.cpp

fellowwindow.o: fellowwindow.cpp fellowwindow.h \
		ui_fellowwindow.h \
		profile_table.h \
		api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fellowwindow.o fellowwindow.cpp

friend_request.o: friend_request.cpp friend_request.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o friend_request.o friend_request.cpp

hashtag.o: hashtag.cpp hashtag.h \
		post.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hashtag.o hashtag.cpp

main.o: main.cpp db.h \
		parser/parser.h \
		mainwindow.h \
		api.h \
		exception.h \
		parser/XML.h \
		parser/node.h \
		cli.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		ui_mainwindow.h \
		clickableimage.h \
		postwindow.h \
		profile_table.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

post.o: post.cpp post.h \
		parser/parser.h \
		db.h \
		photo.h \
		comment.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o post.o post.cpp

postwindow.o: postwindow.cpp postwindow.h \
		ui_postwindow.h \
		commentswindow.h \
		api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		favoriteswindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o postwindow.o postwindow.cpp

profile_table.o: profile_table.cpp profile_table.h \
		api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		postwindow.h \
		clickableimage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o profile_table.o profile_table.cpp

requestbutton.o: requestbutton.cpp requestbutton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o requestbutton.o requestbutton.cpp

user.o: user.cpp user.h \
		friend_request.h \
		db.h \
		post.h \
		photo.h \
		comment.h \
		user_report.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o user.o user.cpp

user_report.o: user_report.cpp user_report.h \
		user.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o user_report.o user_report.cpp

users_table.o: users_table.cpp api.h \
		exception.h \
		db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		requestbutton.h \
		fellowwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o users_table.o users_table.cpp

node.o: parser/node.cpp parser/node.h \
		parser/parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o node.o parser/node.cpp

parser.o: parser/parser.cpp parser/parser.h \
		exception.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parser.o parser/parser.cpp

XML.o: parser/XML.cpp parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o XML.o parser/XML.cpp

moc_clickableimage.o: moc_clickableimage.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_clickableimage.o moc_clickableimage.cpp

moc_commentswindow.o: moc_commentswindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_commentswindow.o moc_commentswindow.cpp

moc_favoriteswindow.o: moc_favoriteswindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_favoriteswindow.o moc_favoriteswindow.cpp

moc_fellowwindow.o: moc_fellowwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_fellowwindow.o moc_fellowwindow.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_postwindow.o: moc_postwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_postwindow.o moc_postwindow.cpp

moc_profile_table.o: moc_profile_table.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_profile_table.o moc_profile_table.cpp

moc_requestbutton.o: moc_requestbutton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_requestbutton.o moc_requestbutton.cpp

moc_users_table.o: moc_users_table.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_users_table.o moc_users_table.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

