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

#ifndef KMEDIAPLAYERVIEW_H
#define KMEDIAPLAYERVIEW_H

#include <QWidget>
#include "kmediaplayer_export.h"

namespace KMediaPlayer
{

/** View is part of the user interface of a Player. */
class KMEDIAPLAYER_EXPORT View : public QWidget
{
    Q_OBJECT
    Q_FLAGS(Button Buttons)
    Q_PROPERTY(Buttons buttons READ buttons WRITE setButtons NOTIFY buttonsChanged)
    Q_PROPERTY(QWidget* videoWidget READ videoWidget)

public:
    /** Your typical QWidget constructor. */
    explicit View(QWidget *parent);
    virtual ~View();

    /** The Possible buttons that can appear in the UI. */
    enum Button {
        /** Button that connects to Player::play */
        Play = 1,
        /** Button that connects to Player::stop */
        Stop = 2,
        /** Button that connects to Player::pause */
        Pause = 4,
        /** A seeker that interfaces with Player::seek */
        Seeker = 8,
        /** Show all buttons. */
        All = 255
    };
    Q_DECLARE_FLAGS(Buttons, Button)

    /** Return which buttons are being displayed. */
    Buttons buttons();

    /** Return the QWidget in which video is displayed.
        May Return 0L if there is none. */
    QWidget *videoWidget();

public Q_SLOTS:
    /** Set which buttons to display. See Button. */
    void setButtons(Buttons Buttons);

    /** Returns if a particular button is being displayed. */
    bool button(Button button);
    /** Display a particular button. */
    void showButton(Button button);
    /** Stop displaying a particular button. */
    void hideButton(Button button);
    /** Toggle the display of a particular button. */
    void toggleButton(Button button);

Q_SIGNALS:
    /** Emitted when the set of displayed buttons changes. */
    void buttonsChanged(KMediaPlayer::View::Buttons buttons);

protected:
    /** The implementing view should set the widget in which
        the video will be displayed. KMediaPlayer users may
        reparent() it to somewhere else, for example.
    */
    void setVideoWidget(QWidget *videoWidget);

private:
    class Private;
    Private *d;
};

}

Q_DECLARE_METATYPE(KMediaPlayer::View::Button)
Q_DECLARE_METATYPE(KMediaPlayer::View::Buttons)
Q_DECLARE_OPERATORS_FOR_FLAGS(KMediaPlayer::View::Buttons)

#endif
