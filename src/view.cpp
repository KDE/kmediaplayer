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

#include "view.h"

class KMediaPlayer::ViewPrivate
{
public:
    ViewPrivate()
        : videoWidget(nullptr)
        , currentButtons(View::All)
    {
        if (!buttonEnumRegistered) {
            buttonEnumRegistered = qRegisterMetaType<KMediaPlayer::View::Button>("KMediaPlayer::View::Button");
        }
        if (!buttonsFlagsRegistered) {
            buttonsFlagsRegistered = qRegisterMetaType<KMediaPlayer::View::Buttons>("KMediaPlayer::View::Buttons");
        }
    }

    QWidget *videoWidget;
    View::Buttons currentButtons;

    static bool buttonEnumRegistered;
    static bool buttonsFlagsRegistered;
};
bool KMediaPlayer::ViewPrivate::buttonEnumRegistered = false;
bool KMediaPlayer::ViewPrivate::buttonsFlagsRegistered = false;

KMediaPlayer::View::View(QWidget *parent)
    : QWidget(parent)
    , d(new ViewPrivate())
{
}

KMediaPlayer::View::~View() = default;

KMediaPlayer::View::Buttons KMediaPlayer::View::buttons()
{
    return d->currentButtons;
}

void KMediaPlayer::View::setButtons(Buttons buttons)
{
    if (buttons != d->currentButtons) {
        d->currentButtons = buttons;
        Q_EMIT buttonsChanged(buttons);
    }
}

bool KMediaPlayer::View::button(Button b)
{
    return d->currentButtons & b;
}

void KMediaPlayer::View::showButton(Button b)
{
    setButtons(d->currentButtons | b);
}

void KMediaPlayer::View::hideButton(Button b)
{
    setButtons(d->currentButtons & ~b);
}

void KMediaPlayer::View::toggleButton(Button b)
{
    setButtons(d->currentButtons ^ b);
}

void KMediaPlayer::View::setVideoWidget(QWidget *videoWidget)
{
    d->videoWidget = videoWidget;
}

QWidget *KMediaPlayer::View::videoWidget()
{
    return d->videoWidget;
}

