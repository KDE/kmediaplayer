find_package(Qt5Test ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
include(ECMMarkAsTest)
include(ECMAddTests)

ecm_add_tests(
   playertest.cpp
   viewtest.cpp
   NAME_PREFIX "kmediaplayer-"
   LINK_LIBRARIES Qt5::Test KF5::MediaPlayer
)

