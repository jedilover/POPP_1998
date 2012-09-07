//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-v
//
//	Note: Includes x levels of nesting easily.
//
//	Now different levels have different types,
//	there should be heightmap for each level that
//	can be used in generation of maps.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-v

#ifndef __BLOCKWORLDGENERATOR_H__
#define __BLOCKWORLDGENERATOR_H__ 1

#include <stdlib.h>
#include <string.h>
#include <stdio.h> //for sprintf
#include "random.h"

typedef unsigned char  BYTE;

enum MAP_LEVELS
{
	BLOCK,
	SUB_BLOCK
};

enum BLOCK_TERRAIN_TYPES
{
	PLAINS,
	WATER,
	FOREST,
	DESERT,
	MOUNTAIN,
	ARCTIC,
	SWAMP,
	VOLCANIC
};

static const char* TT_TEXT[] = 
{ 
	"PLAINS",	
	"WATER",
	"FOREST",
	"DESERT",
	"MOUNTAIN",
	"ARCTIC",
	"SWAMP",
	"VOLCANIC"
};

enum SUB_BLOCK_TYPES
{
	PLAIN,		//like normal grass or snow
	ROCK,		//something u cannot pass trough	
	BUSH,		//something u can pass through but with minue
	HOLE,		//something u can descent		
	POLE,		//something u can ascent	
	COMMON,		//something that really common stuff, ridle here
	SPECIAL,	//something here special here
	RARE		//something really really special here
};

static const char* SBT_TEXT[] = 
{ 
	"PLAIN",	
	"ROCK",
	"BUSH",
	"HOLE",
	"POLE",
	"COMMON",
	"SPECIAL",
	"RARE"
};


#define SECURITY_MUL 0.125


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//    FOR ROOT LEVEL "BLOCKS"	  
//
//   [1bit][3bit][3bit][1bit]
//	  used  type  sec
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#define SHR_BT 7	//BEEN_THERE_SHIFT	
#define SHR_TT 4	//TERRAIN_TYPE_SHIFT	
#define SHR_SR 1	//SECURITY_SHIFT

bool	getBT( BYTE B );
int		getTT( BYTE B );
double  getSR( BYTE B );

const char* getBlockInfo( BYTE b );
const char* getTTText(  int t );


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//  FOR CHILD LEVEL "SUBBLOCKS"
//
//   [1bit][3bit][3bit][1bit]
//    used  type  sec
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const char* getSubBlockInfo( BYTE b );
const char* getSBText( int t );



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-



BYTE randomSB();	//returns random subblock descprition	
BYTE typeSB( int type ); //returns subblock of selecte type
BYTE* createBWRand( int W, int H );
BYTE* createBWTikanheitto( int W, int H );
BYTE* createBWQuattro( int W, int H );

void recurse( int x, int y, int W, int H, BYTE* MAP, bool totuus );
void createBlump( int type, double size, double var, int W, int H, BYTE* MAP );
void createBlumps( int W, int H, BYTE* MAP );

#endif