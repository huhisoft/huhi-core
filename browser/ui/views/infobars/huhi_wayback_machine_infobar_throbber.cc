/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/views/infobars/huhi_wayback_machine_infobar_throbber.h"

#include "base/bind.h"
#include "base/location.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/paint_throbber.h"

HuhiWaybackMachineInfoBarThrobber::HuhiWaybackMachineInfoBarThrobber() {
}

HuhiWaybackMachineInfoBarThrobber::~HuhiWaybackMachineInfoBarThrobber() {
  Stop();
}

void HuhiWaybackMachineInfoBarThrobber::Start() {
  if (IsRunning())
    return;

  start_time_ = base::TimeTicks::Now();
  timer_.Start(
      FROM_HERE, base::TimeDelta::FromMilliseconds(30),
      base::BindRepeating(&HuhiWaybackMachineInfoBarThrobber::SchedulePaint,
                          base::Unretained(this)));
  SchedulePaint();  // paint right away
}

void HuhiWaybackMachineInfoBarThrobber::Stop() {
  if (!IsRunning())
    return;

  timer_.Stop();
  SchedulePaint();
}

void HuhiWaybackMachineInfoBarThrobber::OnPaint(gfx::Canvas* canvas) {
  if (!IsRunning())
    return;

  base::TimeDelta elapsed_time = base::TimeTicks::Now() - start_time_;
  gfx::PaintThrobberSpinning(
      canvas, GetContentsBounds(), SK_ColorWHITE, elapsed_time);
}

bool HuhiWaybackMachineInfoBarThrobber::IsRunning() const {
  return timer_.IsRunning();
}
