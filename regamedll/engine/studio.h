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

#ifndef STUDIO_H
#define STUDIO_H
#ifdef _WIN32
#pragma once
#endif

#include "studio_event.h"

#define MAXSTUDIOTRIANGLES	20000	// TODO: tune this
#define MAXSTUDIOVERTS		2048	// TODO: tune this
#define MAXSTUDIOSEQUENCES	256	// total animation sequences
#define MAXSTUDIOSKINS		100	// total textures
#define MAXSTUDIOSRCBONES	512	// bones allowed at source movement
#define MAXSTUDIOBONES		128	// total bones actually used
#define MAXSTUDIOMODELS		32	// sub-models per model
#define MAXSTUDIOBODYPARTS	32
#define MAXSTUDIOGROUPS		16
#define MAXSTUDIOANIMATIONS	512	// per sequence
#define MAXSTUDIOMESHES		256
#define MAXSTUDIOEVENTS		1024
#define MAXSTUDIOPIVOTS		256
#define MAXSTUDIOCONTROLLERS	8

// lighting options
#define STUDIO_NF_FLATSHADE	0x0001
#define STUDIO_NF_CHROME	0x0002
#define STUDIO_NF_FULLBRIGHT	0x0004

// motion flags
#define STUDIO_X		0x0001
#define STUDIO_Y		0x0002
#define STUDIO_Z		0x0004
#define STUDIO_XR		0x0008
#define STUDIO_YR		0x0010
#define STUDIO_ZR		0x0020
#define STUDIO_LX		0x0040
#define STUDIO_LY		0x0080
#define STUDIO_LZ		0x0100
#define STUDIO_AX		0x0200
#define STUDIO_AY		0x0400
#define STUDIO_AZ		0x0800
#define STUDIO_AXR		0x1000
#define STUDIO_AYR		0x2000
#define STUDIO_AZR		0x4000
#define STUDIO_TYPES		0x7FFF
#define STUDIO_RLOOP		0x8000	// controller that wraps shortest distance

// sequence flags
#define STUDIO_LOOPING		0x0001

// bone flags
#define STUDIO_HAS_NORMALS	0x0001
#define STUDIO_HAS_VERTICES	0x0002
#define STUDIO_HAS_BBOX		0x0004
#define STUDIO_HAS_CHROME	0x0008	// if any of the textures have chrome on them

#define RAD_TO_STUDIO		(32768.0/M_PI)
#define STUDIO_TO_RAD		(M_PI/32768.0)

typedef struct
{
	int id;
	int version;
	char name[64];
	int length;
	vec3_t eyeposition;		// ideal eye position
	vec3_t min;			// ideal movement hull size
	vec3_t max;
	vec3_t bbmin;			// clipping bounding box
	vec3_t bbmax;
	int flags;
	int numbones;			// bones
	int boneindex;
	int numbonecontrollers;		// bone controllers
	int bonecontrollerindex;
	int numhitboxes;		// complex bounding boxes
	int hitboxindex;
	int numseq;			// animation sequences
	int seqindex;
	int numseqgroups;		// demand loaded sequences
	int seqgroupindex;
	int numtextures;		// raw textures
	int textureindex;
	int texturedataindex;
	int numskinref;			// replaceable textures
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numattachments;		// queryable attachable points
	int attachmentindex;
	int soundtable;
	int soundindex;
	int soundgroups;
	int soundgroupindex;
	int numtransitions;		// animation node to animation node transition graph
	int transitionindex;

} studiohdr_t;

// bones
typedef struct
{
	char name[32];		// bone name for symbolic links
	int parent;		// parent bone
	int flags;		// ??
	int bonecontroller[6];	// bone controller index, -1 == none
	float value[6];		// default DoF values
	float scale[6];		// scale for delta DoF values

} mstudiobone_t;

// bone controllers
typedef struct
{
	int bone;	// -1 == 0
	int type;	// X, Y, Z, XR, YR, ZR, M
	float start;
	float end;
	int rest;	// byte index value at rest
	int index;	// 0-3 user set controller, 4 mouth

} mstudiobonecontroller_t;

// demand loaded sequence groups
typedef struct
{
	char label[32];		// textual name
	char name[64];		// file name
	int32 unused1;	// cache index pointer
	int unused2;		// hack for group 0

} mstudioseqgroup_t;

// sequence descriptions
typedef struct
{
	char label[32];			// sequence label
	float fps;			// frames per second
	int flags;			// looping/non-looping flags
	int activity;
	int actweight;
	int numevents;
	int eventindex;
	int numframes;			// number of frames per sequence
	int numpivots;			// number of foot pivots
	int pivotindex;
	int motiontype;
	int motionbone;
	vec3_t linearmovement;
	int automoveposindex;
	int automoveangleindex;
	vec3_t bbmin;			// per sequence bounding box
	vec3_t bbmax;
	int numblends;
	int animindex;			// mstudioanim_t pointer relative to start of sequence group data
					// [blend][bone][X, Y, Z, XR, YR, ZR]
	int blendtype[2];		// X, Y, Z, XR, YR, ZR
	float blendstart[2];		// starting value
	float blendend[2];		// ending value
	int blendparent;
	int seqgroup;			// sequence group for demand loading
	int entrynode;			// transition node at entry
	int exitnode;			// transition node at exit
	int nodeflags;			// transition rules
	int nextseq;			// auto advancing sequences

} mstudioseqdesc_t;

typedef struct
{
	unsigned short offset[6];

} mstudioanim_t;

// animation frames
typedef union
{
	struct
	{
		byte valid;
		byte total;
	} num;
	short int value;

} mstudioanimvalue_t;

// body part index
typedef struct
{
	char name[64];
	int nummodels;
	int base;
	int modelindex; // index into models array

} mstudiobodyparts_t;

#endif // STUDIO_H
