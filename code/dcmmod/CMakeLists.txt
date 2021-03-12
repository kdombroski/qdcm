project(qdcmmod)

set(QT_DONT_USE_QTGUI TRUE)

set(LIBS qdcmcore)

include(build_shared_lib)
include(build_test)
include(build_doc)
