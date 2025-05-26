    QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Items/salledespectacle.cpp \
    Items/structure.cpp \
    arborescence_projet.cpp \
    OpenGL/openglwidget.cpp \
    Items/channel.cpp \
    main.cpp \
    mainwindow.cpp \
    Items/projector.cpp \
    sauvegarder_ou_importer.cpp

HEADERS += \
    Items/salledespectacle.h \
    Items/structure.h \
    arborescence_projet.h \
    OpenGL/openglwidget.h \
    Items/channel.h \
    mainwindow.h \
    global.h \
    Items/projector.h \
    sauvegarder_ou_importer.h

RESOURCES += \
    OpenGL/res.qrc \

TRANSLATIONS += \
    Reaulight_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    OpenGL/shapes.frag \
    OpenGL/shapes.vert
