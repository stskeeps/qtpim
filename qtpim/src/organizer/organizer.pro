TARGET = QtOrganizer
QT = core-private

QMAKE_DOCS = $$PWD/doc/qtorganizer.qdocconf

load(qt_module)

include(details/details.pri)
include(items/items.pri)
include(requests/requests.pri)
include(filters/filters.pri)

PUBLIC_HEADERS += \
    qorganizercollection.h \
    qorganizercollectionchangeset.h \
    qorganizercollectionengineid.h \
    qorganizercollectionid.h \
    qorganizerabstractrequest.h \
    qorganizeritemchangeset.h \
    qorganizeritemdetail.h \
    qorganizeritemfetchhint.h \
    qorganizeritemfilter.h \
    qorganizeritem.h \
    qorganizeritemid.h \
    qorganizeritemengineid.h \
    qorganizeritemobserver.h \
    qorganizermanager.h \
    qorganizermanagerengine.h \
    qorganizermanagerenginefactory.h \
    qorganizerrecurrencerule.h \
    qorganizeritemsortorder.h \
    qorganizerglobal.h \
    qorganizer.h

PRIVATE_HEADERS += \
    qorganizercollection_p.h \
    qorganizercollectionchangeset_p.h \
    qorganizerabstractrequest_p.h \
    qorganizeritemchangeset_p.h \
    qorganizeritem_p.h \
    qorganizeritemdetail_p.h \
    qorganizeritemfilter_p.h \
    qorganizeritemfetchhint_p.h \
    qorganizermanager_p.h \
    qorganizerrecurrencerule_p.h \
    qorganizeritemsortorder_p.h

SOURCES += \
    qorganizercollection.cpp \
    qorganizercollectionchangeset.cpp \
    qorganizercollectionengineid.cpp \
    qorganizercollectionid.cpp \
    qorganizerabstractrequest.cpp \
    qorganizeritemchangeset.cpp \
    qorganizeritem.cpp \
    qorganizeritemdetail.cpp \
    qorganizeritemfetchhint.cpp \
    qorganizeritemfilter.cpp \
    qorganizeritemid.cpp \
    qorganizeritemengineid.cpp \
    qorganizeritemobserver.cpp \
    qorganizermanager.cpp \
    qorganizermanagerengine.cpp \
    qorganizermanagerenginefactory.cpp \
    qorganizerrecurrencerule.cpp \
    qorganizeritemsortorder.cpp \
    qorganizermanager_p.cpp

qtHaveModule(jsondb) {
    isEmpty(ORGANIZER_DEFAULT_ENGINE): ORGANIZER_DEFAULT_ENGINE=jsondb
}

!isEmpty(ORGANIZER_DEFAULT_ENGINE): DEFINES += Q_ORGANIZER_DEFAULT_ENGINE=$$ORGANIZER_DEFAULT_ENGINE

HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS
