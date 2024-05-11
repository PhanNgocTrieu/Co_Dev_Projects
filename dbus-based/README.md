# Application Information:
    [ Application 1 ]                                               [ Application 2]
                                                                
    -------------------------                                   -------------------------
    |                       |                                   |                       |
    |                       |                                   |                       |
    |   [ Tag_button ]      |   ----- on_clicked() ----->       |    [ message ]        |
    |                       |           [dbus]                  |                       |
    |                       |                                   |                       |
    |                       |                                   |                       |
    -------------------------                                   -------------------------               

    [Tag_button] -> gen_message("Hello World") --> dbus -->     [message = "Hello World"]

