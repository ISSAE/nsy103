#include <time.h>
int date(char *strdate, int taillestr, time_t *tm) {
   return strftime(strdate,taillestr,"%F %H:%M:%S", gmtime(tm));
}
 
