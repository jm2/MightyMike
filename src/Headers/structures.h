//
// Structures.h
//

#ifndef __STRUCT__
#define __STRUCT__


#define	SF_HEADER__SHAPE_LIST	4
#define	SHAPE_HEADER_ANIM_LIST	6

#define	MAX_SHAPES_IN_FILE		100


			/* PLAYFIELD ITEM RECORD */

typedef struct ObjectEntryType
{
	long			x,y;
	short			type;
	Byte			parm[4];
}ObjectEntryType;


			/*  OBJECT RECORD STRUCTURE */


struct ObjNode
{
	long		Genre;			// obj genre: 0=sprite, 1=nonsprite
	unsigned  long	Z;			// z sort value
	long		Type;			// obj type
	long		SubType;		// sub type (anim type)
	long		SpriteGroupNum;	// sprite group # (if sprite genre)
	Boolean		DrawFlag;		// set if draw this object
	Boolean		EraseFlag;		// set if erase this object
	Boolean		UpdateBoxFlag;	// set if automatically make update region for shape
	Boolean		MoveFlag;		// set if move this object
	Boolean		AnimFlag;		// set if animate this object
	Boolean		PFCoordsFlag;	// set if x/y coords are global playfield coords, not offscreen buffer coords
	Boolean		TileMaskFlag;	// set if PF draw should use tile masks
	union {
		long L;
		short Frac;
		short	Int;
	}YOffset;					// offset for y draw position on playfield
	short		ClipNum;		// clipping region # to use
	union {
		long L;
		short Frac;
		short	Int;
	}X;							// x coord (low word is fraction)
	union {
		long L;
		short Frac;
		short	Int;
	}Y;							// y coord (low word is fraction)
	long		OldX;			// old x coord (no fraction)
	long		OldY;			// old y coord
	Rect		drawBox;		// box obj was last drawn to

	long		DX;				// DX value (low word is fraction)
	long		DY;				// DY value
	long		DZ;				// DZ value
	void		(*MoveCall)(void);	// pointer to object's move routine
	Ptr			AnimsList;		// ptr to object's animations list. nil = none
	long			AnimLine;		// line # in current anim
	long			CurrentFrame;	// current frame #
	unsigned long AnimConst;		// default "setspeed" rate
	long		AnimCount;		// current value of rate
	unsigned long AnimSpeed;		// amt to subtract from count/rate
	Boolean		Flag0;
	Boolean		Flag1;
	Boolean		Flag2;
	Boolean		Flag3;
	long		Special0;
	long		Special1;
	long		Special2;
	long		Special3;
	long		Misc1;
	long		Misc2;
	unsigned long		CType;		// collision type bits
	unsigned long		CBits;		// collision attribute bits
	long			LeftSide;			// collision side coords
	long			RightSide;
	long			TopSide;
	long			BottomSide;
	long			TopOff;				// collision box side offsets
	long			BottomOff;
	long			LeftOff;
	long			RightOff;
	long			Kind;				// kind
	long			BaseX;
	long			BaseY;
	long			Health;				// health
	Ptr			SHAPE_HEADER_Ptr;	// addr of this sprite's SHAPE_HEADER
	long			OldLeftSide;
	long			OldRightSide;
	long			OldTopSide;
	long			OldBottomSide;
	ObjectEntryType *ItemIndex;		// pointer to item's spot in the ItemList
	struct ObjNode	*ShadowIndex;	// ptr to object's shadow or shadow's owner
	struct ObjNode  *OwnerToMessageNode;	// ptr to owner's message
	struct ObjNode  *MessageToOwnerNode;	// ptr to message's owner
	long			MessageTimer;		// time to display message

	long			Worth;				// "worth" of object / # coins to give
	long		InjuryThreshold;	// threshold for weapon to do damage to enemy

	long			NodeNum;			// node # in array (for internal use)
	struct ObjNode	*PrevNode;		// address of previous node in linked list
	struct ObjNode	*NextNode;		// address of next node in linked list
};
typedef struct ObjNode ObjNode;



					/* COLLISION STRUCTURES */
struct CollisionRec
{
	unsigned long	sides;
	unsigned long	type;
	ObjNode		*objectPtr;		// object that collides with (if object type)
};
typedef struct CollisionRec CollisionRec;

				/* ANIMATION STRUCTURES */

struct AnimEntryType
{
	short	opcode;
	short	operand;
};
typedef struct AnimEntryType AnimEntryType;


				/* GLOBAL COORDS STRUCT */
			/* actually defined on Object.c */

#define union_gX union {	\
	long L;			\
	char Frac;		\
	short	Int;		\
	} gX

#define union_gY union {	\
	long L;			\
	short Frac;		\
	short	Int;		\
	} gY


			/* SAVED PLAYER INFO */

struct PlayerSaveType
{
	Boolean		beenSavedData;						// set if player data is saved on disk
	Boolean		newAreaFlag;						// set if last save was before going to new area
	Boolean		donePlayingFlag;					// set when this player is no longer in the game
	long		score,numCoins;
	short		lives;
	Byte		currentWeaponType;
	Byte		scene,area;
	short		numEnemies,numBunnies;
	short		myX,myY;
	short		nodeStackFront;						// copy of NodeStackFront
	short		numObjects;							// # objects in list
	ObjNode		*firstNodePtr,*myNodePtr;
	short		myBlinkieTimer;
	Byte		numItemsInInventory,inventoryIndex_weapon;
	Boolean		keys[6];
	short		myHealth,myMaxHealth;
	short		lastNonDeathX,lastNonDeathY;
	Ptr			oldItemIndex;
};
typedef struct PlayerSaveType PlayerSaveType;


			/* LONG PT */

struct LongPoint
{
	long		v,h;
};
typedef struct LongPoint LongPoint;




#endif
