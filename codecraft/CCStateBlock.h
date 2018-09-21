#pragma once
#include "CCHeader.h"

struct CCBlockvt;

struct CCBlock {
  struct CCBlockvt *vt;
  GCPtr *outBuff;
  GCPtr *inRef;
  GCPtr *state;
  GCPtr *stateView;
};

struct CCBlockvt {

};