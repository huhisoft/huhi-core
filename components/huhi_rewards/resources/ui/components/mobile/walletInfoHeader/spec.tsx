/* global jest, expect, describe, it, afterEach */
import * as React from 'react'
import { shallow } from 'enzyme'
import { create } from 'react-test-renderer'
import WalletInfoHeader from './index'
import { TestThemeProvider } from 'huhi-ui/theme'

describe('WalletInfoHeader tests', () => {
  const baseComponent = (props?: object) => <TestThemeProvider><WalletInfoHeader id='info-header' {...props} /></TestThemeProvider>

  describe('basic tests', () => {
    it('matches the snapshot', () => {
      const component = baseComponent()
      const tree = create(component).toJSON()
      expect(tree).toMatchSnapshot()
    })

    it('renders the component', () => {
      const wrapper = shallow(baseComponent())
      const assertion = wrapper.find('#info-header').length
      expect(assertion).toBe(1)
    })
  })
})