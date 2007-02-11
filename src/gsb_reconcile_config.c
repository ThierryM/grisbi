/* ************************************************************************** */
/*                                                                            */
/*     Copyright (C)	2000-2007 Cédric Auger (cedric@grisbi.org)	      */
/*			2003-2007 Benjamin Drieu (bdrieu@april.org)	      */
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

/**
 * \file gsb_reconcile_config.c
 * functions used to configure the reconcile
 */


#include "include.h"

/*START_INCLUDE*/
#include "gsb_reconcile_config.h"
#include "dialog.h"
#include "gsb_autofunc.h"
#include "gsb_data_account.h"
#include "gsb_data_reconcile.h"
#include "gsb_data_transaction.h"
#include "utils_dates.h"
#include "navigation.h"
#include "gsb_real.h"
#include "gsb_transactions_list.h"
#include "traitement_variables.h"
#include "utils.h"
#include "structures.h"
#include "fenetre_principale.h"
#include "gsb_reconcile_config.h"
#include "include.h"
/*END_INCLUDE*/

/*START_STATIC*/
static gboolean gsb_reconcile_config_delete ( GtkWidget *button,
				       GtkWidget *tree_view );
static void gsb_reconcile_config_fill ( GtkWidget *tree_view );
static gboolean gsb_reconcile_config_find_alone_transactions ( void );
static gboolean gsb_reconcile_config_select ( GtkTreeSelection *selection, 
				       GtkWidget *table );
static gboolean gsb_reconcile_config_update_line ( GtkWidget *entry,    
					    GtkWidget *tree_view );
/*END_STATIC*/

/*START_EXTERN*/
extern gsb_real null_real ;
extern GtkTreeSelection * selection;
extern GtkWidget *tree_view;
extern GtkWidget *window;
/*END_EXTERN*/

static GtkWidget *reconcile_name_entry;
static GtkWidget *reconcile_init_date_entry;
static GtkWidget *reconcile_final_date_entry;
static GtkWidget *reconcile_init_balance_entry;
static GtkWidget *reconcile_final_balance_entry;
static GtkWidget *delete_reconcile_button;

/**
 * create the config widget for the reconcile
 * to modify/delete a reconcile
 *
 * \param
 *
 * \return a GtkWidget containing the config widget
 */
