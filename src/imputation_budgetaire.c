/* fichier qui s'occupe de l'onglet de gestion des impputations */
/*           imputation_budgetaire.c */

/*     Copyright (C) 2000-2001  C�dric Auger */
/* 			grisbi@tuxfamily.org */
/* 			http://grisbi.tuxfamily.org */

/*     This program is free software; you can redistribute it and/or modify */
/*     it under the terms of the GNU General Public License as published by */
/*     the Free Software Foundation; either version 2 of the License, or */
/*     (at your option) any later version. */

/*     This program is distributed in the hope that it will be useful, */
/*     but WITHOUT ANY WARRANTY; without even the implied warranty of */
/*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/*     GNU General Public License for more details. */

/*     You should have received a copy of the GNU General Public License */
/*     along with this program; if not, write to the Free Software */
/*     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */



#include "include.h"
#include "structures.h"
#include "variables-extern.c"
#include "en_tete.h"




/* **************************************************************************************************** */
/* Fonction onglet_imputations : */
/* cr�e et renvoie le widget contenu dans l'onglet */
/* **************************************************************************************************** */

GtkWidget *onglet_imputations ( void )
{
  GtkWidget *onglet;
  GtkWidget *scroll_window;
  gchar *titres[] =
  {
    "Liste des imputations budg�taires",
    "Montant par IB",
    "Montant par sous-IB",
    "Montant par compte"
  };
  GtkWidget *vbox;
  GtkWidget *frame;
  GtkWidget *vbox_frame;
  GtkWidget *hbox;
  GtkWidget *label;
  GtkWidget *separateur;
  GtkWidget *bouton;


/* cr�ation de la fen�tre qui sera renvoy�e */

  onglet = gtk_hbox_new ( FALSE,
			  5 );
  gtk_container_set_border_width ( GTK_CONTAINER ( onglet ),
				   10 );
  gtk_widget_show ( onglet );



  /* mise en place de la partie de gauche */

/*   cr�ation de la frame de gauche */

  frame = gtk_frame_new ( NULL );
  gtk_frame_set_shadow_type ( GTK_FRAME ( frame ),
			       GTK_SHADOW_IN );
  gtk_box_pack_start ( GTK_BOX ( onglet ),
		       frame,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show (frame );

  vbox = gtk_vbox_new ( FALSE,
			5 );
  gtk_container_set_border_width ( GTK_CONTAINER ( vbox ),
				   15 );
  gtk_container_add ( GTK_CONTAINER ( frame ),
		      vbox );
  gtk_widget_show ( vbox );


  frame = gtk_frame_new ( " Informations : " );
  gtk_box_pack_start ( GTK_BOX ( vbox ),
		       frame,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( frame );

  vbox_frame = gtk_vbox_new ( FALSE,
			      5 );
  gtk_container_set_border_width ( GTK_CONTAINER ( vbox_frame ),
				   5 );
  gtk_container_add ( GTK_CONTAINER ( frame ),
		      vbox_frame );
  gtk_widget_show ( vbox_frame );

  entree_nom_imputation = gtk_entry_new ();
  gtk_widget_set_sensitive ( entree_nom_imputation,
			     FALSE );
  gtk_signal_connect ( GTK_OBJECT ( entree_nom_imputation ),
		       "changed",
		       GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
		       NULL );
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       entree_nom_imputation,
		       FALSE,
		       FALSE,
		       10 );
  gtk_widget_show ( entree_nom_imputation );


/* cr�ation des radio bouton d�bit/cr�dit */

  separateur = gtk_hseparator_new ();
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       separateur,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( separateur );


  label = gtk_label_new ( "Classement :" );
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       label,
		       FALSE,
		       FALSE,
		       10 );
  gtk_widget_show ( label );

  bouton_imputation_debit = gtk_radio_button_new_with_label ( NULL,
							 "D�bit" );
  gtk_widget_set_sensitive ( bouton_imputation_debit,
			     FALSE );
  gtk_signal_connect ( GTK_OBJECT ( bouton_imputation_debit ),
		       "toggled",
		       GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
		       NULL );
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       bouton_imputation_debit,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton_imputation_debit );


  bouton_imputation_credit = gtk_radio_button_new_with_label_from_widget ( GTK_RADIO_BUTTON ( bouton_imputation_debit ),
								      "Cr�dit" );
  gtk_widget_set_sensitive ( bouton_imputation_credit,
			     FALSE );
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       bouton_imputation_credit,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton_imputation_credit );


  separateur = gtk_hseparator_new ();
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       separateur,
		       FALSE,
		       FALSE,
		       10 );
  gtk_widget_show ( separateur );




/*   cr�ation des boutons modifier et annuler */

  hbox = gtk_hbox_new ( TRUE,
			5 );
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       hbox,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( hbox );

  bouton_modif_imputation_modifier = gnome_stock_button ( GNOME_STOCK_BUTTON_APPLY );
  gtk_button_set_relief ( GTK_BUTTON ( bouton_modif_imputation_modifier ),
			  GTK_RELIEF_NONE );
  gtk_widget_set_sensitive ( bouton_modif_imputation_modifier,
			     FALSE );
  gtk_signal_connect ( GTK_OBJECT ( bouton_modif_imputation_modifier ),
		       "clicked",
		       GTK_SIGNAL_FUNC ( clique_sur_modifier_imputation ),
		       NULL );
  gtk_box_pack_start ( GTK_BOX ( hbox ),
		       bouton_modif_imputation_modifier,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton_modif_imputation_modifier );

  bouton_modif_imputation_annuler = gnome_stock_button ( GNOME_STOCK_BUTTON_CANCEL );
  gtk_button_set_relief ( GTK_BUTTON ( bouton_modif_imputation_annuler ),
			  GTK_RELIEF_NONE );
  gtk_signal_connect ( GTK_OBJECT ( bouton_modif_imputation_annuler ),
		       "clicked",
		       GTK_SIGNAL_FUNC ( clique_sur_annuler_imputation ),
		       NULL );
  gtk_widget_set_sensitive ( bouton_modif_imputation_annuler,
			     FALSE );
  gtk_box_pack_start ( GTK_BOX ( hbox ),
		       bouton_modif_imputation_annuler,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton_modif_imputation_annuler);

  bouton_supprimer_imputation = gnome_stock_button ( GNOME_STOCK_PIXMAP_REMOVE );
  gtk_button_set_relief ( GTK_BUTTON ( bouton_supprimer_imputation ),
			  GTK_RELIEF_NONE );
  gtk_widget_set_sensitive ( bouton_supprimer_imputation,
			     FALSE );
  gtk_signal_connect ( GTK_OBJECT ( bouton_supprimer_imputation ),
		       "clicked",
		       GTK_SIGNAL_FUNC ( supprimer_imputation ),
		       NULL );
  gtk_box_pack_start ( GTK_BOX ( vbox_frame ),
		       bouton_supprimer_imputation,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton_supprimer_imputation );


  /* mise en place des boutons ajout d'1 imput / sous-imput */

  bouton_ajouter_imputation = gtk_button_new_with_label ( "Ajouter une imputation" );
  gtk_button_set_relief ( GTK_BUTTON ( bouton_ajouter_imputation ),
			  GTK_RELIEF_NONE );
  gtk_signal_connect ( GTK_OBJECT ( bouton_ajouter_imputation ),
		       "clicked",
		       GTK_SIGNAL_FUNC ( appui_sur_ajout_imputation ),
		       NULL );
  gtk_box_pack_start ( GTK_BOX ( vbox ),
		       bouton_ajouter_imputation,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton_ajouter_imputation );

  bouton_ajouter_sous_imputation = gtk_button_new_with_label ( "Ajouter une sous-imputation" );
  gtk_button_set_relief ( GTK_BUTTON ( bouton_ajouter_sous_imputation ),
			  GTK_RELIEF_NONE );
  gtk_widget_set_sensitive ( bouton_ajouter_sous_imputation,
			     FALSE );
  gtk_signal_connect ( GTK_OBJECT ( bouton_ajouter_sous_imputation ),
		       "clicked",
		       GTK_SIGNAL_FUNC ( appui_sur_ajout_sous_imputation ),
		       NULL );
  gtk_box_pack_start ( GTK_BOX ( vbox ),
		       bouton_ajouter_sous_imputation,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton_ajouter_sous_imputation );

  /* s�paration */

  separateur = gtk_hseparator_new ();
  gtk_box_pack_start ( GTK_BOX ( vbox ),
		       separateur,
		       FALSE,
		       FALSE,
		       10 );
  gtk_widget_show ( separateur );

  /* mise en place du bouton fusionner avec les cat�gories */

  bouton = gtk_button_new_with_label ( "Fusionner les cat�gories" );
  gtk_button_set_relief ( GTK_BUTTON ( bouton ),
			  GTK_RELIEF_NONE );
  gtk_signal_connect ( GTK_OBJECT ( bouton ),
		       "clicked",
		       GTK_SIGNAL_FUNC ( fusion_categories_imputation ),
		       NULL );
  gtk_box_pack_start ( GTK_BOX ( vbox ),
		       bouton,
		       FALSE,
		       FALSE,
		       0 );
  gtk_widget_show ( bouton );


/*   cr�ation de la frame de droite */

  frame = gtk_frame_new ( NULL );
  gtk_frame_set_shadow_type ( GTK_FRAME ( frame ),
			       GTK_SHADOW_IN );
  gtk_box_pack_start ( GTK_BOX ( onglet ),
		       frame,
		       TRUE,
		       TRUE,
		       5 );
  gtk_widget_show (frame );


