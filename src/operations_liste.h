#ifndef _OPERATIONS_LISTE_H
#define _OPERATIONS_LISTE_H (1)


/* define the no of column in the transactions list */

#define TRANSACTION_COL_NB_IS_EXPANDER 0
#define TRANSACTION_COL_NB_CHECK 1
#define TRANSACTION_COL_NB_DATE 2
#define TRANSACTION_COL_NB_PARTY 3
#define TRANSACTION_COL_NB_PR 4
#define TRANSACTION_COL_NB_DEBIT 5
#define TRANSACTION_COL_NB_CREDIT 6
#define TRANSACTION_COL_NB_BALANCE 7

#define TRANSACTION_LIST_COL_NB 8	 /*< must be the last of the list */

/* define the columns in the store
 * as the data are filled above, the number here
 * begin at TRANSACTION_LIST_COL_NB */

#define TRANSACTION_COL_NB_BACKGROUND 8		/*< color of the background */
#define TRANSACTION_COL_NB_AMOUNT_COLOR 9	/*< color of the amount */
#define TRANSACTION_COL_NB_TRANSACTION_ADDRESS 10
#define TRANSACTION_COL_NB_SAVE_BACKGROUND 11	/*< when selection, save of the normal color of background */
#define TRANSACTION_COL_NB_FONT 12		/*< PangoFontDescription if used */
#define TRANSACTION_COL_NB_TRANSACTION_LINE 13	/*< the line in the transaction (1, 2, 3 or 4) */
#define TRANSACTION_COL_NB_VISIBLE 14		/*< whether that transaction is visible or not */
#define TRANSACTION_COL_NB_PIXBUF_CLOSED 15
#define TRANSACTION_COL_NB_PIXBUF_OPEN 16
#define TRANSACTION_COL_NB_IS_EXPANDED 17
#define TRANSACTION_COL_NB_IS_NOT_BREAKDOWN 18

#define TRANSACTION_COL_NB_TOTAL 19


#define TRANSACTION_LIST_ROWS_NB 4

/* constantes qui dÃ©finissent le no associÃ© au paramÃštre
 * dans la liste d'opÃ© */
# define TRANSACTION_LIST_DATE 1
# define TRANSACTION_LIST_VALUE_DATE 2
# define TRANSACTION_LIST_PARTY 3
# define TRANSACTION_LIST_BUDGET 4
# define TRANSACTION_LIST_CREDIT 5
# define TRANSACTION_LIST_DEBIT 6
# define TRANSACTION_LIST_BALANCE 7
# define TRANSACTION_LIST_AMOUNT 8
# define TRANSACTION_LIST_TYPE 9
# define TRANSACTION_LIST_RECONCILE_NB 10
# define TRANSACTION_LIST_EXERCICE 11
# define TRANSACTION_LIST_CATEGORY 12
# define TRANSACTION_LIST_MARK 13
# define TRANSACTION_LIST_VOUCHER 14 
# define TRANSACTION_LIST_NOTES 15
# define TRANSACTION_LIST_BANK 16
# define TRANSACTION_LIST_NO 17
# define TRANSACTION_LIST_CHQ 18

/* Constantes pour la fonction gtk_tree_view_column_set_alignment() (GTK2) */
#define COLUMN_LEFT 0.0
#define COLUMN_CENTER 0.5
#define COLUMN_RIGHT 1.0

/* START_INCLUDE_H */
#include "structures.h"
/* END_INCLUDE_H */


/* START_DECLARATION */
gboolean affichage_traits_liste_operation ( void );
gboolean changement_taille_liste_ope ( GtkWidget *tree_view,
				       GtkAllocation *allocation );
GtkTreeIter *cherche_iter_operation ( gpointer *transaction,
				      gint no_account );
gint cherche_ligne_operation ( gpointer transaction,
			       gint no_account );
void clone_selected_transaction ();
void creation_colonnes_tree_view_par_compte ( gint no_account );
GtkWidget *creation_fenetre_operations ( void );
GtkWidget *creation_tree_view_operations_par_compte ( gint no_account );
void demande_mise_a_jour_tous_comptes ( void );
gint find_p_r_col ();
gboolean gsb_account_list_set_breakdowns_visible ( gint no_account,
						   gpointer transaction,
						   gint visible );
gchar *gsb_transactions_get_category_real_name ( gpointer *transaction );
gboolean gsb_transactions_list_append_transaction ( gpointer transaction,
						    gint no_account );
gpointer gsb_transactions_list_append_white_breakdown ( gpointer *transaction );
gboolean gsb_transactions_list_button_press ( GtkWidget *tree_view,
					      GdkEventButton *ev );
gpointer gsb_transactions_list_clone_transaction ( gpointer *transaction );
gboolean gsb_transactions_list_delete_transaction ( gpointer transaction );
gboolean gsb_transactions_list_edit_current_transaction ( void );
gboolean gsb_transactions_list_fill_row ( gpointer transaction,
					  GtkTreeIter *iter,
					  GtkListStore *store,
					  gint line_in_transaction );
gboolean gsb_transactions_list_fill_store ( gint no_account,
					    gboolean by_part );
gboolean gsb_transactions_list_key_press ( GtkWidget *widget,
					   GdkEventKey *ev );
gboolean gsb_transactions_list_move_to_current_transaction ( gint no_account );
gboolean gsb_transactions_list_set_background_color ( gint no_account );
gboolean gsb_transactions_list_set_current_transaction ( gpointer new_transaction,
							 gint no_account );
gboolean gsb_transactions_list_set_transactions_balances ( gint no_account );
gboolean gsb_transactions_list_set_visibles_rows_on_account ( gint no_account );
gboolean gsb_transactions_list_set_visibles_rows_on_transaction ( gpointer transaction );
void mise_a_jour_affichage_lignes ( gint nb_lignes );
void mise_a_jour_affichage_r ( gint affichage_r );
void mise_a_jour_labels_soldes ( void );
void move_selected_operation_to_account_nb ( gint *account );
void new_transaction () ;
gint recupere_hauteur_ligne_tree_view ( GtkWidget *tree_view );
void remove_transaction ();
void remplissage_liste_operations ( gint compte );
struct operation_echeance *schedule_transaction ( gpointer * transaction );
void update_titres_tree_view ( void );
void verification_list_store_termine ( gint no_account );
/* END_DECLARATION */
#endif
