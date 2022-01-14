void showPersonsInfo(GtkWidget *entryFullName){

}

void formShow(){
    builderShow = gtk_builder_new_from_file("designShow.glade");
   
    windowShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "window"));

    g_signal_connect(windowShow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builderShow, NULL);

    fixedShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "fixed"));
    textEdFullNameShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "textEdFullName"));
    errorOutputShow = GTK_WIDGET(gtk_builder_get_object(builderShow, "errorOutput"));
    buttonAddFS = GTK_WIDGET(gtk_builder_get_object(builderShow, "buttonAdd"));
    buttonShowFS = GTK_WIDGET(gtk_builder_get_object(builderShow, "buttonShow"));

    gtk_widget_show(windowShow);
    gtk_main();
}