/* cr�ation de l'arbre principal */

  scroll_window = gtk_scrolled_window_new ( NULL,
				     NULL );
  gtk_container_set_border_width ( GTK_CONTAINER ( scroll_window ),
				   10 );
  gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scroll_window ),
				   GTK_POLICY_AUTOMATIC,
				   GTK_POLICY_AUTOMATIC );
  gtk_container_add ( GTK_CONTAINER ( frame ),
		      scroll_window );
  gtk_widget_show ( scroll_window );


  arbre_imputation = gtk_ctree_new_with_titles ( 4,
						 0,
						 titres );
  gtk_ctree_set_line_style ( GTK_CTREE ( arbre_imputation ),
			     GTK_CTREE_LINES_DOTTED );
  gtk_ctree_set_expander_style ( GTK_CTREE ( arbre_imputation ),
				 GTK_CTREE_EXPANDER_CIRCULAR );
  gtk_clist_column_titles_passive ( GTK_CLIST ( arbre_imputation ));

  gtk_clist_set_column_justification ( GTK_CLIST ( arbre_imputation ),
				       0,
				       GTK_JUSTIFY_LEFT);
  gtk_clist_set_column_justification ( GTK_CLIST ( arbre_imputation ),
				       1,
				       GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification ( GTK_CLIST ( arbre_imputation ),
				       2,
				       GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification ( GTK_CLIST ( arbre_imputation ),
				       3,
				       GTK_JUSTIFY_CENTER);

  gtk_clist_set_column_resizeable ( GTK_CLIST ( arbre_imputation ),
				    0,
				    FALSE );
  gtk_clist_set_column_resizeable ( GTK_CLIST ( arbre_imputation ),
				    1,
				    FALSE );
  gtk_clist_set_column_resizeable ( GTK_CLIST ( arbre_imputation ),
				    2,
				    FALSE );
  gtk_clist_set_column_resizeable ( GTK_CLIST ( arbre_imputation ),
				    3,
				    FALSE );

  /* on met la fontion de tri alphab�tique en prenant en compte les accents */

  gtk_clist_set_compare_func ( GTK_CLIST ( arbre_imputation ),
			       (GtkCListCompareFunc) classement_alphabetique_tree );

  gtk_signal_connect ( GTK_OBJECT ( arbre_imputation ),
		       "tree-select-row",
		       GTK_SIGNAL_FUNC ( selection_ligne_imputation ),
		       NULL );
  gtk_signal_connect ( GTK_OBJECT ( arbre_imputation ),
		       "tree-unselect-row",
		       GTK_SIGNAL_FUNC ( enleve_selection_ligne_imputation ),
		       NULL );
  gtk_signal_connect_after ( GTK_OBJECT ( arbre_imputation ),
			     "button-press-event",
			     GTK_SIGNAL_FUNC ( verifie_double_click_imputation ),
			     NULL );
  gtk_signal_connect ( GTK_OBJECT ( arbre_imputation ),
		       "size-allocate",
		       GTK_SIGNAL_FUNC ( changement_taille_liste_tiers ),
		       NULL );
  gtk_signal_connect ( GTK_OBJECT ( arbre_imputation ),
		       "tree-expand",
		       GTK_SIGNAL_FUNC ( ouverture_node_imputation ),
		       NULL );
  gtk_signal_connect ( GTK_OBJECT ( arbre_imputation ),
		       "tree-collapse",
		       GTK_SIGNAL_FUNC ( fermeture_node_imputation ),
		       NULL );
  gtk_container_add ( GTK_CONTAINER (  scroll_window ),
		      arbre_imputation );
  gtk_widget_show ( arbre_imputation );


  gtk_clist_set_compare_func ( GTK_CLIST ( arbre_imputation ),
			       (GtkCListCompareFunc) classement_alphabetique_tree );

  /* la 1�re fois qu'on affichera les cat�g, il faudra remplir la liste */

  modif_imputation = 1;

   return ( onglet );
}
/* **************************************************************************************************** */




/* **************************************************************************************************** */
/* Fonction remplit_arbre_imputation */
/* le vide et le remplit */
/* **************************************************************************************************** */

void remplit_arbre_imputation ( void )
{
  gchar *text[4];
  GSList *liste_imputation_tmp;
  struct struct_devise *devise_compte;
  gint place_imputation;
  gint i;

  /* freeze le ctree */

  gtk_clist_freeze ( GTK_CLIST ( arbre_imputation ));

  /* retire la s�lection */

  gtk_clist_unselect_all ( GTK_CLIST ( arbre_imputation ));

  /*   efface l'ancien arbre */

  gtk_clist_clear ( GTK_CLIST ( arbre_imputation ));


  /*   il faut choisir une devise qui sera utilis�e par d�faut : on choisit la devise du premier compte */
  /*   �ventuellement, pourrait �tre choisi dans les param�tres */

  p_tab_nom_de_compte_variable = p_tab_nom_de_compte;

  devise_compte = g_slist_find_custom ( liste_struct_devises,
					GINT_TO_POINTER ( no_devise_totaux_tiers ),
					( GCompareFunc ) recherche_devise_par_no) -> data;

  /* calcule les montants des imputations et sous imputations */

  calcule_total_montant_imputation ();

  /* remplit l'arbre */

  liste_imputation_tmp = liste_struct_imputation;
  place_imputation = 0;

  while ( liste_imputation_tmp )
    {
      struct struct_imputation *imputation;
      GtkCTreeNode *ligne;
      GSList *liste_sous_imputation_tmp;
      GtkCTreeNode *ligne_sous_imputation;
      gint place_sous_imputation;

      imputation = liste_imputation_tmp -> data;

      if ( etat.affiche_nb_ecritures_listes
	   &&
	   nb_ecritures_par_imputation[place_imputation+1] )
	text[0] = g_strconcat ( imputation -> nom_imputation,
				" (",
				itoa ( nb_ecritures_par_imputation[place_imputation+1] ),
				")",
				NULL );
      else
	text[0] = imputation -> nom_imputation ;

      if ( tab_montant_imputation[place_imputation+1] )
	text[1] = g_strdup_printf ( "%4.2f %s",
				    tab_montant_imputation[place_imputation+1],
				    devise_compte -> code_devise );
      else
	text[1] = NULL;

      text[2] = NULL;
      text[3] = NULL;

      ligne = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
				      NULL,
				      NULL,
				      text,
				      10,
				      pixmap_ouvre,
				      masque_ouvre,
				      pixmap_ferme,
				      masque_ferme,
				      FALSE,
				      FALSE );

       /* on associe � ce imputation � l'adr de sa struct */

      gtk_ctree_node_set_row_data ( GTK_CTREE ( arbre_imputation ),
				    ligne,
				    imputation );


      /*       pour chaque imputation, on met ses sous-imputation */


      liste_sous_imputation_tmp = imputation -> liste_sous_imputation;
      place_sous_imputation = 0;

      while ( liste_sous_imputation_tmp )
	{
	  struct struct_sous_imputation *sous_imputation;

	  sous_imputation = liste_sous_imputation_tmp -> data;

	  if ( tab_montant_sous_imputation[place_imputation]
	       &&
	       tab_montant_sous_imputation[place_imputation][place_sous_imputation+1]
	       &&
	       etat.affiche_nb_ecritures_listes
	       &&
	       nb_ecritures_par_sous_imputation[place_imputation][place_sous_imputation+1] )
	    text[0] = g_strconcat ( sous_imputation -> nom_sous_imputation,
				    " (",
				    itoa ( nb_ecritures_par_sous_imputation[place_imputation][place_sous_imputation+1] ),
				    ")",
				    NULL );
	  else
	    text[0] = sous_imputation -> nom_sous_imputation ;

	  text[1] = NULL;

	  if ( tab_montant_sous_imputation[place_imputation]
	       &&
	       tab_montant_sous_imputation[place_imputation][place_sous_imputation+1] )
	    text[2] = g_strdup_printf ( "%4.2f %s",
					tab_montant_sous_imputation[place_imputation][place_sous_imputation+1],
					devise_compte -> code_devise );
	  else
	    text[2] = NULL;

	  text[3] = NULL;

	  ligne_sous_imputation = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
						     ligne,
						     NULL,
						     text,
						     10,
						     NULL,
						     NULL,
						     NULL,
						     NULL,
						     FALSE,
						     FALSE );

	  /* on associe cette sous_imputation � l'adr de sa struct */

	  gtk_ctree_node_set_row_data ( GTK_CTREE ( arbre_imputation ),
					ligne_sous_imputation,
					sous_imputation );


	  /* pour chacun des sous imputation, on met un fils bidon pour pouvoir l'ouvrir */

	  gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
				  ligne_sous_imputation,
				  NULL,
				  text,
				  5,
				  NULL,
				  NULL,
				  NULL,
				  NULL,
				  FALSE,
				  FALSE );

	  place_sous_imputation++;
	  liste_sous_imputation_tmp = liste_sous_imputation_tmp -> next;
	}

      /*       on a fini de saisir les sous cat�gories, s'il y avait des op�s sans sous cat�g, on les mets ici */

      if ( tab_montant_sous_imputation[place_imputation]
	   &&
	   nb_ecritures_par_sous_imputation[place_imputation][0] )
	{
	  if ( etat.affiche_nb_ecritures_listes )
	    text[0] = g_strconcat ( "Aucune sous-imputation (",
				    itoa ( nb_ecritures_par_sous_imputation[place_imputation][0] ),
				    ")",
				    NULL );
	  else
	    text[0] = "Aucune sous-imputation";

	  text[1] = NULL;

	  if ( tab_montant_sous_imputation[place_imputation][0] )
	    text[2] = g_strdup_printf ( "%4.2f %s",
					tab_montant_sous_imputation[place_imputation][0],
					devise_compte -> code_devise );
	  else
	    text[2] = NULL;

	  text[3] = NULL;

	  ligne_sous_imputation = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
						     ligne,
						     NULL,
						     text,
						     10,
						     NULL,
						     NULL,
						     NULL,
						     NULL,
						     FALSE,
						     FALSE );

	  /* pour chacun des sous imputation, on met un fils bidon pour pouvoir l'ouvrir */

	  gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
				  ligne_sous_imputation,
				  NULL,
				  text,
				  5,
				  NULL,
				  NULL,
				  NULL,
				  NULL,
				  FALSE,
				  FALSE );

	}
      place_imputation++;
      liste_imputation_tmp = liste_imputation_tmp -> next;
    }

  /*   on a fini de mettre les cat�gories, on met ici les op�s sans cat�g */

  if ( tab_montant_imputation[0] )
    {
      GtkCTreeNode *ligne;

      if ( etat.affiche_nb_ecritures_listes
	   &&
	   nb_ecritures_par_imputation[0] )
	text[0] = g_strconcat ( "Aucune imputation (",
				itoa ( nb_ecritures_par_imputation[0] ),
				")",
				NULL );
      else
	text[0] = "Aucune imputation";

      text[1] = g_strdup_printf ( "%4.2f %s",
				  tab_montant_imputation[0],
				  devise_compte -> code_devise );
      text[2] = NULL;
      text[3] = NULL;

      ligne = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
				      NULL,
				      NULL,
				      text,
				      10,
				      pixmap_ouvre,
				      masque_ouvre,
				      pixmap_ferme,
				      masque_ferme,
				      FALSE,
				      FALSE );

	  /* on met un fils bidon pour pouvoir l'ouvrir */

      gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
			      ligne,
			      NULL,
			      text,
			      5,
			      NULL,
			      NULL,
			      NULL,
			      NULL,
			      FALSE,
			      FALSE );
    }

  /*   on efface les variables */

  free ( tab_montant_imputation );
  free ( nb_ecritures_par_imputation );

  for ( i=0 ; i<nb_enregistrements_imputations ; i++ )
    free ( tab_montant_sous_imputation[i] );
  free ( tab_montant_sous_imputation );

  for ( i=0 ; i<nb_enregistrements_imputations ; i++ )
    free ( nb_ecritures_par_sous_imputation[i] );
  free ( nb_ecritures_par_sous_imputation );



  gtk_ctree_sort_recursive ( GTK_CTREE ( arbre_imputation ),
			     NULL );

  /* defreeze le ctree */

  gtk_clist_thaw ( GTK_CLIST ( arbre_imputation ));

  enleve_selection_ligne_imputation ();
  modif_imputation = 0;
}
/* **************************************************************************************************** */




