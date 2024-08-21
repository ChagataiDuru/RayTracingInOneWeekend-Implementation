#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "rt.h"

class viewport {
public:
    viewport(int image_width, double aspect_ratio, double focal_length)
        : image_width(image_width),
        image_height(static_cast<int>(image_width / aspect_ratio)),
        viewport_height(2.0),
        viewport_width(viewport_height* aspect_ratio),
        camera_center(0, 0, 0),
        viewport_u(viewport_width, 0, 0),
        viewport_v(0, -viewport_height, 0),
        pixel_delta_u(viewport_u / image_width),
        pixel_delta_v(viewport_v / image_height),
        viewport_upper_left(camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2),
        pixel00_loc(viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v)) {
        // Ensure the image height is at least 1
        image_height = (image_height < 1) ? 1 : image_height;
    }

    int get_image_width() const { return image_width; }
    int get_image_height() const { return image_height; }

    const point3& get_camera_center() const { return camera_center; }
    const vec3& get_viewport_u() const { return viewport_u; }
    const vec3& get_viewport_v() const { return viewport_v; }
    const vec3& get_pixel_delta_u() const { return pixel_delta_u; }
    const vec3& get_pixel_delta_v() const { return pixel_delta_v; }
    const point3& get_pixel00_loc() const { return pixel00_loc; }

private:
    int image_width;
    int image_height;
    double viewport_height;
    double viewport_width;
    point3 camera_center;
    vec3 viewport_u;
    vec3 viewport_v;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    point3 viewport_upper_left;
    point3 pixel00_loc;
};

#endif // VIEWPORT_H