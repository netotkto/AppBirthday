#include "include/include.h"
#include "include/toUpperCase.h"
#include "include/formElements.h"
#include "include/Date.h"
#include "include/Person.h"
#include "include/getListOfElements.h"
#include "include/getInfoFromFile.h"
#include "include/formShow.h"
#include "include/formAdd.h"

/*

include/toUpperCase.h
include/getListOfElements.h
need to be fixed

*/

//FormAdd
extern "C" void on_buttonShowFA_clicked(GtkButton *button, gpointer data)
{
    gtk_widget_hide_on_delete(windowAdd);
    formShow();
}
extern "C" void on_buttonAddFA_clicked(GtkButton *button, gpointer data)
{
    addPersonToBase(textEdNameAdd, textEdLastNameAdd, textEdBirthdayAdd);
}

//FormShow
extern "C" void on_buttonShowFS_clicked(GtkButton *button, gpointer data){
    showPersonsInfo(textEdFullNameShow);
}

extern "C" void on_buttonAddFS_clicked(GtkButton *button, gpointer data)
{
    gtk_widget_hide_on_delete(windowShow);
    formAdd();
}

int main (int argc, char *argv[]){

    //FormShow
    gtk_init( & argc, & argv );
    formShow();

    return EXIT_SUCCESS;

}
