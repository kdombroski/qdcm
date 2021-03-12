project(echoscu)

set(QT_DONT_USE_QTGUI TRUE)
set(QT_USE_QTNETWORK TRUE)

set(MOCS
    CEchoSCU.h
    )

set(LIBS
    qdcmcore
    qdcmnet
    )

include(build_qt_executable)
