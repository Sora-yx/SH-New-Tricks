

#ifndef HEROESTRUCTS_H
#define HEROESTRUCTS_H

#include <stdint.h>
#include "HeroesEnum.h"

#pragma pack(push, 4)

struct C_COLLI;
struct RwMatrixTag;
typedef RwMatrixTag RwMatrix;
struct PARTICLE_MATERIAL;

struct CCL_HIT_INFO;
struct CLASS_PATH;
struct TObjTeam;
struct PL_MOTION;
struct RwLinkList;
struct RwLLLink;
struct RwObject;
struct RpClump;


struct sAngle
{
	int x;
	int y;
	int z;
};


struct sRealAngle3
{
	RwReal x;
	RwReal y;
	RwReal z;
};

struct RwV3d
{
	RwReal x;
	RwReal y;
	RwReal z;
};

struct RwLLLink
{
	RwLLLink* next;
	RwLLLink* prev;
};

struct RwLinkList
{
	RwLLLink link;
};

struct RwMatrixTag
{
	RwV3d right;
	RwMatrixFlag flags;
	RwV3d up;
	RwUInt32 pad1;
	RwV3d at;
	RwUInt32 pad2;
	RwV3d pos;
	RwUInt32 pad3;
};



struct TObject
{
	void* __vftable /*VFT*/;
	char* ClassName;
	unsigned __int16 Signal;
	unsigned __int16 Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
	unsigned __int16 ExecTime;
	unsigned __int16 DispTime;
	unsigned __int16 TDispTime;
	unsigned __int16 PDispTime;
	unsigned __int16 ImmAftSetRasterTime;
	__int16 field_26;
};

struct PL_BUTTON_STATUS
{
	char jump;
	char action;
	char sfa;
	char formChangeL;
	char formChangeR;
	char BYTE_0X5;
	char BYTE_0X6;
};

struct RwRaster
{
	RwRaster* parent;
	RwUInt8* cpPixels;
	RwUInt8* palette;
	RwInt32 width;
	RwInt32 height;
	RwInt32 depth;
	RwInt32 stride;
	RwInt16 nOffsetX;
	RwInt16 nOffsetY;
	RwUInt8 cType;
	RwRasterType cFlags;
	RwUInt8 privateFlags;
	RwUInt8 cFormat;
	RwUInt8* originalPixels;
	RwInt32 originalWidth;
	RwInt32 originalHeight;
	int originalStride;
};

struct RwObject
{
	RwUInt8 type;
	RwUInt8 subType;
	RwUInt8 flags;
	RwUInt8 privateFlags;
	void* parent;
};

struct RwFrame
{
	RwObject object;
	RwLLLink inDirtyListLink;
	RwMatrixTag modelling;
	RwMatrixTag ltm;
	RwLinkList objectList;
	RwFrame* child;
	RwFrame* next;
	RwFrame* root;
};

struct RwTexDictionary
{
	RwObject object;
	RwLinkList texturesInDict;
	RwLLLink lInInstance;
};


struct RwTexture
{
	RwRaster* raster;
	RwTexDictionary* dict;
	RwLLLink lInDictionary;
	RwChar name[32];
	RwChar mask[32];
	RwUInt32 filterAddressing;
	RwInt32 refCount;
};


struct RwMemory {
	unsigned char* start; // offset 0x0, size 0x4
	unsigned int length; // offset 0x4, size 0x4
};

struct RwStreamMemory {
	unsigned int position; // offset 0x0, size 0x4
	unsigned int nSize; // offset 0x4, size 0x4
	unsigned char* memBlock; // offset 0x8, size 0x4
};

struct RwStreamCustom 
{
	signed int (*sfnclose)(void*); // offset 0x0, size 0x4
	unsigned int (*sfnread)(void*, void*, unsigned int); // offset 0x4, size 0x4
	signed int (*sfnwrite)(void*, void*, unsigned int); // offset 0x8, size 0x4
	signed int (*sfnskip)(void*, unsigned int); // offset 0xC, size 0x4
	void* data; // offset 0x10, size 0x4
};



struct RwStreamFile 
{
	void* fpFile; // offset 0x0, size 0x4
	void* constfpFile; // offset 0x0, size 0x4
};

