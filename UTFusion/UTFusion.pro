QT = core gui core network

CONFIG += c++17 cmdline

#comment this part if you face error: ---from here--->
#CONFIG += release
#CONFIG -= debug
#QT += core gui network  # Remove duplicate 'core', add '+=' syntax
# <---until here---


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        FusionUtils/distance_calculator.cpp \
        FusionUtils/fusion.cpp \
        FusionUtils/pixel2world.cpp \
        buffer.cpp \
        datacontainer.cpp \
        # fusion.cpp \
        erfanmocker.cpp \
        main.cpp \
        mockimagereceiver.cpp \
        mockradardata.cpp \
        sensorwrapper.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    FusionUtils/distance_calculator.h \
    FusionUtils/fusion.h \
    FusionUtils/pixel2world.h \
    buffer.h \
    datacontainer.h \
    # fusion.h \
    erfanmocker.h \
    globals.h \
    mockimagereceiver.h \
    mockradardata.h \
    sensorwrapper.h

STATECHARTS +=

DISTFILES += \
    model.qmodel
