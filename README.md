# Matteo Salonia's dwm
This is my personalised build of [dwm](https://dwm.suckless.org) **6.5**.

I applied several quality-of-life patches, as well as some fixes here and there. Note that some of these patches may not apply correctly for a new dwm build, and may need to patch them yourself.

NOTE: to apply the `statuscmd` patch, I had to modify `dwm.c`, in particular the `drawbar()` function: since the patch does not account for the systray, I had to make space for it, otherwhise `dwmblocks` would draw under it.

To get started, compile dwm:

```bash
cd dwm
make
sudo make install
```

It will be available under `/usr/local/bin/dwm`.

## dwmblocks
This repo also contains my build of dwmblocks.

To obtain the scripts, you can:
- Get them from my [dotfiles](https://github.com/saloniamatteo/dotfiles) repo, under `scripts/.local/bin`
- Pull the `dotfiles` submodule, which links to the repo above.

The other scripts (`scripts/.config/scripts`) are launched by dwm, not dwmblocks.

## libXft-bgra & fonts
Glyph support in libXft was [finally fixed](https://gitlab.freedesktop.org/xorg/lib/libxft/-/merge_requests/12)
in 2022, after two and a half years. Better late than never?

It is not necessary anymore to manually patch libXft. Yay!

### Fonts
We need to set fallback fonts, otherwise things will get ugly.

Make sure you have at least one of the following fonts.
- Serif & Sans-serif: IBM Plex, Iosevka
- Emojis: JoyPixels, Noto Color Emoji

You can choose whichever you like most.. or choose all of them!

Modify `.config/fontconfig/fonts.conf`, and add the following:

```xml
<?xml version='1.0'?>
<!DOCTYPE fontconfig SYSTEM 'fonts.dtd'>
<fontconfig>
 <alias>
  <family>serif</family>
  <prefer>
   <family>IBM Plex Serif</family>
   <family>Iosevka</family>
   <family>JoyPixels</family>
   <family>Noto Color Emoji</family>
  </prefer>
 </alias>
 <alias>
  <family>sans-serif</family>
  <prefer>
   <family>IBM Plex Sans</family>
   <family>Iosevka</family>
   <family>JoyPixels</family>
   <family>Noto Color Emoji</family>
  </prefer>
 </alias>
 <alias>
  <family>sans</family>
  <prefer>
   <family>IBM Plex Sans</family>
   <family>Iosevka</family>
   <family>JoyPixels</family>
   <family>Noto Color Emoji</family>
  </prefer>
 </alias>
 <alias>
  <family>monospace</family>
  <prefer>
   <family>IBM Plex Mono</family>
   <family>Iosevka Term</family>
  </prefer>
 </alias>
 <dir>~/.fonts</dir>
</fontconfig>
```

This will set the following font preferences:
- Serif: IBM Plex Serif, Iosevka, JoyPixels, Noto Color Emoji
- Sans Serif: IBM Plex Sans, Iosevka, JoyPixels, Noto Color Emoji
- Sans: IBM Plex Sans, Iosevka, JoyPixels, Noto Color Emoji
- Monospace: IBM Plex Mono, Iosevka Term

## Keybindings
The default action key is the <kbd>ALT</kbd> key.

The Shift key will be referred to as <kbd>S</kbd>.

The Super key (also known as "windows" key) will be referred to as <kbd>WIN</kbd>.

### Actions
- Toggle statusbar: <kbd>ALT</kbd><kbd>b</kbd>
- Make window fullscreen: <kbd>ALT</kbd><kbd>f</kbd>
- Kill client: <kbd>ALT</kbd><kbd>S</kbd><kbd>c</kbd>
- Restart dwm: <kbd>ALT</kbd><kbd>S</kbd><kbd>r</kbd>
- Quit dwm: <kbd>ALT</kbd><kbd>S</kbd><kbd>q</kbd>

### Layouts
- Tile layout: <kbd>ALT</kbd><kbd>t</kbd>
- Monocle layout: <kbd>ALT</kbd><kbd>S</kbd><kbd>t</kbd>
- Spiral layout: <kbd>ALT</kbd><kbd>y</kbd>
- Dwindle layout: <kbd>ALT</kbd><kbd>S</kbd><kbd>y</kbd>
- Deck layout: <kbd>ALT</kbd><kbd>u</kbd>
- Bstack layout: <kbd>ALT</kbd><kbd>S</kbd><kbd>u</kbd>
- Bstack-horiz layout: <kbd>ALT</kbd><kbd>i</kbd>
- Grid layout: <kbd>ALT</kbd><kbd>S</kbd><kbd>i</kbd>
- Nrowgrid layout: <kbd>ALT</kbd><kbd>o</kbd>
- Horizontal grid layout: <kbd>ALT</kbd><kbd>S</kbd><kbd>o</kbd>
- Gapless grid layout: <kbd>ALT</kbd><kbd>p</kbd>
- Centeredmaster layout: <kbd>ALT</kbd><kbd>S</kbd><kbd>p</kbd>
- Make window floating: <kbd>ALT</kbd><kbd>S</kbd><kbd>SPACE</kbd>

### Gaps
- Toggle gaps: <kbd>ALT</kbd><kbd>WIN</kbd><kbd>0</kbd>
- Reset gaps: <kbd>ALT</kbd><kbd>WIN</kbd><kbd>S</kbd><kbd>0</kbd>
- Increase gaps: <kbd>ALT</kbd><kbd>WIN</kbd><kbd>1</kbd>
- Decrease gaps: <kbd>ALT</kbd><kbd>WIN</kbd><kbd>S</kbd><kbd>1</kbd>

All the other keybindings can be found in `config.h`.

### Window actions
- Move window left: <kbd>ALT</kbd><kbd>S</kbd><kbd>h</kbd>
- Move window down: <kbd>ALT</kbd><kbd>S</kbd><kbd>j</kbd>
- Move window up: <kbd>ALT</kbd><kbd>S</kbd><kbd>k</kbd>
- Move window right: <kbd>ALT</kbd><kbd>S</kbd><kbd>l</kbd>
- Decrease window width: <kbd>ALT</kbd><kbd>h</kbd>
- Increase window width: <kbd>ALT</kbd><kbd>l</kbd>
- Focus window down/anti-clockwise: <kbd>ALT</kbd><kbd>j</kbd>
- Focus window up/clockwise: <kbd>ALT</kbd><kbd>k</kbd>

All the other keybindings can be found in `config.h`.

### Tags
- View all windows: <kbd>ALT</kbd><kbd>0</kbd>
- Go to last tag: <kbd>ALT</kbd><kbd>TAB</kbd>.
- Go to tag `x`: <kbd>ALT</kbd>`x` (`x` is a value between `1` and `9`)
- Move selected window to tag `x`: <kbd>ALT</kbd><kbd>S</kbd><kbd>x</kbd>.

### Programs
- Terminal (`/usr/local/bin/st`): <kbd>ALT</kbd><kbd>ENTER</kbd>
- Rofi: <kbd>ALT</kbd><kbd>d</kbd>
- Dmenu: <kbd>ALT</kbd><kbd>S</kbd><kbd>d</kbd>
- File manager (`dolphin`): <kbd>ALT</kbd><kbd>S</kbd><kbd>f</kbd>
- Web browser (`librewolf-bin`): <kbd>ALT</kbd><kbd>S</kbd><kbd>W</kbd>

### Others
The "Print screen" key is referred to as <kbd>PrntScr</kbd>.

- Take a screenshot: <kbd>PrntScr</kbd>
- Select area to screenshot: <kbd>ALT</kbd><kbd>PrntScr</kbd>

The screenshot will be taken using `scrot`, saving it under `$HOME/Pictures`.

Some XF86 action keys are already mapped, so your keyboard's audio & brightness controls should work without any issues. Audio controls use `pactl`, while brightness controls use `xbacklight`.

NOTE: on Gentoo, the `XF86keysym.h` header (required for XF86 keys to work) is provided by the package `xorg-proto`.

### Scripts
NOTE: to launch these scripts, or even add your own, make sure you setup the correct directory! In `config.h`, look for `S_PATH`, which is set to `.config/scripts` by default. Change it only if the path to the scripts is different! You do not need to specify your home directory.

If you have any doubts, just inspect the scripts yourself.

NOTE 2: `TERMCMD` (which is `/usr/local/bin/st` by default) will be used to launch these scripts. Change it if your path is different, or you want to use a different terminal! (Example: `urxvt`)

To use the `set-fan` script, you need a ThinkPad. Even then, you need to configure `thinkpad_acpi` to allow writing custom fan speeds to `/proc/acpi/ibm/fan`. This is well explained [here](https://github.com/saloniamatteo/tp-xfan#requirements). Use your own script/program if you don't.

To use the `screenlock` script, you need `slock`.

To use the `screenrecord` script, you need `ffmpeg`. No, OBS is not used.

To use the `toggletouchpad` script, make sure you have a `synaptics` file in `/etc/X11/xorg.conf.d`! If you don't, you can copy one from your distro's defaults:

```bash
cp /usr/share/X11/xorg.conf.d/*0-synaptics.conf /etc/X11/xorg.conf.d/
```

To use the `randomwall-now` script, you need `hsetroot`. Wallpapers will be loaded from `~/wallpapers`.

The `randomwall` script, which is included but not ran by dwm, will set a random wallpaper immediately, and change it every 3 minutes. This script will run indefinitely.

- Detect and select displays: <kbd>WIN</kbd><kbd>d</kbd>
- Set fan speed: <kbd>WIN</kbd><kbd>f</kbd>
- Move mouse automatically, periodically: <kbd>WIN</kbd><kbd>i</kbd>
- Lock the screen: <kbd>WIN</kbd><kbd>l</kbd>
- Mount drives: <kbd>WIN</kbd><kbd>m</kbd>
- Record the screen: <kbd>WIN</kbd><kbd>r</kbd>
- Toggle touchpad: <kbd>WIN</kbd><kbd>t</kbd>
- Unmount drives: <kbd>WIN</kbd><kbd>u</kbd>
- Set random wallpaper: <kbd>WIN</kbd><kbd>w</kbd>
- Safe mode: <kbd>WIN</kbd><kbd>S</kbd><kbd>b</kbd>
- Emoji chooser: <kbd>WIN</kbd><kbd>S</kbd><kbd>e</kbd>
- Script launcher: <kbd>WIN</kbd><kbd>S</kbd><kbd>l</kbd>
- Set a reminder: <kbd>WIN</kbd><kbd>S</kbd><kbd>r</kbd>
- See disk usage: <kbd>WIN</kbd><kbd>S</kbd><kbd>u</kbd>
- Downloader: <kbd>XF86Search</kbd> ("Search" icon on your keyboard)

## Patches
Here the patches are explained in more detail.

The following patches are applied:
  - dwm-alpha-systray-6.3_full
  - dwm-centeredsizehints-6.5
  - dwm-cfacts-vanitygaps-6.5_full
  - dwm-dragmfact-6.5
  - dwm-focusfollowmouse-6.5
  - dwm-inplacerotate-6.2
  - dwm-netclientliststacking-6.5
  - dwm-placemouse-6.5
  - dwm-r1615-selfrestart
  - dwm-sortscreens-6.5
  - dwm-statuscmd-20210405-67d76bd
  - dwm-swallow-6.5
  - dwm-togglefullscreen-6.5
  - dwm-xresources-6.2

### dwm-alpha-systray-6.3_full
Add translucent bars to dwm, while also adding a system tray (systray).

Patch downloaded from [bakkeby]

### dwm-centeredsizehints-6.5
Center clients based on size hints.

Patch downloaded from [bakkeby]

### dwm-cfacts-vanitygaps-6.5_full
Make windows resizeable (cfacts), and add inner & outer gaps (vanitygaps).

Patch downloaded from [bakkeby]

### dwm-dragmfact-6.5
Resize windows with the mouse.

Patch downloaded from [bakkeby]

### dwm-focusfollowmouse-6.5
Focus follows the mouse

Patch downloaded from [bakkeby]

### dwm-inplacerotate-6.2
Move windows up/down the stack

Patch downloaded from [suckless]

### dwm-netclientliststacking-6.5
Add the _NET_CLIENT_LIST_STACKING property which may be needed by some applications, for example "zoom" for screen sharing

Patch downloaded from [bakkeby]

### dwm-placemouse-6.5
Move window onto another window's location, effectively "swapping" their position and sizes.

Patch downloaded from [bakkeby]

### dwm-r1615-selfrestart
Restart dwm in place.

Patch downloaded from [suckless]

### dwm-resizecorners-6.3
Resize window from the nearest corner, instead of warping the mouse to the bottom-right corner of the window. (NOTE: this was chosen instead of resizepoint because of several patching issues)

Patch downloaded from [suckless]

### dwm-sortscreens-6.5
Multi-monitor fixes

Patch downloaded from [bakkeby]

### dwm-statuscmd-20210405-67d76bd
Signaling for dwmblocks, also fixes weird `[]` shapes

Patch downloaded from [suckless]

### dwm-swallow-6.5
Swallow terminal windows

Patch downloaded from [bakkeby]

### dwm-togglefullscreen-6.5
Toggle fullscreen

Patch downloaded from [bakkeby]

[bakkeby]: https://github.com/bakkeby/patches
[suckless]: https://dwm.suckless.org/patches
