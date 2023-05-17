#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>
#include <stdbool.h>

typedef struct Scene
{
    Model duck;
    bool duck_up;
    Model hare;
    bool hare_up;

    Material material;
    GLuint duck_id;
    GLuint hare_id;
    GLuint Help_menu;
    Model ground;
    GLuint ground_id;
    Model house1;
    Model house2;
    Model house3;
    Model house4;
    GLuint house_id;

    Model raptor;
    GLuint raptor_id;
    float rap_x;
    float direction; //raptor face direction -1,1
    int rap_turn; //raptor movement direcrion 0,1
    float rap_translation;
    bool die;

    bool Help_visible;
    bool gameover;
    float rotation;

} Scene;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, Camera *camera);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Game over
*/
void endGame(Scene *scene);

#endif /* SCENE_H */
