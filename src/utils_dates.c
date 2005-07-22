/* ************************************************************************** */
/*                                  utils_dates.c                             */
/*                                                                            */
/*     Copyright (C)	2000-2003 CÃ©dric Auger (cedric@grisbi.org)      */
/*			2003-2005 Benjamin Drieu (bdrieu@april.org)	      */
/*			2003-2004 Alain Portal (aportal@univ-montp2.fr)	      */
/* 			http://www.grisbi.org				      */
/*                                                                            */
/*  This program is free software; you can redistribute it and/or modify      */
/*  it under the terms of the GNU General Public License as published by      */
/*  the Free Software Foundation; either version 2 of the License, or         */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  This program is distributed in the hope that it will be useful,           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU General Public License for more details.                              */
/*                                                                            */
/*  You should have received a copy of the GNU General Public License         */
/*  along with this program; if not, write to the Free Software               */
/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"


/*START_INCLUDE*/
#include "utils_dates.h"
#include "calendar.h"
#include "traitement_variables.h"
#include "utils_str.h"
#include "operations_formulaire.h"
#include "include.h"
/*END_INCLUDE*/

/*START_STATIC*/
static void close_calendar_popup ( GtkWidget *popup );
static gboolean popup_calendar ( GtkWidget * button, gpointer data );
static gboolean set_date (GtkEntry *entry, gchar *value, gint length, gint * position);
/*END_STATIC*/


/*START_EXTERN*/
extern     gchar * buffer ;
extern GtkWidget *entree_date_finale_etat;
extern GtkWidget *entree_date_init_etat;
extern GtkWidget *fenetre_preferences;
extern GtkTreeSelection * selection;
extern GtkStyle *style_entree_formulaire[2];
extern GtkWidget *window;
/*END_EXTERN*/





/******************************************************************************/
/* fonction qui retourne la date du jour sous forme de string                 */
/******************************************************************************/
gchar *gsb_today ( void )
{
    GDate *date;
    gchar date_str[SIZEOF_FORMATTED_STRING_DATE];

    date = gdate_today();

    g_date_strftime ( date_str, SIZEOF_FORMATTED_STRING_DATE, "%x", date );

    return ( g_strdup ( date_str ) );
}
/******************************************************************************/


/******************************************************************************/
/* fonction qui retourne la date du jour au format GDate                      */
/******************************************************************************/
GDate *gdate_today ( void )
{
    GDate *date;

    date = g_date_new ();
    g_date_set_time (  date,
		       time (NULL));
    return ( date );
}
/******************************************************************************/



/** copy the date given in param
 * \param date a GDate to copy
 * \return a copy or NULL if no date
 * */
GDate *gsb_date_copy ( GDate *date )
{
    GDate *new_date;

    if ( !date )
	return NULL;

    new_date = g_date_new_dmy ( g_date_get_day ( date ),
				g_date_get_month ( date ),
				g_date_get_year ( date ));

    return new_date;
}



    
/******************************************************************************/
/* Fonction modifie_date                                                      */
/* prend en argument une entrÃ©e contenant une date                            */
/* vÃ©rifie la validitÃ© et la modifie si seulement une partie est donnÃ©e       */
/* met la date du jour si l'entrÃ©e est vide                                   */
/* renvoie TRUE si la date est correcte                                       */
/******************************************************************************/
gboolean modifie_date ( GtkWidget *entree )
{
    gchar *pointeur_entry;

    /* si l'entrÃ©e est grise, on se barre */

    if (( gtk_widget_get_style ( entree ) == style_entree_formulaire[ENGRIS] ))
	return ( FALSE );

    pointeur_entry = g_strstrip ( (gchar *) gtk_entry_get_text ( GTK_ENTRY ( entree )) );

    if ( !strlen ( pointeur_entry ))
    {
	/* si on est dans la conf des Ã©tats, on ne met pas la date du jour, on */
	/* laisse vide */

	if ( entree != entree_date_init_etat &&
	     entree != entree_date_finale_etat )
	    gtk_entry_set_text ( GTK_ENTRY ( entree ),
				 gsb_today() );
    }
    else
    {
	return ( format_date ( entree ) );

    }
    return ( TRUE );
}
/******************************************************************************/