GtkWidget *gsb_reconcile_config_create ( void )
{
    GtkWidget *hbox, *scrolled_window;
    GtkWidget *vbox_pref, *paddingbox;
    GtkTreeViewColumn *column;
    GtkCellRenderer *cell;
    GtkTreeStore *reconcile_model;
    GtkTreeSelection *reconcile_selection;
    GtkWidget *reconcile_treeview;
    GtkWidget *label;
    gint i;
    gfloat alignment[] = {
	COLUMN_LEFT, COLUMN_CENTER, COLUMN_CENTER, 
	COLUMN_RIGHT, COLUMN_RIGHT
    };
    gchar *titles[] = {
	_("Account"), _("Init date"), _("Final date"),
	_("Init balance"), _("Final balance")
    };
    GtkWidget *table_selection;
    GtkWidget *button;

    vbox_pref = new_vbox_with_title_and_icon ( _("Reconciliation"),
					       "reconciliation.png" );
    paddingbox = new_paddingbox_with_title ( vbox_pref, TRUE,
					     COLON(_("List of reconciliations") ) );

    /* set the list */
    scrolled_window = gtk_scrolled_window_new ( NULL, NULL );
    gtk_box_pack_start ( GTK_BOX (paddingbox), scrolled_window,
			 TRUE, TRUE, 0);
    gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrolled_window ),
				     GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type ( GTK_SCROLLED_WINDOW ( scrolled_window ),
					  GTK_SHADOW_IN);

    /* need to create first the table to set it in the arg of the changed signal of selection */
    table_selection = gtk_table_new ( 4, 3, FALSE );

    /* create the model */
    reconcile_model = gtk_tree_store_new ( NUM_RECONCILIATION_COLUMNS,
					   G_TYPE_STRING,    /* Name account or reconcile */
					   G_TYPE_STRING,    /* init date  */
					   G_TYPE_STRING,    /* final date  */
					   G_TYPE_STRING,    /* init balance  */
					   G_TYPE_STRING,    /* final balance  */
					   G_TYPE_INT,       /* Account number */
					   G_TYPE_INT );       /* reconcile number */
    reconcile_treeview = gtk_tree_view_new_with_model ( GTK_TREE_MODEL (reconcile_model) );
    gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (reconcile_treeview), TRUE);
    gtk_tree_selection_set_mode ( gtk_tree_view_get_selection (GTK_TREE_VIEW (reconcile_treeview)),
				  GTK_SELECTION_SINGLE );
    gtk_container_add ( GTK_CONTAINER (scrolled_window),
			reconcile_treeview );

    reconcile_selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (reconcile_treeview));
    g_signal_connect (reconcile_selection, "changed", 
		      G_CALLBACK (gsb_reconcile_config_select), table_selection);

    /* Name */
    for (i=RECONCILIATION_NAME_COLUMN ; i<RECONCILIATION_ACCOUNT_COLUMN ; i++)
    {
	cell = gtk_cell_renderer_text_new ();
	g_object_set ( G_OBJECT (cell),
		       "xalign", alignment[i],
		       NULL );
	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_sizing ( column,
					  GTK_TREE_VIEW_COLUMN_AUTOSIZE );
	gtk_tree_view_column_set_alignment ( column,
					     alignment[i] );
	gtk_tree_view_column_pack_end ( column, cell, TRUE );
	gtk_tree_view_column_set_title ( column, titles[i] );
	gtk_tree_view_column_set_attributes (column, cell,
					     "text", i,
					     NULL);
	gtk_tree_view_column_set_expand ( column, TRUE );
	gtk_tree_view_column_set_resizable ( column,
					     TRUE );
	gtk_tree_view_append_column ( GTK_TREE_VIEW(reconcile_treeview), column);
    }

    /* Various remaining settings */
    gsb_reconcile_config_fill(reconcile_treeview);

    /* set the modifying part under the list */
    hbox = new_paddingbox_with_title ( vbox_pref, FALSE,
				       COLON(_("Selected reconcile") ) );

    /* for that we make a table 2x3 but with the names 4x3,
     * the table has been set before to accept as arg on the changed selection */
    gtk_box_pack_start ( GTK_BOX (hbox),
			 table_selection,
			 FALSE, FALSE, 0 );

    /* set the name */
    label = gtk_label_new ( _("Name"));
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				label,
				0, 1,
				0, 1 );

    reconcile_name_entry = gsb_autofunc_entry_new ( NULL,
						    G_CALLBACK (gsb_reconcile_config_update_line), reconcile_treeview,
						    G_CALLBACK (gsb_data_reconcile_set_name), 0 );
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				reconcile_name_entry,
				1, 2,
				0, 1 );

    /* set the initial date */
    label = gtk_label_new ( _("Initial date"));
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				label,
				0, 1,
				1, 2 );

    reconcile_init_date_entry = gsb_autofunc_date_new ( NULL,
							G_CALLBACK (gsb_reconcile_config_update_line), reconcile_treeview,
							G_CALLBACK (gsb_data_reconcile_set_init_date), 0 );
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				reconcile_init_date_entry,
				1, 2,
				1, 2 );

    /* set the final date */
    label = gtk_label_new ( _("Final date"));
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				label,
				0, 1,
				2, 3 );

    reconcile_final_date_entry = gsb_autofunc_date_new ( NULL,
							 G_CALLBACK (gsb_reconcile_config_update_line), reconcile_treeview,
							 G_CALLBACK (gsb_data_reconcile_set_final_date), 0 );
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				reconcile_final_date_entry,
				1, 2,
				2, 3 );


    /* set the delete button */
    delete_reconcile_button = gtk_button_new_with_label (_("Delete the reconcile"));
    gtk_button_set_relief ( GTK_BUTTON (delete_reconcile_button),
			    GTK_RELIEF_NONE );
    g_signal_connect ( G_OBJECT (delete_reconcile_button),
		       "clicked",
		       G_CALLBACK (gsb_reconcile_config_delete),
		       reconcile_treeview );
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				delete_reconcile_button,
				3, 4,
				0, 1 );

    /* set the initial balance */
    label = gtk_label_new ( _("Initial balance"));
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				label,
				2, 3,
				1, 2 );

    reconcile_init_balance_entry = gsb_autofunc_real_new ( null_real,
							   G_CALLBACK (gsb_reconcile_config_update_line), reconcile_treeview,
							   G_CALLBACK (gsb_data_reconcile_set_init_balance), 0 );
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				reconcile_init_balance_entry,
				3, 4,
				1, 2 );

    /* set the final date */
    label = gtk_label_new ( _("Final balance"));
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				label,
				2, 3,
				2, 3 );

    reconcile_final_balance_entry = gsb_autofunc_real_new ( null_real,
							    G_CALLBACK (gsb_reconcile_config_update_line), reconcile_treeview,
							    G_CALLBACK (gsb_data_reconcile_set_final_balance), 0 );
    gtk_table_attach_defaults ( GTK_TABLE (table_selection),
				reconcile_final_balance_entry,
				3, 4,
				2, 3 );

    /* at the begining, the table is unsensitive */
    gtk_widget_set_sensitive ( table_selection,
			       FALSE );

    /* set the button to find non-associated transactions */
    button = gtk_button_new_with_label ( _("Find the marked transactions not associated to a reconcile number"));
    gtk_button_set_relief ( GTK_BUTTON (button),
			    GTK_RELIEF_NONE );
    g_signal_connect ( G_OBJECT (button),
		       "clicked",
		       G_CALLBACK (gsb_reconcile_config_find_alone_transactions),
		       NULL );
    gtk_box_pack_start ( GTK_BOX (vbox_pref),
			 button,
			 FALSE, FALSE, 0 );

    gtk_widget_show_all (vbox_pref);

    if ( !gsb_data_account_get_accounts_amount () )
    {
	gtk_widget_set_sensitive ( vbox_pref, FALSE );
    }

    return vbox_pref;
}