/* **************************************************************************************************** */
/* Fonction ouverture_node_imputation */
/* appel�� lorsqu'on ouvre une imputation, sous imputation ou le compte d'une imputation */
/* remplit ce qui doit �tre affich� */
/* **************************************************************************************************** */

void ouverture_node_imputation ( GtkWidget *arbre,
				 GtkCTreeNode *node,
				 gpointer null )
{			    
  GtkCTreeRow *row;
  gchar *text[4];
  GtkCTreeNode *node_insertion;

  row = GTK_CTREE_ROW ( node );

  /*   si on ouvre une imputation, on fait rien */

  if ( row->level == 1
       &&
       gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
				     node )
       )
    return;


  /* freeze le ctree */

  gtk_clist_freeze ( GTK_CLIST ( arbre_imputation ));


  /* on commence par virer la ligne bidon qui �tait attach�e � ce noeud */

  gtk_ctree_remove_node ( GTK_CTREE ( arbre_imputation ),
			  row -> children );

  /* s�paration entre ouverture de sous-imputation ( 2 ) et ouverture de compte ( 3 ) */

  if ( ( row -> level == 2
	 &&
	 gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
				       GTK_CTREE_ROW ( node ) -> parent ))
       ||
       ( row ->level == 1
	 &&
	 !gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					node )))
    {
      /* c'est une ouverture de sous imputation, on r�cup�re sa structure  */

      gint no_imputation;
      gint no_sous_imputation;
      gint i;

      if ( row -> level != 1 )
	{
	  no_imputation = ((struct struct_imputation *)(gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
									    GTK_CTREE_ROW ( node ) -> parent ))) -> no_imputation;
	  if ( gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					     node))
	    no_sous_imputation = ((struct struct_sous_imputation *)(gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
											node))) -> no_sous_imputation;
	  else
	    no_sous_imputation = 0;
	}
      else
	{
	  no_imputation = 0;
	  no_sous_imputation = 0;
	}

      /* on va scanner tous les comptes, d�s qu'une imputation correspondant � l'imput s�lectionn�e est trouv� */
      /* on affiche le nom du compte */

      p_tab_nom_de_compte_variable = p_tab_nom_de_compte;

      for ( i = 0 ; i < nb_comptes ; i++ )
	{
	  GSList *pointeur_ope;

	  pointeur_ope = LISTE_OPERATIONS;

	  while ( pointeur_ope )
	    {
	      struct structure_operation *operation;
	      
	      operation = pointeur_ope -> data;

	      if ( operation -> imputation == no_imputation
		   &&
		   operation -> sous_imputation == no_sous_imputation
		   &&
		   !operation -> operation_ventilee )
		{
		  /* affiche le compte courant */

		  text[3] = calcule_total_montant_imputation_par_compte ( operation -> imputation,
									  operation -> sous_imputation,
									  operation -> no_compte );

		  if ( etat.affiche_nb_ecritures_listes
		       &&
		       nb_ecritures_par_comptes )
		    text[0] = g_strconcat ( NOM_DU_COMPTE,
					    " (",
					    itoa ( nb_ecritures_par_comptes ),
					    ")",
					    NULL );
		  else
		    text[0] = NOM_DU_COMPTE;

		  text[1] = NULL;
		  text[2] = NULL;

		  node_insertion = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
							   node,
							   NULL,
							   text,
							   5,
							   NULL,
							   NULL,
							   NULL,
							   NULL,
							   FALSE,
							   FALSE );

		  /* associe le no de compte � la ligne du compte */
		  
		  gtk_ctree_node_set_row_data ( GTK_CTREE ( arbre_imputation ),
						node_insertion,
						GINT_TO_POINTER ( i ));

		  /* on met une ligne bidon pour pouvoir l'ouvrir */

		  gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
					  node_insertion,
					  NULL,
					  text,
					  5,
					  NULL,
					  NULL,
					  NULL,
					  NULL,
					  FALSE,
					  FALSE );
		  pointeur_ope = NULL;
		}
	      else
		pointeur_ope = pointeur_ope -> next;
	    }
	      
	  p_tab_nom_de_compte_variable++;
	}
    }
  else
    {
      /* c'est une ouverture d'un compte */
      /*       cette fois, on fait le tour de toutes les op�s du compte pour afficher celles qui correspondent � la imputation */

      GSList *pointeur_ope;
      gint no_imputation;
      gint no_sous_imputation;

      if ( row -> level != 2 )
	{
	  no_imputation = ((struct struct_imputation *)(gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
									    GTK_CTREE_ROW ( GTK_CTREE_ROW ( node ) -> parent ) -> parent ))) -> no_imputation;

	  if ( gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					     GTK_CTREE_ROW ( node ) -> parent ))
	    no_sous_imputation = ((struct struct_sous_imputation *)(gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
											GTK_CTREE_ROW ( node ) -> parent ))) -> no_sous_imputation;
	  else
	    no_sous_imputation = 0;
	}
      else
	{
	  no_imputation = 0;
	  no_sous_imputation = 0;
	}

      p_tab_nom_de_compte_variable = p_tab_nom_de_compte + GPOINTER_TO_INT ( gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
													   node ));

      pointeur_ope = LISTE_OPERATIONS;

      while ( pointeur_ope )
	{
	  struct struct_devise *devise_operation;
	  struct structure_operation *operation;

	  operation = pointeur_ope -> data;

	  devise_operation = g_slist_find_custom ( liste_struct_devises,
						   GINT_TO_POINTER ( operation -> devise ),
						   ( GCompareFunc ) recherche_devise_par_no ) -> data;

	  if ( operation -> imputation == no_imputation
	       &&
	       operation -> sous_imputation == no_sous_imputation
	       &&
	       !operation -> operation_ventilee  )
	    {
		      if ( operation -> notes )
			{
			  if ( operation -> no_operation_ventilee_associee )
			    text[0] = g_strdup_printf ( "%d/%d/%d : %4.2f %s (ventilation) [ %s ]",
							operation -> jour,
							operation -> mois,
							operation -> annee,
							operation -> montant,
							devise_operation -> code_devise,
							operation -> notes );
			  else
			    text[0] = g_strdup_printf ( "%d/%d/%d : %4.2f %s [ %s ]",
							operation -> jour,
							operation -> mois,
							operation -> annee,
							operation -> montant,
							devise_operation -> code_devise,
							operation -> notes );
			}
		      else
			{
			  if ( operation -> no_operation_ventilee_associee )
			    text[0] = g_strdup_printf ( "%d/%d/%d : %4.2f %s (ventilation)",
							operation -> jour,
							operation -> mois,
							operation -> annee,
							operation -> montant,
							devise_operation -> code_devise );
			  else
			    text[0] = g_strdup_printf ( "%d/%d/%d : %4.2f %s",
							operation -> jour,
							operation -> mois,
							operation -> annee,
							operation -> montant,
							devise_operation -> code_devise );
			}

	      text[1] = NULL;
	      text[2] = NULL;
	      text[3] = NULL;

	      node_insertion = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
						       node,
						       NULL,
						       text,
						       5,
						       NULL,
						       NULL,
						       NULL,
						       NULL,
						       FALSE,
						       FALSE );
 
	      /* on associe � cette op� l'adr de sa struct */

	      gtk_ctree_node_set_row_data ( GTK_CTREE ( arbre_imputation ),
					    node_insertion,
					    operation );
	    }
	  pointeur_ope = pointeur_ope -> next;
	}
    }

  /* defreeze le ctree */

  gtk_clist_thaw ( GTK_CLIST ( arbre_imputation ));

}
/* **************************************************************************************************** */





/* **************************************************************************************************** */
/* Fonction fermeture_node_imputation */
/* appel�� lorsqu'on ferme un tiers ou le compte d'un tiers */
/* efface tous les fils et en met un bidon */
/* **************************************************************************************************** */

void fermeture_node_imputation ( GtkWidget *arbre,
				 GtkCTreeNode *node,
				 gpointer null )
{			    
  GtkCTreeNode *child;

  /*   si on ferme une imputation, on fait rien */

  if ( GTK_CTREE_ROW ( node )->level == 1 
       &&
       gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
				     node ))
    return;

  /* freeze le ctree */

  gtk_clist_freeze ( GTK_CLIST ( arbre_imputation ));

  child = GTK_CTREE_ROW ( node ) -> children;


  while ( child && GTK_CTREE_ROW ( child ) -> sibling )
    {
      gtk_ctree_remove_node ( GTK_CTREE ( arbre_imputation ),
			      child );
      child = GTK_CTREE_ROW ( node ) -> children;
    }

  /* defreeze le ctree */

  gtk_clist_thaw ( GTK_CLIST ( arbre_imputation ));

}
/* **************************************************************************************************** */





