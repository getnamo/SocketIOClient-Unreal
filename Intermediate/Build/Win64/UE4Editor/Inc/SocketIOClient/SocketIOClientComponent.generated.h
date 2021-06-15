// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USIOJsonValue;
class UObject;
struct FLatentActionInfo;
class USIOJsonObject;
#ifdef SOCKETIOCLIENT_SocketIOClientComponent_generated_h
#error "SocketIOClientComponent.generated.h already included, missing '#pragma once' in SocketIOClientComponent.h"
#endif
#define SOCKETIOCLIENT_SocketIOClientComponent_generated_h

#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_16_DELEGATE \
struct _Script_SocketIOClient_eventSIOConnectionProblemSignature_Parms \
{ \
	int32 Attempts; \
	int32 NextAttemptInMs; \
	float TimeSinceConnected; \
}; \
static inline void FSIOConnectionProblemSignature_DelegateWrapper(const FMulticastScriptDelegate& SIOConnectionProblemSignature, int32 Attempts, int32 NextAttemptInMs, float TimeSinceConnected) \
{ \
	_Script_SocketIOClient_eventSIOConnectionProblemSignature_Parms Parms; \
	Parms.Attempts=Attempts; \
	Parms.NextAttemptInMs=NextAttemptInMs; \
	Parms.TimeSinceConnected=TimeSinceConnected; \
	SIOConnectionProblemSignature.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_15_DELEGATE \
struct _Script_SocketIOClient_eventSIOCEventJsonSignature_Parms \
{ \
	FString EventName; \
	USIOJsonValue* MessageJson; \
}; \
static inline void FSIOCEventJsonSignature_DelegateWrapper(const FMulticastScriptDelegate& SIOCEventJsonSignature, const FString& EventName, USIOJsonValue* MessageJson) \
{ \
	_Script_SocketIOClient_eventSIOCEventJsonSignature_Parms Parms; \
	Parms.EventName=EventName; \
	Parms.MessageJson=MessageJson; \
	SIOCEventJsonSignature.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_14_DELEGATE \
struct _Script_SocketIOClient_eventSIOCCloseEventSignature_Parms \
{ \
	TEnumAsByte<ESIOConnectionCloseReason> Reason; \
}; \
static inline void FSIOCCloseEventSignature_DelegateWrapper(const FMulticastScriptDelegate& SIOCCloseEventSignature, ESIOConnectionCloseReason Reason) \
{ \
	_Script_SocketIOClient_eventSIOCCloseEventSignature_Parms Parms; \
	Parms.Reason=Reason; \
	SIOCCloseEventSignature.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_13_DELEGATE \
struct _Script_SocketIOClient_eventSIOCOpenEventSignature_Parms \
{ \
	FString SessionId; \
	bool bIsReconnection; \
}; \
static inline void FSIOCOpenEventSignature_DelegateWrapper(const FMulticastScriptDelegate& SIOCOpenEventSignature, const FString& SessionId, bool bIsReconnection) \
{ \
	_Script_SocketIOClient_eventSIOCOpenEventSignature_Parms Parms; \
	Parms.SessionId=SessionId; \
	Parms.bIsReconnection=bIsReconnection ? true : false; \
	SIOCOpenEventSignature.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_12_DELEGATE \
struct _Script_SocketIOClient_eventSIOCSocketEventSignature_Parms \
{ \
	FString Namespace; \
}; \
static inline void FSIOCSocketEventSignature_DelegateWrapper(const FMulticastScriptDelegate& SIOCSocketEventSignature, const FString& Namespace) \
{ \
	_Script_SocketIOClient_eventSIOCSocketEventSignature_Parms Parms; \
	Parms.Namespace=Namespace; \
	SIOCSocketEventSignature.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_11_DELEGATE \
static inline void FSIOCEventSignature_DelegateWrapper(const FMulticastScriptDelegate& SIOCEventSignature) \
{ \
	SIOCEventSignature.ProcessMulticastDelegate<UObject>(NULL); \
}


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_SPARSE_DATA
#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execBindEventToFunction); \
	DECLARE_FUNCTION(execUnbindEvent); \
	DECLARE_FUNCTION(execBindEventToGenericEvent); \
	DECLARE_FUNCTION(execEmitWithGraphCallBack); \
	DECLARE_FUNCTION(execEmitWithCallBack); \
	DECLARE_FUNCTION(execEmit); \
	DECLARE_FUNCTION(execLeaveNamespace); \
	DECLARE_FUNCTION(execJoinNamespace); \
	DECLARE_FUNCTION(execDisconnect); \
	DECLARE_FUNCTION(execConnect);


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execBindEventToFunction); \
	DECLARE_FUNCTION(execUnbindEvent); \
	DECLARE_FUNCTION(execBindEventToGenericEvent); \
	DECLARE_FUNCTION(execEmitWithGraphCallBack); \
	DECLARE_FUNCTION(execEmitWithCallBack); \
	DECLARE_FUNCTION(execEmit); \
	DECLARE_FUNCTION(execLeaveNamespace); \
	DECLARE_FUNCTION(execJoinNamespace); \
	DECLARE_FUNCTION(execDisconnect); \
	DECLARE_FUNCTION(execConnect);


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSocketIOClientComponent(); \
	friend struct Z_Construct_UClass_USocketIOClientComponent_Statics; \
public: \
	DECLARE_CLASS(USocketIOClientComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SocketIOClient"), NO_API) \
	DECLARE_SERIALIZER(USocketIOClientComponent)


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_INCLASS \
private: \
	static void StaticRegisterNativesUSocketIOClientComponent(); \
	friend struct Z_Construct_UClass_USocketIOClientComponent_Statics; \
public: \
	DECLARE_CLASS(USocketIOClientComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SocketIOClient"), NO_API) \
	DECLARE_SERIALIZER(USocketIOClientComponent)


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USocketIOClientComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USocketIOClientComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USocketIOClientComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USocketIOClientComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USocketIOClientComponent(USocketIOClientComponent&&); \
	NO_API USocketIOClientComponent(const USocketIOClientComponent&); \
public:


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USocketIOClientComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USocketIOClientComponent(USocketIOClientComponent&&); \
	NO_API USocketIOClientComponent(const USocketIOClientComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USocketIOClientComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USocketIOClientComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USocketIOClientComponent)


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_PRIVATE_PROPERTY_OFFSET
#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_18_PROLOG
#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_PRIVATE_PROPERTY_OFFSET \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_SPARSE_DATA \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_RPC_WRAPPERS \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_INCLASS \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_PRIVATE_PROPERTY_OFFSET \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_SPARSE_DATA \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_INCLASS_NO_PURE_DECLS \
	CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h_21_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class SocketIOClientComponent."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SOCKETIOCLIENT_API UClass* StaticClass<class USocketIOClientComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CryptoHeroes2_Plugins_SocketIO_UE4_26_main_Source_SocketIOClient_Public_SocketIOClientComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
