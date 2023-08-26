
INCLUDEPATH *= \
    $$PWD/
INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/include/google/
INCLUDEPATH += $$PWD/protobuf/

SOURCES += \
     $$PWD/ProtocCodec.cpp \
     $$PWD/protobuf/query.pb.cc

HEADERS += \
     $$PWD/ProtocCodec.h \
     $$PWD/codec.h \
     $$PWD/dispatcher.h \
     $$PWD/noncopyable.h \
     $$PWD/protobuf/query.pb.h