/* **************************************************************************************************** */
void selection_ligne_imputation ( GtkCTree *arbre,
				  GtkCTreeNode *noeud,
				  gint colonne,
				  gpointer null )
{
  GtkCTreeNode *node_tmp;

  /* on allume le bouton ajouter une sous imputation si ce n'est pas dans aucune imputation */

  node_tmp = noeud;

  while ( GTK_CTREE_ROW ( node_tmp ) -> level  != 1 )
    node_tmp = GTK_CTREE_ROW ( node_tmp ) -> parent;

  if ( gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
				     node_tmp ))
    gtk_widget_set_sensitive ( bouton_ajouter_sous_imputation,
			       TRUE );

  if ( GTK_CTREE_ROW ( noeud ) -> level  == 1
       &&
       gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
				     noeud ))
    {
      struct struct_imputation *imputation;

      imputation = gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					    noeud );

      gtk_signal_handler_block_by_func ( GTK_OBJECT ( entree_nom_imputation ),
					 GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
					 NULL );

      gtk_entry_set_text ( GTK_ENTRY ( entree_nom_imputation ),
			   imputation -> nom_imputation );

      gtk_signal_handler_unblock_by_func ( GTK_OBJECT ( entree_nom_imputation ),
					   GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
					   NULL );

      gtk_object_set_data ( GTK_OBJECT ( entree_nom_imputation ),
			    "adr_struct_imputation",
			    imputation );
      gtk_object_set_data ( GTK_OBJECT ( entree_nom_imputation ),
			    "adr_struct_sous_imputation",
			    NULL );

      gtk_widget_set_sensitive ( bouton_supprimer_imputation,
				 TRUE );
      gtk_widget_set_sensitive ( entree_nom_imputation,
				 TRUE );
      gtk_widget_set_sensitive ( bouton_imputation_debit,
				 TRUE );
      gtk_widget_set_sensitive ( bouton_imputation_credit,
				 TRUE );

      gtk_signal_handler_block_by_func ( GTK_OBJECT ( bouton_imputation_debit ),
					 GTK_SIGNAL_FUNC ( modification_du_texte_imputation ),
					 NULL );
      if ( imputation -> type_imputation )
	gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( bouton_imputation_debit ),
				       TRUE );
      else
	gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( bouton_imputation_credit ),
				       TRUE );

      gtk_signal_handler_unblock_by_func ( GTK_OBJECT ( bouton_imputation_debit ),
					   GTK_SIGNAL_FUNC ( modification_du_texte_imputation ),
					   NULL );


    }
  else
    if ( GTK_CTREE_ROW ( noeud ) -> level  == 2
	 &&
	 gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
				       noeud )
	 &&
	 gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
				       GTK_CTREE_ROW ( noeud ) -> parent ))
    {
      struct struct_sous_imputation *sous_imputation;

      sous_imputation = gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
						 noeud );
      gtk_signal_handler_block_by_func ( GTK_OBJECT ( entree_nom_imputation ),
					 GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
					 NULL );

      gtk_entry_set_text ( GTK_ENTRY ( entree_nom_imputation ),
			   sous_imputation -> nom_sous_imputation );

      gtk_signal_handler_unblock_by_func ( GTK_OBJECT ( entree_nom_imputation ),
					   GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
					   NULL );

      gtk_object_set_data ( GTK_OBJECT ( entree_nom_imputation ),
			    "adr_struct_imputation",
			    NULL );
      gtk_object_set_data ( GTK_OBJECT ( entree_nom_imputation ),
			    "adr_struct_sous_imputation",
			    sous_imputation );

      gtk_widget_set_sensitive ( bouton_supprimer_imputation,
				 TRUE );
      gtk_widget_set_sensitive ( entree_nom_imputation,
				 TRUE );
    }
}
/* **************************************************************************************************** */


/* **************************************************************************************************** */
void verifie_double_click_imputation ( GtkWidget *liste,
				       GdkEventButton *ev,
				       gpointer null )
{
  if ( ev -> type == GDK_2BUTTON_PRESS )
    {
      struct structure_operation *operation;

      if ( GTK_CLIST ( arbre_imputation ) -> selection
	   &&
	   ( GTK_CTREE_ROW ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data ) -> level == 4
	     ||
	     ( GTK_CTREE_ROW ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data ) -> level == 3
	       &&
	       !gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					      GTK_CTREE_ROW ( GTK_CTREE_ROW (( GTK_CLIST ( arbre_imputation ) -> selection ) -> data ) -> parent ) -> parent ))))
	{
	  /* passage sur le compte concern� */

	  operation = gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
						    GTK_CTREE_NODE ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data ) );

	  /* si c'est une op� de ventilation, on se place sur l'op� ventil�e correspondante */
 
	  if ( operation -> no_operation_ventilee_associee )
	    {
	      p_tab_nom_de_compte_variable = p_tab_nom_de_compte + operation -> no_compte;

	      operation = g_slist_find_custom ( LISTE_OPERATIONS,
						GINT_TO_POINTER ( operation -> no_operation_ventilee_associee ),
						(GCompareFunc) recherche_operation_par_no ) -> data;
	    }

	  changement_compte ( GINT_TO_POINTER ( operation -> no_compte ));


	  if ( operation -> pointe == 2 && !etat.r_affiches )
	    {
	      etat.r_affiches = 1;
	      remplissage_liste_operations ( compte_courant );
	    }

	  OPERATION_SELECTIONNEE = operation;

	  selectionne_ligne ( compte_courant );
	}
    }
}
/* **************************************************************************************************** */


/* **************************************************************************************************** */
void enleve_selection_ligne_imputation ( void )
{
  gtk_widget_set_sensitive ( bouton_supprimer_imputation,
			     FALSE );
  gtk_widget_set_sensitive ( bouton_modif_imputation_modifier,
			     FALSE );
  gtk_widget_set_sensitive ( bouton_modif_imputation_annuler,
			     FALSE );
  gtk_widget_set_sensitive ( entree_nom_imputation,
			     FALSE );
  gtk_widget_set_sensitive ( bouton_imputation_debit,
			     FALSE );
  gtk_widget_set_sensitive ( bouton_imputation_credit,
			     FALSE );
  gtk_widget_set_sensitive ( bouton_ajouter_sous_imputation,
			     FALSE );

  gtk_signal_handler_block_by_func ( GTK_OBJECT ( entree_nom_imputation ),
				     GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
				     NULL );

  gtk_editable_delete_text ( GTK_EDITABLE ( entree_nom_imputation ),
			     0,
			     -1 );

  gtk_signal_handler_unblock_by_func ( GTK_OBJECT ( entree_nom_imputation ),
				     GTK_SIGNAL_FUNC ( modification_du_texte_imputation),
				     NULL );

}
/* **************************************************************************************************** */






/* **************************************************************************************************** */
void modification_du_texte_imputation ( void )
{
  gtk_widget_set_sensitive ( bouton_modif_imputation_modifier,
			     TRUE );
  gtk_widget_set_sensitive ( bouton_modif_imputation_annuler,
			     TRUE );
}
/* **************************************************************************************************** */





/* **************************************************************************************************** */
void clique_sur_modifier_imputation ( void )
{
  GtkCTreeNode *node;


/* si c'est une imputation et si c'est une modif du nom, on doit r�afficher la liste des imputation et les listes des op�s, sinon, on change juste la imputation et */
/* met � jour les listes de imputations */
/* si c'est une sous imputation, c'est obligatoirement un changement de nom */

  if ( gtk_object_get_data ( GTK_OBJECT (  entree_nom_imputation ),
			     "adr_struct_imputation" ) )
    {
      /* c'est une imputation */

      struct struct_imputation *imputation;


      imputation =  gtk_object_get_data ( GTK_OBJECT (  entree_nom_imputation ),
				     "adr_struct_imputation" );


      if ( strcmp ( g_strstrip ( gtk_entry_get_text ( GTK_ENTRY ( entree_nom_imputation ))),
		    imputation -> nom_imputation ))
	{
	  free ( imputation -> nom_imputation );

	  imputation -> nom_imputation = g_strdup ( g_strstrip ( gtk_entry_get_text ( GTK_ENTRY ( entree_nom_imputation ))) );


	  node = GTK_CTREE_NODE ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data );

	  if ( GTK_CTREE_ROW ( node ) -> expanded )
	    gtk_ctree_node_set_pixtext ( GTK_CTREE ( arbre_imputation ),
					 node,
					 0,
					 imputation -> nom_imputation,
					 10,
					 pixmap_ferme,
					 masque_ferme );
	  else
	   gtk_ctree_node_set_pixtext ( GTK_CTREE ( arbre_imputation ),
					 node,
					 0,
					 imputation -> nom_imputation,
					 10,
					 pixmap_ouvre,
					 masque_ouvre );
 
	  demande_mise_a_jour_tous_comptes ();
	}
      else
	imputation -> type_imputation = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( bouton_imputation_debit ));
    }
  else
    {
      /* c'est une sous imputation */

      struct struct_sous_imputation *sous_imputation;

      sous_imputation =  gtk_object_get_data ( GTK_OBJECT (  entree_nom_imputation ),
					  "adr_struct_sous_imputation" );

      free ( sous_imputation -> nom_sous_imputation );

      sous_imputation -> nom_sous_imputation = g_strdup ( g_strstrip ( gtk_entry_get_text ( GTK_ENTRY ( entree_nom_imputation ))) );


      node = GTK_CTREE_NODE ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data );

      gtk_ctree_node_set_text ( GTK_CTREE ( arbre_imputation ),
				node,
				0,
				sous_imputation -> nom_sous_imputation );

      demande_mise_a_jour_tous_comptes ();
    }

  gtk_clist_unselect_all ( GTK_CLIST ( arbre_imputation ));

  mise_a_jour_imputation ();

  gtk_widget_set_sensitive ( bouton_modif_imputation_modifier,
			     FALSE );
  gtk_widget_set_sensitive ( bouton_modif_imputation_annuler,
			     FALSE );

  modification_fichier(TRUE);
}
/* **************************************************************************************************** */


/* **************************************************************************************************** */
void clique_sur_annuler_imputation ( void )
{
  if ( gtk_object_get_data ( GTK_OBJECT (  entree_nom_imputation ),
			     "adr_struct_imputation" ))
    {
      /* c'est une imputation */

      struct struct_imputation *imputation;

      imputation =  gtk_object_get_data ( GTK_OBJECT (  entree_nom_imputation ),
				     "adr_struct_imputation" );

      gtk_entry_set_text ( GTK_ENTRY ( entree_nom_imputation ),
			   imputation -> nom_imputation );

      if ( imputation -> type_imputation )
	gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( bouton_imputation_debit ),
				       TRUE );
      else
	gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( bouton_imputation_credit ),
				       TRUE );
    }
  else
    {
      /* c'est une sous imputation */

      struct struct_sous_imputation *sous_imputation;

      sous_imputation =  gtk_object_get_data ( GTK_OBJECT (  entree_nom_imputation ),
					  "adr_struct_sous_imputation" );

      gtk_entry_set_text ( GTK_ENTRY ( entree_nom_imputation ),
			   sous_imputation -> nom_sous_imputation );

    }

  gtk_widget_set_sensitive ( bouton_modif_imputation_modifier,
			     FALSE );
  gtk_widget_set_sensitive ( bouton_modif_imputation_annuler,
			     FALSE );

}
/* **************************************************************************************************** */





