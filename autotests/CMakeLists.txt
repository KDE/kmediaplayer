find_package(Qt5Test ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
include(ECMMarkAsTest)
include(ECMAddTests)

macro(KMEDIAPLAYER_EXECUTABLE_TESTS)
    foreach(_testname ${ARGN})
        add_executable(${_testname} ${_testname}.cpp)
        target_link_libraries(${_testname} KF5::MediaPlayer)
        ecm_mark_as_test(${_testname})
    endforeach()
endmacro()

ecm_add_tests(
   playertest.cpp
   viewtest.cpp
   NAME_PREFIX "kmediaplayer-"
   LINK_LIBRARIES Qt5::Test
)

