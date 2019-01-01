/****************************************************************************
**
** Copyright (C) 2012 Research In Motion <blackberry-qt@qnx.com>
** Contact: http://www.qt-project.org/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qeventdispatcher_blackberry_qpa_p.h"

#include "qapplication_p.h"

#include <QWindowSystemInterface>

QT_BEGIN_NAMESPACE

static bool sendWindowSystemEvents(QAbstractEventDispatcher *eventDispatcher, QEventLoop::ProcessEventsFlags flags)
{
    int nevents = 0;

    // handle gui and posted events
    QCoreApplication::sendPostedEvents();

    while (true) {
        QWindowSystemInterfacePrivate::WindowSystemEvent *event;
        if (!(flags & QEventLoop::ExcludeUserInputEvents)
            && QWindowSystemInterfacePrivate::windowSystemEventsQueued() > 0) {
            // process a pending user input event
            event = QWindowSystemInterfacePrivate::getWindowSystemEvent();
            if (!event)
                break;
        } else {
            break;
        }

        if (eventDispatcher->filterEvent(event)) {
            delete event;
            continue;
        }

        nevents++;

        QApplicationPrivate::processWindowSystemEvent(event);
        delete event;
    }

    return (nevents > 0);
}

QEventDispatcherBlackberryQPA::QEventDispatcherBlackberryQPA(QObject *parent)
    : QEventDispatcherBlackberry(parent)
{
}

QEventDispatcherBlackberryQPA::~QEventDispatcherBlackberryQPA()
{
}

bool QEventDispatcherBlackberryQPA::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    bool didSendEvents = sendWindowSystemEvents(this, flags);

    if (QEventDispatcherBlackberry::processEvents(flags))
        return true;

    return didSendEvents;
}

bool QEventDispatcherBlackberryQPA::hasPendingEvents()
{
    return QEventDispatcherBlackberry::hasPendingEvents() || QWindowSystemInterfacePrivate::windowSystemEventsQueued();
}

void QEventDispatcherBlackberryQPA::flush()
{
    if (qApp)
        qApp->sendPostedEvents();
}

QT_END_NAMESPACE
