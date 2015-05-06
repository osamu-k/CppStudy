#ifndef PRODUCT_GLOBAL_H
#define PRODUCT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PRODUCT_LIBRARY)
#  define PRODUCTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PRODUCTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PRODUCT_GLOBAL_H