/**
 * fill the reconcile list,
 * sort each reconcile in its account
 *
 * \param tree_view
 *
 * \return
 * */
void gsb_reconcile_config_fill ( GtkWidget *tree_view )
{
    GtkTreeModel *model;
    GSList *tmp_list;

    if (!tree_view)
	return;

    model = gtk_tree_view_get_model ( GTK_TREE_VIEW (tree_view));

    gtk_tree_store_clear (GTK_TREE_STORE(model));

    /* we make a tree_model containing the accounts,
     * and for each account, all the reconciles */
    tmp_list = gsb_data_account_get_list_accounts ();
    while (tmp_list)
    {
	gint account_number;
	GtkTreeIter account_iter;
	GList *reconcile_list;

	account_number = gsb_data_account_get_no_account (tmp_list -> data);

	gtk_tree_store_append ( GTK_TREE_STORE (model),
				&account_iter,
				NULL );
	gtk_tree_store_set ( GTK_TREE_STORE (model),
			     &account_iter,
			     RECONCILIATION_NAME_COLUMN, gsb_data_account_get_name (account_number),
			     RECONCILIATION_ACCOUNT_COLUMN, account_number,
			     -1 );

	/* for each account, get the concerned reconciles */
	reconcile_list = gsb_data_reconcile_get_reconcile_list ();
	while (reconcile_list)
	{
	    gint reconcile_number;

	    reconcile_number = gsb_data_reconcile_get_no_reconcile (reconcile_list -> data);

	    if (gsb_data_reconcile_get_account (reconcile_number) == account_number)
	    {
		GtkTreeIter reconcile_iter;
		gchar *init_date, *final_date;
		gchar *init_balance, *final_balance;

		init_date = gsb_format_gdate (gsb_data_reconcile_get_init_date (reconcile_number));
		final_date = gsb_format_gdate (gsb_data_reconcile_get_final_date (reconcile_number));
		init_balance = gsb_real_get_string (gsb_data_reconcile_get_init_balance (reconcile_number));
		final_balance = gsb_real_get_string (gsb_data_reconcile_get_final_balance (reconcile_number));

		gtk_tree_store_append ( GTK_TREE_STORE (model),
					&reconcile_iter,
					&account_iter );
		gtk_tree_store_set ( GTK_TREE_STORE (model),
				     &reconcile_iter,
				     RECONCILIATION_NAME_COLUMN, gsb_data_reconcile_get_name (reconcile_number),
				     RECONCILIATION_INIT_DATE_COLUMN, init_date,
				     RECONCILIATION_FINAL_DATE_COLUMN, final_date,
				     RECONCILIATION_INIT_BALANCE_COLUMN, init_balance,
				     RECONCILIATION_FINAL_BALANCE_COLUMN, final_balance,
				     RECONCILIATION_RECONCILE_COLUMN, reconcile_number,
				     RECONCILIATION_ACCOUNT_COLUMN, account_number,
				     -1 );
		g_free (init_date);
		g_free (final_date);
		g_free (init_balance);
		g_free (final_balance);
	    }
	    reconcile_list = reconcile_list -> next;
	}

	tmp_list = tmp_list -> next;
    }
}



