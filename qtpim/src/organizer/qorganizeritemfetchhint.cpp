/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtOrganizer module of the Qt Toolkit.
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

#include "qorganizeritemfetchhint_p.h"

#include <QtCore/QDataStream>
#ifndef QT_NO_DEBUG_STREAM
#include <QtCore/qdebug.h>
#endif // QT_NO_DEBUG_STREAM

QT_BEGIN_NAMESPACE_ORGANIZER

/*!
    \class QOrganizerItemFetchHint
    \brief The QOrganizerItemFetchHint class provides hints to the manager about which organizer item
           information needs to be retrieved.
    \inmodule QtOrganizer
    \ingroup organizer-filters

    All of the hints may be ignored at the discretion of the manager, however if a manager
    is able to optimize retrieval of organizer items due to hints, it may do so.  If a manager
    ignores a hint, it must retrieve the full set of data that the hint refers to.

    The fetch hint contains:
    \list
    \li a list of detail definition names which the client is interested
       in (empty if interested in all detail definitions)
    \li some optimization flags which allow the client to tell the backend if they are
       not interested in binary blobs (images etc).
    \endlist

    Important note: if certain organizer item is retrieved with fetch hint set, normal saving will
    result in the loss of information that is not retrieved. Partial save should be used to avoid
    information loss.
 */

/*!
    \enum QOrganizerItemFetchHint::OptimizationHint

    This enum defines flags which may be set to inform the backend that the client does
    not require certain information.

    \value AllRequired          Tells the backend that all information is required.
    \value NoActionPreferences  Tells the backend that the client does not require retrieved
                                organizer items to include a cache of action preferences.
    \value NoBinaryBlobs        Tells the backend that the client does not require retrieved
                                organizer items to include binary blobs such as thumbnail images.
 */

/*!
    Constructs a new organizer item fetch hint which requests that the backend fetch all information.
 */
QOrganizerItemFetchHint::QOrganizerItemFetchHint()
    : d(new QOrganizerItemFetchHintPrivate)
{
}

/*!
    Constructs a new organizer item fetch hint as a copy of \a other.
 */
QOrganizerItemFetchHint::QOrganizerItemFetchHint(const QOrganizerItemFetchHint &other)
    : d(other.d)
{
}

/*!
    Frees any memory in use by the fetch hint.
 */
QOrganizerItemFetchHint::~QOrganizerItemFetchHint()
{
}

/*!
    Assigns this fetch hint to the \a other.
 */
QOrganizerItemFetchHint& QOrganizerItemFetchHint::operator=(const QOrganizerItemFetchHint &other)
{
    d = other.d;
    return *this;
}

/*!
    Returns the list of detail types that identify details which should be retrieved by the manager
    when fetching items.

    \sa setDetailTypesHint()
 */
QList<QOrganizerItemDetail::DetailType> QOrganizerItemFetchHint::detailTypesHint() const
{
    return d->m_detailTypesHint;
}

/*!
    Sets the list of detail types to \a detailTypes that identify details which should be retrieved'
    by the manager when fetching items.

    \sa detailTypesHint()
 */
void QOrganizerItemFetchHint::setDetailTypesHint(const QList<QOrganizerItemDetail::DetailType> &detailTypes)
{
    d->m_detailTypesHint = detailTypes;
}

/*!
    Returns the optimization hint flags specified by the client.

    \sa setOptimizationHints()
 */
QOrganizerItemFetchHint::OptimizationHints QOrganizerItemFetchHint::optimizationHints() const
{
    return d->m_optimizationHints;
}

/*!
    Sets the optimization hint flags specified by the client to \a hints.

    \sa optimizationHints()
 */
void QOrganizerItemFetchHint::setOptimizationHints(OptimizationHints hints)
{
    d->m_optimizationHints = hints;
}

#ifndef QT_NO_DATASTREAM
/*!
    \relates QOrganizerItemFetchHint
    Streams \a hint to the data stream \a out.
 */
QDataStream &operator<<(QDataStream &out, const QOrganizerItemFetchHint &hint)
{
    quint8 formatVersion = 1;
    return out << formatVersion
               << hint.detailTypesHint()
               << static_cast<quint32>(hint.optimizationHints());
}

/*!
    \relates QOrganizerItemFetchHint
    Streams \a hint in from the data stream \a in.
 */
QDataStream &operator>>(QDataStream &in, QOrganizerItemFetchHint &hint)
{
    quint8 formatVersion;
    in >> formatVersion;
    if (formatVersion == 1) {
        QList<quint32> detailTypesHint;
        quint32 optimizations;
        in >> detailTypesHint >> optimizations;

        QList<QOrganizerItemDetail::DetailType> types;
        foreach (quint32 detailType, detailTypesHint)
            types.append(static_cast<QOrganizerItemDetail::DetailType>(detailType));
        hint.setDetailTypesHint(types);

        hint.setOptimizationHints(static_cast<QOrganizerItemFetchHint::OptimizationHints>(optimizations));
    } else {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}
#endif // QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
/*!
    \relates QOrganizerItemFetchHint
    Outputs \a hint to the debug stream \a dbg.
 */
QDebug operator<<(QDebug dbg, const QOrganizerItemFetchHint &hint)
{
    dbg.nospace() << "QOrganizerItemFetchHint(";
    dbg.nospace() << "detailDefinitionsHint=";
    dbg.nospace() << hint.detailTypesHint();
    dbg.nospace() << ",";
    dbg.nospace() << "optimizationHints=";
    dbg.nospace() << static_cast<quint32>(hint.optimizationHints());
    dbg.nospace() << ")";
    return dbg.maybeSpace();
}
#endif // QT_NO_DEBUG_STREAM

QT_END_NAMESPACE_ORGANIZER