#include "blockworldgenerator.h"

#define MIN(a,b) (a<b)?(a):(b)
#define MAX(a,b) (a>b)?(a):(b)

bool getBT( BYTE B )
{
	return (bool) ((B>>SHR_BT)&1);
}

int  getTT( BYTE B )
{
	return (int) ((B>>SHR_TT)&7);
}

double  getSR( BYTE B )
{
	return SECURITY_MUL*(double)((B>>SHR_SR)&7);

}

BYTE randomSB()
{
	return ((BYTE)(genrand()*(double)255)&127); //ei haluta ekaa pystyyn

}

BYTE typeSB( int type )
{
		return ( ((type&7)<<SHR_TT) & randomSB() ); //ei haluta ekaa pystyyn
}


// TODO: combine
// FROM THIS ---------------------------------------------------------------
const char* getBlockInfo( BYTE b )
{
	char *keijo = (char*)malloc( 100 );
	sprintf( keijo, " %s kayty, maasto on %s ja security %4.3f", (getBT(b))?"on":"ei", getTTText(getTT(b)), getSR(b));		
	return  keijo;
}

const char* getTTText( int t )
{
	return TT_TEXT[t];
}

const char* getSubBlockInfo( BYTE b )
{
	char *keijo = (char*)malloc( 100 );
	sprintf( keijo, " %s kayty, maasto on %s ", (getBT(b))?"on":"ei", getSBText(getTT(b)) );		
	return  keijo;
}

const char* getSBText( int t )
{
	return SBT_TEXT[t];
}
// TO THIS ---------------------------------------------------------------



BYTE* createBWRand( int W, int H )
{
	int s=(W*H);
	BYTE *MAP = (BYTE*)malloc( s );
	for( int i = 0; i < s; i++ ) MAP[i]=randomSB();
	return MAP;
}

BYTE* createBWTikanheitto( int W, int H )
{
	int s=(W*H);	
	BYTE *MAP = (BYTE*)malloc( s );
	memset( (BYTE*)MAP, 0, s ); //easy plains
	MAP[0]=	randomSB();	
	MAP[W-1]=	randomSB();
	MAP[((H-1)*W)]=	randomSB();	
	MAP[((H-1)*W)+W-1]= randomSB();	
	createBlumps( W, H, MAP );
	
	return MAP;
}

void createBlumps( int W, int H, BYTE* MAP )
{
	int s=(W*H);	
	double ss = MIN(W, H)/2;
	double vaihtelu = ss/2.0;	
	int index = 0, temp, m;

	//pohjalle tavaraa
	for( m = 0; m <100; m++ )
		if( m&1 )
			createBlump( FOREST, ss, vaihtelu, W, H, MAP );
		else
			createBlump( WATER, ss, vaihtelu, W, H, MAP );

	
	//sitten vähän vuoria
	for( m = 0; m <2; m++ )
		createBlump( MOUNTAIN, ss+1, vaihtelu+1.0, W, H, MAP );

	//ja sitten muita vähemmän
	for( int i = 0; i < W*H; i++ ) 
	{
		index = (int) (genrand()*(double)(s-1));
		index++;

		temp = getTT(MAP[index]);
		if( temp == FOREST || temp == PLAINS || temp == WATER || temp == MOUNTAIN )
		{
			temp = getTT(MAP[index-1]);
			if( temp == FOREST || temp == PLAINS || temp == WATER || temp == MOUNTAIN)
				if( genrand()<0.8)
					MAP[index]=MAP[index-1];
				else
					MAP[index]=randomSB();
			else
				MAP[index]=randomSB();
		}
	}

}


void createBlump( int type, double size, double var, int W, int H, BYTE* MAP )
{
	int rivit, rt, rc, index, ix, iy, tv;
	//arvo muutama iso metsä
	rivit = (int)(/*genrand()**/size); //korkeus	
	iy = (int)(genrand()*(double)(H-rivit));	//missa kohtaa y akseli
	for( rc = 0; rc < rivit; rc++ )
	{

		iy+=rc;
		tv=(int)(genrand()*var);
		rt = (int)(size-(genrand()*size*0.5)); //leveys		
		ix = (int)(genrand()*(double)(W-rt-tv));    //missa kohtaa x akseli
		ix+= tv;
		if( ix < 0  || iy < 0 || ix >= W || iy >= H) break;
		index = iy*W+ix;
		memset((BYTE*)&MAP[index],typeSB(type), rt); 
	}
	
}




//BAD
BYTE* createBWQuattro( int W, int H )
{
	int s=(W*H);BYTE *MAP = (BYTE*)malloc( s );	memset( (BYTE*)MAP, 129, s );
	MAP[0]=	randomSB();	MAP[0+W-1]=	randomSB();
	MAP[((0+(H-1))*(W+0))]=	randomSB();	MAP[((0+(H-1))*(W+0))+W-1+0]= randomSB();	
	recurse( 0, 0, W, H, MAP, true );return MAP;
}

void recurse( int x, int y, int W, int H, BYTE* MAP, bool eka )
{	
	if( W<= 2 && H<= 2 ) return;
	if( !eka )
	{	if( MAP[x] == 129 )	  	MAP[x]=0x0fe;//randomSB();
		if( MAP[x+W-1] == 129 ) MAP[x+W-1]=0x0fe;//randomSB();
		if( MAP[((y+(H-1))*(W+x))] == 129 )	MAP[((y+(H-1))*(W+x))]=0x0fe;//	randomSB();
		if( MAP[((y+(H-1))*(W+x))+W-1+x]== 129 )MAP[((y+(H-1))*(W+x))+W-1+x]=0x0fe;// randomSB();	
	}
	int WW = W>>1;	int HH = H>>1;
	recurse( x,	y,	  WW, HH, MAP, false ); //vy
	recurse( x+WW, y,	  WW, HH, MAP, false ); //oy
	recurse( x,	y+HH, WW, HH, MAP, false ); //va
	recurse( x+WW,	y+HH, WW, HH, MAP, false ); //oa
	
}