struct RwStreamUnion 
{
	RwStreamMemory memory; // offset 0x0, size 0xC
	RwStreamFile file; // offset 0x0, size 0x4
	RwStreamCustom custom; // offset 0x0, size 0x14
};

struct ONE_FILEINFO 
{
	char filename[256][64]; // offset 0x0, size 0x4000
};


struct RwObjectHasFrame
{
	RwObject object;
	RwLLLink lFrame;
	RwObjectHasFrameSyncFunction sync;
};

struct RwSphere
{
	RwV3d center;
	RwReal radius;
};

struct RpHAnimNodeInfo
{
	RwInt32 nodeID;
	RwInt32 nodeIndex;
	RwInt32 flags;
	RwFrame* pFrame;
};


struct RpInterpolator
{
	RwInt32 flags;
	RwInt16 startMorphTarget;
	RwInt16 endMorphTarget;
	RwReal time;
	RwReal recipTime;
	RwReal position;
};


struct RpAtomic
{
	RwObjectHasFrame object;
	void* repEntry;
	void* geometry;
	RwSphere boundingSphere;
	RwSphere worldBoundingSphere;
	RpClump* clump;
	RwLLLink inClumpLink;
	RpAtomic* (__cdecl* renderCallBack)(struct RpAtomic*);
	RpInterpolator interpolator;
	unsigned __int16 renderFrame;
	unsigned __int16 pad;
	struct RwLinkList llWorldSectorsInAtomic;
	struct RxPipeline* pipeline;
};


struct RwStream 
{
	RwStreamType type; // offset 0x0, size 0x4
	RwStreamAccessType accessType; // offset 0x4, size 0x4
	signed int position; // offset 0x8, size 0x4
	RwStreamUnion Type; // offset 0xC, size 0x14
	signed int rwOwned; // offset 0x20, size 0x4
};

struct RwMemoryFunctions
{
	void* (__cdecl* rwmalloc)(size_t size);
	void(__cdecl* rwfree)(void* mem);
	void* (__cdecl* rwrealloc)(void* mem, size_t newSize);
	void* (__cdecl* rwcalloc)(size_t numObj, size_t sizeObj);
};

struct RwFreeList
{
	RwUInt32 entrySize;
	RwUInt32 entriesPerBlock;
	RwUInt32 heapSize;
	RwUInt32 alignment;
	RwLinkList blockList;
	RwUInt32 flags;
	RwLLLink link;
};

struct RwFileFunctions
{
	rwFnFexist rwfexist;
	rwFnFopen rwfopen;
	rwFnFclose rwfclose;
	rwFnFread rwfread;
	rwFnFwrite rwfwrite;
	rwFnFgets rwfgets;
	rwFnFputs rwfputs;
	rwFnFeof rwfeof;
	rwFnFseek rwfseek;
	rwFnFflush rwfflush;
	rwFnFtell rwftell;
};

struct RwStringFunctions
{
	vecSprintfFunc vecSprintf;
	vecVsprintfFunc vecVsprintf;
	vecStrcpyFunc vecStrcpy;
	vecStrncpyFunc vecStrncpy;
	vecStrcatFunc vecStrcat;
	vecStrncatFunc vecStrncat;
	vecStrrchrFunc vecStrrchr;
	vecStrchrFunc vecStrchr;
	vecStrstrFunc vecStrstr;
	vecStrcmpFunc vecStrcmp;
	vecStrncmpFunc vecStrncmp;
	vecStricmpFunc vecStricmp;
	vecStrlenFunc vecStrlen;
	vecStruprFunc vecStrupr;
	vecStrlwrFunc vecStrlwr;
	vecStrtokFunc vecStrtok;
	vecSscanfFunc vecSscanf;
};

struct RwGlobals
{
	void* curCamera;
	void* curWorld;
	RwUInt16 renderFrame;
	RwUInt16 lightFrame;
	RwUInt16 pad[2];
	char dOpenDevice[0x38];
	RwStandardFunc stdFunc[29];
	RwLinkList dirtyFrameList;
	RwFileFunctions fileFuncs;
	RwStringFunctions stringFuncs;
	RwMemoryFunctions memoryFuncs;
	RwMemoryAllocFn memoryAlloc;
	RwMemoryFreeFn memoryFree;
	void* metrics;
	RwEngineStatus engineStatus;
	RwUInt32 resArenaInitSize;
};

