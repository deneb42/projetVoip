#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "utils.h"
#include "son.h"

#include <netdb.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>

void on_clicked_button_connect(GtkWidget *pButton, s_par_gtk * param_g);
void on_clicked_button_deconnect(GtkWidget *pButton, s_par_gtk * param_g);
void quit_callback(GtkWidget *pButton, s_par_gtk * param_g);

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


	s_par_gtk param_g;

	gtk_init(&argc, &argv);

	param_g.statut = 0;
	
	/*Chargement des parametres d arriere plan */
	#ifdef CLIENT
		gtk_rc_parse("../data/window_c.rc");
	#endif
	#ifdef SERVEUR
		gtk_rc_parse("../data/window_s.rc");	
	#endif
	

	/* Creation de la fenetre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/* On ajoute un espace de 3 sur les bords de la fenetre */

	gtk_container_set_border_width(GTK_CONTAINER(pWindow), 3);
	param_g.widget = pWindow;

	
	/* Definition de la position */
	gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
	/* Titre de la fenetre */
	gtk_window_set_title(GTK_WINDOW(pWindow), "VoIP");
	/* Definition de la taille de la fenetre */
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 450);

	/* Connexion du signal "destroy" de la fenetre */
	/* On appelle directement la fonction de sortie de boucle */
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(quit_callback), &param_g);


	/* Creation de la GtkBox verticale */
	pVBox = gtk_vbox_new(FALSE, 0);
	//param_g.widget = pVBox;

	/* Ajout de la GtkVBox dans la fenetre */
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/* Chargement d'une image a partir d'un fichier */
	pImage = gtk_image_new_from_file("../data/voip.png");
	gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE, 0);


	/* Creation du premier GtkFrame */
	#ifdef CLIENT
		pFrame = gtk_frame_new("Client");
	#endif
	#ifdef SERVEUR
		pFrame = gtk_frame_new("Serveur");	
	#endif
	gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, TRUE, 0);

	/* Creation et insertion d une boite pour le premier GtkFrame */
	pVBoxFrame = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);

	/* Creation et insertion des elements contenus dans le premier GtkFrame */
	pLabel = gtk_label_new("Adresse :");
	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
	pEntry = gtk_entry_new();
	/* Mets le texte contenu dans le 1er GtkEntry à "localhost" */
	#ifdef CLIENT
		gtk_entry_set_text(GTK_ENTRY(pEntry),"localhost");
	#endif
	#ifdef SERVEUR
		gtk_entry_set_text(GTK_ENTRY(pEntry),"0.0.0.0");
	#endif
	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
	
	pLabel = gtk_label_new("N° de port :");
	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
	pEntry = gtk_entry_new();
	
	/* Mets le texte contenu dans le 2e GtkEntry à "25555" */
	gtk_entry_set_text(GTK_ENTRY(pEntry),"25555");
	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);

	/* Creation d un GtkHSeparator */
	pSeparator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSeparator, TRUE, FALSE, 0);

	/* Creation du label */
	pLabel = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, TRUE, 0);

	pImage = gtk_image_new();
	gtk_box_pack_start(GTK_BOX(pVBox), pImage, TRUE, TRUE, 0);

	
	

	/* Creation du bouton avec un label pour se connecter */
	pButton = gtk_button_new_with_label("Connexion");
	gtk_box_pack_start(GTK_BOX(pVBox), pButton, FALSE, FALSE, 0);
			
	/* Connexion du signal "clicked" du GtkButton */
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(on_clicked_button_connect), &param_g);

	/*#ifdef SERVEUR
		pButton = gtk_button_new();
		gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);

		pButton = gtk_button_new();
		gtk_box_pack_start(GTK_BOX(pVBox), pButton, FALSE, FALSE, 0);
	#endif*/


	/* Creation du bouton avec un label pour se déconnecter */
    	pButton = gtk_button_new_with_label("Déconnexion");
    	gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);

    	/* Connexion du signal "clicked" du GtkButton */
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(on_clicked_button_deconnect), &param_g);
    
	
	/* Affichage de la fenetre et de tout ce qu'elle contient */
    	gtk_widget_show_all(pWindow);
	
	/* Demarrage de la boucle evenementielle */
    	gtk_main();

    	return EXIT_SUCCESS;
}


void on_clicked_button_deconnect(GtkWidget *pButton, s_par_gtk * param_g)
{
	if(param_g->statut == 1)
	{
		pthread_cancel(param_g->threads[CAPTURE]);
		closeSon(CAPTURE);
		pthread_cancel(param_g->threads[PLAYBACK]);
		closeSon(PLAYBACK);
		param_g->statut = 0;
	}
}

void quit_callback(GtkWidget *pButton, s_par_gtk * param_g)
{
	on_clicked_button_deconnect(pButton, param_g);
	gtk_main_quit();
}


