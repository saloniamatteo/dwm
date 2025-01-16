/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
    [BACKGROUND] = "white",
	[INIT]       = "2d2d2d",  /* after initialization */
	[INPUT]      = "#005577", /* during input */
	[FAILED]     = "#CC3333", /* wrong password */
	[CAPS]       = "red",     /* CapsLock on */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* time in seconds before the monitor shuts down */
static const int monitortime = 30;

/* allow control key to trigger fail on clear */
static const int controlkeyclear = 1;

/* default message */
static const char *message = "Suckless: Software that sucks less.";

/* text color */
static const char *text_color = "#ffffff";

/* text size (must be a valid size) */
//static const char *font_name = "6x13";
static const char *font_name = "9x15";

/* DWM logo */
//static const int logosize = 75;
//static const int logow = 12;
//static const int logoh = 6;
/* With these settings, the logo is in the bottom-left corner */
static const int logosize = 40;
static const int logow = 62;
static const int logoh = -22;

static XRectangle rectangles[9] = {
    {0, 3, 1, 3},
    {1, 3, 2, 1},
    {0, 5, 8, 1},
    {3, 0, 1, 5},
    {5, 3, 1, 2},
    {7, 3, 1, 2},
    {8, 3, 4, 1},
    {9, 4, 1, 2},
    {11,4, 1, 2},
};

/* Enable blur */
#define BLUR

/* Set blur radius */
static const int blurRadius = 7;

/* Enable Pixelation */
#define PIXELATION

/* Set pixelation radius */
static const int pixelSize = 12;
