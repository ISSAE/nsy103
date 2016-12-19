	#include <locale.h>
	#include <langinfo.h>
	#include <stdio.h>

	int
main (void)
{
	int	i;
	char *  libelles [] = {
		"YESEXPR", "NOEXPR",
		"YESSTR",  "NOSTR",
		"ABDAY_1", "ABDAY_7",
		"ABMON_1", "ABMON_12",
		"DAY_1",   "DAY_7",
		"MON_1",   "MON_12",
		"AM_STR",  "PM_STR",
		"D_FMT",   "D_T_FMT",
		"T_FMT",   "T_FMT_AMPM",
		NULL
	};
	nl_item objet [] = {
		YESEXPR, NOEXPR,
		YESSTR,  NOSTR,
		ABDAY_1, ABDAY_7,
		ABMON_1, ABMON_12,
		DAY_1,   DAY_7,
		MON_1,   MON_12,
		AM_STR,  PM_STR,
		D_FMT,   D_T_FMT,
		T_FMT,   T_FMT_AMPM,
		0
	};
	setlocale (LC_ALL, "");
	for (i = 0; libelles [i] != NULL; i ++)
		fprintf (stdout, "%10s = \"%s\"\n",
				libelles [i], nl_langinfo (objet [i]));
	return (0);
}
