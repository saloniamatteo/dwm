# Salonia Matteo's build of dwm

This build of dwm has an updated `man` page over at [`dwm.1`](https://github.com/GoDzM4TT3O/dwm/blob/master/dwm.1), containing all of the keybindings. You can also directly look at the source code, inside [`config.h`](https://github.com/GoDzM4TT3O/dwm/blob/master/config.h)

Also, it includes dwmblocks, as well as the scripts I use. Please install dmwblocks separately, as the Makefile included in this directory does not install it for you (you have to `cd dwmblocks; make; sudo make install` yourself)

To be clear, [bin](https://github.com/GoDzM4TT3O/dwm/master/dwmblocks/bin) includes the scripts that make the statusbar work, meanwhile [scripts](https://github.com/GoDzM4TT3O/dwm/master/scripts) includes scripts accessible from dwm by using keybindings, like locking the screen with Super+Shift+L (requires slock, you can get [my build here](https://github.com/GoDzM4TT3O/dotfiles/tree/master/slock))

## Patches and features

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

## Please install `libxft-bgra`!

This build of dwm does not block color emoji in the status/info bar, so you must install [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR, which fixes a libxft color emoji rendering problem, otherwise dwm will crash upon trying to render one. Hopefully this fix will be in all libxft soon enough.
