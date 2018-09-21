#pragma once
#include "CCHeader.h"
#include "CCBlock.h"

typedef struct CCPureBlock CCPureBlock;
typedef struct CCPureBlockvt CCPureBlockvt;
DEFAPPTYPE(CCPureBlock);

struct CCPureBlock {
	struct CCPureBlockvt *vt;
	GCPtr *inRef;
	GCPtr *outBuff;
};

struct CCPureBlockvt {
  CCBlockvtHeader(CCPureBlockvt,CCPureBlock);
	int inputSize;
	int outputSize;
};



CCPureBlockvt * createCCPureBlockvt(CCPureBlockEnableFunc enable, CCPureBlockAppFunc apply, int inputSize, int outputSize, char *type);
