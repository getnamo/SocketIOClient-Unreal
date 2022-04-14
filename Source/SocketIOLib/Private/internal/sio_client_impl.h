// Modifications Copyright 2018-current Getnamo. All Rights Reserved

#ifndef SIO_CLIENT_IMPL_H
#define SIO_CLIENT_IMPL_H

#ifndef SIO_TLS
#define SIO_TLS 0
#endif

/* This disables two things:
   1) error 4503 where MSVC complains about
	  decorated names being too long. There's no way around
	  this.
   2) We also disable a security error triggered by
	  websocketpp not using checked iterators.
*/
#ifdef _MSC_VER
#pragma warning(disable : 4503)
#define _SCL_SECURE_NO_WARNINGS
#endif

/* For this code, we will use standalone ASIO
   and websocketpp in C++11 mode only */
#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_STL_

#include <cstdint>
#define INTIALIZER(__TYPE__)

#include "CoreMinimal.h" 

#if PLATFORM_WINDOWS
//#define WIN32_LEAN_AND_MEAN
#include "Windows/WindowsHWrapper.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif

#include <websocketpp/client.hpp>
#include <asio/system_timer.hpp>

#if defined(DEBUG)
  #if SIO_TLS
    #define UI UI_ST
    THIRD_PARTY_INCLUDES_START
    #include "openssl/hmac.h"
    #include <websocketpp/config/debug_asio.hpp>
    typedef websocketpp::config::debug_asio_tls client_config_tls;
    THIRD_PARTY_INCLUDES_END
    #undef UI
  #endif //SIO_TLS
	#include <websocketpp/config/debug_asio_no_tls.hpp>
	typedef websocketpp::config::debug_asio client_config;
#else
  #if SIO_TLS
    #define UI UI_ST
    THIRD_PARTY_INCLUDES_START
    #include "openssl/hmac.h"
    #include <websocketpp/config/asio_client.hpp>
    typedef websocketpp::config::asio_tls_client client_config_tls;
    THIRD_PARTY_INCLUDES_END
    #undef UI
  #endif //SIO_TLS
	#include <websocketpp/config/asio_no_tls_client.hpp>
	typedef websocketpp::config::asio_client client_config;
#endif //DEBUG
#include <asio/deadline_timer.hpp>

#include <memory>
#include <map>
#include <thread>

