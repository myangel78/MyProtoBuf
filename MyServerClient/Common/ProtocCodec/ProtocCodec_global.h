#pragma once

#include <QtCore/qglobal.h>

#if defined(PROTOCCODEC_LIBRARY)
#  define PROTOCCODEC_EXPORT Q_DECL_EXPORT
#else
#  define PROTOCCODEC_EXPORT Q_DECL_IMPORT
#endif
