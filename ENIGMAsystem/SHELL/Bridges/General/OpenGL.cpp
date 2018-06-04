#include "Platforms/General/PFwindow.h"

#include <GL/glew.h>

namespace enigma {
  GLuint msaa_fbo = 0;
}

namespace enigma_user {

void display_reset(int samples, bool vsync) {
  GLint fbo;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &fbo);

  GLuint ColorBufferID, DepthBufferID;

  // Cleanup the multi-sampler fbo if turning off multi-sampling
  if (samples == 0) {
    if (enigma::msaa_fbo != 0) {
      glDeleteFramebuffers(1, &enigma::msaa_fbo);
      enigma::msaa_fbo = 0;
    }
    return;
  }

  //TODO: Change the code below to fix this to size properly to views
  // If we don't already have a multi-sample fbo then create one
  if (enigma::msaa_fbo == 0) {
    glGenFramebuffersEXT(1, &enigma::msaa_fbo);
  }
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, enigma::msaa_fbo);
  // Now make a multi-sample color buffer
  glGenRenderbuffersEXT(1, &ColorBufferID);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, ColorBufferID);
  glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, samples, GL_RGBA8, window_get_region_width(), window_get_region_height());
  // We also need a depth buffer
  glGenRenderbuffersEXT(1, &DepthBufferID);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, DepthBufferID);
  glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, samples, GL_DEPTH_COMPONENT24, window_get_region_width(), window_get_region_height());
  // Attach the render buffers to the multi-sampler fbo
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, ColorBufferID);
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, DepthBufferID);

  set_synchronization(vsync);
}

}
