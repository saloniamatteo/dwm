/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };

/* Bar background color */
static char normbgcolor[]           = "#15181E";

/* Bar foreground color */
static char normfgcolor[]           = "#7FC1E9";

/* Selected foreground color */
static char selfgcolor[]            = "#15181E";

/* Light Border color used for focused windows */
static char selbordercolor[]        = "#8C9CA8";

/* Dark Border color used for unfocused windows */
static char normbordercolor[]       = "#15181E";

/* Bar foreground color */	
static char selbgcolor[]            = "#7FC1E9";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class	instance	title		tags mask	isfloating	isterminal noswallow  monitor */
	{ "Gimp",	NULL,		NULL,		1 << 8,		0,		0,         0,        -1 },
	{ NULL,		NULL,		"PlayOnLinux",	0,		1,		0,         0,        -1 },
	{ NULL,		NULL,		"cpupower-gui",	0,		1,		0,         0,        -1 },
	{ TERMCLASS,	NULL,		NULL,		0,		0,		1,         0,        -1 },
	{ NULL,		NULL,		"Event Tester",	0,		0,		0,         1,        -1 },
	{ NULL,		"spterm",	NULL,		SPTAG(0),	1,		1,         0,        -1 },
	{ NULL,		"spcalc",	NULL,		SPTAG(1),	1,		1,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	/* { MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \ */
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *layoutmenu_cmd = "~/.config/scripts/layoutmenu";

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	/*
		{ "dwm.color0",		STRING,	&normbordercolor },
		{ "dwm.color8",		STRING,	&selbordercolor },
		{ "dwm.color0",		STRING,	&normbgcolor },
		{ "dwm.color4",		STRING,	&normfgcolor },
		{ "dwm.color0",		STRING,	&selfgcolor },
		{ "dwm.color4",		STRING,	&selbgcolor },
	*/
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {

	/* >>> DWM <<<
	 * These keybindings will be used for DWM-specific stuff, for example:
	 * killing a window
	 * switching between tags
	 * closing/restarting dwm
	 * etc. */

	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	/* J and K are automatically bound above in STACKEYS */

	/* [TAGS] */
	/* Assign keys to tags ("containers") */
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	TAGKEYS(			XK_0,		9)

	/* Set various layouts */
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */

	/* Switch between active tag and last opened tag */
	{ MODKEY,			XK_Tab,		view,		{0} },

	/* View the last opened tag */
	{ MODKEY,			XK_backslash,	view,		{0} },

	/* Cycle through tags */
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },

	/* Interact with tags on other monitors */
	{ MODKEY,			XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,	tagmon,		{.i = +1 } },

	/* Go a tag left */
	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	/* Go a tag right */
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },

	/* Move window to tag on the left */
	{ MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	/* Move window to tag on the right */
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },

	/* [WINDOWS] */

	/* Sticky windows */
	{ MODKEY,			XK_s,		togglesticky,	{0} },

	/* Increase/decrease the number of master windows */
	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },

	/* Kill a window */
	{ MODKEY,			XK_F4,		killclient,	{0} },

	/* Move window to previous tag */
	{ MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },

	/* Resize window left (make it smaller)*/
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	/* Resize window right (make it bigger) */
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.05} },

	/* Promote selected window to master */
	{ MODKEY,			XK_space,	zoom,		{0} },

	/* Toggle floating mode for a window */
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

	/* [GAPS] */
	/* Toggle gaps */
	{ SUPERKEY,			XK_g,		togglegaps,	{0} },

	/* Reset gaps to default size */
	{ SUPERKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },

	/* Increase/decrease gaps */
	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },

	/* [DWM] */

	/* Toggle fullscreen */
	{ MODKEY,			XK_f,		togglefullscr,	{0} },

	/* Show/hide bar */
	{ MODKEY,			XK_b,		togglebar,	{0} },

	/* Lock the screen */
	{ SUPERKEY,			XK_l,		spawn,		SHCMD("st -e ~/.config/scripts/screenlock") },

	/* Close DWM */
	{ MODKEY|ShiftMask,		XK_c,		quit,		{0} },

	/* Restart DWM */
	{ MODKEY|ShiftMask,		XK_r,		quit,		{1} },

	/* >>> PROGRAMS <<<
	 * These keybindings will be used to open programs. */

	/* [TERMINAL] */
	/* Launch a terminal (st) */
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	/* Open/close terminal (st) in scratchpad */
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.ui = 0} },

	/* [VIDEO] */
	/* Take a screenshot */
	{ 0,				XK_Print,	spawn,		SHCMD("cd ~/Pictures && scrot 'Screenshot-%d%b%4Y-%a-%H-%M-%S.png'") },
	/* Show webcam */
	{ MODKEY,			XK_F7,		spawn,		SHCMD("mpv av://v4l2:/dev/video0 --title=webcam /dev/video0 || notify-send -u critical 'Webcam' 'Could not open webcam!'") },
	/* Launch obs */
	{ MODKEY,			XK_Print,	spawn,		SHCMD("obs") },

	/* [LAUNCHER] */
	/* Launch dmenu */
	{ MODKEY|ShiftMask,		XK_d,		spawn,		SHCMD("dmenu_run") },
	/* Launch rofi */
	{ MODKEY,			XK_d,		spawn,		SHCMD("rofi -show-icons -lines 12 -padding 18 -width 60 -location 0 -show drun -sidebar-mode -columns 3 -font 'Noto Sans 8'") },
	/* Launch networkmanager-dmenu */
	{ SUPERKEY,			XK_n,		spawn,		SHCMD("networkmanager_dmenu") },

	/* [OTHERS] */
	/* Open file manager */
	{ MODKEY|ShiftMask,		XK_f,		spawn,		SHCMD("nautilus") },
	/* Open Firefox */
	{ MODKEY|ShiftMask,		XK_w,		spawn,		SHCMD("firefox") },

	/* [SPECIAL KEYS] */
	/* [AUDIO] */
	/* Mute audio */
	{ 0, XF86XK_AudioMute,				spawn,		SHCMD("amixer -qD pulse sset Master toggle; kill -44 $(pidof dwmblocks)") },
	/* Raise/lower volume */
	{ 0, XF86XK_AudioRaiseVolume,			spawn,		SHCMD("amixer -qD pulse sset Master 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,			spawn,		SHCMD("amixer -qD pulse sset Master 5%-; kill -44 $(pidof dwmblocks)") },
	/* Mute microphone */
	{ 0, XF86XK_AudioMicMute,			spawn,		SHCMD("amixer -qD pulse sset Capture toggle; kill -44 $(pidof dwmblocks)") },

	/* [VIDEO] */
	/* Toggle screenkey */
	{ MODKEY|ShiftMask,		XK_Print,	spawn,		SHCMD("killall screenkey || screenkey &") },
	{ 0, XF86XK_Tools,				spawn,		SHCMD("killall screenkey || screenkey &") },
	/* When Caps Lock is pressed, update the bar */
	{ 0,				XK_Caps_Lock,	spawn,		SHCMD("kill -36 dwmblocks") },

	/* [OTHER] */
	/* Enable/disable/toggle touchpad */
	{ 0, XF86XK_TouchpadOn,				spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_TouchpadOff,			spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadToggle,			spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },

	/* >>>SCRIPTS<<< */
	/* These keybindings will be used to launch scripts */
	/* [SUPER-BOUND] */
	{ SUPERKEY,			XK_c,		spawn,		SHCMD("st -e ~/.config/scripts/classroom") },
	{ SUPERKEY,			XK_d,		spawn,		SHCMD("st -e ~/.config/scripts/displayselect") },
	{ SUPERKEY,			XK_i,		spawn,		SHCMD("st -e ~/.config/scripts/inactivity") },
	{ SUPERKEY,			XK_m,		spawn,		SHCMD("st -e ~/.config/scripts/dmenumount") },
	{ SUPERKEY,			XK_r,		spawn,		SHCMD("st -e ~/.config/scripts/screenrecord") },
	{ SUPERKEY,			XK_s,		spawn,		SHCMD("st -e ~/.config/scripts/music") },
	{ SUPERKEY,			XK_t,		spawn,		SHCMD("st -e ~/.config/scripts/toggletouchpad") },
	{ SUPERKEY,			XK_u,		spawn,		SHCMD("st -e ~/.config/scripts/dmenuumount") },
	{ SUPERKEY,			XK_w,		spawn,	    	SHCMD("st -e ~/.config/scripts/randomwall-now") },
	{ SUPERKEY|ShiftMask,		XK_b,		spawn,		SHCMD("st -e ~/.config/scripts/safe-switch") },
	{ SUPERKEY|ShiftMask,		XK_e,		spawn,		SHCMD("st -e ~/.config/scripts/dmenuunicode") },
	{ SUPERKEY|ShiftMask,		XK_r,		spawn,		SHCMD("st -e ~/.config/scripts/reminder") },
	{ SUPERKEY|ShiftMask,		XK_u,		spawn,		SHCMD("st -e ~/.config/scripts/disk-usage") },

	/* [FNKEY-BOUND] */
	{ 0, XF86XK_Display,				spawn,		SHCMD("st -e ~/.config/scripts/webcam") },
	{ 0, XF86XK_Explorer,				spawn,		SHCMD("st -e ~/.config/scripts/orario") },
	{ 0, XF86XK_LaunchA,				spawn,		SHCMD("st -e ~/.config/scripts/launcher") },
	{ 0, XF86XK_MonBrightnessDown,			spawn,		SHCMD("xbacklight -dec 10; kill -45 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessUp,			spawn,		SHCMD("xbacklight -inc 10; kill -45 $(pidof dwmblocks)") },
	{ 0, XF86XK_Search,				spawn,		SHCMD("st -e ~/.config/scripts/downloader") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkLtSymbol,		0,		Button3,	layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/dwm/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};
