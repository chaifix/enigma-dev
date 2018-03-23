/** Copyright (C) 2018 Greg Williamson, Robert B. Colton
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

#include "codegen/project.pb.h"

#include <string>

namespace gmx {
buffers::Project* LoadGMX(std::string fName, bool verbose = false);
void PackBuffer(std::string type, std::string res, int &id, google::protobuf::Message *m, std::string gmxPath);
template<class T>
T* LoadResource(std::string fName, std::string type, bool verbose);

}  //namespace gmx
