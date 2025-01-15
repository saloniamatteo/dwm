#include <unistd.h>

// Where the dwm executable lives
// Change this if you change PREFIX in config.mk!
#define DWM_PATH "/usr/local/bin/dwm"

void self_restart(const Arg *arg);

/**
 * self-restart
 *
 * Initially inspired by: Yu-Jie Lin
 * https://sites.google.com/site/yjlnotes/notes/dwm
 *
 * Modified by: Matteo Salonia
 * https://github.com/saloniamatteo/dwm
 */
void self_restart(const Arg *arg)
{
    /* The original code simply got the CURRENT executable from /proc/self/exe:
     * while it did allow us to self-restart, it only worked if the executable
     * itself didn't change. However, if we recompile dwm, fetching the exec
     * from /proc/self/exe doesn't make any sense, because we, in fact,
     * modified the actual wanted executable. With this method,
     * we do not need to look for anything: load it directly from its path. */
    char *argv[] = { DWM_PATH, NULL };
    execv(argv[0], argv);
}
