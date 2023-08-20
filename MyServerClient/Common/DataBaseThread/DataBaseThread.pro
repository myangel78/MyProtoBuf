QT -= gui

TEMPLATE = lib
DEFINES += DATABASETHREAD_LIBRARY

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
    DESTDIR = $$PWD/../../bin/debug/Applib
} else {
    DESTDIR =  $$PWD/../../bin/release/Applib
}

SOURCES += \
    DataBaseThread.cpp

HEADERS += \
    DataBaseThread_global.h \
    DataBaseThread.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


//拷贝文件到bin目录下
FROM_FILES += \
    $$DESTDIR/$$TARGET.dll
# copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    # replace slashes in destination path for Windows
    win32:dir ~= s,/,\\,g

    for(file, files) {
        # replace slashes in source path for Windows
        win32:file ~= s,/,\\,g
        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }
    export(QMAKE_POST_LINK)
}
copyToDestDir($$FROM_FILES, $$DESTDIR/../)