void on_clicked_button_connect(GtkWidget *pButton, s_par_gtk * param_g)
{
	GtkWidget *pTempEntry;
	//GtkWidget *pEntry;
	GtkWidget *pTempImage;
	GtkWidget *pTempLabel;
	GList *pList;
	const gchar *adress;
	const gchar *port;
	GtkWidget *pQuestion;
	GtkWidget *pAbout;
   	//int ind;
	//GString* pString = g_string_new(NULL);
	
    

	if(param_g->statut == 0)
	{	
		/* Creation de la 1ere boite de message pQuestion */
    		/* Type : Question -> GTK_MESSAGE_QUESTION */
    		/* Boutons : 1 OUI, 1 NON -> GTK_BUTTONS_YES_NO */
    		pQuestion = gtk_message_dialog_new (GTK_WINDOW(param_g->widget),
        	GTK_DIALOG_MODAL,
        	GTK_MESSAGE_QUESTION,
        	GTK_BUTTONS_YES_NO,
        	"Voulez-vous accepter\nla demande de connexion ?");
		/* Creation de la 2e boite de message pAbout*/
		/* Type : Information -> GTK_MESSAGE_INFO */
		/* Bouton : 1 OK -> GTK_BUTTONS_OK */
		pAbout = gtk_message_dialog_new (GTK_WINDOW(param_g->widget),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		"Veuillez patienter quelques instants, s'il vous plaît ...");

		/* Recuperation de la GtkVBox contenu dans la fenetre*/
		pList = gtk_container_get_children(GTK_CONTAINER(param_g->widget));

		/* Recuperation de la liste des elements que contient la GtkVBox */
		pList = gtk_container_get_children(GTK_CONTAINER(GTK_WIDGET(pList->data)));
		
		/* Le premier element est la GtkImage:" de pList */
		/* Passage a l element suivant : le GtkFrame */
		pList = g_list_next(pList);

		/* Passage a l element suivant : le GtkLabel */
		pList = g_list_next(pList);
		pTempLabel = GTK_WIDGET(pList->data);

		/* Passage a l element suivant : la GtkImage */
		pList = g_list_next(pList);
		pTempImage = GTK_WIDGET(pList->data);

		/* Passage a l element precedent : le GtkLabel */
		pList = g_list_previous(pList);

		/* Passage a l element precedent : la GtkFrame */
		pList = g_list_previous(pList);
		
		/* Recuperation de la GtkVBoxFrame contenu dans la GtkFrame*/
		pList = gtk_container_get_children(GTK_CONTAINER(GTK_WIDGET(pList->data)));
		
		/* Recuperation de la GtkVBoxFrame contenu dans la GtkVBoxFrame*/
		pList = gtk_container_get_children(GTK_CONTAINER(GTK_WIDGET(pList->data)));

		//printf("%s\n",gtk_label_get_text(GTK_LABEL(pList->data)));
		
		/* Le premier element est le GtkLabel "Adresse:" de pList2 */
		/* Passage a l element suivant : le GtkEntry */
		pList = g_list_next(pList);
		pTempEntry = GTK_WIDGET(pList->data);
		//gtk_entry_set_text(GTK_ENTRY(pTempEntry),"test");

		/* Recuperation du texte contenu dans le 1er GtkEntry */
		adress = gtk_entry_get_text(GTK_ENTRY(pTempEntry));

		/* Passage a l element suivant : le GtkLabel "N° de port :" */
		pList = g_list_next(pList);

		/* Passage a l element suivant : le GtkEntry */
		pList = g_list_next(pList);
		pTempEntry = GTK_WIDGET(pList->data);


		/* Recuperation du texte contenu dans le 2e GtkEntry */
		port = gtk_entry_get_text(GTK_ENTRY(pTempEntry));
		
		#ifdef CLIENT
			gtk_label_set_text(GTK_LABEL(pTempLabel), "Attente de Connexion");

			gtk_image_set_from_file(GTK_IMAGE(pTempImage),"../data/phone.gif");
		#endif
		
		
		/*Appel de la fonction principale */
		/*Le serveur se met en attente */
		/*Le client lance une demande de connxion via l'interface */
		if(init_connection((char*)adress, (char*)port, param_g->threads, &(param_g->param_t)) == EXIT_FAILURE)
		{
			gtk_label_set_text(GTK_LABEL(pTempLabel), "Erreur de connection, vérifiez les paramètres et reesayez");
			gtk_image_set_from_file(GTK_IMAGE(pTempImage), NULL);
		}
		else
		{
			gtk_label_set_text(GTK_LABEL(pTempLabel), "Connecté");
			param_g->statut = 1;
		}
		/*
		g_string_sprintf(pString,
		"Connexion : loacale \nIP = %s, Port = %u \n",
		inet_ntoa( param_g->param_t.destination.sin_addr), 
		ntohs (param_g->param_t.destination.sin_port));

	        pEntry = gtk_label_new(pString->str);
		
		#ifdef SERVEUR
			gtk_label_set_text(GTK_LABEL(pTempLabel), "Demande de Connexion");
			// Affichage et attente d une reponse
			switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
			{
				case GTK_RESPONSE_YES:
					// Le serveur accepte la demande de connexion
					// La comuncation est établie
					launch(NULL, NULL, param_g->threads, &(param_g->param_t));
					// On detruit la boite de message
					gtk_widget_destroy(pQuestion);

					gtk_label_set_text(GTK_LABEL(pTempLabel), gtk_label_get_text(pEntry));

					gtk_image_set_from_file(GTK_IMAGE(pTempImage),NULL);
					break;
				case GTK_RESPONSE_NO:
					 // Le serveur rejette la demande de connexion
					// On detruit la boite de message
					gtk_widget_destroy(pQuestion);
					gtk_label_set_text(GTK_LABEL(pTempLabel), NULL);

					gtk_image_set_from_file(GTK_IMAGE(pTempImage),NULL);

					 break;
			}
			
		#endif
		g_string_free(pString,TRUE);

		#ifdef CLIENT
		
			// Affichage de la boite de message
			switch(gtk_dialog_run(GTK_DIALOG(pAbout)))
			{
				case GTK_RESPONSE_OK:
					gtk_label_set_text(GTK_LABEL(pTempLabel), "Etablissement de la connexion terminée");

					gtk_image_set_from_file(GTK_IMAGE(pTempImage), NULL);
					// Destruction de la boite de message
					gtk_widget_destroy(pAbout);
					break;	
			}


		#endif */
		
		

		

		/* Liberation de la memoire utilisee par la liste */
		
		g_list_free(pList);
	}
}


