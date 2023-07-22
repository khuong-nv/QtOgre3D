DEPENDPATH 	+= $$PWD
INCLUDEPATH += $$PWD
VPATH 		+= $$PWD


SOURCES += \
    KOgre3DWidget.cpp \
    KApplicationContext.cpp \
    KCameraMan.cpp \
    MyTestWidget.cpp \
    helper/KBaseObject.cpp \
    helper/KGridObject.cpp \
    helper/KMeshObject.cpp \
    helper/KAssimpLoader.cpp

HEADERS += \
    KOgre3DWidget.h \
    KApplicationContext.h \
    KCameraMan.h \
    MyTestWidget.h \
    helper/KBaseObject.h\
    helper/KGridObject.h \
    helper/KCommons.h \
    helper/KMeshObject.h \
    helper/KAssimpLoader.h
