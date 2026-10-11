// Copyright 2026-current Getnamo. All Rights Reserved

// Same websocketpp/asio setup as WebSocketLib, plus the server side and certificate generation

#pragma once

#ifdef _MSC_VER
#pragma warning(disable : 4503)
#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif
#endif

#ifndef ASIO_STANDALONE
#define ASIO_STANDALONE
#endif
#ifndef _WEBSOCKETPP_CPP11_STL_
#define _WEBSOCKETPP_CPP11_STL_
#endif

#include "CoreMinimal.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif

THIRD_PARTY_INCLUDES_START
#define UI UI_ST
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#undef UI
THIRD_PARTY_INCLUDES_END

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformAtomics.h"
#endif
