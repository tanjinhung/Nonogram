QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickablelabel.cpp \
    csvleveldao.cpp \
    csvscoredao.cpp \
    csvuserdao.cpp \
    customscrollarea.cpp \
    customtile.cpp \
    editorlevel.cpp \
    frame.cpp \
    gamecontroller.cpp \
    level.cpp \
    main.cpp \
    profilecontroller.cpp \
    score.cpp \
    user.cpp \
    useritemwidget.cpp

HEADERS += \
    clickablelabel.h \
    csvleveldao.h \
    csvscoredao.h \
    csvuserdao.h \
    customscrollarea.h \
    customtile.h \
    difficulty.h \
    editorflag.h \
    editorlevel.h \
    frame.h \
    gamecontroller.h \
    level.h \
    leveldao.h \
    profilecontroller.h \
    score.h \
    scoredao.h \
    user.h \
    userdao.h \
    useritemwidget.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