/* **************************************************************************************************** */
void supprimer_imputation ( void )
{
  struct struct_imputation *imputation;
  GtkCTreeNode *node;
  gint i;
  gint ope_trouvee;


  if ( !gtk_object_get_data ( GTK_OBJECT (  entree_nom_imputation ),
			      "adr_struct_imputation" ))
    {
      supprimer_sous_imputation();
      return;
    }

  node = GTK_CTREE_NODE ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data );

  imputation = gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					node );

  /* fait le tour des op�s pour en trouver une qui a cette cat�gorie */

  p_tab_nom_de_compte_variable = p_tab_nom_de_compte;
  ope_trouvee = 0;

  for ( i=0 ; i<nb_comptes ; i++ )
    {
      GSList *liste_tmp;

      liste_tmp = LISTE_OPERATIONS;

      while ( liste_tmp )
	{
	  struct structure_operation *operation;

	  operation = liste_tmp -> data;

	  if ( operation -> imputation == imputation -> no_imputation )
	    {
	      ope_trouvee = 1;
	      liste_tmp = NULL;
	      i = nb_comptes;
	    }
	  else
	    liste_tmp = liste_tmp -> next;
	}
      p_tab_nom_de_compte_variable++;
    }


  if ( ope_trouvee )
    {
      GtkWidget *dialog;
      GtkWidget *label;
      gint resultat;
      GtkWidget *separation;
      GtkWidget *hbox;
      GtkWidget *bouton_imputation_generique;
      GtkWidget *combofix;
      GSList *liste_combofix;
      GSList *pointeur;
      GSList *liste_tmp;
      GtkWidget *bouton_transfert;
      gint i;
      struct struct_imputation *nouvelle_imputation;
      struct struct_sous_imputation *nouvelle_sous_imputation;
      GSList *liste_imputation_credit;
      GSList *liste_imputation_debit;
      gchar **split_imputation;
      gint nouveau_no_imputation;
      gint nouveau_no_sous_imputation;

      dialog = gnome_dialog_new ( "Suppression d'une imputation",
					    GNOME_STOCK_BUTTON_OK,
					    GNOME_STOCK_BUTTON_CANCEL,
					     NULL);
      gnome_dialog_set_parent ( GNOME_DIALOG ( dialog ),
				GTK_WINDOW ( window ));

      label = gtk_label_new ( "L'imputation s�lectionn�e contient encore des op�rations.\n\nVous pouvez : " );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   label,
			   FALSE,
			   FALSE,
			   0 );

      separation = gtk_hseparator_new ( );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   separation,
			   FALSE,
			   FALSE,
			   0 );

/*       mise en place du choix tranfert vers un autre imputation */
      
      hbox = gtk_hbox_new ( FALSE,
			    5 );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   hbox,
			   FALSE,
			   FALSE,
			   0 );

      bouton_transfert = gtk_radio_button_new_with_label ( NULL,
							   "Transf�rer les op�rations sur l'imputation : "  );
      gtk_box_pack_start ( GTK_BOX ( hbox ),
			   bouton_transfert,
			   FALSE,
			   FALSE,
			   0 );


      pointeur = liste_struct_imputation;
      liste_combofix = NULL;
      liste_imputation_credit = NULL;
      liste_imputation_debit = NULL;

      while ( pointeur )
	{
	  struct struct_imputation *imputation;
	  GSList *sous_pointeur;

	  imputation = pointeur -> data;

	  if ( imputation-> no_imputation != imputation -> no_imputation )
	    {
	      if ( imputation -> type_imputation )
		liste_imputation_debit = g_slist_append ( liste_imputation_debit,
						     g_strdup ( imputation -> nom_imputation ) );
	      else
		liste_imputation_credit = g_slist_append ( liste_imputation_credit,
						      g_strdup ( imputation -> nom_imputation ) );


	      sous_pointeur = imputation -> liste_sous_imputation;

	      while ( sous_pointeur )
		{
		  struct struct_sous_imputation *sous_imputation;

		  sous_imputation = sous_pointeur -> data;

		  if ( imputation -> type_imputation )
		    liste_imputation_debit = g_slist_append ( liste_imputation_debit,
							 g_strconcat ( "\t",
								       sous_imputation -> nom_sous_imputation,
								       NULL ) );
		  else
		    liste_imputation_credit = g_slist_append ( liste_imputation_credit,
							  g_strconcat ( "\t",
									sous_imputation -> nom_sous_imputation,
									NULL ) );

		  sous_pointeur = sous_pointeur -> next;
		}
	    }
	  pointeur = pointeur -> next;
	}

      /*   on ajoute les listes des cr�dits / d�bits � la liste du combofix du formulaire */

      liste_combofix = g_slist_append ( liste_combofix,
						   liste_imputation_debit );
      liste_combofix = g_slist_append ( liste_combofix,
						   liste_imputation_credit );


      combofix = gtk_combofix_new_complex ( liste_combofix,
					    TRUE,
					    TRUE,
					    TRUE );
      gtk_box_pack_start ( GTK_BOX ( hbox ),
			   combofix,
			   FALSE,
			   FALSE,
			   0 );

      /*       mise en place du choix supprimer le imputation */

      hbox = gtk_hbox_new ( FALSE,
			    5 );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   hbox,
			   FALSE,
			   FALSE,
			   0 );

      bouton_imputation_generique = gtk_radio_button_new_with_label ( gtk_radio_button_group ( GTK_RADIO_BUTTON ( bouton_transfert )),
											  " Supprimer simplement cette imputation." );
      gtk_box_pack_start ( GTK_BOX ( hbox ),
			   bouton_imputation_generique,
			   FALSE,
			   FALSE,
			   0 );

      gtk_widget_show_all ( dialog );


    retour_dialogue:
      resultat = gnome_dialog_run ( GNOME_DIALOG ( dialog ) );

      if ( resultat )
	{
	  if ( resultat == 1 )
	    gnome_dialog_close ( GNOME_DIALOG ( dialog ) );
	  return;
	}


      if ( gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( bouton_transfert )) )
	{

	  if ( !strlen (gtk_combofix_get_text ( GTK_COMBOFIX ( combofix ))))
	    {
	      dialogue ( "Veuillez entrer une imputation !" );
	      goto retour_dialogue;
	    }

	  /* transfert des imputation au niveau des listes */

	  split_imputation = g_strsplit ( gtk_combofix_get_text ( GTK_COMBOFIX ( combofix )),
				     " : ",
				     2 );

	  nouvelle_imputation = g_slist_find_custom ( liste_struct_imputation,
						      split_imputation[0],
						      (GCompareFunc) recherche_imputation_par_nom ) -> data;
	  nouveau_no_imputation = nouvelle_imputation -> no_imputation;

	  if ( split_imputation[1] )
	    {
	      nouvelle_sous_imputation = g_slist_find_custom ( nouvelle_imputation -> liste_sous_imputation,
							  split_imputation[1],
							  (GCompareFunc) recherche_sous_imputation_par_nom ) -> data;
	      nouveau_no_sous_imputation = nouvelle_sous_imputation -> no_sous_imputation;
	    }
	  else
	    nouveau_no_sous_imputation = 0;

	  g_strfreev ( split_imputation );
	}
      else
	{
	  nouveau_no_imputation = 0;
	  nouveau_no_sous_imputation = 0;
	}


      /* on fait le tour des op�s pour mettre le nouveau num�ro de imputation et sous_imputation */

      p_tab_nom_de_compte_variable = p_tab_nom_de_compte;

      for ( i = 0 ; i < nb_comptes ; i++ )
	{
	  liste_tmp = LISTE_OPERATIONS;

	  while ( liste_tmp )
	    {
	      struct structure_operation *operation;

	      operation = liste_tmp -> data;

	      if ( operation -> imputation == imputation -> no_imputation )
		{
		  operation -> imputation = nouveau_no_imputation;
		  operation -> sous_imputation = nouveau_no_sous_imputation;
		}

	      liste_tmp = liste_tmp -> next;
	    }

	  p_tab_nom_de_compte_variable++;
	}

      /* fait le tour des �ch�ances pour mettre le nouveau num�ro de imputation et sous_imputation  */

      liste_tmp = gsliste_echeances;

      while ( liste_tmp )
	{
	  struct operation_echeance *echeance;

	  echeance = liste_tmp -> data;

	  if ( echeance -> imputation == imputation -> no_imputation )
	    {
	      echeance -> imputation = nouveau_no_imputation;
	      echeance -> sous_imputation = nouveau_no_sous_imputation;

	      if ( !echeance -> imputation )
		echeance -> compte_virement = -1;
	    }

	  liste_tmp = liste_tmp -> next;
	}


      demande_mise_a_jour_tous_comptes ();

      gnome_dialog_close ( GNOME_DIALOG ( dialog ) );

    }


  /* supprime dans la liste des imputation  */

  liste_struct_imputation = g_slist_remove ( liste_struct_imputation,
					     imputation );
  nb_enregistrements_imputations--;

  enleve_selection_ligne_imputation();

  mise_a_jour_imputation  ();
  remplit_arbre_imputation ();

  modification_fichier(TRUE);
}
/* **************************************************************************************************** */








