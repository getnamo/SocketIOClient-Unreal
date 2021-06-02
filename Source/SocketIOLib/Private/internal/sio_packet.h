// Modifications Copyright 2018-current Getnamo. All Rights Reserved
//
//  sio_packet.h
//
//  Created by Melo Yao on 3/19/15.
//

#ifndef SIO_PACKET_H
#define SIO_PACKET_H

#include <sstream>
#include "sio_message.h"
#include <functional>

namespace sio
{
	using namespace std;

	class packet
	{
	public:
		enum frame_type
		{
			frame_open = 0,
			frame_close = 1,
			frame_ping = 2,
			frame_pong = 3,
			frame_message = 4,
			frame_upgrade = 5,
			frame_noop = 6
		};

<<<<<<< HEAD
		enum type
		{
			type_min = 0,
			type_connect = 0,
			type_disconnect = 1,
			type_event = 2,
			type_ack = 3,
			type_error = 4,
			type_binary_event = 5,
			type_binary_ack = 6,
			type_max = 6,
			type_undetermined = 0x10 //undetermined mask bit
		};
	private:
		frame_type _frame;
		int _type;
		string _nsp;
		int _pack_id;
		message::ptr _message;
		unsigned _pending_buffers;
		vector<shared_ptr<const string> > _buffers;
	public:
		packet(string const& nsp, message::ptr const& msg, int pack_id = -1, bool isAck = false);//message type constructor.
=======
        enum type
        {
            type_min = 0,
            type_connect = 0,
            type_disconnect = 1,
            type_event = 2,
            type_ack = 3,
            type_error = 4,
            type_binary_event = 5,
            type_binary_ack = 6,
            type_max = 6,
            type_undetermined = 0x10 //undetermined mask bit
        };
    private:
        frame_type _frame;
        int _type;
        string _nsp;
        int _pack_id;
        message::ptr _message;
        unsigned _pending_buffers;
        vector<shared_ptr<const string> > _buffers;
    public:
        packet(string const& nsp,message::ptr const& msg,int pack_id = -1,bool isAck = false);//message type constructor.
<<<<<<< HEAD
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)
=======
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)

		packet(frame_type frame);

<<<<<<< HEAD
<<<<<<< HEAD
		packet(type type, string const& nsp = string(), message::ptr const& msg = message::ptr());//other message types constructor.
		//empty constructor for parse.
		packet();
=======
=======
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)
        packet(type type,string const& nsp= string(),message::ptr const& msg = message::ptr());//other message types constructor.
        //empty constructor for parse.
        packet();
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)

		frame_type get_frame() const;

		type get_type() const;

		bool parse(string const& payload_ptr);//return true if need to parse buffer.

		bool parse_buffer(string const& buf_payload);

<<<<<<< HEAD
<<<<<<< HEAD
		bool accept(string& payload_ptr, vector<shared_ptr<const string> >& buffers); //return true if has binary buffers.
=======
        bool accept(string& payload_ptr, vector<shared_ptr<const string> >&buffers); //return true if has binary buffers.
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)
=======
        bool accept(string& payload_ptr, vector<shared_ptr<const string> >&buffers); //return true if has binary buffers.
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)

		string const& get_nsp() const;

		message::ptr const& get_message() const;

		unsigned get_pack_id() const;

		static bool is_message(string const& payload_ptr);
		static bool is_text_message(string const& payload_ptr);
		static bool is_binary_message(string const& payload_ptr);
	};

<<<<<<< HEAD
	class packet_manager
	{
	public:
		typedef function<void(bool, shared_ptr<const string> const&)> encode_callback_function;
		typedef  function<void(packet const&)> decode_callback_function;
=======
    class packet_manager
    {
    public:
        typedef function<void (bool,shared_ptr<const string> const&)> encode_callback_function;
        typedef  function<void (packet const&)> decode_callback_function;
<<<<<<< HEAD
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)
=======
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)

		void set_decode_callback(decode_callback_function const& decode_callback);

		void set_encode_callback(encode_callback_function const& encode_callback);

<<<<<<< HEAD
<<<<<<< HEAD
		void encode(packet& pack, encode_callback_function const& override_encode_callback = encode_callback_function()) const;
=======
        void encode(packet& pack,encode_callback_function const& override_encode_callback = encode_callback_function()) const;
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)
=======
        void encode(packet& pack,encode_callback_function const& override_encode_callback = encode_callback_function()) const;
>>>>>>> parent of 1ad78b7 (Compatibility with socketio 3.0 and 4.0)

		void put_payload(string const& payload);

		void reset();

	private:
		decode_callback_function m_decode_callback;

		encode_callback_function m_encode_callback;

		std::unique_ptr<packet> m_partial_packet;
	};
}
#endif
