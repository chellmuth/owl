// ======================================================================== //
// Copyright 2019 Ingo Wald                                                 //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

/*! \file optix/common.h Creates a common set of includes, #defines,
  and helpers that will be visible across _all_ files, both host _and_
  device */

#pragma once

// device-safe parts of gdt
#include "gdt/math/vec.h"
#include "gdt/math/box.h"
#include "gdt/math/AffineSpace.h"

#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <typeinfo>
#include <mutex>
#include <atomic>

namespace owl {
  using gdt::vec3f;
}

#define IGNORING_THIS() std::cout << "## ignoring " << __PRETTY_FUNCTION__ << std::endl;
  
#define OWL_NOTIMPLEMENTED std::cerr << (std::string(__PRETTY_FUNCTION__)+" : not implemented") << std::endl; exit(1);

