// Modifications Copyright 2018-current Getnamo. All Rights Reserved
//
//  sio_client.h
//
//  Created by Melo Yao on 3/25/15.
//

#ifndef SIO_CLIENT_H
#define SIO_CLIENT_H
#include <string>
#include <functional>
#include "sio_message.h"
#include "sio_socket.h"

namespace sio
{
    class client_impl_base;
    
    class SOCKETIOLIB_API client {
    public:
        enum close_reason
        {
            close_reason_normal,
            close_reason_drop
        };
        
        typedef std::function<void(void)> con_listener;
        
        typedef std::function<void(close_reason const& reason)> close_listener;

        typedef std::function<void(unsigned, unsigned)> reconnect_listener;
        
        typedef std::function<void(std::string const& nsp)> socket_listener;

        typedef std::function<message::ptr()> auth_provider;

        typedef std::function<std::map<std::string, std::string>()> query_provider;

        client();

        client(const bool bShouldUseTlsLibraries, const bool bShouldVerifyTLSCertificate);

        ~client();
        
        //set listeners and event bindings.
        void set_open_listener(con_listener const& l);
        
        void set_fail_listener(con_listener const& l);
        
        void set_reconnecting_listener(con_listener const& l);

        void set_reconnect_listener(reconnect_listener const& l);

        void set_close_listener(close_listener const& l);
        
        void set_socket_open_listener(socket_listener const& l);
        
        void set_socket_close_listener(socket_listener const& l);
        
        void clear_con_listeners();
        
        void clear_socket_listeners();
        
        // Client Functions - such as send, etc.

        void connect();

        void connect(const std::string& uri);

        void connect(const std::string& uri, const std::map<std::string,std::string>& query);

        void connect(const std::string& uri, const std::map<std::string,std::string>& query,
                     const std::map<std::string,std::string>& http_extra_headers, const message::ptr& auth);

        // Supplies the auth payload for every namespace connect packet, automatic reconnections included,
        // in place of the auth given to connect().
        // Returning nullptr sends no auth. Called on the network thread when the connection (re)opens, and on
        // the calling thread when socket() joins a namespace on an open connection, so it must be thread-safe
        // and must not call back into this client. Set it before connect().
        void set_auth_provider(auth_provider const& provider);

        // Replaces the query sent with the next connect and automatic reconnections. Thread-safe.
        // Ignored while a query provider is set.
        void set_query(const std::map<std::string, std::string>& query);

        // Supplies the URL query for every connection attempt (reconnections included), instead of connect()/set_query().
        // Called on the network thread: must be thread-safe and not call back into this client. Set it before connect().
        void set_query_provider(query_provider const& provider);

        void set_reconnect_attempts(int attempts);

        void set_reconnect_delay(unsigned millis);

        void set_reconnect_delay_max(unsigned millis);

        void set_path(const std::string& path);

        void set_logs_default();

        void set_logs_quiet();

        void set_logs_verbose();

        sio::socket::ptr const& socket(const std::string& nsp = "");
        
        // Closes the connection
        void close();
        
        void sync_close();

        // stop io_service
        void stop();
        
        bool opened() const;
        
        std::string const& get_sessionid() const;

        std::string const& get_url() const;
        
    private:
        //disable copy constructor and assign operator.
        client(client const&){}
        void operator=(client const&){}
        
        client_impl_base* m_impl;

        std::string m_path;
    };
    
}


#endif // __SIO_CLIENT__H__
