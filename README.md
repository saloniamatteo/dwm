# Salonia Matteo's build of dwm

This build of dwm has an updated `man` page over at [`dwm.1`](https://github.com/saloniamatteo/dwm/blob/master/dwm.1), containing all of the keybindings. You can also directly look at the source code, inside [`config.h`](https://github.com/saloniamatteo/dwm/blob/master/config.h)

Also, it includes dwmblocks, as well as the scripts I use. Please install dmwblocks separately, as the Makefile included in this directory does not install it for you (you have to `cd dwmblocks; make; sudo make install` yourself)

To be clear, [bin](https://github.com/saloniamatteo/dwm/tree/master/dwmblocks/bin) includes the scripts that make the statusbar work, meanwhile [scripts](https://github.com/saloniamatteo/dwm/tree/master/scripts) includes scripts accessible from dwm by using keybindings, like locking the screen with Super+Shift+L (requires slock, you can get [my build here](https://github.com/saloniamatteo/dotfiles/tree/master/slock))

I also created a custom patch ([`dwm-systray.diff`](https://github.com/saloniamatteo/dwm/blob/master/patches/dwm-systray.diff)) that implements a systray (system tray). To patch an existing dwm build, copy the file in your build's directory, then run this command: `patch < dwm-systray.diff`. Then, if there were no errors, run `make clean`, then build it with `make` and finally `sudo make install`.

Here's how the systray looks (applets are `copyq` and `nm-applet`)
![Systray](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/systray.png)

## Patches and features

- Added a systray (the new patch is available in the [patches folder](https://github.com/saloniamatteo/dwm/tree/master/patches))
- Clickable statusbar with Luke Smith's build of [dwmblocks](https://github.com/lukesmithxyz/dwmblocks).
- Reads xresources colors/variables (i.e. works with `pywal`, etc.).
- scratchpad: Accessible with <kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>Enter</kbd> (will open `st` in the scratchpad) or <kbd>Alt</kbd>+<kbd>0</kbd> (will access all programs in the scratchpad).
- New layouts: bstack, fibonacci, deck, centered master and more.
All bound to keys <kbd>Alt</kbd>+(<kbd>Shift</kbd>+)
<kbd>T</kbd>/<kbd>Y</kbd>/<kbd>U</kbd>/<kbd>I</kbd>.
- True fullscreen (<kbd>Alt</kbd>+<kbd>F</kbd>) and prevents focus shifting.
- Windows can be made sticky (<kbd>Alt</kbd>+<kbd>S</kbd>).
- stacker: Move windows up the stack manually (<kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>K</kbd>/<kbd>J</kbd>).
- shiftview: Cycle through tags (<kbd>Alt</kbd>+<kbd>G</kbd>).
- vanitygaps: Gaps allowed across all layouts.
- swallow patch: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- dwm can now be closed and restarted (<kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>C</kbd> to close it, <kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>R</kbd> to restart it)
- LayoutMenu patch: you can now right click the layout indicator to get a list of available layouts.
- RioResize patch: you can resize a window with <kbd>Alt</kbd>+<kbd>R</kbd>, like Plan9's rio; you can also create a new floating terminal with <kbd>Alt</kbd>+<kbd>Ctrl</kbd>+<kbd>Enter</kbd>.
- PlaceMouse patch: replace a window's position by dragging it over another window.
- ResizePoint patch: intuitively resize a window.
- cfact & dragcfact patches: resize slave windows' height with <kbd>Alt</kbd>+<kbd>Ctrl</kbd>+<kbd>H</kbd>, <kbd>Alt</kbd>+<kbd>Ctrl</kbd>+<kbd>L</kbd>, and reset it with <kbd>Alt</kbd>+<kbd>Ctrl</kbd>+<kbd>O</kbd>;
Alternatively, resize them by sliding your cursor while pressing <kbd>Alt</kbd>+<kbd>Shift</kbd>+<kbd>RightMouseButton</kbd>

(Video previews of RioResize, PlaceMouse, and ResizePoint are available [here](#Previews))

## Please install `libxft-bgra`!
This build of dwm does not block color emoji in the status/info bar, so you must install (or patch) libxft-bgra,
which fixes a libXft color emoji rendering problem, otherwise dwm will crash upon trying to render one.
Hopefully this fix will be in all libXft soon enough.

### Gentoo
You have to patch libXft with the following steps:

1. Create the `/etc/portage/patches/x11-misc/libXft` directory:
`mkdir -p /etc/portage/patches/x11-misc/libXft`
2. Add the patch to the new directory:
`wget https://gitlab.freedesktop.org/xorg/lib/libxft/merge_requests/1.patch -O /etc/portage/patches/x11-misc/libXft/libxft-bgra.patch`
3. Re-emerge `x11-misc/libXft`. Portage will automatically apply the patch:
`emerge x11-misc/libXft`
4. You should now see color emojis, if you installed a Font that supports color emojis, like "JoyPixels" or "Noto Color Emoji".

### Arch Linux
You can get libxft-bgra [here](https://aur.archlinux.org/packages/libxft-bgra/)

## dwmblocks

This repository includes my fork of Luke Smith's build of dwmblocks.

+ Available blocks explained, from left to right:
	- Caps Lock indicator

	![On](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-capslock-on.png) ![Off](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-capslock-off.png)

	- Brightness indicator

	![High Brightness](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-brightness-high.png) ![Mid Brightness](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-brightness-mid.png) ![Low Brightness](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-brightness-low.png)

	- RAM usage

	![Memory](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-memory.png)

	- CPU temperature

	![Cpu](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-cpu.png)

	- Volume indicator, as well as microphone status (on/off)

	![Vol High](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-vol-high.png) ![Vol Mid](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-vol-mid.png) ![Vol Low](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-vol-low.png) ![Vol Mute](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-vol-mute.png)

	- Fan speed indicator (a = auto, [1-7] is normal level, max = full speed). NOTE: this only works on ThinkPads, so modify the script for your system accordingly if you want to use it.

	![Fan Auto](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-fan-auto.png) ![Fan 5](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-fan-5.png) ![Fan Max](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-fan-max.png)

	- Internet (Wi-Fi/Ethernet) indicator

	![Internet](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-internet.png)

	- Battery status (Charging/Discharging/Unknown) & capacity indicator

	![Bat Charging](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-bat-charging.png) ![Bat Discharging](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-bat-discharging.png)

	- Date and time indicator

	![Date and Time](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/blocks-datetime.png)


## Previews

### Video Previews (Patches)
RioResize:
![RioResize](https://user-images.githubusercontent.com/28765699/114319182-da048780-9aff-11eb-93c8-2fbee7cb4bbc.gif)

PlaceMouse:
![PlaceMouse](https://user-images.githubusercontent.com/28765699/114319092-85f9a300-9aff-11eb-90d2-c10ec06a785b.gif)

ResizePoint:
![ResizePoint](https://user-images.githubusercontent.com/28765699/114319158-c35e3080-9aff-11eb-8311-834fc5d225d9.gif)


### Misc

St
![St](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/preview-st.png)

Floating window
![Floating window](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/preview-floating-win.png)

No windows
![No windows](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/preview-nowin.png)

### Layouts

Tile
![Tile](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/layouts-tile.png)

Bstack
![Bstack](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/layouts-bstack.png)

Spiral
![Spiral](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/layouts-spiral.png)

Dwindle
![Dwindle](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/layouts-dwindle.png)

Centered Master
![Centered Master](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/layouts-centeredmaster.png)

Centered Floating Master
![Centered Floating Master](https://raw.githubusercontent.com/saloniamatteo/dwm/master/Previews/layouts-centeredfloatingmaster.png)
