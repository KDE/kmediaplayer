# KMediaPlayer

Interface for media player KParts

## Introduction

KMediaPlayer builds on the KParts framework to provide a common interface for
KParts that can play media files.

This framework is a porting aid. It is not recommended for new projects, and
existing projects that use it are advised to port away from it, and use plain
KParts instead.


## Usage

If you are using CMake, you need to have

    find_package(KF5MediaPlayer NO_MODULE)

(or similar) in your CMakeLists.txt file, and you need to link any target that
uses KMediaPlayer against KF5::MediaPlayer.

A KPart that wishes to implement this interface must inherit
KMediaPlayer::Player, and indicate in the desktop file that it provides the
KMediaPlayer/Engine service.  It may also provide a user interface (by
implementing KMediaPlayer::View), and indicate this by listing the
KMediaPlayer/Player service in the desktop file.

Code needing to make use of this interface can search for relevant KParts with

    KService::List offers =
        KServiceTypeTrader::self()->query("KMediaPlayer/Player");

if the GUI is required, or

    KService::List offers =
        KServiceTypeTrader::self()->query("KMediaPlayer/Engine");

if not.  After checking to see if any services were returned, one can be
instantiated with

    KPluginFactory *factory = KPluginLoader(offers.first()).factory();
    if (factory) {
        KMediaPlayer::Player part = factory->create<KMediaPlayer::Player>(this);
        // use the part
    }


