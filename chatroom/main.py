#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

import wx
import LoginWindow
import ContactWindow

class MainApp(wx.App):
    def OnInit(self):
        self.frame = LoginWindow.LoginFrame()
        #        self.frame = ContactWindow.ContactFrame()
        self.frame.Show()
        #        self.SetTopWindow(self.frame)
        return True


if __name__=='__main__':
    app = MainApp()
    app.MainLoop()
