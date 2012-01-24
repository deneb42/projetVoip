#include <stdlib.h>
#include <gtk/gtk.h>


void on_clicked_button_connection(GtkWidget *pButton, gpointer data);
void on_clicked_button_disconnection(GtkWidget *pButton, gpointer data);

int main(int argc, char **argv)
{
	/* Declaration des widgets */
    	GtkWidget *pWindow;
    	GtkWidget *pVBox;
    	GtkWidget *pFrame;
    	GtkWidget *pVBoxFrame;
    	GtkWidget *pSeparator;
    	GtkWidget *pEntry;
	GtkWidget *pButton;
	GtkWidget *pLabel;
	GtkWidget *pImage;

    	gtk_init(&argc, &argv);

	/*Chargement des parametres d arriere plan */
	gtk_rc_parse("./window.rc");

    	/* Creation de la fenetre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/* On ajoute un espace de 5 sur les bords de la fenetre */
    	gtk_container_set_border_width(GTK_CONTAINER(pWindow), 3);
	/* Definition de la position */
 	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
	/* Titre de la fenetre */
	gtk_window_set_title(GTK_WINDOW(pWindow), "VoIP");
	/* Definition de la taille de la fenetre */
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 240);
	
	/* Connexion du signal "destroy" de la fenetre */
	/* On appelle directement la fonction de sortie de boucle */
    	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    	/* Creation de la GtkBox verticale */
    	pVBox = gtk_vbox_new(TRUE, 0);

	/* Chargement d'une image a partir d'un fichier */
    	pImage = gtk_image_new_from_file("../img/voip.png");
    	gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE, 0);

    	/* Ajout de la GtkVBox dans la fenetre */
    	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    	/* Creation du premier GtkFrame */
    	pFrame = gtk_frame_new("Serveur");
    	gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, TRUE, 0);

    	/* Creation et insertion d une boite pour le premier GtkFrame */
    	pVBoxFrame = gtk_vbox_new(TRUE, 0);
    	gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);

    	/* Creation et insertion des elements contenus dans le premier GtkFrame */
    	pLabel = gtk_label_new("Adresse :");
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, TRUE, 0);
    	pEntry = gtk_entry_new();
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
    	pLabel = gtk_label_new("N° de port :");
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    	pEntry = gtk_entry_new();
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);

    	/* Creation d un GtkHSeparator */
    	pSeparator = gtk_hseparator_new();
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSeparator, TRUE, FALSE, 0);

	pImage = gtk_image_new_from_file("../img/phone.gif");
    	gtk_box_pack_start(GTK_BOX(pVBox), pImage, TRUE, TRUE, 0);
	
	/* Creation du bouton avec un label pour se connecter */
    	pButton = gtk_button_new_with_label("Connexion");
    	gtk_box_pack_start(GTK_BOX(pVBox), pButton, FALSE, FALSE, 0);
	
    	/* Connexion du signal "clicked" du GtkButton */
    	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(on_clicked_button_connection), (GtkWidget*) pVBoxFrame);

	/* Creation du bouton avec un label pour se deconnecter */
	pButton = gtk_button_new_with_label("Déconnexion");
    	gtk_box_pack_start(GTK_BOX(pVBox), pButton, FALSE, FALSE, 0);

	/* Connexion du signal "clicked" du GtkButton */
    	/*g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(on_clicked_button_disconnection), (GtkWidget*) pWindow);*/
	
	/* Affichage de la fenetre et de tout ce qu'elle contient */
    	gtk_widget_show_all(pWindow);
	
	/* Demarrage de la boucle evenementielle */
    	gtk_main();

    	return EXIT_SUCCESS;
}

void on_clicked_button_connection(GtkWidget *pButton, gpointer data)
{
	GtkWidget *pTempEntry;
    	GList *pList;
	const gchar *adress;
	const gchar *port;
	
	/*port="25555";
	adress="localhost"*/
	
    	/* Recuperation de la liste des elements que contient la GtkVBox */
    	pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));

    	/* Le premier element est le GtkLabel "Adresse:" */
    	/* Passage a l element suivant : le GtkEntry */
    	pList = g_list_next(pList);
    	pTempEntry = GTK_WIDGET(pList->data);
	
	/* Mets le texte contenu dans le 1er GtkEntry à "localhost" */
	gtk_entry_set_text(GTK_ENTRY(pTempEntry),"localhost");

    	/* Recuperation du texte contenu dans le 1er GtkEntry */
    	adress = gtk_entry_get_text(GTK_ENTRY(pTempEntry));

	/* Passage a l element suivant : le GtkLabel "N° de port :" */
    	pList = g_list_next(pList);

	/* Passage a l element suivant : le GtkEntry */
    	pList = g_list_next(pList);
	pTempEntry = GTK_WIDGET(pList->data);
	
	/* Mets le texte contenu dans le 2e GtkEntry à "25555" */
	gtk_entry_set_text(GTK_ENTRY(pTempEntry),"25555");

	/* Recuperation du texte contenu dans le 2e GtkEntry */
    	port = gtk_entry_get_text(GTK_ENTRY(pTempEntry));

	printf("coucou\n");

	/*Appel de la fonction principale */
    	launch(adress, port);

	/* Liberation de la memoire utilisee par la liste */
    	g_list_free(pList);
}

/*void on_clicked_button_disconnection(GtkWidget *pButton, gpointer data)
{	
}*/

