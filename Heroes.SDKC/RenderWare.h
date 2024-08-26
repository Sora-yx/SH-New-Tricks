#ifndef TYPEDEF_H
#define TYPEDEF_H


#ifndef _TYPEDEF_BYTE
#define _TYPEDEF_BYTE
typedef char _BYTE;
#endif

typedef float RwReal;
#ifndef _TYPEDEF_WORD
#define _TYPEDEF_WORD
typedef WORD _WORD;
#endif

#ifndef _TYPEDEF_RwUInt8
#define _TYPEDEF_RwUInt8
typedef unsigned __int8 RwUInt8;
#endif
typedef unsigned int RwUInt32;
typedef unsigned __int16 RwUInt16;

typedef signed __int8 RwInt8;
typedef __int16 RwInt16;
typedef int RwInt32;
typedef RwInt32 RwBool;
typedef char RwChar;

struct RwTexture;
struct RpAtomic;
struct RwObjectHasFrame;
struct RtAnimInterpolatorInfo;
struct RtAnimAnimation;
struct RwStream;
struct RwFrame;
struct RtAnimInterpolator;

typedef RwFrame* (__cdecl* RwFrameCallBack)(RwFrame* frame, void* data);

typedef void(__cdecl* RtAnimKeyFrameApplyCallBack)(void* result, void* voidIFrame);
typedef void(__cdecl* RtAnimKeyFrameBlendCallBack)(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha);
typedef void(__cdecl* RtAnimKeyFrameInterpolateCallBack)(void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData);
typedef void(__cdecl* RtAnimKeyFrameAddCallBack)(void* voidOut, void* voidIn1, void* voidIn2);
typedef void(__cdecl* RtAnimKeyFrameMulRecipCallBack)(void* voidFrame, void* voidStart);
typedef RtAnimAnimation* (__cdecl* RtAnimKeyFrameStreamReadCallBack)(RwStream* stream, RtAnimAnimation* animation);
typedef RwBool(__cdecl* RtAnimKeyFrameStreamWriteCallBack)(RtAnimAnimation* animation, RwStream* stream);
typedef RwInt32(__cdecl* RtAnimKeyFrameStreamGetSizeCallBack)(RtAnimAnimation* animation);
typedef RtAnimInterpolator* (__cdecl* RtAnimCallBack)(RtAnimInterpolator* animInstance, void* data);

typedef RwBool(__cdecl* rwFnFexist)(const RwChar* name);
typedef void* (__cdecl* rwFnFopen)(const RwChar* name, const RwChar* access);
typedef int(__cdecl* rwFnFclose)(void* fptr);
typedef unsigned int size_t;
typedef size_t(__cdecl* rwFnFread)(void* addr, size_t size, size_t count, void* fptr);
typedef size_t(__cdecl* rwFnFwrite)(const void* addr, size_t size, size_t count, void* fptr);
typedef RwChar* (__cdecl* rwFnFgets)(RwChar* buffer, int maxLen, void* fptr);
typedef int(__cdecl* rwFnFputs)(const RwChar* buffer, void* fptr);
typedef int(__cdecl* rwFnFeof)(void* fptr);
typedef int(__cdecl* rwFnFseek)(void* fptr, int offset, int origin);
typedef int(__cdecl* rwFnFflush)(void* fptr);
typedef int(__cdecl* rwFnFtell)(void* fptr);

typedef int (*vecSprintfFunc)(RwChar* buffer, const RwChar* format, ...);


typedef int(__cdecl* vecVsprintfFunc)(RwChar* buffer, const RwChar* format, void** argptr);
typedef RwChar* (__cdecl* vecStrcpyFunc)(RwChar* dest, const RwChar* srce);
typedef RwChar* (__cdecl* vecStrncpyFunc)(RwChar* dest, const RwChar* srce, size_t size);
typedef RwChar* (__cdecl* vecStrcatFunc)(RwChar* dest, const RwChar* srce);
typedef RwChar* (__cdecl* vecStrncatFunc)(RwChar* dest, const RwChar* srce, size_t size);
typedef RwChar* (__cdecl* vecStrrchrFunc)(const RwChar* string, int findThis);
typedef RwChar* (__cdecl* vecStrchrFunc)(const RwChar* string, int findThis);
typedef RwChar* (__cdecl* vecStrstrFunc)(const RwChar* string, const RwChar* findThis);

typedef int(__cdecl* vecStrcmpFunc)(const RwChar* string1, const RwChar* string2);
typedef int(__cdecl* vecStrncmpFunc)(const RwChar* string1, const RwChar* string2, size_t max_size);
typedef int(__cdecl* vecStricmpFunc)(const RwChar* string1, const RwChar* string2);

typedef size_t(__cdecl* vecStrlenFunc)(const RwChar* string);
typedef RwChar* (__cdecl* vecStruprFunc)(RwChar* string);
typedef RwChar* (__cdecl* vecStrlwrFunc)(RwChar* string);
typedef RwChar* (__cdecl* vecStrtokFunc)(RwChar* string, const RwChar* delimit);
typedef int (*vecSscanfFunc)(const RwChar* buffer, const RwChar* format, ...);

struct RwFreeList;
typedef RwFreeList* (__cdecl* RwMemoryFreeFn)(RwFreeList* fl, void* pData);

typedef RwBool(__cdecl* RwStandardFunc)(void* pOut, void* pInOut, RwInt32 nI);
typedef void* (__cdecl* RwMemoryAllocFn)(RwFreeList* fl);
typedef RwTexture* (__cdecl* RwTextureCallBack)(RwTexture* texture, void* pData);
typedef RwObjectHasFrame* (__cdecl* RwObjectHasFrameSyncFunction)(RwObjectHasFrame* object);
typedef RpAtomic* (__cdecl* RpAtomicCallBack)(RpAtomic* atomic, void* data);




#endif