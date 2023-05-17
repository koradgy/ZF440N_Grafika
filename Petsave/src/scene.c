#include "scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <string.h>
#include <obj/load.h>
#include <obj/draw.h>




void init_scene(Scene* scene)
{
    scene->gameover = false;
    load_model(&(scene->duck), "assets/models/duck.obj");
    load_model(&(scene->hare), "assets/models/hare.obj");
    load_model(&(scene->ground), "assets/models/ground.obj");

    load_model(&(scene->house1), "assets/models/house.obj");
    load_model(&(scene->house2), "assets/models/house.obj");
    load_model(&(scene->house3), "assets/models/house.obj");
    load_model(&(scene->house4), "assets/models/house.obj");

    load_model(&(scene->raptor), "assets/models/raptor.obj");

    scene->raptor_id = load_texture("assets/textures/raptor.png");
    scene->ground_id = load_texture("assets/textures/ground.webp");
    scene->duck_id = load_texture("assets/textures/duck.jpg");
    scene->hare_id = load_texture("assets/textures/hare.jpg");
    scene->house_id = load_texture("assets/textures/house.jpg");
    scene->duck_up = false;
    scene->hare_up = false;

    scene->rap_x = 0;
    scene->direction = 1.0f;
    scene->rap_turn = 0; 


    scene->Help_menu = load_texture("assets/textures/help_texture.jpg");
    scene->Help_visible = false;

    scene->material.ambient.red = 0.2;
    scene->material.ambient.green = 0.2;
    scene->material.ambient.blue = 0.2;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 100.0;

}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, Camera *camera)
{
    scene->rotation+=1;
    
    // Raptor movement
    if (scene->rap_turn == 0)
    {
        scene->rap_x += 0.02f;
    }

    if (scene->rap_x >= 6.0f)
    {
        scene->direction = -1.0f;
        scene->rap_turn = 1;
    }

    if (scene->rap_turn == 1)
    {
        scene->rap_x -= 0.02f;
    }

    if (scene->rap_x <= -12.0f)
    {
        scene->direction = 1.0f;
        scene->rap_turn = 0;
    }


    if(scene->gameover)
    {
        endGame(&scene);
    }
}


void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    //draw_origin();

    //grass
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->ground_id);
    glScalef(1.5, 1.5, 0.5);
    glRotated(90, 1, 0, 0);
    glTranslatef(0, 0, 0);
    draw_model(&(scene->ground));
    glPopMatrix();

    // house 1
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_id);
    glScalef(0.02f, 0.02f, 0.02f);
    glRotated(90, 1, 0, 0);
    glTranslatef(300.0f, 10.0f, 390.0f);
    draw_model(&(scene->house1));
    glPopMatrix();


    // house 2
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_id);
    glScalef(0.02f, 0.02f, 0.02f);
    glRotated(90, 1, 0, 0);
    glTranslatef(-390.0, 10.0, 390.0);
    draw_model(&(scene->house2));
    glPopMatrix();

    // house 3
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_id);
    glScalef(0.02f, 0.02f, 0.02f);
    glRotated(90, 1, 0, 0);
    glTranslatef(-390.0f, 10.0f, -390.0f);
    draw_model(&(scene->house3));
    glPopMatrix();

    // house 4
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->house_id);
    glScalef(0.02f, 0.02f, 0.02f);
    glRotated(90, 1, 0, 0);
    glTranslatef(300.0f, 10.0f, -380.0f);
    draw_model(&(scene->house4));
    glPopMatrix();

    //rabbit
    if(!scene->hare_up)
    {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->hare_id);
        glTranslatef(-13.28f, 7.67f, 0.0f);
        glRotatef(90, 0, 0, 1);
        glRotatef(scene->rotation, 0, 0, 1);
        glScalef(0.1, 0.1, 0.1);
        draw_model(&(scene->hare));
        glPopMatrix();
    }

    //duck
    if(!scene->duck_up)
    {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->duck_id);
        glTranslatef(-4.88f, 12.76f, 0.0f);
        glRotatef(scene->rotation, 0, 0, 1);
        glScalef(0.1, 0.1, 0.1);
        draw_model(&(scene->duck));
        glPopMatrix();
    }

    //raptor
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->raptor_id);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(scene->rap_x, 0.0f, 0.0f);
    glRotated(90, 0, 0, -scene->direction);
    draw_model(&(scene->raptor));
    glPopMatrix();

    if(scene->gameover)
    {
        endGame(&scene);
    }

    if(scene->die)
    {
        death(&scene);
    }
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void Help(GLuint Help_menu) 
{
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, Help_menu);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3d(-2, 1.5, -3);
        glTexCoord2f(1, 0);
        glVertex3d(2, 1.5, -3);
        glTexCoord2f(1, 1);
        glVertex3d(2, -1.5, -3);
        glTexCoord2f(0, 1);
        glVertex3d(-2, -1.5, -3);
        glEnd();


        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
}

void endGame(Scene *scene)
{
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("assets/textures/end.jpg"));

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

}

void death(Scene *scene)
{
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("assets/textures/die.jpg"));

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

}