/* **************************************************************************************************** */
void supprimer_sous_imputation ( void )
{
  struct struct_imputation *imputation;
  struct struct_sous_imputation *sous_imputation;
  GtkCTreeNode *node;
  gint i;
  gint ope_trouvee;



  node = GTK_CTREE_NODE ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data );

  sous_imputation = gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					     node );

  node = GTK_CTREE_ROW ( ( GTK_CLIST ( arbre_imputation ) -> selection ) -> data ) -> parent;

  imputation = gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					node );

  /* fait le tour des op�s pour en trouver une qui a cette sous-cat�gorie */

  p_tab_nom_de_compte_variable = p_tab_nom_de_compte;
  ope_trouvee = 0;

  for ( i=0 ; i<nb_comptes ; i++ )
    {
      GSList *liste_tmp;

      liste_tmp = LISTE_OPERATIONS;

      while ( liste_tmp )
	{
	  struct structure_operation *operation;

	  operation = liste_tmp -> data;

	  if ( operation -> imputation == imputation -> no_imputation
	       &&
	       operation -> sous_imputation == sous_imputation -> no_sous_imputation )
	    {
	      ope_trouvee = 1;
	      liste_tmp = NULL;
	      i = nb_comptes;
	    }
	  else
	    liste_tmp = liste_tmp -> next;
	}
      p_tab_nom_de_compte_variable++;
    }


  if ( ope_trouvee )
    {
      GtkWidget *dialog;
      GtkWidget *label;
      gint resultat;
      GtkWidget *separation;
      GtkWidget *hbox;
      GtkWidget *bouton_imputation_generique;
      GtkWidget *combofix;
      GSList *liste_combofix;
      GSList *pointeur;
      GSList *liste_tmp;
      GtkWidget *bouton_transfert;
      gint i;
      struct struct_imputation *nouvelle_imputation;
      struct struct_sous_imputation *nouvelle_sous_imputation;
      GSList *liste_imputation_credit;
      GSList *liste_imputation_debit;
      gchar **split_imputation;
      gint nouveau_no_imputation;
      gint nouveau_no_sous_imputation;

      dialog = gnome_dialog_new ( "Suppression d'une sous-imputation",
					    GNOME_STOCK_BUTTON_OK,
					    GNOME_STOCK_BUTTON_CANCEL,
					     NULL);
      gnome_dialog_set_parent ( GNOME_DIALOG ( dialog ),
				GTK_WINDOW ( window ));

      label = gtk_label_new ( "La sous-imputation s�lectionn�e contient encore des op�rations.\n\nVous pouvez : " );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   label,
			   FALSE,
			   FALSE,
			   0 );

      separation = gtk_hseparator_new ( );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   separation,
			   FALSE,
			   FALSE,
			   0 );

/*       mise en place du choix tranfert vers un autre sous imputation */
      
      hbox = gtk_hbox_new ( FALSE,
			    5 );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   hbox,
			   FALSE,
			   FALSE,
			   0 );

      bouton_transfert = gtk_radio_button_new_with_label ( NULL,
							   "Transf�rer les op�rations sur l'imputation : "  );
      gtk_box_pack_start ( GTK_BOX ( hbox ),
			   bouton_transfert,
			   FALSE,
			   FALSE,
			   0 );


      pointeur = liste_struct_imputation;
      liste_combofix = NULL;
      liste_imputation_credit = NULL;
      liste_imputation_debit = NULL;

      while ( pointeur )
	{
	  struct struct_imputation *imputation;
	  GSList *sous_pointeur;

	  imputation = pointeur -> data;

	  if ( imputation -> type_imputation )
	    liste_imputation_debit = g_slist_append ( liste_imputation_debit,
						 g_strdup ( imputation -> nom_imputation ) );
	  else
	    liste_imputation_credit = g_slist_append ( liste_imputation_credit,
						  g_strdup ( imputation -> nom_imputation ) );


	  sous_pointeur = imputation -> liste_sous_imputation;

	  while ( sous_pointeur )
	    {
	      struct struct_sous_imputation *sous_imputation;

	      sous_imputation = sous_pointeur -> data;

	      if ( sous_imputation -> no_sous_imputation !=  sous_imputation -> no_sous_imputation )
		{
		  if ( imputation -> type_imputation )
		    liste_imputation_debit = g_slist_append ( liste_imputation_debit,
							 g_strconcat ( "\t",
								       sous_imputation -> nom_sous_imputation,
								       NULL ) );
		  else
		    liste_imputation_credit = g_slist_append ( liste_imputation_credit,
							  g_strconcat ( "\t",
									sous_imputation -> nom_sous_imputation,
									NULL ) );
		}
	      sous_pointeur = sous_pointeur -> next;
	    }
	  pointeur = pointeur -> next;
	}

      /*   on ajoute les listes des cr�dits / d�bits � la liste du combofix du formulaire */

      liste_combofix = g_slist_append ( liste_combofix,
						   liste_imputation_debit );
      liste_combofix = g_slist_append ( liste_combofix,
						   liste_imputation_credit );


      combofix = gtk_combofix_new_complex ( liste_combofix,
					    TRUE,
					    TRUE,
					    TRUE );
      gtk_box_pack_start ( GTK_BOX ( hbox ),
			   combofix,
			   FALSE,
			   FALSE,
			   0 );

      /*       mise en place du choix supprimer le imputation */

      hbox = gtk_hbox_new ( FALSE,
			    5 );
      gtk_box_pack_start ( GTK_BOX ( GNOME_DIALOG ( dialog ) -> vbox ),
			   hbox,
			   FALSE,
			   FALSE,
			   0 );

      bouton_imputation_generique = gtk_radio_button_new_with_label ( gtk_radio_button_group ( GTK_RADIO_BUTTON ( bouton_transfert )),
											  " Supprimer simplement cette sous-imputation." );
      gtk_box_pack_start ( GTK_BOX ( hbox ),
			   bouton_imputation_generique,
			   FALSE,
			   FALSE,
			   0 );

      gtk_widget_show_all ( dialog );


    retour_dialogue:
      resultat = gnome_dialog_run ( GNOME_DIALOG ( dialog ) );

      if ( resultat )
	{
	  if ( resultat == 1 )
	    gnome_dialog_close ( GNOME_DIALOG ( dialog ) );
	  return;
	}


      if ( gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( bouton_transfert )) )
	{

	  if ( !strlen (gtk_combofix_get_text ( GTK_COMBOFIX ( combofix ))))
	    {
	      dialogue ( "Veuillez entrer une imputation !" );
	      goto retour_dialogue;
	    }

	  /* r�cup�re les no de imputation et sous imputation */

	  split_imputation = g_strsplit ( gtk_combofix_get_text ( GTK_COMBOFIX ( combofix )),
				     " : ",
				     2 );

	  nouvelle_imputation = g_slist_find_custom ( liste_struct_imputation,
						split_imputation[0],
						(GCompareFunc) recherche_imputation_par_nom ) -> data;
	  nouveau_no_imputation = nouvelle_imputation -> no_imputation;

	  if ( split_imputation[1] )
	    {
	      nouvelle_sous_imputation = g_slist_find_custom ( nouvelle_imputation -> liste_sous_imputation,
							  split_imputation[1],
							  (GCompareFunc) recherche_sous_imputation_par_nom ) -> data;
	      nouveau_no_sous_imputation = nouvelle_sous_imputation -> no_sous_imputation;
	    }
	  else
	    nouveau_no_sous_imputation = 0;

	  g_strfreev ( split_imputation );
	}
      else
	{
	  nouveau_no_imputation = 0;
	  nouveau_no_sous_imputation = 0;
	}


      /* on fait le tour des op�s pour mettre le nouveau num�ro de imputation et sous_imputation */

      p_tab_nom_de_compte_variable = p_tab_nom_de_compte;

      for ( i = 0 ; i < nb_comptes ; i++ )
	{
	  liste_tmp = LISTE_OPERATIONS;

	  while ( liste_tmp )
	    {
	      struct structure_operation *operation;

	      operation = liste_tmp -> data;

	      if ( operation -> imputation == imputation -> no_imputation
		   &&
		   operation -> sous_imputation == sous_imputation -> no_sous_imputation )
		{
		  operation -> imputation = nouveau_no_imputation;
		  operation -> sous_imputation = nouveau_no_sous_imputation;
		}

	      liste_tmp = liste_tmp -> next;
	    }

	  p_tab_nom_de_compte_variable++;
	}

      /* fait le tour des �ch�ances pour mettre le nouveau num�ro de imputation et sous_imputation  */

      liste_tmp = gsliste_echeances;

      while ( liste_tmp )
	{
	  struct operation_echeance *echeance;

	  echeance = liste_tmp -> data;

	  if ( echeance -> imputation == imputation -> no_imputation
	       &&
	       echeance -> sous_imputation == sous_imputation -> no_sous_imputation )
	    {
	      echeance -> imputation = nouveau_no_imputation;
	      echeance -> sous_imputation = nouveau_no_sous_imputation;

	      if ( !echeance -> imputation )
		echeance -> compte_virement = -1;
	    }

	  liste_tmp = liste_tmp -> next;
	}


      demande_mise_a_jour_tous_comptes ();

      gnome_dialog_close ( GNOME_DIALOG ( dialog ) );

    }


  /* supprime dans la liste des imputation  */

  imputation -> liste_sous_imputation = g_slist_remove ( imputation -> liste_sous_imputation,
					       sous_imputation );


  enleve_selection_ligne_imputation();

  mise_a_jour_imputation  ();
  remplit_arbre_imputation ();

  modification_fichier(TRUE);
}
/* **************************************************************************************************** */




/***********************************************************************************************************/
/* Routine creation_liste_imputations */
/* appel�e lors d'un nouveau fichier */
/* cr�e la liste des cat�gories � partir de la liste ci dessus */
/* en fait, merge la liste de base avec rien */
/***********************************************************************************************************/

void creation_liste_imputations ( void )
{

  liste_struct_imputation = NULL;
  nb_enregistrements_imputations = 0;
  no_derniere_imputation = 0;
}
/***********************************************************************************************************/





/***********************************************************************************************************/
/*  Routine qui cr�e la liste des cat�gories pour les combofix du formulaire et de la ventilation */
/* c'est � dire 3 listes dans 1 liste : */
/* la premi�re contient les cat�gories de d�bit */
/* la seconde contient les cat�gories de cr�dit */
/* la troisi�me contient les cat�gories sp�ciales ( virement, retrait, ventilation ) */
/* la ventilation n'apparait pas dans les �ch�ances ( et dans la ventilation ) */
/***********************************************************************************************************/

