/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef QCONTACTACTIONSERVICEMANAGER_P_H
#define QCONTACTACTIONSERVICEMANAGER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QMultiHash>
#include <QHash>
#include <QMutex>

#include "qservice.h"
#include "qservicemanager.h"

#include "qcontactactionmanager_p.h"

QTM_BEGIN_NAMESPACE

class QContactAction;
class QContactActionFactory;

class QContactActionServiceManager : public QObject, public QContactActionManagerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QtMobility::QContactActionManagerPlugin)
public:
    static QContactActionServiceManager* instance();

    // this is a private class, so despite being a singleton we make this ctor public.
    QContactActionServiceManager();
    ~QContactActionServiceManager();

    QHash<QContactActionDescriptor, QContactActionFactory*> actionFactoryHash();
    QMultiHash<QString, QContactActionDescriptor> descriptorHash();

public slots:
    void serviceAdded(const QString& serviceName);
    void serviceRemoved(const QString& serviceName);

private:
    void init();
    bool initLock;

    QMutex m_instanceMutex;
    QServiceManager m_serviceManager;

    QHash<QContactActionDescriptor, QContactActionFactory*> m_actionFactoryHash; // descriptor to action factory ptr.
    QMultiHash<QString, QContactActionDescriptor> m_descriptorHash;  // action name to descriptor
};

QTM_END_NAMESPACE

#endif

