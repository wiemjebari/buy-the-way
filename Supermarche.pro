QT       += core gui
QT       += core gui sql
QT       += core gui multimedia
QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    caisseetrayon.cpp \
    calculatrice.cpp \
    connexion.cpp \
    employe.cpp \
    facture.cpp \
    fournisseuretstocks.cpp \
    main.cpp \
    mainwindow.cpp \
    promotion.cpp

HEADERS += \
    caisseetrayon.h \
    calculatrice.h \
    connexion.h \
    employe.h \
    facture.h \
    fournisseuretstocks.h \
    mainwindow.h \
    promotion.h

FORMS += \
    caisseetrayon.ui \
    calculatrice.ui \
    employe.ui \
    facture.ui \
    fournisseuretstocks.ui \
    mainwindow.ui \
    promotion.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc

DISTFILES += \
    ../../Projet C++/imagelogin.png \
    ../131013-abstract-blue-and-white-triangle-geometric-background-vector.jpg \
    ../add-file.png \
    ../cloud.png \
    ../delete.png \
    ../istockphoto-995719694-612x612.jpg \
    ../logo entreprise.png \
    ../logo entreprise.png \
    ../logo entreprise.png \
    ../logo.png \
    ../pie-chart.png \
    ../printer.png \
    ../smartphone.png
