#pragma once

#include <QtCore/qglobal.h>

#if defined(NETWORK_LIBRARY)
#  define NETWORK_EXPORT Q_DECL_EXPORT
#else
#  define NETWORK_EXPORT Q_DECL_IMPORT
#endif
