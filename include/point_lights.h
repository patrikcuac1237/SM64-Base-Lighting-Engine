#ifndef __POINT_LIGHTS_H__
#define __POINT_LIGHTS_H__

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <macros.h>
#include <config.h>

#define LIGHT_TYPE_AMBIENT              0
#define LIGHT_TYPE_DIRECTIONAL          1
#define LIGHT_TYPE_POINT                2
#define LIGHT_TYPE_POINT_OCCLUDE        3
#define LIGHT_TYPE_CAMERA               4
#define LIGHT_TYPE_RELATIVE             5
#define LIGHT_TYPE_VANILLA_STYLE        6

#define LIGHT_FLAG_OCCLUDE              (1 << 0)
#define LIGHT_FLAG_IS_POINT             (1 << 1)
#define LIGHT_FLAG_IS_DIRECTIONAL       (1 << 2)
#define LIGHT_FLAG_IS_FLOORED           (1 << 3)
#define LIGHT_FLAG_IS_RELATIVE          (1 << 4)
#define LIGHT_FLAG_IS_FLAME             (1 << 5)

#define MAX_POINT_LIGHTS_ACTIVE 5
#define MAX_POINT_LIGHTS 100
#define MAX_POINT_LIGHT_DIST 30000000

STATIC_ASSERT(MAX_POINT_LIGHTS_ACTIVE <= 5    , "The lights cannot be more than 5");

struct SceneLight {
    Light l;
    Vec3s worldPos;
    s16 flags;
    f32 maxDist;
    u8 RGBMultAdd[3];
    s32 brightness;
    s32 floorType;
    s16 RelativeYLoc;
    s16 minX;
    s16 maxX;
    s16 minY;
    s16 maxY;
    s16 minZ;
    s16 maxZ;
    u8 bLerp;
    u8 isActive;
};

extern int gPointLightCompatibilityMode;
extern s8 gLightDir[3];
extern struct SceneLight gPointLights[];
extern u8 gAreaPointLightCount;
extern u8 gPointLightCount;

void addPointLight(struct Object *obj, const u8 rgb[3], f32 maxDist, s32 brightness, s32 bOcclude);
void addPositionedLight(Vec3f pos, const u8 rgb[3], f32 maxDist, s32 brightness);
void addDirectionalLight(u8 rgb[3], s8 dir[3], s16 volumeID);
void addFlooredLight(const u8 rgb[3], s8 dir[3], s32 floorType, f32 maxDist, u8 bOcclude, u8 bLerp);
void addRelativeLight(Vec3f pos, const u8 rgb[3], f32 maxDist, s32 brightness, s16 RelativeYloc, s16 minY, s16 maxY);
void addDirectionalLightBasedOnFLoorType(const u8 rgb[3], s8 dir[3], s32 floorType);
void addFlameLight(Vec3f pos, const u8 rgb[3], f32 maxDist, s32 brightness, s16 minX, s16 maxX, s16 minY, s16 maxY, s16 minZ, s16 maxZ);
void set_ambient_light(u8 lightColor[3]);
void set_directional_light(u8 lightColor[3], u8 lightDir[3]);
#endif