void creation_liste_imputation_combofix ( void )
{
  GSList *pointeur;
  GSList *liste_imputation_credit;
  GSList *liste_imputation_debit;

  liste_imputations_combofix = NULL;
  liste_imputation_credit = NULL;
  liste_imputation_debit = NULL;


  pointeur = liste_struct_imputation;

  while ( pointeur )
    {
      struct struct_imputation *imputation;
      GSList *sous_pointeur;

      imputation = pointeur -> data;

      if ( imputation -> type_imputation )
	liste_imputation_debit = g_slist_append ( liste_imputation_debit,
						  g_strdup ( imputation -> nom_imputation ) );
      else
	liste_imputation_credit = g_slist_append ( liste_imputation_credit,
						   g_strdup ( imputation -> nom_imputation ) );

      sous_pointeur = imputation -> liste_sous_imputation;

      while ( sous_pointeur )
	{
	  struct struct_sous_imputation *sous_imputation;

	  sous_imputation = sous_pointeur -> data;

	  if ( imputation -> type_imputation )
	    liste_imputation_debit = g_slist_append ( liste_imputation_debit,
						      g_strconcat ( "\t",
								    sous_imputation -> nom_sous_imputation,
								    NULL ) );
	  else
	    liste_imputation_credit = g_slist_append ( liste_imputation_credit,
						       g_strconcat ( "\t",
								     sous_imputation -> nom_sous_imputation,
								     NULL ) );
	  sous_pointeur = sous_pointeur -> next;
	}
      pointeur = pointeur -> next;
    }


/*   on ajoute les listes des cr�dits / d�bits � la liste du combofix du formulaire */

  liste_imputations_combofix = g_slist_append ( liste_imputations_combofix,
					       liste_imputation_debit );
  liste_imputations_combofix = g_slist_append ( liste_imputations_combofix,
					       liste_imputation_credit );
}
/***********************************************************************************************************/




/***********************************************************************************************************/
/* Fonction mise_a_jour_imputation */
/* recr�e les listes de cat�gories des combofix */
/* et remet les combofix � jour */
/***********************************************************************************************************/

void mise_a_jour_imputation ( void )
{
  creation_liste_imputation_combofix ();

  gtk_combofix_set_list ( GTK_COMBOFIX ( widget_formulaire_operations[12] ),
			  liste_imputations_combofix,
			  TRUE,
			  TRUE );

  gtk_combofix_set_list ( GTK_COMBOFIX ( widget_formulaire_ventilation[3] ),
			  liste_imputations_combofix,
			  TRUE,
			  TRUE );

  gtk_combofix_set_list ( GTK_COMBOFIX ( widget_formulaire_echeancier[10] ),
			  liste_imputations_combofix,
			  TRUE,
			  TRUE );

  modif_imputation = 1;
}
/***********************************************************************************************************/





/***********************************************************************************************************/
/* Fonction ajoute_nouvelle_imputation */
/* appel�e pour ajouter une nouvelle cat�g � la liste des cat�g */
/* entr�e : la nouvelle cat�g */
/* retour : l'adr de la struct */
/***********************************************************************************************************/

struct struct_imputation *ajoute_nouvelle_imputation ( gchar *imputation )
{
  struct struct_imputation *nouvelle_imputation;

  nouvelle_imputation = calloc ( 1,
				 sizeof ( struct struct_imputation ));

  nouvelle_imputation -> no_imputation = ++no_derniere_imputation;
  nouvelle_imputation -> nom_imputation = g_strdup ( g_strstrip ( imputation ));

  liste_struct_imputation = g_slist_append ( liste_struct_imputation,
					     nouvelle_imputation );
  nb_enregistrements_imputations++;

  return ( nouvelle_imputation );
}
/***********************************************************************************************************/




/***********************************************************************************************************/
/* Fonction ajoute_nouvelle_sous_imputation */
/* appel�e pour ajouter une nouvelle sous cat�g � une cat�g */
/* entr�e : la nouvelle sous cat�g et l'adr de la struct de la cat�g correspondante */
/* retour : l'adr de la struct */
/***********************************************************************************************************/

struct struct_sous_imputation *ajoute_nouvelle_sous_imputation ( gchar *sous_imputation,
								 struct struct_imputation *imputation )
{
  struct struct_sous_imputation *nouvelle_sous_imputation;

  nouvelle_sous_imputation = malloc ( sizeof ( struct struct_sous_imputation ));

  nouvelle_sous_imputation -> no_sous_imputation = ++( imputation->no_derniere_sous_imputation );
  nouvelle_sous_imputation -> nom_sous_imputation = g_strdup ( g_strstrip ( sous_imputation ));

  imputation -> liste_sous_imputation = g_slist_append ( imputation -> liste_sous_imputation,
							 nouvelle_sous_imputation );

  return ( nouvelle_sous_imputation );
}
/***********************************************************************************************************/




/***********************************************************************************************************/
/* Fonction recherche_imputation_par_nom */
/***********************************************************************************************************/

gint recherche_imputation_par_nom ( struct struct_imputation *imputation,
				    gchar *nom_imputation )
{
  return ( g_strcasecmp ( imputation -> nom_imputation,
			  nom_imputation ) );
}
/***********************************************************************************************************/


/***********************************************************************************************************/
/* Fonction recherche_sous_imputation_par_nom */
/***********************************************************************************************************/

gint recherche_sous_imputation_par_nom ( struct struct_sous_imputation *sous_imputation,
					gchar *nom_sous_imputation )
{
  return ( g_strcasecmp ( sous_imputation -> nom_sous_imputation,
			  nom_sous_imputation ) );
}
/***********************************************************************************************************/



/***************************************************************************************************/
/* Fonction  recherche_imputation_par_no */
/* appel�e par un g_slist_find_custom */
/* donne en arg la struct du tiers et le no du tiers recherch� */
/***************************************************************************************************/
  
gint recherche_imputation_par_no ( struct struct_imputation *imputation,
				   gint *no_imputation )
{
  return (  imputation ->  no_imputation != GPOINTER_TO_INT ( no_imputation ) );
}
/***************************************************************************************************/


/***************************************************************************************************/
/* Fonction  recherche_imputation_par_no */
/* appel�e par un g_slist_find_custom */
/* donne en arg la struct du tiers et le no du tiers recherch� */
/***************************************************************************************************/
  
gint recherche_sous_imputation_par_no ( struct struct_sous_imputation *sous_imputation,
					gint *no_sous_imputation )
{
  return (  sous_imputation ->  no_sous_imputation != GPOINTER_TO_INT ( no_sous_imputation ) );
}
/***************************************************************************************************/



/***************************************************************************************************/
void fusion_categories_imputation ( void )
{
  /* on fait le tour des cat�gories et on ajoute aux imputations celles qui n'existent pas */

  GSList *liste_tmp;

  if ( !question ( "Attention, cette op�ration va ajouter aux Imputations Budg�taires les cat�gories\net sous-cat�gories qui ne s'y trouvent pas.\nDe plus, cette op�ration est irr�versible (pas d'annulation)\n�tes-vous s�r de continuer ?" ))
       return;

  liste_tmp = liste_struct_categories;

  while ( liste_tmp )
    {
      struct struct_categ *categorie;
      struct struct_imputation *imputation;
      GSList *result;
      GSList *liste_sous_tmp;

      categorie = liste_tmp -> data;

      /* v�rifie si une imputation du nom de la cat�gorie existe */

      result = g_slist_find_custom ( liste_struct_imputation,
				     categorie -> nom_categ,
				     (GCompareFunc) recherche_imputation_par_nom );

      if ( result )
	/* l'imputation existe, on la r�cup�re */
	imputation = result -> data;
      else
	{
	  /* 	  l'imputation n'existe pas, on la cr�e */

	  imputation = ajoute_nouvelle_imputation ( categorie -> nom_categ );
	  imputation -> type_imputation = categorie -> type_categ;
	}

      /* on fait maintenant la comparaison avec les sous cat�g et les sous imputations */

      liste_sous_tmp = categorie -> liste_sous_categ;

      while ( liste_sous_tmp )
	{
	  struct struct_sous_categ *sous_categ;

	  sous_categ = liste_sous_tmp -> data;

	  result = g_slist_find_custom ( imputation -> liste_sous_imputation,
					 sous_categ -> nom_sous_categ,
					 (GCompareFunc) recherche_sous_imputation_par_nom );

	  if ( !result )
	      /* 	  la sous imputation n'existe pas, on la cr�e */
	      ajoute_nouvelle_sous_imputation ( sous_categ -> nom_sous_categ,
						imputation );

	  liste_sous_tmp = liste_sous_tmp -> next;
	}
      liste_tmp = liste_tmp -> next;
    }

  /* on met � jour les listes */

  mise_a_jour_imputation ();
  remplit_arbre_imputation ();

  modification_fichier(TRUE);
}
/***************************************************************************************************/




/* **************************************************************************************************** */
/* cr�e un tableau de imputation et de sous imputation aussi gds que le nb de tiers */
/* et les renvoie dans un tab de 2 pointeurs */
/* **************************************************************************************************** */

