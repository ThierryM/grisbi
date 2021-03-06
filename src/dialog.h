#ifndef _DIALOG_H
#define _DIALOG_H (1)

#include <gtk/gtk.h>

/* START_INCLUDE_H */
/* END_INCLUDE_H */


struct ConditionalMessage
{
    const gchar * name;
    const gchar * hint;
    const gchar * message;
    gboolean hidden;
    gboolean default_answer;	/** Useful for yes/no questions. */
};


/* START_DECLARATION */
void 		dialog_message 								(const gchar *label, ...);
void 		dialogue 									(const gchar *texte_dialogue);
void 		dialogue_conditional_hint 					(const gchar *text,
														 const gchar *hint,
														 const gchar *var);
void 		dialogue_error 								(const gchar *text);
void 		dialogue_error_brain_damage 				(void);
void 		dialogue_error_hint 						(const gchar *text,
														 const gchar *hint);
void 		dialogue_error_memory 						(void);
GtkWidget *	dialog_get_content_area 					(GtkWidget *dialog);
void 		dialogue_hint 								(const gchar *text,
														 const gchar *hint);
gchar *		dialogue_hint_with_entry 					(const gchar *text,
														 const gchar *hint,
														 const gchar *entry_description);
GtkWidget *	dialogue_special_no_run 					(GtkMessageType param,
														 GtkButtonsType buttons,
														 const gchar *text,
														 const gchar* hint);
gboolean 	dialogue_update_struct_message 				(GtkWidget *checkbox,
														 struct ConditionalMessage *message);
void 		dialogue_warning (const gchar *text);
void 		dialogue_warning_hint 						(const gchar *text,
														 const gchar *hint);
gchar *		make_blue 									(const gchar *text);
gchar *		make_pango_attribut 						(const gchar *attribut,
														 const gchar *text);
gchar *		make_red 									(const gchar *text);
gboolean 	question_conditional_yes_no 				(const gchar *var);
gint 		question_conditional_yes_no_get_no_struct 	(struct ConditionalMessage *msg,
														 const gchar *name);
gboolean 	question_conditional_yes_no_with_struct 	(struct ConditionalMessage *message);
gboolean 	question_yes_no 							(const gchar *text,
														 const gchar *hint,
														 gint default_answer);
/* END_DECLARATION */
#endif
