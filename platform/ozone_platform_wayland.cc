// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ozone/platform/ozone_platform_wayland.h"

#include "ozone/ui/cursor/cursor_factory_ozone_wayland.h"
#if defined(TOOLKIT_VIEWS) && !defined(OS_CHROMEOS)
#include "ozone/ui/desktop_aura/desktop_factory_wayland.h"
#endif
#include "ozone/ui/events/event_factory_ozone_wayland.h"
#include "ozone/ui/ime/input_method_context_factory_wayland.h"
#include "ui/ozone/ime/input_method_context_factory_ozone.h"
#include "ozone/wayland/display.h"
#include "ozone/wayland/proxy_display.h"
#include "ui/base/cursor/ozone/cursor_factory_ozone.h"
#include "ui/ozone/ozone_platform.h"

namespace ui {

namespace {

// OzonePlatform for Wayland
//
// This platform is Linux with the Wayland display server.
class OzonePlatformWayland : public OzonePlatform {
 public:
  OzonePlatformWayland() : wayland_proxy_display_(NULL) {}

  virtual ~OzonePlatformWayland() {
    delete wayland_proxy_display_;
  }

  // OzonePlatform:
  virtual gfx::SurfaceFactoryOzone* GetSurfaceFactoryOzone() OVERRIDE {
    return wayland_display_.get();
  }
  virtual EventFactoryOzone* GetEventFactoryOzone() OVERRIDE {
    return event_factory_ozone_.get();
  }

  virtual InputMethodContextFactoryOzone* GetInputMethodContextFactoryOzone()
      OVERRIDE {
    return &input_method_context_factory_ozone_;
  }

  virtual CursorFactoryOzone* GetCursorFactoryOzone() OVERRIDE {
    return cursor_factory_ozone_.get();
  }

  virtual void InitializeUI() OVERRIDE {
    input_method_factory_.reset(
        new ui::InputMethodContextFactoryWayland());
    event_factory_ozone_.reset(
        new ui::EventFactoryOzoneWayland());
    cursor_factory_ozone_.reset(new ui::CursorFactoryOzoneWayland());
    wayland_proxy_display_ = new ozonewayland::WaylandProxyDisplay();
  }

  virtual void InitializeGPU() OVERRIDE {
    // We don't need proxy display in case of Single process.
    // TODO(kalyan): Find a better way to handle this.
    if (wayland_proxy_display_) {
      delete wayland_proxy_display_;
      wayland_proxy_display_ = NULL;
    }

    wayland_display_.reset(new ozonewayland::WaylandDisplay());
    if (!event_factory_ozone_)
      event_factory_ozone_.reset(new ui::EventFactoryOzoneWayland());
  }

 private:
#if defined(TOOLKIT_VIEWS) && !defined(OS_CHROMEOS)
  views::DesktopFactoryWayland desktop_factory_ozone_;
#endif
  ozonewayland::WaylandProxyDisplay* wayland_proxy_display_;
  scoped_ptr<ui::InputMethodContextFactoryWayland> input_method_factory_;
  scoped_ptr<ui::EventFactoryOzoneWayland> event_factory_ozone_;
  scoped_ptr<ui::CursorFactoryOzoneWayland> cursor_factory_ozone_;
  scoped_ptr<ozonewayland::WaylandDisplay> wayland_display_;
  InputMethodContextFactoryOzone input_method_context_factory_ozone_;

  DISALLOW_COPY_AND_ASSIGN(OzonePlatformWayland);
};

}  // namespace

OzonePlatform* CreateOzonePlatformWayland() { return new OzonePlatformWayland; }

}  // namespace ui
