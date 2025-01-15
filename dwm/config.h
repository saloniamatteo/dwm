/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int swterminheritfs    = 1;        /* 1 terminal inherits fullscreen on unswallow, 0 otherwise */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static unsigned int systrayspacing = 2;   /* systray spacing */
static int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static int showsystray             = 1;   /* 0 means no systray */
/* These values are set for a 2560x1440 monitor (T470p). Change to 10px, 10px for a smaller monitor (1366x768 on T440p) */
static char *fonts[]          = { "Iosevka:size=9:antialias=true:autohint=true", "JoyPixels:pixelsize=20:antialias=true:autohint=true" };
static char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]     = "#15181E"; // Bar bg color
static char normfgcolor[]     = "#7FC1E9"; // Bar fg color
static char selfgcolor[]      = "#15181E"; // Selected fg color
static char selbordercolor[]  = "#8C9CA8"; // Focused window border color
static char normbordercolor[] = "#15181E"; // Unfocused window border col
static char selbgcolor[]      = "#7FC1E9"; // Bar fg color
static const unsigned int baralpha  = 0xd0;
static const unsigned int b_alpha   = OPAQUE;
static char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, b_alpha },
	[SchemeSel]  = { OPAQUE, baralpha, b_alpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance    title                tags mask  isfloating  isterminal  noswallow  monitor */
	{ NULL,                 NULL,      "Appearance",          0,         1,          0,          -1,        -1 },
	{ NULL,                 NULL,      "Event Tester",        0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,                 NULL,      "Meeting",             0,         0,          0,          -1,        -1 }, /* Zoom meeting window */
	{ NULL,                 NULL,      "Network Connections", 0,         1,          0,          -1,        -1 },
	{ NULL,                 NULL,      "Steam Settings",      0,         1,          0,          -1,        -1 },
	{ NULL,                 NULL,      "Volume Control",      0,         1,          0,          -1,        -1 },
	{ "copyq",              NULL,      NULL,                  0,         1,          0,           0,        -1 },
	{ "Gimp",               NULL,      NULL,                  0,         0,          0,           0,        -1 },
	{ "Firefox",            NULL,      NULL,                  0,         0,          0,          -1,        -1 },
	{ "Firefox",            "Browser", NULL,                  0,         1,          0,          -1,        -1 }, /* Floating windows */
	{ "LibreWolf",          NULL,      NULL,                  0,         0,          0,          -1,        -1 },
	{ "LibreWolf",          "Browser", NULL,                  0,         1,          0,          -1,        -1 }, /* Floating windows */
	{ "St",                 NULL,      NULL,                  0,         0,          1,           0,        -1 },
	{ "VirtualBox",         NULL,      NULL,                  0,         1,          0,           0,        -1 }, /* Settings window */
	{ "VirtualBox Manager", NULL,      NULL,                  0,         0,          0,           0,        -1 },
	{ "zoom",               NULL,      NULL,                  0,         1,          0,          -1,        -1 },
};

/* layout(s) */
static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* Key definitions
 * Modkey+[0-9]:			Go to tag
 * Modkey+CTRL+[0-9]:		Add tag to current view
 * Modkey+Shift+[0-9]:		Move window to tag
 * Modkey+CTRL+Shift+[0-9]:	Show window in other tag (similar to sticky)
