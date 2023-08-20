#pragma once

#include <QtCore/qglobal.h>

#if defined(TCPSOKCET_LIBRARY)
#  define TCPSOKCET_EXPORT Q_DECL_EXPORT
#else
#  define TCPSOKCET_EXPORT Q_DECL_IMPORT
#endif
