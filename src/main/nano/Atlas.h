#ifndef ATLAS_H
#define ATLAS_H

typedef enum bool {false, true} bool;

typedef unsigned short Entity;
#define MAX_ENTITIES 4096
#define MAX_COMPONENTS 16

#include "components/Component.h"
#include "components/Health.h"
#include "components/Sprite.h"
#include "components/Position.h"
#include "components/Velocity.h"

#endif
