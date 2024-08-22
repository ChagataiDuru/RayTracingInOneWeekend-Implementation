#include "rt.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.6));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 95));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;

    cam.render(world);
}

