#include <gio/gio.h>
#include "dbus.res.h"
#include <iostream>

#define LOGGER(MSG) \
    std::cout << "[Server][ " << MSG << " ]" << std::endl;
static GMainLoop* loop = nullptr;

class Server {
    public:     
        static Server& getInstance(GMainLoop* loop) {
            static Server* _ins = new Server(loop);
            return *_ins;
        };

        void registerDbusService(GBusType Type) {
            m_ownerId = g_bus_own_name(Type,
                getServiceName().c_str(),
                G_BUS_NAME_OWNER_FLAGS_NONE,
                onDBusAcquired,
                onDBusNameAcquired,
                onDBusNameLost,
                this,
                nullptr
            );
            std::cout << " register DBus Service: " << m_ownerId << std::endl;
        }

        void unregisterDbusService() {
            if (m_ownerId != 0) {
                g_bus_unown_name(m_ownerId);
                m_ownerId = 0;
            }
        }

        std::string getServiceName(void) const {
            return "dbus.demo.research";
        }

        std::string getObjectName(void) const {
            return "/dbus/demo/research/object";
        }

        static gboolean onHandleSayHello(
            DbusDemoResearch *object,
            GDBusMethodInvocation *invocation,
            const gchar *arg_toSay,
            gpointer userData
        ) {
            Server* server = static_cast<Server*>(userData);
            server->received_message();

            return true;
        }

        DbusDemoResearch* adaptorCreateSkeleton() {
            return dbus_demo_research_skeleton_new();
        }
    protected:
        Server(GMainLoop* loop)
        : m_loop(loop)
        {
            std::cout << " Created Server Application " << std::endl;
        }

        void received_message() {
            std::cout << "Server is received" << std::endl;
        }

        void registerHandler(gpointer userData) {
            if (m_skeleton) {
                m_cbId = g_signal_connect(m_skeleton, "handle-hello-to", G_CALLBACK(onHandleSayHello), userData);
            } else {
                std::cout << "Can't register signal handler: skeleton is null" << std::endl;
            }
        }

        void unregisterHandler() {
            g_signal_handler_disconnect(m_skeleton, m_cbId);
        }

        static void onDBusAcquired(GDBusConnection* connection,
            const gchar* name,
            gpointer userData
        ) {
            std::cout << "onDBusAcquired" << std::endl;
            Server* instance = (Server*)userData;

            instance->m_skeleton = instance->adaptorCreateSkeleton();
            if (instance->m_skeleton == nullptr) {
                std::cout << "Failed to create Server skeleton" << std::endl;
            }

            instance->registerHandler(userData);
            gboolean ret = g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(instance->m_skeleton),
                connection,
                instance->getObjectName().c_str(),
                NULL);
            
            LOGGER("Service : " << name << "Object: " << instance->getObjectName() << " export -result: " << ret);
        }

        static void onDBusNameAcquired(
            GDBusConnection* connection,
            const gchar* name,
            gpointer user_data
        ) {
            std::cout << "onDBusNameAcquired" << std::endl;
        }

        static void onDBusNameLost (
            GDBusConnection* connection,
            const gchar* name,
            gpointer user_data
        ) {
            std::cout << "onDBusNameLost" << std::endl;
        }

    protected:
        guint m_ownerId;
        DbusDemoResearch* m_proxy;
        DbusDemoResearch* m_skeleton;
        GDBusConnection* m_dbusConnection;
        GDBusInterfaceInfo* m_interfaceInfo;
        GMainLoop* m_loop;
        unsigned long m_cbId;
};

int main() {
    
    loop = g_main_loop_new(NULL, false);
    Server& _server = Server::getInstance(loop);
    _server.registerDbusService(G_BUS_TYPE_SESSION);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);
    _server.unregisterDbusService();
    return 0;
}