void calcule_total_montant_imputation ( void )
{
  gint i;
  struct struct_devise *devise_compte;

  /* on cr�e les tableaux de montant */

  /* le +1 pour reserver le [0] pour aucune cat�gorie */

  tab_montant_imputation = calloc ( nb_enregistrements_imputations + 1,
			       sizeof ( gfloat ));
  nb_ecritures_par_imputation = calloc ( nb_enregistrements_imputations + 1,
				    sizeof ( gint ));

  tab_montant_sous_imputation = calloc ( nb_enregistrements_imputations,
				    sizeof ( gpointer ));
  nb_ecritures_par_sous_imputation = calloc ( nb_enregistrements_imputations,
					 sizeof ( gpointer ));

  /*   la devise par d�faut a �t� choisie dans les param�tres */

  p_tab_nom_de_compte_variable = p_tab_nom_de_compte;

  devise_compte = g_slist_find_custom ( liste_struct_devises,
					GINT_TO_POINTER ( no_devise_totaux_tiers ),
					( GCompareFunc ) recherche_devise_par_no) -> data;

  for ( i=0 ; i<nb_comptes ; i++ )
    {
      GSList *liste_tmp;

      p_tab_nom_de_compte_variable = p_tab_nom_de_compte + i;

      liste_tmp = LISTE_OPERATIONS;

      while ( liste_tmp )
	{
	  struct structure_operation *operation;
	  struct struct_devise *devise_operation;
	  gdouble montant;
	  gint place_imputation;


	  operation = liste_tmp -> data;

	  /* on commence par calculer le montant dans la devise demand�e */

	  if ( operation -> devise == devise_compte -> no_devise )
	    montant = operation -> montant;
	  else
	    {
	      /* ce n'est pas la devise par d�faut */
	      /* si le compte passe � l'euro et que la devise est l'euro, utilise la conversion du compte, */
	      /* si c'est une devise qui passe � l'euro et que la devise du compte est l'euro, utilise la conversion du compte */
	      /* sinon utilise la conversion stock�e dans l'op� */

	      devise_operation = g_slist_find_custom ( liste_struct_devises,
						       GINT_TO_POINTER ( operation -> devise ),
						       ( GCompareFunc ) recherche_devise_par_no ) -> data;

	      if ( devise_compte -> passage_euro
		   &&
		   !strcmp ( devise_operation -> nom_devise, "Euro" ) )
		montant = operation -> montant * devise_compte -> change;
	      else
		if ( devise_operation -> passage_euro
		     &&
		     !strcmp ( devise_compte -> nom_devise, "Euro" ))
		  montant = operation -> montant / devise_operation -> change;
		else
		  if ( operation -> une_devise_compte_egale_x_devise_ope )
		    montant = operation -> montant / operation -> taux_change - operation -> frais_change;
		  else
		    montant = operation -> montant * operation -> taux_change - operation -> frais_change;

	      montant = ( rint (montant * 100 )) / 100;
	    }

	  /* on traite ensuite l'op�ration */
	
	  if ( operation -> imputation )
	    {
	      struct struct_imputation *imputation;

	      /* il y a une cat�gorie */

	      imputation = g_slist_find_custom ( liste_struct_imputation,
						GINT_TO_POINTER ( operation -> imputation ),
						(GCompareFunc) recherche_imputation_par_no ) -> data;

	      /* recherche la place du tiers dans la liste */

	      place_imputation = g_slist_index ( liste_struct_imputation,
					    imputation );

	      /* cr�e la place pour les sous cat�g de cette imputation si ce n'est d�j� fait */

	      if ( !tab_montant_sous_imputation[place_imputation] )
		{
		  gint nb_sous_imputation;

		  nb_sous_imputation = g_slist_length ( imputation -> liste_sous_imputation );

		  /* on r�serve nb_sous_imputation + 1 pour aucune sous imputation qui sera en [0] */

		  tab_montant_sous_imputation[place_imputation] = calloc ( nb_sous_imputation + 1,
								 sizeof ( float ));
		  nb_ecritures_par_sous_imputation[place_imputation] = calloc ( nb_sous_imputation + 1,
								      sizeof ( gint ));
		}

	      tab_montant_imputation[place_imputation+1] = tab_montant_imputation[place_imputation+1] + montant;
	      nb_ecritures_par_imputation[place_imputation+1]++;

	      /* on ajoute maintenant le montant � la sous imputation si elle existe */

	      if ( operation -> sous_imputation )
		{
		  gint place_sous_imputation;

		  place_sous_imputation = g_slist_position ( imputation -> liste_sous_imputation,
							g_slist_find_custom ( imputation -> liste_sous_imputation,
									      GINT_TO_POINTER ( operation -> sous_imputation ),
									      (GCompareFunc) recherche_sous_imputation_par_no ));
		  tab_montant_sous_imputation[place_imputation][place_sous_imputation+1] = tab_montant_sous_imputation[place_imputation][place_sous_imputation+1] + montant;
		  nb_ecritures_par_sous_imputation[place_imputation][place_sous_imputation+1]++;
		}
	      else
		{
		  if ( tab_montant_sous_imputation[place_imputation] )
		    {
		      tab_montant_sous_imputation[place_imputation][0] = tab_montant_sous_imputation[place_imputation][0] + montant;
		      nb_ecritures_par_sous_imputation[place_imputation][0]++;
		    }
		}
	    }
	  else
	      /* il n'y a pas d'imputation */
	      /* on met le montant dans tab_montant_imputation[0} si ce n'est une ventil */
	    if ( !operation -> operation_ventilee )
	      {
		tab_montant_imputation[0] = tab_montant_imputation[0] + montant;
		nb_ecritures_par_imputation[0]++;
	      }
	  liste_tmp = liste_tmp -> next;
	}
    }
}
/* **************************************************************************************************** */




/* **************************************************************************************************** */
gchar *calcule_total_montant_imputation_par_compte ( gint imputation,
						     gint sous_imputation,
						     gint no_compte )
{
  gdouble retour_int;
  struct struct_devise *devise_compte;
  GSList *liste_tmp;

  retour_int = 0;
  nb_ecritures_par_comptes = 0;

  p_tab_nom_de_compte_variable = p_tab_nom_de_compte + no_compte;

  devise_compte = g_slist_find_custom ( liste_struct_devises,
					GINT_TO_POINTER ( no_devise_totaux_tiers ),
					( GCompareFunc ) recherche_devise_par_no) -> data;

  liste_tmp = LISTE_OPERATIONS;


  while ( liste_tmp )
    {
      struct structure_operation *operation;

      operation = liste_tmp -> data;

      if ( operation -> imputation == imputation
	   &&
	   operation -> sous_imputation == sous_imputation
	   &&
	   !operation -> operation_ventilee   )
	{
	  struct struct_devise *devise_operation;
	  gdouble montant;

	  if ( operation -> devise == devise_compte -> no_devise )
	    montant = operation -> montant;
	  else
	    {
	      /* ce n'est pas la devise du compte, si le compte passe � l'euro et que la devise est l'euro, utilise la conversion du compte, */
	      /* si c'est une devise qui passe � l'euro et que la devise du compte est l'euro, utilise la conversion du compte */
	      /* sinon utilise la conversion stock�e dans l'op� */

	      devise_operation = g_slist_find_custom ( liste_struct_devises,
						       GINT_TO_POINTER ( operation -> devise ),
						       ( GCompareFunc ) recherche_devise_par_no ) -> data;

	      if ( devise_compte -> passage_euro
		   &&
		   !strcmp ( devise_operation -> nom_devise, "Euro" ) )
		montant = operation -> montant * devise_compte -> change;
	      else
		if ( devise_operation -> passage_euro
		     &&
		     !strcmp ( devise_compte -> nom_devise, "Euro" ))
		  montant = operation -> montant / devise_operation -> change;
		else
		  if ( operation -> une_devise_compte_egale_x_devise_ope )
		    montant = operation -> montant / operation -> taux_change - operation -> frais_change;
		  else
		    montant = operation -> montant * operation -> taux_change - operation -> frais_change;

	      montant = ( rint (montant * 100 )) / 100;
	    }

	  retour_int = retour_int + montant;
	  nb_ecritures_par_comptes++;
	}
      liste_tmp = liste_tmp -> next;
    }

  if ( retour_int )
    return ( g_strdup_printf ( "%4.2f %s",
			       retour_int,
			       devise_compte -> code_devise ));
  else
    return ( NULL );
}
/* **************************************************************************************************** */


/* **************************************************************************************************** */
void appui_sur_ajout_imputation ( void )
{
  gchar *nom_imputation;
  struct struct_imputation *nouvelle_imputation;
  gchar *text[4];
  GtkCTreeNode *ligne;

  if ( !( nom_imputation = demande_texte ( "Nouvelle imputation",
					   "Entrer le nom de la nouvelle imputation :" )))
    return;

  /* on l'ajoute � la liste des op�s */
  
  nouvelle_imputation = ajoute_nouvelle_imputation ( nom_imputation );


  /* on l'ajoute directement au ctree et on fait le tri pour �viter de toute la r�afficher */

  text[0] = nouvelle_imputation -> nom_imputation;
  text[1] = NULL;
  text[2] = NULL;
  text[3] = NULL;

  ligne = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
				  NULL,
				  NULL,
				  text,
				  10,
				  pixmap_ouvre,
				  masque_ouvre,
				  pixmap_ferme,
				  masque_ferme,
				  FALSE,
				  FALSE );

  /* on associe � ce imputation � l'adr de sa struct */

  gtk_ctree_node_set_row_data ( GTK_CTREE ( arbre_imputation ),
				ligne,
				nouvelle_imputation );

  gtk_ctree_sort_recursive ( GTK_CTREE ( arbre_imputation ),
			     NULL );

  mise_a_jour_imputation();
  modif_imputation = 0;
  modification_fichier(TRUE);
}
/* **************************************************************************************************** */



/* **************************************************************************************************** */
void appui_sur_ajout_sous_imputation ( void )
{
  gchar *nom_sous_imputation;
  struct struct_sous_imputation *nouvelle_sous_imputation;
  struct struct_imputation *imputation;
  gchar *text[4];
  GtkCTreeNode *ligne;
  GtkCTreeNode *node_parent;

  if ( !( nom_sous_imputation = demande_texte ( "Nouvelle sous-imputation",
						"Entrer le nom de la nouvelle sous-imputation :" )))
    return;

  /* r�cup�re le node parent */

  node_parent = GTK_CLIST ( arbre_imputation ) -> selection -> data;

  while ( GTK_CTREE_ROW ( node_parent ) -> level != 1 )
    node_parent = GTK_CTREE_ROW ( node_parent ) -> parent;

  /* on r�cup�re l'imputation parente */

  imputation = gtk_ctree_node_get_row_data ( GTK_CTREE ( arbre_imputation ),
					     node_parent );

  /* on l'ajoute � la liste des op�s */
  
  nouvelle_sous_imputation = ajoute_nouvelle_sous_imputation ( nom_sous_imputation,
							       imputation );


  /* on l'ajoute directement au ctree et on fait le tri pour �viter de toute la r�afficher */

  text[0] = nouvelle_sous_imputation -> nom_sous_imputation;
  text[1] = NULL;
  text[2] = NULL;
  text[3] = NULL;

  ligne = gtk_ctree_insert_node ( GTK_CTREE ( arbre_imputation ),
				  node_parent,
				  NULL,
				  text,
				  10,
				  NULL,
				  NULL,
				  NULL,
				  NULL,
				  FALSE,
				  FALSE );

  /* on associe � ce imputation � l'adr de sa struct */

  gtk_ctree_node_set_row_data ( GTK_CTREE ( arbre_imputation ),
				ligne,
				nouvelle_sous_imputation );

  gtk_ctree_sort_recursive ( GTK_CTREE ( arbre_imputation ),
			     NULL );


  mise_a_jour_imputation();
  modif_imputation = 0;
  modification_fichier(TRUE);
}
/* **************************************************************************************************** */
