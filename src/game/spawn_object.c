#include <PR/ultratypes.h>

#include "audio/external.h"
#include "engine/geo_layout.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "level_table.h"
#include "object_constants.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "spawn_object.h"
#include "types.h"
#include "puppylights.h"

/**
 * Attempt to allocate an object from freeList (singly linked) and append it
 * to the end of destList (doubly linked). Return the object, or NULL if
 * freeList is empty.
 */
struct Object *try_allocate_object(struct ObjectNode *destList, struct ObjectNode *freeList) {
    struct ObjectNode *nextObj;

    if ((nextObj = freeList->next) != NULL) {
        // Remove from free list
        freeList->next = nextObj->next;

        // Insert at end of destination list
        nextObj->prev = destList->prev;
        nextObj->next = destList;
        destList->prev->next = nextObj;
        destList->prev = nextObj;
    } else {
        return NULL;
    }

    geo_remove_child(&nextObj->gfx.node);
    geo_add_child(&gObjParentGraphNode, &nextObj->gfx.node);

    return (struct Object *) nextObj;
}

/**
 * Remove the given object from the object list that it's currently in, and
 * insert it at the beginning of the free list (singly linked).
 */
static void deallocate_object(struct ObjectNode *freeList, struct ObjectNode *obj) {
    // Remove from object list
    obj->next->prev = obj->prev;
    obj->prev->next = obj->next;

    // Insert at beginning of free list
    obj->next = freeList->next;
    freeList->next = obj;
}

/**
 * Add every object in the pool to the free object list.
 */
void init_free_object_list(void) {
    s32 i;
    s32 poolLength = OBJECT_POOL_CAPACITY;

    // Add the first object in the pool to the free list
    struct Object *obj = &gObjectPool[0];
    gFreeObjectList.next = (struct ObjectNode *) obj;

    // Link each object in the pool to the following object
    for (i = 0; i < poolLength - 1; i++) {
        obj->header.next = &(obj + 1)->header;
        obj++;
    }

    // End the list
    obj->header.next = NULL;
}

/**
 * Clear each object list, without adding the objects back to the free list.
 */
void clear_object_lists(struct ObjectNode *objLists) {
    s32 i;

    for (i = 0; i < NUM_OBJ_LISTS; i++) {
        objLists[i].next = &objLists[i];
        objLists[i].prev = &objLists[i];
    }
}

/**
 * Free the given object.
 */
void unload_object(struct Object *obj) {
    obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    obj->prevObj = NULL;

    obj->header.gfx.throwMatrix = NULL;
    stop_sounds_from_source(obj->header.gfx.cameraToObject);
    geo_remove_child(&obj->header.gfx.node);
    geo_add_child(&gObjParentGraphNode, &obj->header.gfx.node);

    obj->header.gfx.node.flags &= ~(GRAPH_RENDER_BILLBOARD | GRAPH_RENDER_ACTIVE);

    deallocate_object(&gFreeObjectList, &obj->header);
}

/**
 * Attempt to allocate a new object slot into the given object list, freeing
 * an unimportant object if necessary. If this is not possible, hang using an
 * infinite loop.
 */
struct Object *allocate_object(struct ObjectNode *objList) {
    s32 i;
    struct Object *obj = try_allocate_object(objList, &gFreeObjectList);

    if (obj == NULL) {
        struct Object *unimportantObj = find_unimportant_object();
        if (unimportantObj == NULL) {
            while (1) {
                // Infinite loop in case of object pool exhaustion
            }
        } else {
            unload_object(unimportantObj);
            obj = try_allocate_object(objList, &gFreeObjectList);
        }
    }

    // Initialize object fields
    obj->activeFlags = ACTIVE_FLAG_ACTIVE | ACTIVE_FLAG_ALLOCATED;
    obj->parentObj = obj;
    obj->prevObj = NULL;
    obj->collidedObjInteractTypes = 0;
    obj->numCollidedObjs = 0;

    for (i = 0; i < MAX_OBJECT_FIELDS; i++) {
        obj->rawData.asS32[i] = 0;
#if IS_64_BIT
        obj->ptrData.asVoidPtr[i] = NULL;
#endif
    }

    obj->unused1 = 0;
    obj->bhvStackIndex = 0;
    obj->bhvDelayTimer = 0;

    // Initialize hitbox and hurtbox properties
    obj->hitboxRadius = 50.0f;
    obj->hitboxHeight = 100.0f;
    obj->hurtboxRadius = 0.0f;
    obj->hurtboxHeight = 0.0f;
    obj->hitboxDownOffset = 0.0f;
    obj->unused2 = 0;

    // Initialize other properties
    obj->platform = NULL;
    obj->collisionData = NULL;
    obj->oIntangibleTimer = -1;
    obj->oDamageOrCoinValue = 0;
    obj->oHealth = 2048;
    obj->oCollisionDistance = 1000.0f;
    obj->oDrawingDistance = 4000.0f;
    mtxf_identity(obj->transform);
    obj->respawnInfoType = RESPAWN_INFO_TYPE_NULL;
    obj->respawnInfo = NULL;
    obj->oDistanceToMario = 19000.0f;
    obj->oRoom = -1;

    // Reset GFX properties
    obj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
#ifdef OBJECTS_REJ
    obj->header.gfx.ucode = GRAPH_NODE_UCODE_REJ;
#endif
    vec3_same(obj->header.gfx.pos, -10000.0f);
    obj->header.gfx.throwMatrix = NULL;
#ifdef PUPPYLIGHTS
    obj->oLightID = 0xFFFF;
#endif

    return obj;
}

/**
 * Spawn an object at the origin with the behavior script at virtual address bhvScript.
 */
struct Object *create_object(const BehaviorScript *bhvScript) {
    s32 objListIndex = ((bhvScript[0] >> 24) == 0) ? ((bhvScript[0] >> 16) & 0xFFFF) : OBJ_LIST_DEFAULT;
    struct Object *obj = allocate_object(&gObjectLists[objListIndex]);

    obj->curBhvCommand = obj->behavior = bhvScript;
    obj->activeFlags |= (objListIndex == OBJ_LIST_UNIMPORTANT) ? ACTIVE_FLAG_UNIMPORTANT : 0;

    return obj;
}