struct rwStreamGlobals
{
	RwFreeList* streamFreeList;
};


struct ONEFILE
{
	char fname[64]; // offset 0x0, size 0x40
	void* exBuffer; // offset 0x40, size 0x4
	ONE_FILEINFO* oneFileInfo; // offset 0x44, size 0x4
	signed int showError; // offset 0x48, size 0x4
	signed int flagBW; // offset 0x4C, size 0x4
	RwMemory memInfo; // offset 0x50, size 0x8
	RwStream* mCurStream; // offset 0x58, size 0x4
};


struct PLAYER_INPUT
{
	float stroke;
	DWORD angle;
	BYTE moveEdgePressed;
	PL_BUTTON_STATUS PL_BUTTON_STATUS;
};



struct PARTICLE_SPRITE
{
	_BYTE gap0[12];
	void* atomic_HHC;
	void* SPRITE_INFO;
};

struct PARTICLE_INSTANCE
{
	void* nextInstance_HHC;
	PARTICLE_MATERIAL* PARTICLE_MATERIAL;
	_BYTE gap8[60];
	int field_44;
};


struct PARTICLE_MATERIAL
{
	void* __vftable /*VFT*/;
	__int16 short_0x4;
	RwInt32 flags;
	_BYTE gapC[16];
	RwReal field_1C;
	RwReal field_20;
	_BYTE gap24[4];
	RwReal field_28;
	_BYTE gap2C[4];
	RwInt32 spriteFlags;
	RwFrame* field_34;
	PARTICLE_SPRITE* PARTICLE_SPRITE;
	void* texture_HHC; //RW TEXTURE MISSING
	_BYTE gap40[8];
	PARTICLE_MATERIAL* lastMaterial_HHC;
	PARTICLE_MATERIAL* nextMaterial_HHC;
	PARTICLE_INSTANCE* lastInstance_HHC;
	PARTICLE_INSTANCE* nextInstance_HHC;
	RwV3d pos;
	sAngle ang;
	_BYTE gap70[8];
	int field_78;
};

struct RwRGBA
{
	RwUInt8 red;
	RwUInt8 green;
	RwUInt8 blue;
	RwUInt8 alpha;
};


struct PARTICLE_TASK : TObject
{
	PARTICLE_MATERIAL PARTICLE_MATERIAL;
	_BYTE gapA4[16];
	RwRGBA colorMaybe;
};


struct RpClump
{
	RwObject object;
	RwLinkList atomicList;
	RwLinkList lightList;
	RwLinkList cameraList;
	RwLLLink inWorldLink;
	RpClump* (__cdecl* callback)(struct RpClump*, void*);
};



struct MOTIONWK
{
	RwV3d spd;
	RwV3d acc;
	sAngle ang_aim;
	sAngle ang_spd;
	signed int ang_shoulder;
	unsigned int reserve0;
	unsigned int reserve1;
	unsigned int reserve2;
};

struct player_parameter
{
	int jump2_timer;
	float pos_error;
	float lim_h_spd;
	float lim_v_spd;
	float max_x_spd;
	float max_psh_spd;
	float jmp_y_spd;
	float nocon_speed;
	float slide_speed;
	float jog_speed;
	float run_speed;
	float rush_speed;
	float crash_speed;
	float dash_speed;
	float jmp_addit;
	float run_accel;
	float air_accel;
	float slow_down;
	float run_break;
	float air_break;
	float air_resist_air;
	float air_resist;
	float air_resist_y;
	float air_resist_z;
	float grd_frict;
	float grd_frict_z;
	float lim_frict;
	float rat_bound;
	float rad;
	float height;
	float weight;
	float eyes_height;
	float center_height;
};



struct PATHTAG
{
	RwInt16 pathtype;
	RwInt16 points;
	RwReal totallen;
	RwV3d* tblhead;
	void(__cdecl* pathtask)(CLASS_PATH*);
};


