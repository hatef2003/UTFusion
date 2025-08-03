QT += quick

# OpenCV configuration
OPENCV_PATH = E:/openCV/opencv/build
INCLUDEPATH += $$OPENCV_PATH/include

# OpenCV libraries - update the version numbers to match your actual .lib files in OPENCV_PATH/x64/vc16/lib
win32:CONFIG(release, debug|release): LIBS += -L$$OPENCV_PATH/x64/vc16/lib/ -lopencv_core4110 -lopencv_imgproc4110 -lopencv_calib3d4110
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OPENCV_PATH/x64/vc16/lib/ -lopencv_core4110 -lopencv_imgproc4110 -lopencv_calib3d4110

# Add OpenCV DLL path to runtime (needed for Windows)
win32: LIBS += -L$$OPENCV_PATH/x64/vc16/bin

SOURCES += \
        main.cpp \
        pixeltoworld.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    pixeltoworld.h