/**
 * callback called when select a line in the tree
 * fill the entry of the name, dates and balances
 *
 * \param selection the GtkTreeSelection
 * \param table the GtkTable containing the widgets to set the value of the selection
 *
 * \return FALSE
 */
gboolean gsb_reconcile_config_select ( GtkTreeSelection *selection, 
				       GtkWidget *table )
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    gboolean good;

    good = gtk_tree_selection_get_selected (selection, &model, &iter);
    if (good)
    {
	gint reconcile_number;

	gtk_tree_model_get (model, &iter, 
			    RECONCILIATION_RECONCILE_COLUMN, &reconcile_number,
			    -1 );

	if (reconcile_number)
	{
	    /* we are on a payment method, we fill the fields */
	    gsb_autofunc_entry_set_value ( reconcile_name_entry,
					   gsb_data_reconcile_get_name (reconcile_number),
					   reconcile_number );
	    gsb_autofunc_date_set ( reconcile_init_date_entry,
				    gsb_data_reconcile_get_init_date (reconcile_number),
				    reconcile_number);
	    gsb_autofunc_date_set ( reconcile_final_date_entry,
				    gsb_data_reconcile_get_final_date (reconcile_number),
				    reconcile_number );
	    gsb_autofunc_real_set ( reconcile_init_balance_entry,
				    gsb_data_reconcile_get_init_balance (reconcile_number),
				    reconcile_number );
	    gsb_autofunc_real_set ( reconcile_final_balance_entry,
				    gsb_data_reconcile_get_final_balance (reconcile_number),
				    reconcile_number );

	    /* we make the table sensitive */
	    gtk_widget_set_sensitive ( table, TRUE );
	}
	else 
	    gtk_widget_set_sensitive ( table, FALSE );
    }
    else
	gtk_widget_set_sensitive ( table, FALSE );
    return FALSE;
}


/**
 * callback called when something change in the entries of the configuration of the reconcile
 *
 * \param tree_view
 *
 * \return FALSE
 * */
gboolean gsb_reconcile_config_update_line ( GtkWidget *entry,    
					    GtkWidget *tree_view )
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    gboolean good;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view));
    good = gtk_tree_selection_get_selected (selection, &model, &iter);

    if (good)
    {
	gint reconcile_number;

	gtk_tree_model_get (model, &iter, 
			    RECONCILIATION_RECONCILE_COLUMN, &reconcile_number,
			    -1 );

	if (reconcile_number)
	{
	    /* we are on a reconcile, change the line with the new values */
		gchar *init_date, *final_date;
		gchar *init_balance, *final_balance;

		init_date = gsb_format_gdate (gsb_data_reconcile_get_init_date (reconcile_number));
		final_date = gsb_format_gdate (gsb_data_reconcile_get_final_date (reconcile_number));
		init_balance = gsb_real_get_string (gsb_data_reconcile_get_init_balance (reconcile_number));
		final_balance = gsb_real_get_string (gsb_data_reconcile_get_final_balance (reconcile_number));

		gtk_tree_store_set ( GTK_TREE_STORE (model),
				     &iter,
				     RECONCILIATION_NAME_COLUMN, gsb_data_reconcile_get_name (reconcile_number),
				     RECONCILIATION_INIT_DATE_COLUMN, init_date,
				     RECONCILIATION_FINAL_DATE_COLUMN, final_date,
				     RECONCILIATION_INIT_BALANCE_COLUMN, init_balance,
				     RECONCILIATION_FINAL_BALANCE_COLUMN, final_balance,
				     -1 );
		g_free (init_date);
		g_free (final_date);
		g_free (init_balance);
		g_free (final_balance);

	}
    }

    return FALSE;
}

/**
 * callback called when the user click on 'Delete the reconcile'
 * this will delete the selected reconcile and mark all the concerned
 * transactions as marked P
 *
 * \param button
 * \param tree_view
 *
 * \return FALSE
 * */
