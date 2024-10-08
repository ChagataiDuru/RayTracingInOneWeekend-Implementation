#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "rt.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "obj_loader.h"

int main(int argc, char* argv[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int image_width = 400;
    int image_height = int(image_width / (16.0 / 9.0));

    SDL_Window* window = SDL_CreateWindow("Ray Tracer", 100, 100, image_width, image_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, image_width, image_height);
    if (texture == nullptr) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    hittable_list world;

    auto obj_material = make_shared<lambertian>(color(0.8, 0.4, 0.3));
    auto obj_mesh = OBJLoader::load_obj("teapot.obj", obj_material);
    for (const auto& triangle : obj_mesh) {
        world.add(triangle);
    }
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = image_width;
    cam.samples_per_pixel = 1;
    cam.max_depth = 50;

    cam.vfov = 105;
    cam.lookfrom = point3(5, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    std::vector<uint8_t> pixels(image_width * image_height * 3);

    cam.render(world, pixels.data());

    SDL_UpdateTexture(texture, nullptr, pixels.data(), image_width * 3);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