*/
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define TERMCMD  "/usr/local/bin/st"
#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *browsercmd[] = { "librewolf-bin", NULL };
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *filemgrcmd[] = { "dolphin", NULL };
static const char *roficmd[]    = { "rofi", "-show-icons", "-show", "drun", "-sidebar-mode", "-columns", "3", "-dpi", "1", NULL };
static const char *termcmd[]    = { TERMCMD, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { TERMCMD, "-t", scratchpadname, "-g", "120x34", NULL };

/* Scripts */
#define S_PATH ".config/scripts/"
static const char *scripts[][4] = {
	/* Termcmd  -e   PATH    script name */
	{ TERMCMD, "-e", S_PATH "displayselect",  NULL },
	{ TERMCMD, "-e", S_PATH "set-fan",        NULL },
	{ TERMCMD, "-e", S_PATH "inactivity",     NULL },
	{ TERMCMD, "-e", S_PATH "screenlock",     NULL },
	{ TERMCMD, "-e", S_PATH "dmenumount",     NULL },
	{ TERMCMD, "-e", S_PATH "screenrecord",   NULL },
	{ TERMCMD, "-e", S_PATH "toggletouchpad", NULL },
	{ TERMCMD, "-e", S_PATH "dmenuumount",    NULL },
	{ TERMCMD, "-e", S_PATH "randomwall-now", NULL },
	{ TERMCMD, "-e", S_PATH "safe-switch",    NULL },
	{ TERMCMD, "-e", S_PATH "dmenuunicode",   NULL },
	{ TERMCMD, "-e", S_PATH "launcher",       NULL },
	{ TERMCMD, "-e", S_PATH "reminder",       NULL },
	{ TERMCMD, "-e", S_PATH "disk-usage",     NULL },
	{ TERMCMD, "-e", S_PATH "downloader",     NULL },
	{ NULL },
};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include "selfrestart.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	// Tags
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)

	/* Actions */
	{ MODKEY,           XK_b,     togglebar,      {0} },   // Toggle statusbar
	{ MODKEY,           XK_f,     togglefullscreen, {0} }, // Fullscreen
	{ MODKEY|ShiftMask, XK_c,     killclient,     {0} },   // Kill client
	{ MODKEY|ShiftMask, XK_r,     self_restart,   {0} },   // Restart DWM
	{ MODKEY|ShiftMask, XK_q,     quit,           {0} },   // Close DWM

	/* Layouts */
	{ MODKEY,           XK_t,     setlayout, {.v = &layouts[0]} }, // Tile
	{ MODKEY|ShiftMask, XK_t,     setlayout, {.v = &layouts[1]} }, // Monocle
	{ MODKEY,           XK_y,     setlayout, {.v = &layouts[2]} }, // Spiral
	{ MODKEY|ShiftMask, XK_y,     setlayout, {.v = &layouts[3]} }, // Dwindle
	{ MODKEY,           XK_u,     setlayout, {.v = &layouts[4]} }, // Deck
	{ MODKEY|ShiftMask, XK_u,     setlayout, {.v = &layouts[5]} }, // Bstack
	{ MODKEY,           XK_i,     setlayout, {.v = &layouts[6]} }, // Bstackho
	{ MODKEY|ShiftMask, XK_i,     setlayout, {.v = &layouts[7]} }, // Grid
	{ MODKEY,           XK_o,     setlayout, {.v = &layouts[8]} }, // Nrowgrid
	{ MODKEY|ShiftMask, XK_o,     setlayout, {.v = &layouts[9]} }, // Horizgrd
	{ MODKEY,           XK_p,     setlayout, {.v = &layouts[10]} }, // Gapless
	{ MODKEY|ShiftMask, XK_p,     setlayout, {.v = &layouts[11]} }, // Centrdm
	{ MODKEY|ShiftMask, XK_space, togglefloating, {0} }, // Floating

	/* Gaps */
	{ MODKEY|Mod4Mask,           XK_0, togglegaps,  {0} }, // Toggle gaps
	{ MODKEY|Mod4Mask|ShiftMask, XK_0, defaultgaps, {0} }, // Reset gaps
	{ MODKEY|Mod4Mask,           XK_1, incrgaps,    {.i = +1 } },//Inc gaps
	{ MODKEY|Mod4Mask|ShiftMask, XK_1, incrgaps,    {.i = -1 } },//Dec gaps
	{ MODKEY|Mod4Mask,           XK_2, incrigaps,   {.i = +1 } },//+inner gaps
	{ MODKEY|Mod4Mask|ShiftMask, XK_2, incrigaps,   {.i = -1 } },//-inner gaps
	{ MODKEY|Mod4Mask,           XK_3, incrogaps,   {.i = +1 } },//+outer gaps
	{ MODKEY|Mod4Mask|ShiftMask, XK_3, incrogaps,   {.i = -1 } },//-outer gaps
	{ MODKEY|Mod4Mask,           XK_4, incrihgaps,  {.i = +1 } },//+inner hgap
	{ MODKEY|Mod4Mask|ShiftMask, XK_4, incrihgaps,  {.i = -1 } },//-inner hgap
	{ MODKEY|Mod4Mask,           XK_5, incrivgaps,  {.i = +1 } },//+inner wgap
	{ MODKEY|Mod4Mask|ShiftMask, XK_5, incrivgaps,  {.i = -1 } },//-inner wgap
	{ MODKEY|Mod4Mask,           XK_6, incrohgaps,  {.i = +1 } },//+outer hgap
	{ MODKEY|Mod4Mask|ShiftMask, XK_6, incrohgaps,  {.i = -1 } },//-outer hgap
	{ MODKEY|Mod4Mask,           XK_7, incrovgaps,  {.i = +1 } },//+outer wgap
	{ MODKEY|Mod4Mask|ShiftMask, XK_7, incrovgaps,  {.i = -1 } },//-outer wgap

	/* Window actions */
	{ MODKEY,            XK_h,    setmfact,   {.f = -0.05} }, //Dec win width
	{ MODKEY,            XK_l,    setmfact,   {.f = +0.05} }, //Inc win width
	{ MODKEY,            XK_k,    focusstack, {.i = +1 } }, // Focus up/clock
	{ MODKEY,            XK_j,    focusstack, {.i = -1 } }, // Focus dn/a-clk
	{ MODKEY,            XK_m,    incnmaster, {.i = +1 } }, // Add master
	{ MODKEY|ShiftMask,  XK_m,    incnmaster, {.i = -1 } }, // Remove master
	{ MODKEY,            XK_p,    zoom,       {0} }, // Selected win->master
	{ MODKEY|ControlMask,XK_j,    setcfact,   {.f = +0.25} },//Inc win height
	{ MODKEY|ControlMask,XK_k,    setcfact,   {.f = -0.25} },//Dec win height
	{ MODKEY|ShiftMask,  XK_h,    inplacerotate,{.i = +2} }, //Move window left
	{ MODKEY|ShiftMask,  XK_j,    inplacerotate,{.i = +1} }, //Move window down
	{ MODKEY|ShiftMask,  XK_k,    inplacerotate,{.i = -1} }, //Move window up
	{ MODKEY|ShiftMask,  XK_l,    inplacerotate,{.i = -2} }, //Move win right
	{ MODKEY|ShiftMask,  XK_o,    setcfact,   {.f =  0.00} },//Reset height

	/* Tag actions */
	{ MODKEY,           XK_0,      togglescratch, {0} }, // Toggle scratchpad
	{ MODKEY,           XK_Tab,    view,     {0} }, // View previous tag
	{ MODKEY,           XK_comma,  focusmon, {.i = -1 } }, // Focus prev mon
	{ MODKEY,           XK_period, focusmon, {.i = +1 } }, // Focus next mon
	{ MODKEY|ShiftMask, XK_0,      tag,      {.ui = ~0 } }, // Tag all tags
	{ MODKEY|ShiftMask, XK_comma,  tagmon,   {.i = -1 } }, // Tag prev monitor
	{ MODKEY|ShiftMask, XK_period, tagmon,   {.i = +1 } }, // Tag next monitor

	/* Programs */
	{ MODKEY,           XK_Return, spawn,    {.v = termcmd } },    // Terminal
	{ MODKEY,           XK_d,      spawn,    {.v = roficmd } },    // Rofi
	{ MODKEY|ShiftMask, XK_Return, spawn,    {.v = scratchpadcmd } }, // Scratch
	{ MODKEY|ShiftMask, XK_d,      spawn,    {.v = dmenucmd } },   // Dmenu
	{ MODKEY|ShiftMask, XK_f,      spawn,    {.v = filemgrcmd } }, // File mgr
	{ MODKEY|ShiftMask, XK_w,      spawn,    {.v = browsercmd } }, // Browser

	/* XF* actions */
	#include <X11/XF86keysym.h>
	{ 0, XF86XK_AudioMute,         spawn,    SHCMD("wpctl set-mute @DEFAULT_SINK@ toggle; kill -40 $(pidof dwmblocks)") }, // Toggle volume
	{ 0, XF86XK_AudioLowerVolume,  spawn,    SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%-; kill -40 $(pidof dwmblocks)") },     // Decrease volume
	{ 0, XF86XK_AudioRaiseVolume,  spawn,    SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%+; kill -40 $(pidof dwmblocks)") },     // Increase volume
	{ 0, XF86XK_AudioMicMute,      spawn,    SHCMD("wpctl set-mute @DEFAULT_SOURCE@ toggle; kill -40 $(pidof dwmblocks)") }, // Toggle mic
	{ 0, XF86XK_MonBrightnessUp,   spawn,    SHCMD("xbacklight -inc 10; kill -37 $(pidof dwmblocks)") }, // Increase brightness
	{ 0, XF86XK_MonBrightnessDown, spawn,    SHCMD("xbacklight -dec 10; kill -37 $(pidof dwmblocks)") }, // Decrease brightness
	{ 0, XF86XK_TouchpadOn,        spawn,    SHCMD("synclient TouchpadOff=0") }, // Enable touchpad
	{ 0, XF86XK_TouchpadOff,       spawn,    SHCMD("synclient TouchpadOff=1") }, // Disable touchpad
	{ 0, XF86XK_TouchpadToggle,    spawn,    SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },

	/* Others */
	//{ 0,      XK_Caps_Lock,  spawn,  SHCMD("kill -35 dwmblocks") }, // Update dwmblocks on CapsLock
	{ 0,      XK_Print,      spawn,  SHCMD("scrot -q 100 -p \"$HOME/Pictures/Screenshot-%4Y%m%d_%H%M%S.png\"") },
	{ MODKEY, XK_Print,	     spawn,  SHCMD("scrot -q 100 -s -p \"$HOME/Pictures/Screenshot-%4Y%m%d_%H%M%S.png\"") },

	/* Scripts */
	{ SUPERKEY,           XK_d,      spawn, { .v = &scripts[0] } }, // Select display
	{ SUPERKEY,           XK_f,      spawn, { .v = &scripts[1] } }, // Set fan speed
	{ SUPERKEY,           XK_i,      spawn, { .v = &scripts[2] } }, // Move mouse automatically
	{ SUPERKEY,           XK_l,      spawn, { .v = &scripts[3] } }, // Lock screen
	{ SUPERKEY,           XK_m,      spawn, { .v = &scripts[4] } }, // Mount drives
	{ SUPERKEY,           XK_r,      spawn, { .v = &scripts[5] } }, // Record screen
	{ SUPERKEY,           XK_t,      spawn, { .v = &scripts[6] } }, // Toggle touchpad
	{ SUPERKEY,           XK_u,      spawn, { .v = &scripts[7] } }, // Unmount drives
	{ SUPERKEY,           XK_w,      spawn, { .v = &scripts[8] } }, // Set random wallpaper
	{ SUPERKEY|ShiftMask, XK_b,      spawn, { .v = &scripts[9] } }, // Safe mode
	{ SUPERKEY|ShiftMask, XK_e,      spawn, { .v = &scripts[10]} }, // Emoji chooser
	{ SUPERKEY|ShiftMask, XK_l,      spawn, { .v = &scripts[11]} }, // Script launcher
	{ SUPERKEY|ShiftMask, XK_r,      spawn, { .v = &scripts[12]} }, // Set a reminder
	{ SUPERKEY|ShiftMask, XK_u,      spawn, { .v = &scripts[13]} }, // See disk usage
	{ 0,         XF86XK_Search,      spawn, { .v = &scripts[14]} }, // Downloader
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      dragmfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
