#ifndef _ERREUR_H
#define _ERREUR_H (1)
/* START_INCLUDE_H */
#include "erreur.h"
/* END_INCLUDE_H */


/* START_DECLARATION */
void debug_message ( gchar *prefixe, gchar *message, gint level, gboolean force_debug_display);
gboolean fermeture_grisbi ( void );
void initialize_debugging ( void );
void traitement_sigsegv ( gint signal_nb );
/* END_DECLARATION */
#endif