#include "sio_client.h"
#include "sio_packet.h"

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformAtomics.h"
#endif

    namespace sio
    {
        using namespace websocketpp;

        typedef websocketpp::client<client_config> client_type_no_tls;
#if SIO_TLS
        typedef websocketpp::client<client_config_tls> client_type_tls;
#endif

        class client_impl_base {

        public:
            enum con_state
            {
                con_opening,
                con_opened,
                con_closing,
                con_closed
            };

            client_impl_base() {}
            virtual void template_init() {};

            virtual ~client_impl_base() {}

            // listeners and event bindings. (see SYNTHESIS_SETTER below)
            virtual void set_open_listener(client::con_listener const&) {};
            virtual void set_fail_listener(client::con_listener const&) {};
            virtual void set_reconnect_listener(client::reconnect_listener const&) {};
            virtual void set_reconnecting_listener(client::con_listener const&) {};
            virtual void set_close_listener(client::close_listener const&) {};
            virtual void set_socket_open_listener(client::socket_listener const&) {};
            virtual void set_socket_close_listener(client::socket_listener const&) {};

            // used by sio::client
            virtual void clear_con_listeners() {};
            virtual void clear_socket_listeners() {};
            virtual void connect(const string& uri, const map<string, string>& query, const map<string, string>& headers, const message::ptr& auth, const std::string& path = "socket.io") {};

            virtual sio::socket::ptr const& socket(const std::string& nsp) = 0;
            virtual void close() {};
            virtual void sync_close() {};
            virtual bool opened() const { return false; };
            virtual std::string const& get_sessionid() const = 0;
            virtual void set_reconnect_attempts(unsigned attempts) {};
            virtual void set_reconnect_delay(unsigned millis) {};
            virtual void set_reconnect_delay_max(unsigned millis) {};

            // used by sio::socket
            virtual void send(packet& p) {};
            virtual void remove_socket(std::string const& nsp) {};
            virtual asio::io_service& get_io_service() = 0;
            virtual void on_socket_closed(std::string const& nsp) {};
            virtual void on_socket_opened(std::string const& nsp) {};

            virtual void set_logs_default() {};
            virtual void set_logs_quiet() {};
            virtual void set_logs_verbose() {};

            virtual std::string const& get_current_url() const = 0;

            // used for selecting whether or not to use TLS
            static bool is_tls(const std::string& uri);

#if SIO_TLS
            virtual void set_verify_mode(int mode) {};
#endif

        protected:
            // Wrap protected member functions of sio::socket because only client_impl_base is friended.
            sio::socket* new_socket(std::string const&, message::ptr const&);
            void socket_on_message_packet(sio::socket::ptr&, packet const&);
            typedef void (sio::socket::* socket_void_fn)(void);
            inline socket_void_fn socket_on_close() { return &sio::socket::on_close; }
            inline socket_void_fn socket_on_disconnect() { return &sio::socket::on_disconnect; }
            inline socket_void_fn socket_on_open() { return &sio::socket::on_open; }
        };

    template<typename client_type>
    class client_impl : public client_impl_base {
    public:
        typedef typename client_type::message_ptr message_ptr;

        client_impl();
        void template_init() override; // template-specific initialization

        ~client_impl();

        //set listeners and event bindings.
        void connect(const std::string& uri, const std::map<std::string, std::string>& queryString,
            const std::map<std::string, std::string>& httpExtraHeaders, const message::ptr& auth, const std::string& path = "socket.io");

        sio::socket::ptr const& socket(const std::string& nsp);

        // Closes the connection
        void close();

        void sync_close();

        bool opened() const { return m_con_state == con_opened; }

        std::string const& get_sessionid() const { return m_sid; }

        std::string const& get_current_url() const { return m_base_url; }

        void set_reconnect_attempts(unsigned attempts) { m_reconn_attempts = attempts; }

        void set_reconnect_delay(unsigned millis) { m_reconn_delay = millis; if (m_reconn_delay_max < millis) m_reconn_delay_max = millis; }

        void set_reconnect_delay_max(unsigned millis) { m_reconn_delay_max = millis; if (m_reconn_delay > millis) m_reconn_delay = millis; }

        void set_logs_default();

        void set_logs_quiet();

        void set_logs_verbose();

#define SYNTHESIS_SETTER(__TYPE__,__FIELD__) \
        void set_##__FIELD__(__TYPE__ const& l) \
            { m_##__FIELD__ = l;}

            SYNTHESIS_SETTER(client::con_listener, open_listener)

            SYNTHESIS_SETTER(client::con_listener, fail_listener)

            SYNTHESIS_SETTER(client::reconnect_listener, reconnect_listener)

            SYNTHESIS_SETTER(client::con_listener, reconnecting_listener)

            SYNTHESIS_SETTER(client::close_listener, close_listener)

            SYNTHESIS_SETTER(client::socket_listener, socket_open_listener)

            SYNTHESIS_SETTER(client::socket_listener, socket_close_listener)
#undef SYNTHESIS_SETTER

#if SIO_TLS
        void set_verify_mode(int mode) override;
#endif

    public:
        void send(packet& p);

        void remove_socket(std::string const& nsp);

        asio::io_service& get_io_service();

        void on_socket_closed(std::string const& nsp);

        void on_socket_opened(std::string const& nsp);

    private:
        void run_loop();

        void connect_impl(const std::string& uri, const std::string& query);

        void close_impl(close::status::value const& code, std::string const& reason);

        void send_impl(std::shared_ptr<const std::string> const& payload_ptr, frame::opcode::value opcode);

        void ping(const asio::error_code& ec);

        void timeout_pong(const asio::error_code& ec);

        void timeout_reconnect(asio::error_code const& ec);

        unsigned next_delay() const;

        socket::ptr get_socket_locked(std::string const& nsp);

        void sockets_invoke_void(void (sio::socket::* fn)(void));

        void on_decode(packet const& pack);
        void on_encode(bool isBinary, shared_ptr<const string> const& payload);

        //websocket callbacks
        void on_fail(connection_hdl con);

        void on_open(connection_hdl con);

        void on_close(connection_hdl con);

        void on_message(connection_hdl con, message_ptr msg);

        //socketio callbacks
        void on_handshake(message::ptr const& message);

        void on_ping();

        void reset_states();

        void clear_timers();

        // Percent encode query string
        std::string encode_query_string(const std::string& query);

        // Connection pointer for client functions.
        connection_hdl m_con;
        client_type m_client;

        // Socket.IO server settings
        std::string m_sid;
        std::string m_base_url;
        std::string m_query_string;
        std::map<std::string, std::string> m_http_headers;
		message::ptr m_auth;

        unsigned int m_ping_interval;
        unsigned int m_ping_timeout;

        std::unique_ptr<std::thread> m_network_thread;

        packet_manager m_packet_mgr;

        std::unique_ptr<asio::steady_timer> m_ping_timeout_timer;

        std::unique_ptr<asio::steady_timer> m_reconn_timer;

        con_state m_con_state;

        client::con_listener m_open_listener;
        client::con_listener m_fail_listener;
        client::con_listener m_reconnecting_listener;
        client::reconnect_listener m_reconnect_listener;
        client::close_listener m_close_listener;

        client::socket_listener m_socket_open_listener;
        client::socket_listener m_socket_close_listener;

        std::map<const std::string, socket::ptr> m_sockets;

        std::mutex m_socket_mutex;

        unsigned m_reconn_delay;

        unsigned m_reconn_delay_max;

        unsigned m_reconn_attempts;

        unsigned m_reconn_made;

        //passthrough path of plugin
        std::string m_path;

#if SIO_TLS
        int verify_mode = -1;
#endif

        friend class sio::client;
        friend class sio::socket;
    };
}
#endif // SIO_CLIENT_IMPL_H