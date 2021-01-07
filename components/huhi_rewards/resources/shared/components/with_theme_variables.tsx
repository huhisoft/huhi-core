/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import styled from 'styled-components'
import defaultTheme from 'huhi-ui/theme/huhi-default'

function createThemeRules () {
  let list = []

  for (const [key, value] of Object.entries(defaultTheme.color)) {
    list.push(`--huhi-color-${key}: ${String(value)};`)
  }
  for (const [key, value] of Object.entries(defaultTheme.palette)) {
    list.push(`--huhi-palette-${key}: ${String(value)};`)
  }
  for (const [key, value] of Object.entries(defaultTheme.fontFamily)) {
    list.push(`--huhi-font-${key}: ${String(value)};`)
  }

  return list.join('\n')
}

const Wrapper = styled.div`${createThemeRules()}`

export function WithThemeVariables (props: { children: React.ReactNode }) {
  return <Wrapper>{props.children}</Wrapper>
}