struct CLASS_PATH
{
	char field_0;
	char field_1;
	__int16 field_2;
	_BYTE gap4[64];
	PATHTAG* field_44;
	_BYTE gap48[8];
	CLASS_PATH* field_50;
	void(__cdecl* pFunction_HHC)(CLASS_PATH*);
};



struct CCL_INFO
{
	char kind;
	char form;
	char push;
	char damage;
	unsigned int attr;
	RwV3d center;
	RwReal rad;
	RwReal center_height;
	RwReal horizontalObjectCollisionRadiusMaybe;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
};


struct CCL_HIT_INFO
{
	char my_num;
	char hit_num;
	unsigned __int16 flag;
	C_COLLI* hit_twp;
};

struct C_COLLI
{
	unsigned __int16 id;
	signed __int16 nbHit;
	__int16 strength;
	__int16 vitality;
	__int16 flag;
	__int16 nbInfo;
	float colli_range;
	CCL_INFO* info;
	CCL_HIT_INFO hit_info[8];
	RwV3d normal;
	RwV3d pos;
	sAngle angle;
	int character_id;
	RwV3d field_7C;
};

struct EffWink
{
	float patno;
	float patno_max;
	float patno_speed;
	Enum_EffWinkMode mode_last;
	Enum_EffWinkMode mode;
	signed int timer;
	signed int interval;
	signed int interval_base;
	signed int interval_diff;
	signed int wink;
};




struct RpHAnimHierarchy
{
	RwInt32 flags;
	RwInt32 numNodes;
	RwMatrix* pMatrixArray;
	void* pMatrixArrayUnaligned;
	RpHAnimNodeInfo* pNodeInfo;
	RwFrame* parentFrame;
	RpHAnimHierarchy* parentHierarchy;
	RwInt32 rootParentOffset;
	RtAnimInterpolator* currentAnim;
};


struct PL_NODE_PARAMETER
{
	signed int node_number;
	struct RwFrame* pFrame_Root;
	struct RwFrame* pFrame;
	struct RwMatrixTag matrix;
	struct RwV3d pos;
	struct RwV3d vec;
};

struct PL_NODE_PARAMETERT //test
{
	signed int node_number;
	struct RwFrame* pFrame_Root;
	struct RwFrame* pFrame;
	int paddingCrap;
	struct RwMatrixTag matrix;
	struct RwV3d pos;
	struct RwV3d vec;
	int padding[2];
};


struct EffShadow
{
	char pnoMaybe;
	char field_1;
	float field_4;
	_BYTE gap8[36];
	RwFrame* field_2C;
	RpClump* field_30;
	_BYTE gap34[8];
	RpHAnimHierarchy* hAnimTailsShadow__;
};

struct EffBall
{
	RwRGBA color;
	RpClump* clumps_HHC[6];
};

struct SONICWK
{
	signed __int16 lsdtm;
	signed __int16 modetm;
	signed __int16 downtm;
	signed __int16 ringcnt;
	RwV3d preringpos;
	RwV3d pos_Start;
	char pClump[144];
	EffWink Eyelid;
};

