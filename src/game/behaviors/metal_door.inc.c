//metal_door.inc
void bhv_overworld_door_loop(void) {
    //s8 fileIndex;
    //s8 courseIndex;    
    //s16 starCount = save_file_get_total_star_count(fileIndex, COURSE_NUM_TO_INDEX(COURSE_MIN), COURSE_NUM_TO_INDEX(COURSE_MAX));
    //u8 requiredNumStars = 25;
    u8 starFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_NONE));
    o->oDrawingDistance = 20000.0f;
    
    o->oCollisionDistance = 20000.0f;
    //If you have more than 25 stars, the door will disappear.
if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= 25 && !(starFlags & SAVE_FLAG_TO_STAR_FLAG(SAVE_FLAG_UNLOCKED_4_COURSE_STAR))) {
        //Visible Door: false
        cur_obj_set_model(MODEL_NONE);
    } else {
        //Visible Door: true
        load_object_collision_model();
    }
}