add_library(KF5MediaPlayer)
add_library(KF5::MediaPlayer ALIAS KF5MediaPlayer)

target_sources(KF5MediaPlayer PRIVATE
   player.cpp
   view.cpp
   kmediaplayeradaptor.cpp
)

generate_export_header(KF5MediaPlayer BASE_NAME KMediaPlayer)

# Apps must include <KMediaPlayer/File> or <kmediaplayer/file.h>
target_include_directories(KF5MediaPlayer INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KMediaPlayer>")

target_link_libraries(KF5MediaPlayer PUBLIC
   Qt5::Widgets
   KF5::Parts
)
target_link_libraries(KF5MediaPlayer PRIVATE
   KF5::XmlGui
)
set_target_properties(KF5MediaPlayer PROPERTIES
   VERSION ${KMEDIAPLAYER_VERSION}
   SOVERSION ${KMEDIAPLAYER_SOVERSION}
   EXPORT_NAME MediaPlayer
)

ecm_generate_headers(KMediaPlayer_CamelCase_HEADERS
  HEADER_NAMES
  Player
  View

  PREFIX KMediaPlayer
  REQUIRED_HEADERS KMediaPlayer_HEADERS
)
install(FILES ${KMediaPlayer_CamelCase_HEADERS} DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KMediaPlayer/KMediaPlayer COMPONENT Devel)

install(TARGETS KF5MediaPlayer
        EXPORT KF5MediaPlayerTargets
        ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kmediaplayer_export.h
  ${KMediaPlayer_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KMediaPlayer/kmediaplayer
  COMPONENT Devel
)

install(FILES
   kmediaplayer-engine.desktop
   kmediaplayer-player.desktop
   DESTINATION ${KDE_INSTALL_KSERVICETYPES5DIR})
install(FILES
   org.kde.KMediaPlayer.xml
   DESTINATION ${KDE_INSTALL_DBUSINTERFACEDIR}
   RENAME kf5_org.kde.KMediaPlayer.xml)
