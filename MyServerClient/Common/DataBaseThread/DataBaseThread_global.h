#pragma once

#include <QtCore/qglobal.h>

#if defined(DATABASETHREAD_LIBRARY)
#  define DATABASETHREAD_EXPORT Q_DECL_EXPORT
#else
#  define DATABASETHREAD_EXPORT Q_DECL_IMPORT
#endif
