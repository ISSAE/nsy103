#include <time.h>
/**
  * initialise une chaine strdate qui correspond à la date courante au format
  * ISO 8601
  */
int date(char *strdate, int taillestr) {

   /* time()   renvoie  la  date  sous  la forme du nombre de secondes depuis l'époque, 1er janvier 1970 à 00:00:00 (UTC). */
   time_t ticks = time(NULL);

/* La  fonction  gmtime()  convertit  la  date au format calendrier (temps écoulé depuis un  référentiel)  timep  en  une  représentation  humaine exprimée  en  temps  universel  (UTC).*/ 
   struct tm *strucTime=gmtime(ticks);

/* La  fonction strftime() formate les divers champs de la structure tm en fonction de la chaîne de spécification format, puis place  le  résultat dans la chaîne s de taille max. */
   return strftime(strdate,taillestr,"%F %H:%M:%S", strucTime);
}
 
