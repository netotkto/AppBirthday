#include <iostream>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>



GtkWidget  *window;
GtkWidget  *fixed1;
GtkWidget  *button1;
GtkWidget  *label1;
GtkBuilder *builder;


void on_button1_clicked(GtkWidget *widget, gpointer window) {

  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
          GTK_DIALOG_DESTROY_WITH_PARENT,
          GTK_MESSAGE_QUESTION,
          GTK_BUTTONS_YES_NO,
          "Are you sure to quit?");
  gtk_window_set_title(GTK_WINDOW(dialog), "Question");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}