#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>

void on_clicked_button(GtkWidget *pButton, gpointer data);

int main(int argc, char **argv)
{
	/* Declaration des widgets */
    	GtkWidget *pWindow;
    	GtkWidget *pVBox;
    	GtkWidget *pFrame;
    	GtkWidget *pVBoxFrame;
    	GtkWidget *pSeparator;
    	GtkWidget *pEntry1;
	GtkWidget *pEntry2;
    	GtkWidget *pButton;
	GtkWidget *pLabel;

    	gtk_init(&argc, &argv);

    	/* Creation de la fenetre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/* On ajoute un espace de 5 sur les bords de la fenetre */
    	gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
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
    	pEntry1 = gtk_entry_new();
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry1, TRUE, FALSE, 0);
    	pLabel = gtk_label_new("N° de port :");
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    	pEntry2 = gtk_entry_new();
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry2, TRUE, FALSE, 0);

    	/* Creation d un GtkHSeparator */
    	pSeparator = gtk_hseparator_new();
    	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSeparator, TRUE, FALSE, 0);
	
	/* Creation du bouton avec un label*/
    	pButton = gtk_button_new_with_label("Connexion");
    	gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);

    	/* Connexion du signal "clicked" du GtkButton */
    	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(on_clicked_button), (GtkWidget*) pEntry1);
	
	/* Affichage de la fenetre et de tout ce qu'elle contient */
    	gtk_widget_show_all(pWindow);
	
	/* Demarrage de la boucle evenementielle */
    	gtk_main();

    	return EXIT_SUCCESS;
}

void on_clicked_button(GtkWidget *pButton, gpointer data)
{
	const gchar *adresse;
	printf("coucou\n");
	/*const char *port;*/
	/* Recuperation du texte contenu dans le GtkEntry */
    	adresse = gtk_entry_get_text(GTK_ENTRY((GtkWidget*)data));
    launch(adresse);
}

