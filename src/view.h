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

#include <memory>

namespace KMediaPlayer
{

/**
 * A user interface to control a Player object.
 *
 * Player::view() should be used to access an instance of this class.
 */
class KMEDIAPLAYER_EXPORT View : public QWidget
{
    Q_OBJECT
    Q_FLAGS(Button Buttons)
    /**
     * The controls that are displayed by the interface.
     */
    Q_PROPERTY(Buttons buttons READ buttons WRITE setButtons NOTIFY buttonsChanged)
    /**
     * The widget that displays video output.
     *
     * This may be 0 if video output is not supported.
     */
    Q_PROPERTY(QWidget* videoWidget READ videoWidget)

public:
    /**
     * Creates the user interface widget.
     *
     * @param parent  The parent widget.
     */
    explicit View(QWidget *parent);
    /**
     * Destroys all related resources (but not the player object).
     */
    ~View() override;

    /** The controls that can appear in the interface. */
    enum Button {
        /**
         * A control to start playback.
         *
         * @see Player::play()
         */
        Play = 1,
        /**
         * A control to stop playback.
         *
         * @see Player::stop()
         */
        Stop = 2,
        /**
         * A control to pause playback.
         *
         * @see Player::pause()
         */
        Pause = 4,
        /**
         * A control to adjust the playback position.
         *
         * @see Player::seek()
         */
        Seeker = 8,
        /**
         * All controls.
         */
        All = 255
    };
    Q_DECLARE_FLAGS(Buttons, Button)

    /**
     * Returns which buttons are being displayed.
     */
    Buttons buttons();

    /**
     * Returns the widget used to display video output.
     *
     * May return 0 if video output is not supported.
     */
    QWidget *videoWidget();

public Q_SLOTS:
    /**
     * Set the controls to display.
     *
     * @param buttons  A ORed combination of buttons to display.
     */
    void setButtons(Buttons buttons);

    /**
     * Queries whether a particular control is being displayed.
     *
     * @param button  The control to query.
     */
    bool button(Button button);
    /**
     * Display a control.
     *
     * If the control is already displayed, this has no effect. Otherwise, it
     * will be added to the set of controls to be displayed.
     *
     * @param button  The control to display.
     */
    void showButton(Button button);
    /**
     * Stop displaying a control.
     *
     * If the control is not already displayed, this has no effect. Otherwise,
     * it will be removed from the set of controls to be displayed.
     *
     * @param button  The control to stop displaying.
     */
    void hideButton(Button button);
    /**
     * Toggle the display of a control.
     *
     * If the control is not already displayed, it will be added to the set of
     * controls to be displayed. Otherwise, it will be removed from that set.
     *
     * @param button  The control to toggle.
     */
    void toggleButton(Button button);

Q_SIGNALS:
    /**
     * Indicates that the value returned by buttons() has changed.
     *
     * Subclasses should connect to this signal to update the set of controls
     * they display.
     *
     * @param buttons  The new value.
     */
    void buttonsChanged(KMediaPlayer::View::Buttons buttons);

protected:
    /**
     * Set the widget used to display video output.
     *
     * This should normally be created with this object as the parent, but users
     * of this object may use QWidget::setParent(QWidget*) to move it elsewhere.
     */
    void setVideoWidget(QWidget *videoWidget);

private:
    std::unique_ptr<class ViewPrivate> const d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(View::Buttons)

}

Q_DECLARE_METATYPE(KMediaPlayer::View::Button)
Q_DECLARE_METATYPE(KMediaPlayer::View::Buttons)

#endif