struct TObjSonic
{
	void* vtbl;
	char objectName;
	_BYTE gap5[25];
	char objectSize;
	_BYTE gap1F[13];
	int collisionNumberMaybe;
	WORD currentDamage;
	_BYTE gap32[10];
	CCL_INFO* collisionStuff;
	_BYTE gap40[100];
	int CCLCharacterId;
	_BYTE gapA8[12];
	int field_B4;
	_BYTE gapB8[2];
	BYTE formationTypeID;
	Character characterID;
	BYTE suitNo;
	char field_BD;
	BYTE teamNo;
	BYTE teamMemberID;
	BYTE controllerNo;
	char role;
	char formationLeaderNo;
	__int16 ItemFlags;
	int superFlag;
	TObjTeam* pTObjTeam;
	_BYTE gapD0[4];
	WORD jumpBallTime;
	WORD delayMovementTime;
	WORD idleTime;
	WORD nextAnimation;
	float slopeAngle;
	_BYTE gapE4[16];
	WORD mode;
	WORD stateCopy;
	WORD modeChange;
	WORD flashTimer;
	float flt_0xfc;
	float flt_0x100;
	float flt_0x104;
	RwV3d spd;
	RwV3d position;
	sAngle rotation;
	RwV3d scale;
	RwV3d speedCopy;
	RwV3d acceleration;
	sAngle rotationCopy;
	RwV3d pushedSpeed;
	_BYTE gap168[24];
	sAngle accelerationDirection;
	RwV3d slopeCollisionAngleMaybe;
	int int0x198_wallJumpRotationMaybe;
	int int0x19C_wallJumpRotationMaybe;
	int int0x1A0_wallJumpRotationMaybe;
	int statusRelated0x1A4;
	int statusRelated0x1A8;
	int playerStatus_0x1AC_PhysicsMaybe;
	_BYTE gap1B0[4];
	int field_1B4;
	int statusRelated0x1B8;
	int statusBits;
	char playerStatus_0x1C0;
	player_parameter playerpwp;
	BYTE waterEffectIs2;
	DWORD DWORD_0x250;
	DWORD DWORD_0x254;
	float groundBelowFallMaybe;
	float groundHeight;
	_BYTE gap260[12];
	RwV3d flyFormationPosition;
	int npcTargetRelatedMaybe0x278;
	float field_27C;
	float notStartMovingRad;
	float distanceXZToTargetPosCopy;
	float distanceXZToTargetPos;
	_BYTE gap28C[60];
	ENUM_CHAR_MODE charMode;
	ENUM_CHAR_MODE lastAIState;
	ENUM_CHAR_MODE charModeReserve;
	__int16 relatedToSwitchingRails;
	float pathPointDistance;
	void* PATHTAG;
	_BYTE gap2D8[5];
	BYTE finaleFlipType;
	WORD airAttackTimer;
	_WORD airAttackTimer2;
	DWORD flyFormationYTilt;
	DWORD flyFormationZTilt;
	DWORD flyFormationBoostYTilt;
	_BYTE gap2F8[20];
	WORD grindTimer;
	_BYTE gap30E[6];
	WORD powerAirSpinTimer;
	float powerAirSpinDistance;
	WORD tornadoTimer;
	float tornadoRadius;
	RwV3d tornadoPosition;
	float field_330;
	float field_334;
	_BYTE gap338[8];
	int someTimerMaybeFlashRelated;
	_BYTE gap344[84];
	WORD animationIndex;
	WORD animation;
	WORD animationCopy;
	_BYTE gap39E[46];
	RpClump* clump_3CC;
	_BYTE gap3D0[344];
	_BYTE gap528[1012];
	void* pTexture;
	void* textureRelated;
	int field_924;
	_BYTE gap928[100];
	RwV3d field_98C;
	RwV3d lightAttackPos_HHC;
	_BYTE gap9A4[12];
	_BYTE gap9B0[36];
	_BYTE gap9D4[28];
	DWORD* pSuperSonicAura;
	_BYTE gap9F4[12];
	void* pSuperSonicSparkles;
	int field_A04;
};