gboolean gsb_reconcile_config_delete ( GtkWidget *button,
				       GtkWidget *tree_view )
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;
    gboolean good;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view));
    good = gtk_tree_selection_get_selected (selection, &model, &iter);

    if (good)
    {
	gint reconcile_number;

	gtk_tree_model_get (model, &iter, 
			    RECONCILIATION_RECONCILE_COLUMN, &reconcile_number,
			    -1 );

	if (reconcile_number)
	{
	    /* we are on a reconcile,
	     * we ask if the user want to continue and warn him */
	    if (!question_yes_no_hint ( _("Deleting a reconcile"),
					g_strdup_printf (_("Carreful, you are about to deleting a reconcile.\nIf you continue, the reconcile %s will be erased and all the transactions marked by this reconcile will be un-reconciled and marked P.\nAre you sure you want to continue ?"),
							 gsb_data_reconcile_get_name (reconcile_number))))
		return FALSE;

	    /* ok we delete the reconcile
	     * this will automatickly remove it from the marked transactions */
	    gtk_tree_store_remove ( GTK_TREE_STORE (model),
				    &iter );
	    gsb_data_reconcile_remove (reconcile_number);

	    /* first, if the R transactions are not added in the transactions list,
	     * we load them now (should be rare, disabled by default */
	    if (!etat.fill_r_done)
		gsb_transactions_list_load_marked_r ();

	    /* if we are on an account, we update the list */
	    if (gsb_gui_navigation_get_current_page () == GSB_ACCOUNT_PAGE)
	    {
		gint account_number;
		
		account_number = gsb_gui_navigation_get_current_account ();
		if (account_number != -1)
		{
		    gsb_transactions_list_set_visibles_rows_on_account (account_number);
		    gsb_transactions_list_set_background_color (account_number);
		    gsb_transactions_list_set_transactions_balances (account_number);

		    /* update the last statement for that account */
		    gsb_navigation_update_statement_label (account_number);
		}
	    }
	    modification_fichier (TRUE);
	}
    }

    return FALSE;
}

/**
 * called by user, find all the R marked transactions without a number of reconcile
 * show them in a list and propose to associate them to a reconcile
 *
 * \param
 *
 * \return FALSE
 * */
