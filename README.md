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
- scratchpad: Accessible with `Alt+Shift+Enter` (will open `st` in the scratchpad) or `Alt+0` (will access all programs in the scratchpad).
- New layouts: bstack, fibonacci, deck, centered master and more. All bound to keys `Alt+(Shift+)T/Y/U/I`.
- True fullscreen (`Alt+F`) and prevents focus shifting.
- Windows can be made sticky (`Alt+S`).
- stacker: Move windows up the stack manually (`Alt+Shift+K/J`).
- shiftview: Cycle through tags (`Alt+G`).
- vanitygaps: Gaps allowed across all layouts.
- swallow patch: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- dwm can now be closed and restarted (`Alt+Shift+C` to close it, `Alt+Shift+R` to restart it)
- LayoutMenu patch: you can now right click the layout indicator to get a list of available layouts.
- RioResize patch: you can resize a window with `Alt+R`, like Plan9's rio; you can also create a new floating terminal with `Alt+Ctrl+Enter`.
- PlaceMouse patch: replace a window's position by dragging it over another window.
- ResizePoint patch: intuitively resize a window.
- cfact & dragcfact patches: resize slave windows' height with `Alt+Ctrl+H`, `Alt+Ctrl+L`, and reset it with `Alt+Ctrl+O`;
Alternatively, resize them by sliding your cursor while pressing `Alt+Shift+RightMouseButton`

## Please install `libxft-bgra`!

This build of dwm does not block color emoji in the status/info bar, so you must install [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR, which fixes a libxft color emoji rendering problem, otherwise dwm will crash upon trying to render one. Hopefully this fix will be in all libxft soon enough.

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
