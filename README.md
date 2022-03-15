# moving_widgets_in_gtk3
moving a gtk widget like a gtkimage without using Cairo.h
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
