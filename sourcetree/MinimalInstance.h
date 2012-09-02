/*
 Copyright 2012 Allan Yoshio Hasegawa

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 -----------------------------------------------------------------------------
 */

#ifndef MINIMAL_MINIMALINSTANCE_H_
#define MINIMAL_MINIMALINSTANCE_H_

#include "GLES2/gl2.h"
#include "ppapi/cpp/instance.h"
#include "external/nacl/opengl_context.h"
#include "external/nacl/opengl_context_ptrs.h"

class MinimalInstance : public pp::Instance {
 public:
  explicit MinimalInstance(PP_Instance instance)
      : pp::Instance(instance),
        r_(0),
        g_(0),
        b_(0) {
  }
  ;
  virtual ~MinimalInstance() {
    opengl_context_->MakeContextCurrent(this);
  }

  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);

  // Called whenever the in-browser window changes size.
  virtual void DidChangeView(const pp::View& view);

  void Update();

 private:
  tumbler::SharedOpenGLContext opengl_context_;
  GLfloat r_, g_, b_;
};

#endif /* MINIMAL_MINIMALINSTANCE_H_ */