/******************************************************************************/
/* Fonction format_date                                                       */
/* Prend en argument une entrÃ©e contenant une date                            */
/* VÃ©rifie la validitÃ© et la modifie si seulement une partie est donnÃ©e       */
/* Met la date du jour si l'entrÃ©e est vide                                   */
/* Renvoie TRUE si la date est correcte                                       */
/******************************************************************************/
gboolean format_date ( GtkWidget *entree )
{
    gchar *pEntry;
    GDate *date;

    pEntry = g_strstrip ( ( gchar * ) gtk_entry_get_text ( GTK_ENTRY ( entree ) ) );

    if ( !pEntry || !strlen(pEntry) )
    {
	date = gdate_today();
    }
    else 
    {
	date = gsb_parse_date_string ( pEntry );
    }

    if ( ! date )
    {
	return FALSE;
    }

    gtk_entry_set_text ( GTK_ENTRY ( entree ), gsb_format_gdate ( date ) );

    return ( TRUE );
}



/**
 * Create and return a GDate from a string reprensentation of a date.
 *
 * \param	
 *
 */
GDate * gsb_parse_date_string ( const gchar * date_string )
{
    gchar * separators[4] = { "/", ".", "-", NULL };
    int jour = -1, mois = -1, annee = -1, i;
    gchar **tab_date;
    GDate * date;

    if ( !date_string
	 ||
	 !strlen (date_string))
	return NULL;

    date = (GDate *) malloc ( sizeof (GDate) );

    g_date_set_parse ( date, date_string );
    if ( g_date_valid ( date ) )
	return date;

    for ( i = 0; separators[i]; i++ )
    {
	date = gdate_today();
	
	tab_date = g_strsplit ( date_string, separators[i], 3 );

	if ( tab_date[2] && tab_date[1] )
	{
	    /* on a rentrÃ© les 3 chiffres de la date */
	    jour = utils_str_atoi ( tab_date[0] );
	    mois = utils_str_atoi ( tab_date[1] );
	    annee = utils_str_atoi ( tab_date[2] );
	    
	    if ( annee < 100 )
	    {
		if ( annee < 80 )
		    annee = annee + 2000;
		else
		    annee = annee + 1900;
	    }
	    return g_date_new_dmy ( jour, mois, annee );
	}
	else
	{
	    if ( tab_date[1] )
	    {
		/* on a rentrÃ© la date sous la forme xx/xx,
		   il suffit de mettre l'annÃ©e courante */
		jour = utils_str_atoi ( tab_date[0] );
		mois = utils_str_atoi ( tab_date[1] );
		annee = g_date_year ( date );
		return g_date_new_dmy ( jour, mois, annee );
	    }
	    else
	    {
		/* on a rentrÃ© que le jour de la date, il
		   faut mettre le mois et l'annÃ©e courante
		   ou bien on a rentrÃ© la date sous forme
		   jjmm ou jjmmaa ou jjmmaaaa */
		gchar buffer[3];
		
		switch ( strlen ( tab_date[0] ) )
		{
		/* forme jj ou j */
		case 1:
		case 2:
		    jour = utils_str_atoi ( tab_date[0] );
		    mois = g_date_month ( date );
		    annee = g_date_year ( date );
		    return g_date_new_dmy ( jour, mois, annee );

		/* forme jjmm */
		case 4 :
		    buffer[0] = tab_date[0][0];
		    buffer[1] = tab_date[0][1];
		    buffer[2] = 0;

		    jour = utils_str_atoi ( buffer );
		    mois = utils_str_atoi ( tab_date[0] + 2 );
		    annee = g_date_year ( date );
		    return g_date_new_dmy ( jour, mois, annee );

		/* forme jjmmaa */
		case 6:
		    buffer[0] = tab_date[0][0];
		    buffer[1] = tab_date[0][1];
		    buffer[2] = 0;

		    jour = utils_str_atoi ( buffer );
		    buffer[0] = tab_date[0][2];
		    buffer[1] = tab_date[0][3];

		    mois = utils_str_atoi ( buffer );
		    annee = utils_str_atoi ( tab_date[0] + 4 ) + 2000;
		    return g_date_new_dmy ( jour, mois, annee );

		/* forme jjmmaaaa */
		case 8:
		    buffer[0] = tab_date[0][0];
		    buffer[1] = tab_date[0][1];
		    buffer[2] = 0;

		    jour = utils_str_atoi ( buffer );
		    buffer[0] = tab_date[0][2];
		    buffer[1] = tab_date[0][3];

		    mois = utils_str_atoi ( buffer );
		    annee = utils_str_atoi ( tab_date[0] + 4 );
		    return g_date_new_dmy ( jour, mois, annee );
		}
	    }
	}
	g_strfreev ( tab_date );
    }

    return NULL;
}



