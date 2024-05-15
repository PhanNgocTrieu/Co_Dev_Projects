#include <gtk/gtk.h>
#include <gio/gio.h>

static GDBusNodeInfo *introspection_data = NULL;
static GMainLoop* m_loop = nullptr;
static GMainContext* m_ctx = nullptr;

/* Introspection data for the service we are exporting */
static const gchar introspection_xml[] =
  "<node>"
  "  <interface name='org.gtk.dbus-based..test-debug'>"
  "    <method name='HelloWorld'>"
  "      <arg type='s' name='greeting' direction='in'/>"
  "      <arg type='s' name='response' direction='out'/>"
  "    </method>"
  "  </interface>"
  "</node>";


class Application {
    public:
        Application(GMainLoop* loop)
        : m_loop(loop) {

        }

        int execute() {

        }

        GMainLoop* get_main_loop() {
            return m_loop;
        }


    protected:
        void activate(GtkApplication *app, gpointer user_data) {

        }

        void init_window(int argc, char* argv[]) {
#if 0
            app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
            g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
            status = g_application_run(G_APPLICATION(app), argc, argv);
            g_object_unref(app);
#endif
        }

    protected:
        GMainLoop* m_loop = nullptr;
        GtkApplication *app = nullptr   ;
};

class DbusInterface {
    public:
        gchar* get_name() {
            return "/org/gtk/gdbus.test";
        }

        gchar* get_interface_name() {
            return "org.gtk.dbus-based.test-debug";
        }
};


static void
print_hello(GtkWidget *widget,
            gpointer data)
{
    g_print("Hello World\n");
}

static void
activate(GtkApplication *app,
         gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 480);

    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_window_set_child(GTK_WINDOW(window), button);

    gtk_window_present(GTK_WINDOW(window));
}


int main(int argc,
         char **argv)
{
#if 1
    /* We are lazy here - we don't want to manually provide
     * the introspection data structures - so we just build
     * them from XML.
     */
    introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, NULL);
    g_assert(introspection_data != NULL);
    g_print("Interface name %s\n", introspection_data->interfaces[0]->name); 
    g_dbus_node_info_unref(introspection_data);

    m_loop = g_main_loop_new( nullptr, true );
    g_main_loop_ref(m_loop);
    g_main_loop_run(m_loop);
    g_main_loop_unref(m_loop);
#endif
#if 0
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
#endif
    return 0;
}