//I removed some alignement to do check if it still work
struct TObjPlayer : TObject
{
	_BYTE gap28[4];
	C_COLLI C_COLLI_;
	_BYTE gapB4[6];
	char playerNo;
	char characterKind;
	BYTE suitNo;
	char field_BD;
	char teamNo_HHC;
	BYTE memberNo;
	BYTE controllerNo;
	char role;
	char formationLeaderNo;
	__int16 item;
	int equipment;
	TObjTeam* pTObjTeam;
	_BYTE gapD0[4];
	WORD jumpBallTime;
	WORD nocontimer;
	WORD idleTime;
	RwInt32 nextAnimation_HHC;
	float dotp;
	int accel;
	float frict;
	RwReal field_EC;
	float field_F0;
	WORD mode;
	WORD stateCopy;
	WORD smode;
	WORD flashTimer;
	RwV3d acc;
	RwV3d spd;
	RwV3d position;
	sAngle ang;
	RwV3d scale;
	MOTIONWK mwp;
	RwV3d field_174;
	sAngle accelerationDirection;
	RwV3d slopeCollisionAngleMaybe;
	int int0x198_wallJumpRotationMaybe;
	int int0x19C_wallJumpRotationMaybe;
	int int0x1A0_wallJumpRotationMaybe;
	int attr;
	int last_attr;
	int playerStatus_0x1AC_PhysicsMaybe;
	_BYTE gap1B0[4];
	int field_1B4;
	int statusRelated0x1B8;
	__int16 flag;
	int playerStatus_0x1C0;
	player_parameter p;
	BYTE waterEffectIs2;
	DWORD DWORD_0x250;
	DWORD DWORD_0x254;
	float groundBelowFallMaybe;
	float groundHeight;
	_BYTE gap260[12];
	RwV3d flyFormationPosition;
	int targetPosGroundPolyGroupNo;
	float field_27C;
	float notStartMovingRad;
	float distanceXZToTargetPosCopy;
	float distanceXZToTargetPos;
	_BYTE gap28C[60];
	ENUM_CHAR_MODE charMode;
	ENUM_CHAR_MODE lastAIState;
	ENUM_CHAR_MODE charModeReserve;
	__int16 relatedToSwitchingRails;
	RwReal hpos;
	PATHTAG* pathtag;
	_BYTE gap2D8[5];
	BYTE finaleFlipType;
	WORD airAttackTimer;
	_WORD airAttackTimer2;
	C_COLLI* cwp;
	DWORD flyFormationYTilt;
	DWORD idk;
	DWORD flyFormationZTilt;
	DWORD flyFormationBoostYTilt;
	_BYTE gap2F8[20];
	WORD grindTimer;
	_BYTE gap30E[6];
	WORD powerAirSpinTimer;
	float powerAirSpinPositionRelated;
	WORD tornadoTimer;
	_BYTE gap31E[6];
	RwV3d tornadoOrigin;
	float alphaAmount__;
	int idk2[3];
	int someTimerMaybeFlashRelated;
	float holdingWorksMaybe[4];
	_BYTE gap354[64];
	char field_394;
	char field_395;
	char field_396[2];
	WORD animationIndex;
	WORD motion;
	WORD reqaction;
	__int16 action;
	__int16 lastaction;
	__int16 nextaction;
	__int16 acttimer;
	_BYTE gap3A5[6];
	float animFrameMaybe;
	float field_3B0;
	_BYTE gap3B4[8];
	RwReal field_3BC;
	_BYTE gap3C0[4];
	float* field_3C4;
	PL_MOTION* animList;
	RpClump* clump_3CC;
	RpHAnimHierarchy* field_3D0;
	RpHAnimHierarchy* field_3D4;
	RpHAnimHierarchy* field_3D8;
	_BYTE gap3DC[40];
	PL_NODE_PARAMETER field_404;
	_BYTE gap460[4];
	char field_464;
	PL_NODE_PARAMETER field_468;
	_BYTE gap4C4[8];
	PL_NODE_PARAMETER field_4CC;
	int gap528[2];
	PL_NODE_PARAMETER field_530;
	_BYTE gap58C[8];
	PL_NODE_PARAMETER field_594;
	_BYTE gap5F0[108];
	PL_NODE_PARAMETER field_65C;
	_BYTE gap6B8[4];
	_BYTE gap6BC[608 / 2];
	_BYTE gapAgain[608 / 2];
	void* pTexture;
	void* textureRelated;
	int muteCount;
	EffShadow EffShadow;
	EffBall EffBall_HHC;
	__int16 lightDashStopCount_HHC;
	__int16 lightDashCountSinceLastRing_HHC;
	_BYTE gap988[2];
	__int16 lightDashRingCount_HHC;
	RwV3d lightDashLastRingPos_HHC;
	_BYTE gap998[12];
	float field_9A4;
	int field_9A8;
	int field_9AC;
	EffWink pEffWink;
	int field_9D8;
	int field_9DC;
	int field_9E0;
	int field_9E4;
	int field_9E8;
	RpClump* pClumpSuperAura_HHC;
	RpHAnimHierarchy* pSuperSonicAura;
	RwV3d field_9F4;
	void* pSuperSonicSparkles;
	_BYTE gapA04[56];
	char field_0;
};