/**
 * Convenience function that return the string representation of a
 * date based on locale settings.
 *
 * \param day		Day of the date to represent.
 * \param month		Month of the date to represent.
 * \param year		Year of the date to represent.
 *
 * \return		A string representing date.
 */
gchar * gsb_format_date ( gint day, gint month, gint year )
{
    return gsb_format_gdate ( g_date_new_dmy ( day, month, year ) );
}



/**
 * Convenience function that return the string representation of a
 * date based on locale settings.
 *
 * \param date		A GDate structure containing the date to represent.
 *
 * \return		A string representing date.
 */
gchar * gsb_format_gdate ( GDate *date )
{
    gchar retour_str[SIZEOF_FORMATTED_STRING_DATE];

    if ( !date || !g_date_valid ( date ))
    {
	return NULL;
    }

    g_date_strftime ( retour_str, SIZEOF_FORMATTED_STRING_DATE, "%x", date );

    return g_strdup ( retour_str );
}



/**
 * Sets a GDate according to a date widget
 *
 * \param entry A GtkEntry that triggered this handler
 * \param value Handler parameter.  Not used.
 * \param length Handler parameter.  Not used.
 * \param position Handler parameter.  Not used.
 */
gboolean set_date (GtkEntry *entry, gchar *value, gint length, gint * position)
{
    GDate ** data, temp_date;

    data = g_object_get_data ( G_OBJECT ( entry ), "pointer");

    g_date_set_parse ( &temp_date, gtk_entry_get_text (GTK_ENTRY(entry)) );
    if ( g_date_valid (&temp_date) && data)
    {
	if (!*data)
	    *data = g_date_new ();
	g_date_set_parse ( *data, gtk_entry_get_text (GTK_ENTRY(entry)) );
    }

    /* Mark file as modified */
    modification_fichier ( TRUE );

    return FALSE;
}
/******************************************************************************/






/**
 * Creates a new GtkHBox with an entry to type in a date.
 *
 * \param value A pointer to a GDate that will be modified at every
 * change.
 * \param An optional hook to run.
 */
GtkWidget * new_date_entry ( gchar ** value, GCallback hook )
{
    GtkWidget *hbox, *entry, *date_entry;

    hbox = gtk_hbox_new ( FALSE, 6 );

    entry = gtk_entry_new ();
    gtk_box_pack_start ( GTK_BOX(hbox), entry,
			 TRUE, TRUE, 0 );

    g_object_set_data ( G_OBJECT (entry), "pointer", value);

    if ( hook )
    {
	g_object_set_data ( G_OBJECT (entry), "insert-hook", 
			    (gpointer) g_signal_connect_after (GTK_OBJECT(entry), 
							       "insert-text",
							       ((GCallback) hook), 
							       NULL));
	g_object_set_data ( G_OBJECT (entry), "delete-hook", 
			    (gpointer) g_signal_connect_after (GTK_OBJECT(entry), 
							       "delete-text",
							       ((GCallback) hook), 
							       NULL));
    }
    g_object_set_data ( G_OBJECT (entry), "insert-text", 
			(gpointer) g_signal_connect_after (GTK_OBJECT(entry), 
							   "insert-text",
							   ((GCallback) set_date), 
							   NULL));
    g_object_set_data ( G_OBJECT (entry), "delete-text", 
			(gpointer) g_signal_connect_after (GTK_OBJECT(entry), 
							   "delete-text",
							   ((GCallback) set_date), 
							   NULL));

    date_entry = gtk_button_new_with_label ("...");
    gtk_box_pack_start ( GTK_BOX(hbox), date_entry,
			 FALSE, FALSE, 0 );
    g_object_set_data ( G_OBJECT ( date_entry ),
			"entry", entry);

    g_signal_connect ( GTK_OBJECT ( date_entry ), "clicked",
		       ((GCallback) popup_calendar ), NULL );

    return hbox;
}



