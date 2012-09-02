/*
 -----------------------------------------------------------------------------
 This source file is part of the Project Furai.
 For more information, go to:
 http://code.google.com/p/furai/
 -----------------------------------------------------------------------------

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

#include <stdio.h>
#include "ppapi/cpp/completion_callback.h"
#include "ppapi/cpp/rect.h"
#include "ppapi/cpp/var.h"
#include "GLES2/gl2.h"
#include "external/nacl/opengl_context.h"
#include "MinimalInstance.h"

namespace async {
void UpdateCallback(void* data, int32_t /*result*/) {
  MinimalInstance* minimal_instance = static_cast<MinimalInstance*>(data);
  minimal_instance->Update();
}

void UpdateScheduler(int32_t delay, void* data) {
  pp::Core* core = pp::Module::Get()->core();
  core->CallOnMainThread(delay,
                         pp::CompletionCallback(async::UpdateCallback, data));
}
}

bool MinimalInstance::Init(uint32_t argc, const char* argn[],
                           const char* argv[]) {
  async::UpdateScheduler(0, this);
  return true;
}

void MinimalInstance::DidChangeView(const pp::View& view) {
  pp::Rect position = view.GetRect();
  if (opengl_context_ == NULL)
    opengl_context_.reset(new tumbler::OpenGLContext(this));
  opengl_context_->InvalidateContext(this);
  opengl_context_->ResizeContext(position.size());
  if (!opengl_context_->MakeContextCurrent(this))
    return;

  glViewport(0, 0, position.width(), position.height());
}

void MinimalInstance::Update() {

  if (opengl_context_ == NULL)
    return;
  opengl_context_->MakeContextCurrent(this);

  r_ += 0.01f;
  if (r_ > 1.f) {
    r_ = 0;
  }

  g_ += 0.02f;
  if (g_ > 1.f) {
    g_ = 0;
  }

  b_ += 0.03f;
  if (b_ > 1.f) {
    b_ = 0;
  }

  glClearColor(r_, g_, b_, 1.f);

  glClear(GL_COLOR_BUFFER_BIT);

  opengl_context_->FlushContext();

  async::UpdateScheduler(17, this);
}
