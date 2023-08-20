QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG(debug,debug|release) {
    DESTDIR = $$PWD/../bin/debug/
} else {
    DESTDIR =  $$PWD/../bin/release/
}



SOURCES += \
    Client.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Client.h \
    MainWindow.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/release/Applib/ -lNetwork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/debug/Applib/ -lNetwork
else:unix:!macx: LIBS += -L$$OUT_PWD/../bin/Applib/ -lNetwork

INCLUDEPATH += $$PWD/../Common/Network
DEPENDPATH += $$PWD/../Common/Network

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/release/Applib/ -lDataBaseThread
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/debug/Applib/ -lDataBaseThread
else:unix:!macx: LIBS += -L$$PWD/../bin/Applib/ -lDataBaseThread

INCLUDEPATH += $$PWD/../Common/DataBaseThread
DEPENDPATH += $$PWD/../Common/DataBaseThread
