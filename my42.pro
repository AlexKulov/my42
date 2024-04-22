QT -= gui

CONFIG += console
CONFIG -= app_bundle

DEFINES += _USE_GUI_
DEFINES += _USE_SHADERS_

CONFIG += QTPLOT
QTPLOT {
    DEFINES += _USE_QTPLOT_
    QT += core gui widgets
    QT+=network printsupport #for customplot
    INCLUDEPATH +=PlotQt \

    SOURCES += \
    PlotQt/Source/mainwindow.cpp \
    PlotQt/main.cpp \
    PlotQt/qcustomplot.cpp \

    HEADERS += \
    PlotQt/Source/mainwindow.h \
    PlotQt/qcustomplot.h

    FORMS += \
    PlotQt/mainwindow.ui
} else {
    SOURCES += \
    Source/42main.c \
}

INCLUDEPATH +=Include \
              Include/GL \
              Kit/Include \
              glew/include \
              glew/include/GL \
              freeglut/include \
              freeglut/include/GL \
              glfw\include\GLFW \
              #PlotQt \

SOURCES += \
        Kit/Source/dcmkit.c \
        Kit/Source/envkit.c \
        Kit/Source/fswkit.c \
        Kit/Source/geomkit.c \
        Kit/Source/glkit.c \
        Kit/Source/iokit.c \
        Kit/Source/mathkit.c \
        Kit/Source/msis86kit.c \
        Kit/Source/nrlmsise00kit.c \
        Kit/Source/orbkit.c \
        Kit/Source/sigkit.c \
        Kit/Source/sphkit.c \
        Kit/Source/timekit.c \
        Source/42GlutGui.c \
        Source/42actuators.c \
        Source/42cmd.c \
        Source/42dynamics.c \
        Source/42environs.c \
        Source/42ephem.c \
        Source/42exec.c \
        Source/42fsw.c \
        Source/42init.c \
        Source/42ipc.c \
        #Source/42main.c \
        Source/42perturb.c \
        Source/42report.c \
        Source/42sensors.c \
        Source/AcApp.c \
        Source/IPC/SimReadFromFile.c \
        Source/IPC/SimReadFromSocket.c \
        Source/IPC/SimWriteToFile.c \
        Source/IPC/SimWriteToSocket.c \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lopengl32 -lfreeglut -lglu32 -lws2_32 -lglew32
