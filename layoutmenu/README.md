# Matteo Salonia's build of dwm

## Patches and features

- Clickable statusbar with Luke Smith's build of [dwmblocks](https://github.com/lukesmithxyz/dwmblocks).
- Reads xresources colors/variables (i.e. works with `pywal`, etc.).
- scratchpad: Accessible with Alt+Shift+Enter (or Alt+0).
- New layouts: bstack, fibonacci, deck, centered master and more. All bound to keys `Alt+(Shift+)T/Y/U/I`.
- True fullscreen (`Alt+F`) and prevents focus shifting.
- Windows can be made sticky (`Alt+S`).
- stacker: Move windows up the stack manually (`Alt+Shift+K/J`).
- shiftview: Cycle through tags (`Alt+G`).
- vanitygaps: Gaps allowed across all layouts.
- swallow patch: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- dwm can now be closed and restarted (`Alt+Shift+C` to close it, `Alt+Shift+R` to restart it)

For other keybindings, read the manual page (`dwm.1`) or the config file (`config.h`)

## Please install `libxft-bgra`!

This build of dwm does not block color emoji in the status/info bar, so you must install [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra-git/) from the AUR, which fixes a libxft color emoji rendering problem, otherwise dwm will crash upon trying to render one. Hopefully this fix will be in all libxft soon enough.
