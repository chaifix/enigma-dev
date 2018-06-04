#include "Platforms/Win32/WINDOWSmain.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <windows.h>

namespace enigma {
  namespace swaphandling {
    bool has_checked_extensions = false;
    bool ext_swapcontrol_supported;

    void investigate_swapcontrol_support() {

      if (has_checked_extensions) return; // Already calculated, no need to calculate it more.

      const char *wgl_extensions = wglGetExtensionsStringARB(window_hDC);

      ext_swapcontrol_supported = strstr(wgl_extensions, "WGL_EXT_swap_control");

      has_checked_extensions = true;
    }
  }

  void graphics_swap_buffers() {
    SwapBuffers(enigma::window_hDC);
  }

  bool is_ext_swapcontrol_supported() {
    swaphandling::investigate_swapcontrol_support();
    return swaphandling::ext_swapcontrol_supported;
  }
}

namespace enigma_user {

void set_synchronization(bool enable) {
  // General notes:
  // Setting swapping on and off is platform-dependent and requires platform-specific extensions.
  // Platform-specific extensions are even more bothersome than regular extensions.
  // What functions and features to use depends on which version of OpenGL is used.
  // For more information, see the following pages:
  // http://www.opengl.org/wiki/Load_OpenGL_Functions
  // http://www.opengl.org/wiki/OpenGL_Loading_Library
  // http://www.opengl.org/wiki/Swap_Interval
  // http://en.wikipedia.org/wiki/WGL_%28software%29
  // Also note that OpenGL version >= 3.0 does not use glGetString for getting extensions.
  int interval = enable ? 1 : 0;

  if (enigma::is_ext_swapcontrol_supported()) {
    wglSwapIntervalEXT(interval);
  }
}

}