struct TObjTeam : TObject
{
	_BYTE gap0[4];
	int pointer_0x2c;
	char field_30;
	ENUM_TEAM_KIND teamKind;
	char teamNo;
	BYTE numOfTeamMembersActive;
	char leaderPlayerNo;
	char nowLeaderPlayerNo;
	BYTE cameraTarget;
	char field_3D;
	__int16 cameraTargetPositionHistoryCount;
	RwV3d camTargetPos;
	RwV3d cameraTargetPositionHistory[16];
	float flightVerticalCamSpeed;
	char playerNo[3];
	TObjPlayer* playerPtr[3];
	BYTE formationMemberNo;
	BYTE postedMemberNumber;
	char memberAvailableCopy_HHC[3];
	char memberAvailable_HHC[3];
	TObjPlayer* pFormationMember[3];
	TObjPlayer* pPostedMember0;
	TObjPlayer* pPostedMember1;
	TObjPlayer* pPostedMember2;
	int formationNo;
	int oldFormationNo;
	int formationNoRelated;
	char controllerNo;
	char specialActionButtonStatus;
	WORD SFACount;
	ENUM_TEAMPLAY_MODE teamPlayModeReserve;
	ENUM_TEAMPLAY_MODE teamplayMode;
	int lastTeamPlayMode;
	PLAYER_INPUT player_input_HHC[10];
	__int16 autoMoveTime;
	WORD lightAttackTime;
	WORD speedShoesTimer;
	__int16 MutekiTime;
	__int16 prohibitionOfFormationChange;
	ItemFlags ItemFlags;
	char level[3];
	BYTE railRideFlag;
	_BYTE gap20C;
	char prohibitFormationChangeNo[3];
	char field_210;
	_BYTE gap211[11];
	char SFADamageForEnemy;
	BYTE neonScreen;
	BYTE whiteScreen;
	RwV3d SFABasePos;
	char SFABaseAngleY;
	PARTICLE_TASK* field_230;
	_BYTE gap234[8];
	int chaotixClearItem;
	_BYTE gap240[12];
	char techniquePoint[8];
	char techniquePoint2[8];
	char techniquePoint3[8];
	BYTE suitNo;
	char isCasinoBallLane;
	char BYTE_0x266;
	BYTE dontUsePinballMode;
	int* cameraMotionGoal;
	RpClump* cameraMotionTB;
	void* cameraMotionTB2;
	_BYTE gap274[4];
	int field_278;
};

struct PL_MOTION
{
	signed __int16 thismotdat;
	signed __int16 mtnmode;
	signed __int16 next;
	signed __int16 dummy;
	float start;
	float end;
	float interpolate_delta;
	float speed;
};

struct RtAnimInterpolatorInfo
{
	RwInt32 typeID;
	RwInt32 interpKeyFrameSize;
	RwInt32 animKeyFrameSize;
	RtAnimKeyFrameApplyCallBack keyFrameApplyCB;
	RtAnimKeyFrameBlendCallBack keyFrameBlendCB;
	RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB;
	RtAnimKeyFrameAddCallBack keyFrameAddCB;
	RtAnimKeyFrameMulRecipCallBack keyFrameMulRecipCB;
	RtAnimKeyFrameStreamReadCallBack keyFrameStreamReadCB;
	RtAnimKeyFrameStreamWriteCallBack keyFrameStreamWriteCB;
	RtAnimKeyFrameStreamGetSizeCallBack keyFrameStreamGetSizeCB;
	RwInt32 customDataSize;
};

struct RtAnimInterpolator
{
	RtAnimAnimation* pCurrentAnim;
	RwReal currentTime;
	void* pNextFrame;
	RtAnimCallBack pAnimCallBack;
	void* pAnimCallBackData;
	RwReal animCallBackTime;
	RtAnimCallBack pAnimLoopCallBack;
	void* pAnimLoopCallBackData;
	RwInt32 maxInterpKeyFrameSize;
	RwInt32 currentInterpKeyFrameSize;
	RwInt32 currentAnimKeyFrameSize;
	RwInt32 numNodes;
	RwBool isSubInterpolator;
	RwInt32 offsetInParent;
	RtAnimInterpolator* parentAnimation;
	RtAnimKeyFrameApplyCallBack keyFrameApplyCB;
	RtAnimKeyFrameBlendCallBack keyFrameBlendCB;
	RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB;
	RtAnimKeyFrameAddCallBack keyFrameAddCB;
};


