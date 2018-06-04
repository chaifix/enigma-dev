/** Copyright (C) 2013 forthevin
***
*** This file is a part of the ENIGMA Development Environment.
***
*** ENIGMA is free software: you can redistribute it and/or modify it under the
*** terms of the GNU General Public License as published by the Free Software
*** Foundation, version 3 of the license or any later version.
***
*** This application and its source code is distributed AS-IS, WITHOUT ANY
*** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
*** FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
*** details.
***
*** You should have received a copy of the GNU General Public License along
*** with this code. If not, see <http://www.gnu.org/licenses/>
**/
#include "Graphics_Systems/graphics_mandatory.h"
#include "Graphics_Systems/General/GScolors.h"
#include "Platforms/xlib/XLIBwindow.h" // window_set_caption
#include "Platforms/General/PFwindow.h"
#include "Universal_System/roomsystem.h" // room_caption, update_mouse_variables

//#include <GL/glx.h>
#include <X11/Xlib.h>
#include <GL/glxew.h>

#include <iostream>
#include <cstring>
#include <stdio.h>

// NOTE: Changes/fixes that applies to this likely also applies to the OpenGL3 version.
namespace enigma {

GLXContext glxc;
XVisualInfo *vi;

extern void (*WindowResizedCallback)();
void WindowResized() {
  glViewport(0,0,enigma_user::window_get_width(),enigma_user::window_get_height());
  glScissor(0,0,enigma_user::window_get_width(),enigma_user::window_get_height());
  enigma_user::draw_clear(enigma_user::window_get_color());
}

XVisualInfo* CreateVisualInfo() {
  // Prepare openGL
  GLint att[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24, None };
  vi = glXChooseVisual(enigma::x11::disp,0,att);
  if(!vi){
      printf("Failed to Obtain GL Visual Info\n");
      return NULL;
  }
  return vi;
}

void EnableDrawing(void* handle) {
  WindowResizedCallback = &WindowResized;

  //give us a GL context
  glxc = glXCreateContext(enigma::x11::disp, vi, NULL, True);
  if (!glxc){
      printf("Failed to Create Graphics Context\n");
      return;
  }

  //apply context
  glXMakeCurrent(enigma::x11::disp,enigma::x11::win,glxc); //flushes
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_ACCUM_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void DisableDrawing(void* handle) {
  glXDestroyContext(enigma::x11::disp,glxc);
    /*
  for(char q=1;q;ENIGMA_events())
      while(XQLength(disp))
          if(handleEvents()>0) q=0;
  glxc = glXGetCurrentContext();
  glXDestroyContext(disp,glxc);
  XCloseDisplay(disp);
  return 0;*/
}

}
