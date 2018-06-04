#include "Bridges.h"

#include "Platforms/General/PFwindow.h"
#include "Universal_System/roomsystem.h"

namespace enigma_user {

void screen_refresh() {
  enigma::graphics_swap_buffers();
  enigma::update_mouse_variables();
  window_set_caption(room_caption);
}

}
