#include <wayland-server.h>

#include "protocols/xdg-shell.h"

void wl_compositor_create_surface() {}

void wl_compositor_create_region() {}

static struct wl_compositor_interface wl_compositor_impl = {
    .create_surface = &wl_compositor_create_surface,
    .create_region = &wl_compositor_create_region};

static void compositor_bind(struct wl_client *client, void *data,
                            uint32_t version, uint32_t id) {
  struct wl_resource *resource =
      wl_resource_create(client, &wl_compositor_interface, 1, id);
  wl_resource_set_implementation(resource, &wl_compositor_impl, NULL, NULL);
}

void xdg_wm_base_destroy() {}

void xdg_wm_base_create_positioner() {}

void xdg_wm_base_get_xdg_surface() {}

void xdg_wm_base_pong() {}

static struct xdg_wm_base_interface xdg_wm_base_impl = {
    .destroy = &xdg_wm_base_destroy,
    .create_positioner = &xdg_wm_base_create_positioner,
    .get_xdg_surface = &xdg_wm_base_get_xdg_surface,
    .pong = &xdg_wm_base_pong};

static void xdg_wm_base_bind(struct wl_client *client, void *data,
                             uint32_t version, uint32_t id) {
  struct wl_resource *resource =
      wl_resource_create(client, &xdg_wm_base_interface, 1, id);
  wl_resource_set_implementation(resource, &xdg_wm_base_impl, NULL, NULL);
}

int main() {
  struct wl_display *display = wl_display_create();

  // TODO maybe use the explicit add socket API to use a different path?
  wl_display_add_socket_auto(display);

  wl_global_create(display, &wl_compositor_interface, 3, NULL,
                   &compositor_bind);
  wl_global_create(display, &xdg_wm_base_interface, 1, NULL, &xdg_wm_base_bind);

  wl_display_init_shm(display);

  struct wl_event_loop *event_loop = wl_display_get_event_loop(display);
  int wayland_fd = wl_event_loop_get_fd(event_loop);
  while (1) {
    wl_event_loop_dispatch(event_loop, 0);
    // backend_dispatch_nonblocking ();
    wl_display_flush_clients(display);
    // draw ();
    // backend_wait_for_events (wayland_fd);
  }
}
