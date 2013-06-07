/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtPim module of the Qt Toolkit.
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

import QtQuick 2.0
import QtTest 1.0
import QtContacts 5.0

TestCase {
    name: "ContactRemoveDetailTests"
    id: contactRemoveDetailTests

    Contact {
        id: contact0
    }

    function test_contact_remove_null_detail_emits_no_signal() {
        listenToSignalFromObject("contactChanged", contact0);
        contact0.removeDetail(null);
        verifyNoSignalReceived();
    }

    Contact {
        id: contact2
        Name {
            id: contact2Name
        }
    }

    function test_contact_remove_detail_emits_signal() {
        listenToSignalFromObject("contactChanged", contact2);
        contact2.removeDetail(contact2Name);
        verifySignalReceived();
    }

    Contact {
        id: contact3
        Name {
            id: contact3Name1
        }
    }

    Name {
        id: contact3Name2
    }

    function test_contact_remove_unrelated_detail_emits_no_signal() {
        listenToSignalFromObject("contactChanged", contact3);
        contact3.removeDetail(contact3Name2);
        verifyNoSignalReceived();
    }

    Contact {
        id: contact4
        Name {
            id: contact4Name
        }
    }

    PhoneNumber {
        id: contact4PhoneNumber
    }

    function test_contact_remove_unrelated_detail_of_the_different_type_emits_no_signal() {
        listenToSignalFromObject("contactChanged", contact4);
        contact4.removeDetail(contact4PhoneNumber);
        verifyNoSignalReceived();
    }

    Contact {
        id: contact5
        PhoneNumber {
            id: contact5PhoneNumber1
        }
        PhoneNumber {
            id: contact5PhoneNumber2
        }
    }

    function test_contact_remove_one_of_multiple_details_emits_signal() {
        listenToSignalFromObject("contactChanged", contact5);
        contact5.removeDetail(contact5PhoneNumber1);
        verifySignalReceived();
    }

    Contact {
        id: contact6
        PhoneNumber {
            id: contact6PhoneNumber1
        }
        PhoneNumber {
            id: contact6PhoneNumber2
        }
    }

    function test_contact_remove_multiple_details_emits_signal() {
        contact6.removeDetail(contact6PhoneNumber1);
        listenToSignalFromObject("contactChanged", contact6);
        contact6.removeDetail(contact6PhoneNumber2);
        verifySignalReceived();
    }

    Contact {
        id: contact7
        Name {
            id: contact7Name
            firstName: "old"
        }
    }

    function test_contact_modify_detail_already_removed_emits_no_signal() {
        var detail = contact7.detail(ContactDetail.Name);
        contact7.removeDetail(detail);
        listenToSignalFromObject("contactChanged", contact7);
        detail.firstName = "new";
        verifyNoSignalReceived();
    }

    property SignalSpy spy

    function init() {
        spy = Qt.createQmlObject("import QtTest 1.0;" +
                                 "SignalSpy {}",
                                 contactRemoveDetailTests);
    }

    function listenToSignalFromObject(signalName, object) {
        spy.target = object;
        spy.signalName = signalName;
        spy.clear();
    }

    function verifySignalReceived() {
        spy.wait();
    }

    function verifyNoSignalReceived() {
        verify(spy.count == 0, "no signal was received");
    }
}
