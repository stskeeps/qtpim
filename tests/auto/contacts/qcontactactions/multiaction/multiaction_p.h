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

#ifndef QCONTACTMULTIACTION_P_H
#define QCONTACTMULTIACTION_P_H

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

#include "qcontactaction.h"
#include "qcontactactionfactory.h"

#include "qserviceinterfacedescriptor.h"
#include "qserviceplugininterface.h"
#include "qservicecontext.h"
#include "qabstractsecuritysession.h"

#include <QSharedData>
#include <QString>
#include <QVariantMap>

QTM_USE_NAMESPACE

//! [Example Contact Action Plugin Declaration]

/*
   This action plugin is capable of producing two actions which each have the
   same action name, service name, interface name and implementation (minor) version,
   but internally use a different implementation.  This difference is reported via the
   meta data function of the factory (which is exposed to clients via the descriptor
   which provides a "front end" to the factory).

   Example use case:
   Company "Example VoIP Solutions" wants to provide a "Call" action with different implementations.
       -> it provides a SINGLE plugin which provides two actions, both of which are:
           - ServiceName = "Example VoIP Solution"
           - InterfaceName = "org.qt-project.Qt.SampleContactsActionPlugin" (QContactActionFactory::InterfaceName)
           - Major Version = "1"
           - Minor Version = "1"
           - ActionName = "call" (this is a custom property in the service interface xml)
       -> BUT one of the actions has the custom property:
           - Provider = "sip"
       -> where the other action has the custom property:
           - Provider = "example proprietary protocol"
       -> the custom properties are available to clients via the QContactActionDescriptor::metaData() function.
 */

class QContactMultiActionPlugin : public QObject, public QServicePluginInterface
{
    Q_OBJECT
    Q_INTERFACES(QtMobility::QServicePluginInterface)

public:
    QObject* createInstance(const QServiceInterfaceDescriptor& descriptor,
                            QServiceContext* context,
                            QAbstractSecuritySession* session);
};

class QContactMultiActionFactory : public QContactActionFactory
{
    Q_OBJECT

public:
    QContactMultiActionFactory();
    ~QContactMultiActionFactory();

    QList<QContactActionDescriptor> actionDescriptors() const;
    QContactAction* create(const QContactActionDescriptor& which) const;

    QSet<QContactActionTarget> supportedTargets(const QContact& contact, const QContactActionDescriptor& which) const;
    QContactFilter contactFilter(const QContactActionDescriptor& which) const;
    QVariant metaData(const QString& key, const QList<QContactActionTarget>& targets, const QVariantMap& parameters, const QContactActionDescriptor& which) const;

    bool supportsContact(const QContact& contact, const QContactActionDescriptor& which) const;

private:
    QContactActionDescriptor m_actionOneDescriptor;
    QContactActionDescriptor m_actionTwoDescriptor;
};

class QContactActionOne : public QContactAction
{
    Q_OBJECT

public:
    QContactActionOne();
    ~QContactActionOne();

    bool invokeAction(const QContactActionTarget& target, const QVariantMap& params = QVariantMap());
    bool invokeAction(const QList<QContactActionTarget>& targets, const QVariantMap& params = QVariantMap());
    QVariantMap results() const;
    State state() const;

private slots:
    void performAction();
};

class QContactActionTwo : public QContactAction
{
    Q_OBJECT

public:
    QContactActionTwo();
    ~QContactActionTwo();

    bool invokeAction(const QContactActionTarget& target, const QVariantMap& params = QVariantMap());
    bool invokeAction(const QList<QContactActionTarget>& targets, const QVariantMap& params = QVariantMap());
    QVariantMap results() const;
    State state() const;

private slots:
    void performAction();
};

//! [Example Contact Action Plugin Declaration]

#endif
