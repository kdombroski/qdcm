project(dcmview)

set(MOCS
        MainWindow.h
        DicomWindow.h
        DicomTreeModel.h
   )

set(LIBS
        qdcmcore
        qdcmimage
   )

set(dcmview_DISABLE_CONSOLE TRUE)
include(build_qt_executable)