/**
 * Change the date that is handled by a date entry.
 *
 * \param hbox The date entry widget.
 * \param value The new date to modify.
 * \param Update GtkEntry value as well.
 */
void date_set_value ( GtkWidget * hbox, GDate ** value, gboolean update )
{
    GtkWidget * entry;


    entry = get_entry_from_date_entry (hbox);
    g_object_set_data ( G_OBJECT ( entry ), "pointer", value );

    if ( update )
    {
	if (g_object_get_data ((GObject*) entry, "insert-hook") > 0)
	    g_signal_handler_block ( entry,
				     (gulong) g_object_get_data ((GObject*) entry, 
								 "insert-hook"));
	if (g_object_get_data ((GObject*) entry, "insert-text") > 0)
	    g_signal_handler_block ( entry,
				     (gulong) g_object_get_data ((GObject*) entry, 
								 "insert-text"));
	if (g_object_get_data ((GObject*) entry, "delete-hook") > 0)
	    g_signal_handler_block ( entry,
				     (gulong) g_object_get_data ((GObject*) entry, 
								 "delete-hook"));
	if (g_object_get_data ((GObject*) entry, "delete-text") > 0)
	    g_signal_handler_block ( entry,
				     (gulong) g_object_get_data ((GObject*) entry, 
								 "delete-text"));

	if ( value && *value )
	{
	    gtk_entry_set_text ( GTK_ENTRY(entry), gsb_format_gdate ( *value ) );
	}

	if (g_object_get_data ((GObject*) entry, "insert-hook") > 0)
	    g_signal_handler_unblock ( entry,
				       (gulong) g_object_get_data ((GObject*) entry, 
								   "insert-hook"));
	if (g_object_get_data ((GObject*) entry, "insert-text") > 0)
	    g_signal_handler_unblock ( entry,
				       (gulong) g_object_get_data ((GObject*) entry, 
								   "insert-text"));
	if (g_object_get_data ((GObject*) entry, "delete-hook") > 0)
	    g_signal_handler_unblock ( entry,
				       (gulong) g_object_get_data ((GObject*) entry, 
								   "delete-hook"));
	if (g_object_get_data ((GObject*) entry, "delete-text") > 0)
	    g_signal_handler_unblock ( entry,
				       (gulong) g_object_get_data ((GObject*) entry, 
								   "delete-text"));
    }
}



/**
 * Pop up a window with a calendar that allows a date selection.  This
 * calendar runs "date_selectionnee" as a callback if a date is
 * selected.
 *
 * \param button Normally a GtkButton that triggered the handler.
 * This parameter will be used as a base to set popup's position.
 * This widget must also have a parameter (data) of name "entry"
 * which contains a pointer to a GtkEntry used to set initial value of
 * calendar.
 * \param data Handler parameter.  Not used.
 */
