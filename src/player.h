// Copyright (C) 2002 Neil Stevens <neil@qualityassistant.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// THE AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
// AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Except as contained in this notice, the name(s) of the author(s) shall not be
// used in advertising or otherwise to promote the sale, use or other dealings
// in this Software without prior written authorization from the author(s).

#ifndef KMEDIAPLAYERPLAYER_H
#define KMEDIAPLAYERPLAYER_H

#include <kparts/readonlypart.h>
#include "view.h"

#include "kmediaplayer_export.h"

#include <memory>

/**
 * An interface for media playback parts.
 */
namespace KMediaPlayer
{

/**
 * KPart interface to allow controlling and querying playback of a media track.
 *
 * This class provides methods to control playback of a single media track, as
 * well as providing information on the current playback state. It can
 * optionally provide access to a user interface that can be displayed to the
 * user.
 *
 * There are two servicetypes for this KParts interface:  KMediaPlayer/Player
 * and KMediaPlayer/Engine. KMediaPlayer/Player provides a user interface (see
 * view()), while KMediaPlayer/Engine just provides direct control via this
 * class.
 */
class KMEDIAPLAYER_EXPORT Player : public KParts::ReadOnlyPart
{
    Q_OBJECT
    Q_ENUMS(State)
    /**
     * Whether the length property is valid.
     *
     * Not all media tracks have a length (for example, some streams are
     * continuous).
     */
    Q_PROPERTY(bool hasLength READ hasLength)
    /**
     * The length of the media track in milliseconds.
     *
     * The value is undefined if hasLength is @c false.
     */
    Q_PROPERTY(qlonglong length READ length)
    /**
     * Whether playback should loop.
     *
     * As this interface has no concept of a playlist, this indicates
     * whether the current media track will play repeatedly.
     */
    Q_PROPERTY(bool looping READ isLooping WRITE setLooping)
    /**
     * The position in the media track in milliseconds.
     */
    Q_PROPERTY(qlonglong position READ position)
    /**
     * Whether seek() can be expected to work on the current media track.
     *
     * Some streams cannot be seeked.
     */
    Q_PROPERTY(bool seekable READ isSeekable)
    /**
     * The current state of the player.
     */
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)

public:
    /**
     * Constructs a Player instance with no associated GUI.
     *
     * This should be used when a KMediaPlayer/Engine is requested.
     */
    explicit Player(QObject *parent);

    /**
     * Constructs a Player instance with a GUI.
     *
     * This should be used when a KMediaPlayer/Player is requested.
     */
    Player(QWidget *parentWidget, const char *widgetName, QObject *parent);

    /**
     * Cleans up any associated resources.
     *
     * This should not explicitly delete any widget returned by view(): if it
     * has been reparented, it is up to the caller to dispose of it properly.
     */
    ~Player() override;

    /**
     * Returns the widget associated with this player.
     *
     * If the part's service type is KMediaPlayer/Player, this should not return
     * 0. However, if the part's service is just KMediaPlayer/Engine, this may
     * return 0.
     *
     * @returns  A widget to view and control this Player instance, or 0 if
     *           there is no GUI.
     */
    virtual View *view() = 0;

public Q_SLOTS:
    /**
     * Pauses playback of the media track.
     *
     * If the media track is not already paused, this should have no effect.
     */
    virtual void pause() = 0;

    /**
     * Starts playing the media track.
     *
     * If the media track is already playing, this should have no effect.
     */
    virtual void play() = 0;

    /**
     * Stops playback of the media track and returns it to the beginning.
     */
    virtual void stop() = 0;

    /**
     * Moves the current playback position.
     *
     * This will have no effect if isSeekable() is @c false.
     *
     * @param msec  The new playback position in milliseconds.
     */
    virtual void seek(qlonglong msec) = 0;
public:
    /**
     * Returns whether seek() can be expected to work on the current media
     * track.
     */
    virtual bool isSeekable() const = 0;

    /**
     * Returns the current playback position in milliseconds.
     */
    virtual qlonglong position() const = 0;

    /**
     * Returns whether the current media track has a length.
     */
    virtual bool hasLength() const = 0;

    /**
     * Returns the length of the current media track.
     *
     * The returned value is undefined if hasLength() returns @c false.
     */
    virtual qlonglong length() const = 0;

public Q_SLOTS:
    /**
     * Sets whether playback should loop.
     *
     * @param on  If @c true, playback will resume from the start of the
     *            track when the end is reached; if @c false it will not.
     */
    void setLooping(bool on);
public:
    /**
     * Returns whether playback will loop.
     */
    bool isLooping() const;
Q_SIGNALS:
    /**
     * Indicates that the value of isLooping() has changed.
     *
     * @param isLooping  The new value.
     */
    void loopingChanged(bool isLooping);

public:
    /**
     * The possible states of the player.
     */
    enum State {
        /**
         * No track is loaded.
         *
         * Most functions will not work in this state.
         */
        Empty,
        /**
         * A track is loaded, but playback is stopped.
         *
         * The position should always be 0 in this state. Playback will start
         * from the beginning when play() is called.
         */
        Stop,
        /**
         * Playback is temporarily suspended.
         *
         * Playback will resume from the current position when play() is called.
         */
        Pause,
        /**
         * The media is currently being output.
         */
        Play
    };
    /**
     * Returns the current state of the player.
     */
    State state() const;
Q_SIGNALS:
    /**
     * Indicates that the value returned by state() has changed.
     *
     * @param newState  The new value.
     */
    void stateChanged(KMediaPlayer::Player::State newState);

protected Q_SLOTS:
    /**
     * Sets the current state.
     *
     * This allows implementors to alter the playback state. This will emit the
     * stateChanged() signal as appropriate.
     */
    void setState(State state);

protected:
    /* Enable the stateChanged(QString&, ...) method that was hidden by
       the stateChanged(State) signal */
    using KXMLGUIClient::stateChanged;

private:
    std::unique_ptr<class PlayerPrivate> const d;
};

}

Q_DECLARE_METATYPE(KMediaPlayer::Player::State)

#endif
