project(dcmview)

set(MOCS
        MainWindow.h
        DicomWindow.h
        DicomTreeModel.h
   )

set(LIBS
        dcmcore
   )

include(build_qt_executable)