gboolean popup_calendar ( GtkWidget * button, gpointer data )
{
    GtkWidget *popup, *entree, *popup_boxv, *calendrier, *bouton, *frame;
    GtkRequisition taille_entree, taille_popup;
    GDate * date;
    gint x, y;

    /* Find associated gtkentry */
    entree = g_object_get_data ( G_OBJECT(button), "entry" );

    /* Find popup position */
    gdk_window_get_origin ( GTK_BUTTON (button) -> event_window, &x, &y );
    gtk_widget_size_request ( GTK_WIDGET (button), &taille_entree );
    y = y + taille_entree.height;

    /* Create popup */
    popup = gtk_window_new ( GTK_WINDOW_POPUP );
    gtk_window_set_modal ( GTK_WINDOW (popup), TRUE);

    /* Create popup widgets */
    frame = gtk_frame_new ( NULL );
    gtk_container_add ( GTK_CONTAINER (popup), frame);
    popup_boxv = gtk_vbox_new ( FALSE, 5 );
    gtk_container_set_border_width ( GTK_CONTAINER ( popup_boxv ), 5 );
    gtk_container_add ( GTK_CONTAINER ( frame ), popup_boxv);

    /* Set initial date according to entry */
    if ( strlen ( g_strstrip ( (gchar *) gtk_entry_get_text (GTK_ENTRY(entree))) ) )
    {
	date = gsb_parse_date_string ( (gchar *) gtk_entry_get_text ( GTK_ENTRY ( entree ) ) );
    }
    else
    {
	date = gdate_today ();
    }

    /* Creates calendar */
    calendrier = gtk_calendar_new();
    gtk_calendar_select_month ( GTK_CALENDAR ( calendrier ), g_date_get_month ( date ) - 1,
				g_date_get_year ( date ) );
    gtk_calendar_select_day  ( GTK_CALENDAR ( calendrier ), g_date_get_day ( date ) );
    gtk_calendar_display_options ( GTK_CALENDAR ( calendrier ),
				   GTK_CALENDAR_SHOW_HEADING |
				   GTK_CALENDAR_SHOW_DAY_NAMES |
				   GTK_CALENDAR_WEEK_START_MONDAY );

    /* Create handlers */
    gtk_signal_connect ( GTK_OBJECT ( calendrier), "day-selected-double-click",
			 ((GCallback)  date_selection ), entree );
    gtk_signal_connect_object ( GTK_OBJECT ( calendrier), "day-selected-double-click",
				((GCallback)  close_calendar_popup ), popup );
    gtk_signal_connect ( GTK_OBJECT ( popup ), "key-press-event",
			 ((GCallback)  clavier_calendrier ), NULL );
    gtk_box_pack_start ( GTK_BOX ( popup_boxv ), calendrier,
			 TRUE, TRUE, 0 );

    /* Add the "cancel" button */
    bouton = gtk_button_new_with_label ( _("Cancel") );
    gtk_signal_connect_object ( GTK_OBJECT ( bouton ), "clicked",
				((GCallback)  close_calendar_popup ),
				GTK_WIDGET ( popup ) );
    gtk_box_pack_start ( GTK_BOX ( popup_boxv ), bouton,
			 TRUE, TRUE, 0 );


    /* Show everything */
    gtk_widget_show_all ( popup );
    gtk_widget_set_uposition ( GTK_WIDGET ( popup ), x, y );
    gtk_widget_size_request ( GTK_WIDGET ( popup ), &taille_popup );
    gtk_widget_set_uposition ( GTK_WIDGET ( popup ), 
			       x-taille_popup.width+taille_entree.width, y );

    /* Grab pointer */
    gdk_pointer_grab ( popup -> window, TRUE,
		       GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
		       GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK |
		       GDK_POINTER_MOTION_MASK,
		       NULL, NULL, GDK_CURRENT_TIME );

    return FALSE;
}



/**
 * Closes the popup specified as an argument.  As a quick but
 * disgusting hack, we also grab focus on "fenetre_preferences", the
 * dialog that contains all tabs, in order to preserve it.
 *
 * \param popup The popup to close.
 */
void close_calendar_popup ( GtkWidget *popup )
{
    gtk_widget_destroy ( popup );
    gtk_grab_remove ( fenetre_preferences );
    gtk_grab_add ( fenetre_preferences );
}



/**
 * Convenience function that returns the first widget child of a
 * GtkBox.  This is specially usefull for date "widgets" that contains
 * one GtkEntry and one GtkButton, both packed in a single GtkHBox.
 *
 * \param hbox A GtkBox that contains at least one child.
 */
GtkWidget * get_entry_from_date_entry (GtkWidget * hbox)
{
    return ((GtkBoxChild *) GTK_BOX(hbox)->children->data)->widget;
}


/* Local Variables: */
/* c-basic-offset: 4 */
/* End: */
