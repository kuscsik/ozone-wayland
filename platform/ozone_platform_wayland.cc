// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/platform/ozone_platform_wayland.h"

#include "ozone/ui/cursor/cursor_factory_ozone_wayland.h"
#if defined(TOOLKIT_VIEWS) && !defined(OS_CHROMEOS)
#include "ozone/ui/desktop_aura/desktop_factory_wayland.h"
#endif
#include "ozone/ui/events/event_factory_ozone_wayland.h"
#include "ozone/ui/gfx/surface_factory_wayland.h"
#include "ozone/ui/ime/input_method_context_factory_wayland.h"
#include "ozone/wayland/display.h"
#include "ui/base/cursor/ozone/cursor_factory_ozone.h"
#include "ui/ozone/ozone_platform.h"

namespace ui {

namespace {

// OzonePlatform for Wayland
//
// This platform is Linux with the Wayland display server.
class OzonePlatformWayland : public OzonePlatform {
 public:
  OzonePlatformWayland() {}

  virtual ~OzonePlatformWayland() {}

  // OzonePlatform:
  virtual gfx::SurfaceFactoryOzone* GetSurfaceFactoryOzone() OVERRIDE {
    return &surface_factory_ozone_;
  }
  virtual ui::EventFactoryOzone* GetEventFactoryOzone() OVERRIDE {
    return &event_factory_ozone_;
  }
  virtual ui::InputMethodContextFactoryOzone*
  GetInputMethodContextFactoryOzone() OVERRIDE {
    return &input_method_context_factory_;
  }
  virtual ui::CursorFactoryOzone* GetCursorFactoryOzone() OVERRIDE {
    return &cursor_factory_ozone_;
  }

 private:
  ozonewayland::WaylandDisplay wayland_display_;
  gfx::SurfaceFactoryWayland surface_factory_ozone_;
  ui::EventFactoryOzoneWayland event_factory_ozone_;
  ui::InputMethodContextFactoryWayland input_method_context_factory_;
  ui::CursorFactoryOzoneWayland cursor_factory_ozone_;
#if defined(TOOLKIT_VIEWS) && !defined(OS_CHROMEOS)
  views::DesktopFactoryWayland desktop_factory_ozone_;
#endif
  DISALLOW_COPY_AND_ASSIGN(OzonePlatformWayland);
};

}  // namespace

OzonePlatform* CreateOzonePlatformWayland() { return new OzonePlatformWayland; }

}  // namespace ui
