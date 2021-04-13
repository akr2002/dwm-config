I stumbled upon this work by github.com/qwertycoder and modified it for my use.    
Find their repo at github.com/qwertycoder/dwm


# QWERTY's dwm build
[dwm](https://dwm.suckless.org) is an extremely fast, small, and dynamic window manager for X.


# Getting Started
## Installation
- Clone the repository and run `make` (with root privilidges if needed):
```
git clone https://github.com/qwertycoder/dwm.git && cd dwm
make clean install
```

## Running dwm
### Using startx
Add the following in `.xinitrc` file:
```
exec dwm
```
### Using a display manager
Make a desktop entry in `/usr/share/xsessions` directory:
```
cp dwm.desktop /usr/share/xsessions/
```


# Patches
- [autostart](https://dwm.suckless.org/patches/autostart/)
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
- [bar-height](https://dwm.suckless.org/patches/bar_height/)
- [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/)
- [dragmfact](https://github.com/bakkeby/patches/wiki/dragmfact/)
- [focusurgent](https://dwm.suckless.org/patches/focusurgent/)
- [fullscreen-compilation](https://github.com/bakkeby/patches/wiki/fullscreen-compilation/)
- [hide-vacant-tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [netclientliststacking](https://github.com/bakkeby/patches/wiki/netclientliststacking/)
- [pertag](https://dwm.suckless.org/patches/pertag/)
- [placemouse](https://github.com/bakkeby/patches/wiki/placemouse/)
- [resizepoint](https://github.com/bakkeby/patches/wiki/resizepoint/)
- [restartsig](https://dwm.suckless.org/patches/restartsig/)
- [reorganizetags](https://dwm.suckless.org/patches/reorganizetags/)
- [rotatestack](https://dwm.suckless.org/patches/rotatestack/)
- [savefloats](https://dwm.suckless.org/patches/save_floats/)
- [sticky](https://dwm.suckless.org/patches/sticky/)
- [stickyindicator](https://dwm.suckless.org/patches/stickyindicator/)
- [systray](https://dwm.suckless.org/patches/systray/)
- [urgentborder](https://dwm.suckless.org/patches/urgentborder/)
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
- [viewontag](https://dwm.suckless.org/patches/viewontag/)
- [xresources](https://dwm.suckless.org/patches/xresources/)


# Layouts
- Bstack
- Centered floating master
- Centered master
- Deck
- Gaplessgrid
- Grid
- Monocle
- Tile