gboolean gsb_reconcile_config_find_alone_transactions ( void )
{
    GSList *transactions_list = NULL;
    GSList *tmp_list;
    gint transaction_number;
    gint number_of_transactions;
    GtkWidget *dialog;
    GtkWidget *tree_view;
    GtkListStore *store;
    GtkWidget *label;
    GtkWidget *label_number_transactions;
    GtkWidget *scrolled_window;
    gint i;
    enum transactions_column {
	TRANSACTION_DATE = 0,
	TRANSACTION_PAYEE,
	TRANSACTION_AMOUNT,
	TRANSACTION_ACCOUNT,
	TRANSACTION_NUMBER,
	TRANSACTION_NB_COL
    };
    GtkTreeSelection *selection;
    GtkTreeIter iter;
    gint reconcile_number;
    gint return_value;

    /* for now, just return, wait and see the next commit ;-) */
    return FALSE;

    /* first we check if there is some transactions */
    tmp_list = gsb_data_transaction_get_transactions_list ();
    while (tmp_list)
    {
	transaction_number = gsb_data_transaction_get_transaction_number (tmp_list -> data);

	if ( gsb_data_transaction_get_marked_transaction (transaction_number) == OPERATION_RAPPROCHEE
	     &&
	     !gsb_data_transaction_get_reconcile_number (transaction_number))
	    transactions_list = g_slist_append ( transactions_list,
						 GINT_TO_POINTER (transaction_number));
	tmp_list = tmp_list -> next;
    }

    if (!transactions_list)
    {
	dialogue (_("No marked transactions without reconcile found !"));
	return FALSE;
    }

    /* ok, we have some orphan transactions, we make a list with that transactions */

    /* get the number of transactions to associate, we will decrease it for each association */
    number_of_transactions = g_slist_length (transactions_list);

    dialog = gtk_dialog_new_with_buttons ( _("Non associated transactions"),
					   GTK_WINDOW (window),
					   GTK_DIALOG_MODAL,
					   _("Associate the selection..."), GTK_RESPONSE_OK,
					   GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE,
					   NULL );
    /* need to set a size, else the list will be small */
    gtk_widget_set_usize ( dialog,
			   600,
			   400 );

    label_number_transactions = gtk_label_new ( g_strdup_printf (_("%d transactions are marked R but not associated with a reconcile"),
								 number_of_transactions ));
    gtk_box_pack_start ( GTK_BOX (GTK_DIALOG (dialog) -> vbox),
			 label_number_transactions,
			 FALSE, FALSE, 0 );
    gtk_widget_show (label_number_transactions);

    label = gtk_label_new ( _("Select the transaction(s) you want to associate with a reconcile :"));
    gtk_box_pack_start ( GTK_BOX (GTK_DIALOG (dialog) -> vbox),
			 label,
			 FALSE, FALSE, 0 );
    gtk_widget_show (label);

    scrolled_window = gtk_scrolled_window_new (FALSE, FALSE);
    gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW (scrolled_window),
				     GTK_POLICY_AUTOMATIC,
				     GTK_POLICY_AUTOMATIC );
    gtk_box_pack_start ( GTK_BOX (GTK_DIALOG (dialog) -> vbox),
			 scrolled_window,
			 TRUE, TRUE, 0 );
    gtk_widget_show (scrolled_window);

    /* set up the tree view */
    store = gtk_list_store_new ( TRANSACTION_NB_COL,
				 G_TYPE_STRING,
				 G_TYPE_STRING,
				 G_TYPE_STRING,
				 G_TYPE_STRING,
				 G_TYPE_INT );
    tree_view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
    gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (tree_view), TRUE);
    gtk_tree_selection_set_mode ( gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view)),
				  GTK_SELECTION_MULTIPLE );
    gtk_container_add ( GTK_CONTAINER (scrolled_window),
			tree_view );
    gtk_widget_show (tree_view);

    /* set the columns */
    for (i=TRANSACTION_DATE ; i<TRANSACTION_NUMBER ; i++)
    {
	GtkTreeViewColumn *column;
	GtkCellRenderer *cell;
	gchar *titles[] = {
	    _("Date"), _("Payee"), _("Amount"), _("Account")
	};
	gfloat alignment[] = {
	    COLUMN_CENTER, COLUMN_LEFT, COLUMN_CENTER, COLUMN_CENTER
	};

	cell = gtk_cell_renderer_text_new ();
	g_object_set ( G_OBJECT (cell),
		       "xalign", alignment[i],
		       NULL );
	column = gtk_tree_view_column_new ();
	gtk_tree_view_column_set_sizing ( column,
					  GTK_TREE_VIEW_COLUMN_AUTOSIZE );
	gtk_tree_view_column_set_alignment ( column,
					     alignment[i] );
	gtk_tree_view_column_pack_start ( column, cell, TRUE );
	gtk_tree_view_column_set_title ( column, titles[i] );
	gtk_tree_view_column_set_attributes (column, cell,
					     "text", i,
					     NULL);
	gtk_tree_view_column_set_expand ( column, TRUE );
	gtk_tree_view_column_set_resizable ( column,
					     TRUE );
	gtk_tree_view_append_column ( GTK_TREE_VIEW(tree_view), column);
    }

    /* fill the list */
    tmp_list = transactions_list;
    while (tmp_list)
    {
	gchar *amount_str;
	gchar *date_str;

	transaction_number = GPOINTER_TO_INT (tmp_list -> data);
	amount_str = gsb_real_get_string (gsb_data_transaction_get_amount (transaction_number));
	date_str = gsb_format_gdate (gsb_data_transaction_get_date (transaction_number));

	gtk_list_store_append ( GTK_LIST_STORE (store),
				&iter );
	gtk_list_store_set ( GTK_LIST_STORE (store),
			     &iter,
			     TRANSACTION_DATE, date_str,
			     TRANSACTION_PAYEE, gsb_data_payee_get_name (gsb_data_transaction_get_party_number (transaction_number), TRUE),
			     TRANSACTION_AMOUNT, amount_str,
			     TRANSACTION_ACCOUNT, gsb_data_account_get_name (gsb_data_transaction_get_account_number (transaction_number)),
			     TRANSACTION_NUMBER, transaction_number,
			     -1 );
	g_free (amount_str);
	g_free (date_str);
	tmp_list = tmp_list -> next;
    }

    /* run the dialog */
    return_value = gtk_dialog_run (GTK_DIALOG (dialog));

    if (return_value != GTK_RESPONSE_OK)
    {
	gtk_widget_destroy (dialog);
	return FALSE;
    }

    /* we have a GTK_RESPONSE_OK here, wich mean there is a selection,
     * perhaps several transactions, and we want associate them to
     * a reconcile */
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view));

    if (gtk_tree_selection_get_selected ( GTK_TREE_SELECTION (selection),
					  NULL,
					  &iter))
    {
	/* ok, we have a selection */
	gtk_tree_model_get ( GTK_TREE_MODEL (store),
			     &iter,
			     TRANSACTION_NUMBER, &reconcile_number,
			     -1 );
	gtk_widget_destroy (dialog);
	return FALSE;
    }
    
    dialogue_error ( _("Grisbi couldn't get the selection, operation canceled..."));
    gtk_widget_destroy (dialog);
    return FALSE;
}

