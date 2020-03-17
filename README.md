# fcitx-skk

fcitx-skk is an input method engine for Fcitx, which uses libskk as its backend.

## Requirements:

 - libskk
 - Qt4 (optional), for rule and dictionary configuration UI.
 - fcitx 4.2.9
 - skk-jisyo
 - libjson-glib-1.0-0

### For Ubuntu User

Please install this packages before build this Program.

 - libskk-dev
 - qtbase5-dev
 - libfcitx-qt5-dev
 - skkdic
 - libjson-glib-1.0-0

    $ sudo aptitude install libskk-dev qtbase5-dev libfcitx-qt5-dev skkdic


## Build dependency:

 - cmake
 - C++ Compiler(g++)

You can specify the skk dictionary path by -DSKK_DEFAULT_PATH=path_you_want

By default it's /usr/share/skk/SKK-JISYO.L

## Installation 

    git clone https://github.com/fcitx/fcitx-skk.git
    cd fcitx-skk
    cmake .
    sudo make install
