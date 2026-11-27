// 0x16000ED4
const GeoLayout dirt_animation_geo[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(6, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_red),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_green),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_blue),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_ALPHA,  dirt_seg3_dl_dirt_particle),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_yellow),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_billboard),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
