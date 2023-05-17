#include "app.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

void initialize_audio()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void play_sound(const char* sound_file)
{
    Mix_Chunk* sound = Mix_LoadWAV(sound_file);
    Mix_PlayChannel(-1, sound, 0);
}



void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Find Your Pets!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    bool end_played = false;
    app->death_played = false;
    app->scene.die = false;

    init_opengl();
    reshape(width, height);
    initialize_audio();
    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 100
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_F12:
                SDL_SetWindowBrightness(app->window, SDL_GetWindowBrightness(app->window) + 0.1);
                break;
            case SDL_SCANCODE_F11:
                SDL_SetWindowBrightness(app->window, SDL_GetWindowBrightness(app->window) - 0.1);
                break;

                
			case SDL_SCANCODE_F1:
                if(!app->scene.Help_visible) {
                app->scene.Help_visible = true;
                }else{
                app->scene.Help_visible = false;
				glFrustum(
				-.08, .08,
				-.06, .06,
				.1, 6000
				);
                }
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene), &(app->camera));
    //hare collision
    if(collision(&(app->camera), -13.28, 7.67, 0.5, 0.5) && !app->scene.hare_up)
    {
        play_sound("assets/sounds/collect.wav");
        printf("Nyul felveve!\n");
        app->scene.hare_up = true;
    }

    //duck collision
    if(collision(&(app->camera), -4.88, 12.76, 0.5, 0.5) && !app->scene.duck_up)
    {
        play_sound("assets/sounds/collect.wav");
        printf("Kacsa felveve!\n");
        app->scene.duck_up = true;
    }

 

   if(collision(&(app->camera), 5.5, -8.175, 2.8, 4.15) == 1)
    {
        app->camera.position.x -= 0.1;
        app->camera.position.y -= 0.1;
    }
    
    if(collision(&(app->camera), -7.5, -7.5, 2.8, 4.15) == 1)
    {
        app->camera.position.x -= 0.1;
        app->camera.position.y -= 0.1;
    }

    if(collision(&(app->camera), 6.5, 7.2, 2.8, 4.15) == 1)
    {
        app->camera.position.x -= 0.1;
        app->camera.position.y -= 0.1;
    }

    if(collision(&(app->camera), -7.5, 7.5, 2.8, 4.15) == 1)
    {
        app->camera.position.x -= 0.1;
        app->camera.position.y -= 0.1;
    }

    

    if(app->scene.duck_up && app->scene.hare_up)
    {
        if(!app->end_played)
        {
            play_sound("assets/sounds/end.wav");
            app->end_played = true;
        }
        app->scene.gameover = true;
    }

    if(collision(&(app->camera), app->scene.rap_x, 0.0, 0.5 , 1))
    {
        if(!app->death_played)
        {
            play_sound("assets/sounds/die.wav");
            app->death_played = true;
        }
        app->scene.die = true;
    }
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    if (app->scene.Help_visible){
        Help(app->scene.Help_menu);
	}

    SDL_GL_SwapWindow(app->window);
}

int collision(Camera *camera, float posX, float posY, float boxSizeX, float boxSizeY)
{
    if ((camera->position.x > posX - boxSizeX) && (camera->position.x < posX + boxSizeX))
        if ((camera->position.y > posY - boxSizeY) && (camera->position.y < posY + boxSizeY))
            return 1;
    return 0;
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

