#include "pch.h"
#pragma once
/*
 *(this + 102) = heap:
int __thiscall StdSystem::setHeap(StdSystem *this, int a2)
{
  int v2; // ST50_4

  v2 = *(this + 102);
  *(this + 102) = a2;
  return v2;
}

*(gsys + 108) = int lights;
*(gsys + 14) = updateAnim timer
*/