struct RtAnimAnimation
{
	RtAnimInterpolatorInfo* interpInfo;
	signed int numFrames;
	signed int flags;
	float duration;
	void* pFrames;
	void* customData;
};


struct MML_MOTIONTABLE
{
	signed int thismotion;
	signed int id;
	RtAnimAnimation* ptr;
	void* pARAM;
};

struct sHeap
{
	sHeap* Next;
	unsigned int Size;
};


struct THeapCtrl
{
	sHeap* HeapTop;
	unsigned int HeapSize;
	unsigned int Boundary;
};



struct TObjCannon
{
	_BYTE gap0[184];
	DWORD state;
	_BYTE gapBC[12];
	DWORD DWORD_0xC8;
	DWORD DWORD_0xCC;
	DWORD DWORD_0xD0;
	BYTE pno;
	BYTE formationTypeMaybe;
	BYTE numPlayersInCanon;
	_BYTE gapD7[3];
	BYTE playersInCanonBitFieldMaybe;
	BYTE BYTE_0xDB;
	WORD cooldown;
	WORD uncurlTimer;
	WORD WORD_0xE0;
	WORD WORD_0xE2;
	DWORD speedTargetYRotation;
	DWORD flyTargetYRotation;
	DWORD powerTargetYRotation;
	DWORD speedTargetXRotation;
	DWORD flyTargetXRotation;
	DWORD powerTargetXRotation;
	DWORD yRotation;
	DWORD xRotation;
	_BYTE gap104[95];
	char field_0;
};

struct OBJ_MoveOnGround
{
	unsigned short cCheck; // offset 0x0, size 0x2
	unsigned short flagMOG; // offset 0x2, size 0x2
	OBJ_MOG_BOUND_MODE bound_mode; // offset 0x4, size 0x4
	RwV3d posCenter; // offset 0x8, size 0xC
	sRealAngle3 angGround; // offset 0x14, size 0xC
	RwV3d spdObject; // offset 0x20, size 0xC
	float radObject; // offset 0x2C, size 0x4
	float bound_coef; // offset 0x30, size 0x4
	unsigned int lattr_Ignore; // offset 0x34, size 0x4
};


struct TObjDummyRingBomb : TObject, C_COLLI, OBJ_MoveOnGround
{
	TObjDummyRingBomb* next_drb;
	TObjDummyRingBomb* last_drb;
	signed __int8 teamNo;
	signed __int8 mode;
	signed __int16 timer;
	struct RwV3d pos;
	struct RwV3d spd;
	struct RwV3d pos_shadow;
	struct sAngle ang_shadow;
	signed int rotation;
	float scale;
	void* pClumpInstance;
};


struct TObjCheese
{
	TObject obj;
	C_COLLI ccl;
	OBJ_MoveOnGround objMoveGround;
	signed __int8 playerno;
	signed __int8 animno;
	signed __int8 disp_event;
	signed __int16 mode;
	signed __int16 timer_Attack;
	struct RwV3d pos_Target;
	struct RwV3d pos;
	struct sAngle ang;
	float spd;
	float dist_Target;
	float nframe;
	struct RwV3d pos_shadow;
	struct sRealAngle3 ang_shadow;
	struct PL_NODE_PARAMETER head;
	struct PARTICLE_TASK* pPtcl_SFA[8];
};


struct TObjFormGateSub
{
	TObject obj_;
	C_COLLI col_;
	char formation;
	int mode;
	float width_offset;
};



struct TObjSetObj
{
	int __vftable;
	void* objTable;
	C_COLLI cwp;
};



struct TObjSignal : TObject, TObjSetObj, C_COLLI
{
	signed __int8 formation;
	RwV3d pos;
	RwV3d pos_org;
	sAngle ang;
	void* pClumpInstance;
	RwV3d pos_shadow;
	sRealAngle3 ang_shadow;
};


struct RwModuleInfo
{
	RwInt32 globalsOffset;
	RwInt32 numInstances;
};


struct CCL_SEARCH
{
	void** pTaskwk;
	void* FuncAddr;
	int CurrNum;
	int Kind;
};

#pragma pack(pop)

#endif /* SADXMODLOADER_SADXSTRUCTS_H */