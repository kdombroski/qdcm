project(dcmmod)

set(QT_DONT_USE_QTGUI TRUE)

set(LIBS dcmcore)

include(build_shared_lib)
include(build_test)
include(build_doc)
