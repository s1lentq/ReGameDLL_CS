/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef MODEL_H
#define MODEL_H
#ifdef _WIN32
#pragma once
#endif

#include "maintypes.h"
#include "const.h"
#include "bspfile.h"
//#include "quakedef.h"
#include "crc.h"

#define TEX_SPECIAL		1		// sky or slime, no lightmap or 256 subdivision

#define SURF_PLANEBACK		2
#define SURF_DRAWSKY		4
#define SURF_DRAWSPRITE		8
#define SURF_DRAWTURB		0x10
#define SURF_DRAWTILED		0x20
#define SURF_DRAWBACKGROUND	0x40

#define MAX_MODEL_NAME		64
#define MIPLEVELS		4
#define NUM_AMBIENTS		4
#define MAXLIGHTMAPS		4
#define MAX_KNOWN_MODELS	1024

typedef enum
{
	ST_SYNC = 0,
	ST_RAND
} synctype_t;

/* <6816> ../engine/model.h:27 */
typedef struct mvertex_s
{
	vec3_t position;
} mvertex_t;

/* <6838> ../engine/model.h:39 */
typedef struct mplane_s
{
	vec3_t normal;			// surface normal
	float dist;			// closest appoach to origin
	byte type;			// for texture axis selection and fast side tests
	byte signbits;			// signx + signy<<1 + signz<<1
	byte pad[2];
} mplane_t;

/* <68a6> ../engine/model.h:48 */
typedef struct texture_s
{
	char name[16];
	unsigned width, height;
	int anim_total;				// total tenths in sequence ( 0 = no)
	int anim_min, anim_max;			// time for this frame min <=time< max
	struct texture_s *anim_next;		// in the animation sequence
	struct texture_s *alternate_anims;	// bmodels in frame 1 use these
	unsigned offsets[MIPLEVELS];		// four mip maps stored
	unsigned paloffset;
} texture_t;

/* <6950> ../engine/model.h:71 */
typedef struct medge_s
{
	unsigned short v[2];
	unsigned int cachededgeoffset;
} medge_t;

/* <697e> ../engine/model.h:78 */
typedef struct mtexinfo_s
{
	float vecs[2][4];			// [s/t] unit vectors in world space.
	float mipadjust;			// ?? mipmap limits for very small surfaces
	texture_t *texture;
	int flags;				// sky or slime, no lightmap or 256 subdivision
} mtexinfo_t;

/* <69d0> ../engine/model.h:91 */
typedef struct msurface_s msurface_t;

/* <1db66> ../engine/model.h:92 */
typedef struct decal_s decal_t;

// JAY: Compress this as much as possible
/* <1db71> ../engine/model.h:96 */
struct decal_s
{
	decal_t *pnext;			// linked list for each surface
	msurface_t *psurface;		// Surface id for persistence / unlinking
	short dx;			// Offsets into surface texture (in texture coordinates, so we don't need floats)
	short dy;
	short texture;			// Decal texture
	byte scale;			// Pixel scale
	byte flags;			// Decal flags
	short entityIndex;		// Entity this is attached to
};

/* <69db> ../engine/model.h:118 */
struct msurface_s
{
	int visframe;			// should be drawn when node is crossed
	int dlightframe;		// last frame the surface was checked by an animated light
	int dlightbits;			// dynamically generated. Indicates if the surface illumination
					// is modified by an animated light.
	mplane_t *plane;		// pointer to shared plane
	int flags;			// see SURF_ #defines

	int firstedge;			// look up in model->surfedges[], negative numbers
	int numedges;			// are backwards edges

	// surface generation data
	struct surfcache_s *cachespots[MIPLEVELS];
	short texturemins[2];		// smallest s/t position on the surface.
	short extents[2];		// ?? s/t texture size, 1..256 for all non-sky surfaces
	mtexinfo_t *texinfo;
	byte styles[MAXLIGHTMAPS];	// index into d_lightstylevalue[] for animated lights
					// no one surface can be effected by more than 4
					// animated lights.
	color24 *samples;
	decal_t *pdecals;
};

/* <6b6c> ../engine/model.h:149 */
typedef struct mnode_s
{
	// common with leaf
	int contents;			// 0, to differentiate from leafs
	int visframe;			// node needs to be traversed if current
	short minmaxs[6];		// for bounding box culling
	struct mnode_s *parent;

	// node specific
	mplane_t *plane;
	struct mnode_s *children[2];
	unsigned short firstsurface;
	unsigned short numsurfaces;
} mnode_t;

/* <1dcd4> ../engine/model.h:169 */
typedef struct mleaf_s
{
	// common with node
	int contents;			// wil be a negative contents number
	int visframe;			// node needs to be traversed if current
	short minmaxs[6];		// for bounding box culling
	struct mnode_s *parent;
	byte *compressed_vis;
	struct efrag_s *efrags;
	msurface_t **firstmarksurface;
	int nummarksurfaces;
	int key;			// BSP sequence number for leaf's contents
	byte ambient_sound_level[NUM_AMBIENTS];
} mleaf_t;

/* <1ddbe> ../engine/model.h:190 */
typedef struct hull_s
{
	dclipnode_t *clipnodes;
	mplane_t *planes;
	int firstclipnode;
	int lastclipnode;
	vec3_t clip_mins, clip_maxs;
} hull_t;

/* <1de30> ../engine/model.h:315 */
typedef enum modtype_e
{
	mod_brush,
	mod_sprite,
	mod_alias,
	mod_studio,
} modtype_t;

/* <1de5e> ../engine/model.h:331 */
typedef struct model_s
{
	char name[MAX_MODEL_NAME];
	qboolean needload;
	modtype_t type;
	int numframes;
	synctype_t synctype;
	int flags;
	vec3_t mins, maxs;
	float radius;
	int firstmodelsurface;
	int nummodelsurfaces;
	int numsubmodels;
	dmodel_t *submodels;
	int numplanes;
	mplane_t *planes;
	int numleafs;
	struct mleaf_s *leafs;
	int numvertexes;
	mvertex_t *vertexes;
	int numedges;
	medge_t *edges;
	int numnodes;
	mnode_t *nodes;
	int numtexinfo;
	mtexinfo_t *texinfo;
	int numsurfaces;
	msurface_t *surfaces;
	int numsurfedges;
	int *surfedges;
	int numclipnodes;
	dclipnode_t *clipnodes;
	int nummarksurfaces;
	msurface_t **marksurfaces;
	hull_t hulls[MAX_MAP_HULLS];
	int numtextures;
	texture_t **textures;
	byte *visdata;
	color24 *lightdata;
	char *entities;
	cache_user_t cache;
} model_t;

typedef struct mod_known_info_s
{
	qboolean shouldCRC;
	qboolean firstCRCDone;
	CRC32_t initialCRC;
} mod_known_info_t;

#endif // MODEL_H
