/*
---------------gboolean  g_source_remove (guint tag);-----------------
input   :       tag : the ID of the source to remove.
Returns :       TRUE if the source was found and removed.
Role    :
 Removes the source with the given id from the default main context.
 The id of a GSource is given by g_source_get_id(),
 or will be returned by the functions g_source_attach(),
 g_idle_add(), g_idle_add_full(), g_timeout_add(), g_timeout_add_full(),
 g_child_watch_add(), g_child_watch_add_full(), g_io_add_watch(), and g_io_add_watch_full().

See also g_source_destroy(). You must use g_source_destroy() for sources added to a non-default main context.

---------------guint  g_timeout_add(guint interval, GSourceFunc function, gpointer data);-----------------

inputs      :    interval :the time between calls to the function, in milliseconds (1/1000ths of a second)
                 function :function to call
                 data :data to pass to function
Returns     :    the ID (greater than 0) of the event source.
Role        :

 Sets a function to be called at regular intervals, with the default priority, G_PRIORITY_DEFAULT.
 The function is called repeatedly until it returns FALSE, at which point the timeout is automatically
 destroyed and the function will not be called again. The first call to the function will be at the
 end of the first interval.

Note that timeout functions may be delayed, due to the processing of other event sources.
 Thus they should not be relied on for precise timing. After each call to the timeout function,
 the time of the next timeout is recalculated based on the current time and the given
 interval (it does not try to 'catch up' time lost in delays).
*/


#include <gtk/gtk.h>
typedef struct {
    GtkWidget *fix;
    GtkWidget *image[2];
    gint x[2];
    gint y[2];
    gint j;
    int count;
}mov;
//
gint i=1;
//the g_source tag
guint t=0;
/*
 * this is the fuction that moves the images (objects)
 * you can make your own rules here
*/
gint deplacer(mov*fixe )
{
    //update the counter
    fixe->count++;
    //if j is not null increment the cordinate
    if(fixe->j)
    {
        fixe->x[0]++;fixe->y[0]++;
        fixe->x[1]--;fixe->y[1]++;
        if(fixe->x[0]==600 || fixe->x[1]==0 ) fixe->j=0;
    }
    else {//decrement
        fixe->x[0]--;fixe->y[0]--;
        fixe->x[1]++;fixe->y[1]--;
        if(fixe->x[0]==0 || fixe->x[1]==600) fixe->j=1;
    }
    //move the first images to their new positions
    gtk_fixed_move(GTK_FIXED(fixe->fix),fixe->image[0], fixe->x[0],fixe->y[0]);
    gtk_fixed_move(GTK_FIXED(fixe->fix),fixe->image[1], fixe->x[1],fixe->y[1]);
    //if counter is less than 10000ms return true
    return (fixe->count<10000);
}
//when the user clicks the update button
// this fuction is called to start the simulation
void on_update (GtkWidget * but, gpointer *data)
{
    if(i==1)//if i=1 then call deplacer() to move the objects
    {
        i=0;
        /*call deplacer every 10ms to move the objects,
         * note that while t=true deplacer() will be called every 10ms*/
        t=g_timeout_add(10, G_SOURCE_FUNC(deplacer), data);

    }
    else if(i==0)//if i=0 stop g_timeout_add()
    {
        i=1;//update i
        //this will give t the false value and stop g_timeout_add()
        g_source_remove(t);
    }
}
//used to initialize and alocate memory for a mov struct
mov*initmov()
{
    mov*fix=(mov*) malloc(sizeof (mov));
    //j is used to manage the images overflowing the dimension of the fixed container
    fix->j=1;
    //initialiese the counter
    fix->count=0;
    return fix;
}

int
main (int   argc,char *argv[])
{

    GtkWidget *update_button,*window,*box;
    mov*fixe;
    gtk_init (&argc, &argv);
    //create a window
    window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,700,750);
    //create a box and an update button
    box= gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
    update_button=gtk_button_new_with_label("update");
    //add the button to the box
    gtk_box_pack_start(GTK_BOX(box),update_button,0,0,0);
    //create a mov structure
    //fixe have one fixed widget, 2 images widget and 2 coordinates tables
    fixe=initmov();
    fixe->fix= gtk_fixed_new();
    //add the fixed widget to the box
    gtk_box_pack_start(GTK_BOX(box),fixe->fix,0,0,0);

    //create the 2 images
    fixe->image[0]= gtk_image_new_from_file("path_of_image1.png");
    fixe->image[1]= gtk_image_new_from_file("path_of_image2.png");
    //initialize the images coordinates
    fixe->x[0]=0; fixe->y[0]=0;
    fixe->x[1]=600; fixe->y[1]=0;
    //put the images in the fixed widget (container)
    gtk_fixed_put(GTK_FIXED(fixe->fix),fixe->image[0],fixe->x[0],fixe->y[0]);
    gtk_fixed_put(GTK_FIXED(fixe->fix),fixe->image[1],fixe->x[1],fixe->y[1]);

    // signal to start simulation when update button is clicked
    g_signal_connect(update_button, "clicked", G_CALLBACK(on_update),(gpointer *) fixe);
    //signal destroy (ma3rof hada hhh)
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit),NULL);
    // add the box to the window
    gtk_container_add(GTK_CONTAINER(window),box);
    //show all
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
