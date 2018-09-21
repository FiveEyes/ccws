#pragma once
#include "CCHeader.h"

#define DEFAPPTYPE(OBJ) \
	typedef void (*OBJ##AppFunc)(OBJ *); \
	typedef int (*OBJ##EnableFunc)(OBJ *);

#define CCBlockvtHeader(VT,OBJ) \
	GCObjvtHeader(VT,OBJ); \
	void (*set)(OBJ *block, int index, GCPtr *p); \
	GCPtr * (*get)(OBJ *block, int index); \
	int (*size)(OBJ *block, int i); \
	int (*isEnabled)(OBJ *block); \
	void (*apply)(OBJ *block)

#define InitCCBlockvtHeader(var,prefix,type) \
	InitGCObjvtHeader(var,prefix,type); \
	(var)->set = prefix##_set; \
	(var)->get = prefix##_get; \
	(var)->size = prefix##_size; \
	(var)->isEnabled = prefix##_isEnabled; \
	(var)->apply = prefix##_apply

typedef struct CCBlock CCBlock;
typedef struct CCBlockvt CCBlockvt;

DEFAPPTYPE(CCBlock);


struct CCBlock {
	struct CCBlockvt *vt;
};


struct CCBlockvt {
	CCBlockvtHeader(CCBlockvt, CCBlock);
};