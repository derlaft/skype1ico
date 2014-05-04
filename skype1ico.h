#ifndef SKYPE1ICO_H
#define SKYPE1ICO_H

#include "skype1ico_global.h"

#include <QtGui/QWidget>
#include <QtGui/QSystemTrayIcon>

#include <QList>
#include <dlfcn.h>
#include <stdio.h>
#include <hashing.h>
#include <QHash>
#include <QFile>
#include <QTextStream>

typedef void (QSystemTrayIcon::*setIconProto)(const QIcon&);
extern setIconProto realSetIcon;


#endif // SKYPE1ICO_H
