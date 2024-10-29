// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import Skibidi

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    visibility: Window.FullScreen
    title: "Skibidi"

    Screen01 {
        id: mainScreen
    }
}

