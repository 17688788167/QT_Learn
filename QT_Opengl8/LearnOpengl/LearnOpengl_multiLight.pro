#-------------------------------------------------
#
# Project created by QtCreator 2022-07-28T22:21:04
#
#-------------------------------------------------
CONFIG +=C++11
QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LearnOpengl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ./opengl
INCLUDEPATH += ./includes
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    opengl/myopenglwidget.cpp \
    opengl/actor.cpp \
    opengl/scene.cpp \
    opengl/camera.cpp \
    opengl/light/directionalpoint.cpp \
    opengl/light/pointlight.cpp \
    opengl/light/spotlight.cpp \
    opengl/light/lightbase.cpp

HEADERS += \
        mainwindow.h \
    opengl/myopenglwidget.h \
    opengl/actor.h \
    opengl/scene.h \
    opengl/data.h \
    opengl/camera.h \
    opengl/light/directionalpoint.h \
    opengl/light/pointlight.h \
    opengl/light/spotlight.h \
    opengl/light/lightbase.h \
    includes/glm/common.hpp \
    includes/glm/exponential.hpp \
    includes/glm/ext.hpp \
    includes/glm/fwd.hpp \
    includes/glm/geometric.hpp \
    includes/glm/glm.hpp \
    includes/glm/integer.hpp \
    includes/glm/mat2x2.hpp \
    includes/glm/mat2x3.hpp \
    includes/glm/mat2x4.hpp \
    includes/glm/mat3x2.hpp \
    includes/glm/mat3x3.hpp \
    includes/glm/mat3x4.hpp \
    includes/glm/mat4x2.hpp \
    includes/glm/mat4x3.hpp \
    includes/glm/mat4x4.hpp \
    includes/glm/matrix.hpp \
    includes/glm/packing.hpp \
    includes/glm/trigonometric.hpp \
    includes/glm/vec2.hpp \
    includes/glm/vec3.hpp \
    includes/glm/vec4.hpp \
    includes/glm/vector_relational.hpp

FORMS += \
        mainwindow.ui

RESOURCES += \
    images/image.qrc \
    shader/shaders.qrc

DISTFILES += \
    includes/glm/CMakeLists.txt

