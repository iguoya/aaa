#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

import wx
import ContactWindow

import socket

class LoginFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, parent = None, id = -1, pos = wx.DefaultPosition,size=(300, 500), title = '登陆窗口')
        panel = wx.Panel(self, -1)
        panel.SetAutoLayout(True)

        sizer = wx.BoxSizer(wx.VERTICAL)

        #用户名，密码框
        lbl_user = wx.StaticText(panel, -1, "用户名", (300,50),  style=wx.ALIGN_CENTER)

        #lbl_user.SetForegroundColour("white")
        #lbl_user.SetBackgroundColour("red")
        txt_user = wx.TextCtrl(panel, -1, "", size = wx.DefaultSize)
        txt_user.SetFocus()

        lbl_pwd = wx.StaticText(panel, -1, "登陆密码", (300,50), (250, -1), wx.ALIGN_RIGHT)
        txt_pwd = wx.TextCtrl(panel, -1, "", size = wx.DefaultSize, style=wx.TE_PASSWORD)

        #登陆按钮
        sizer_btn = wx.GridSizer(rows = 1, cols = 2, vgap = 3, hgap = 5)
        btn_login = wx.Button(panel, -1, "登陆")
        btn_exit  = wx.Button(panel, -1, "退出")

        sizer_btn.Add(btn_login, 0, wx.ALIGN_CENTER)
        sizer_btn.Add(btn_exit, 0, wx.ALIGN_CENTER)

        #排版，布局
        space = 10

        sizer.Add(lbl_user, 0, wx.GROW | wx.ALL, space)
        sizer.Add(txt_user, 0, wx.GROW | wx.ALL, space)

        sizer.Add(lbl_pwd, 0, wx.GROW | wx.ALL, space)
        sizer.Add(txt_pwd, 0, wx.GROW | wx.ALL, space)
        sizer.Add(sizer_btn, 0, wx.GROW | wx.ALL, space)

        panel.SetSizer(sizer)
        self.panel = panel
        self.txt_user = txt_user
        self.txt_pwd = txt_pwd

        #事件绑定
        self.Bind(wx.EVT_BUTTON, self.OnLogin, btn_login)
        self.Bind(wx.EVT_BUTTON, self.OnExit, btn_exit)


    def OnLogin(self, evt):
        user = self.txt_user.GetValue()
        password = self.txt_pwd.GetValue()

        # if len(user) <= 3 or len(password) <= 3:
        #     dlg = wx.MessageDialog(self.panel, "用户名和密码长度不能小于3位！",
        #                      "提示",wx.OK | wx.ICON_INFORMATION)
        #     dlg.ShowModal()
        #     dlg.Destroy()
        #        print txt, pwd
        print user, password
        bufsize = 100
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect(("localhost", 5000))
        msg = "{\"action\":\"login\",\"user\":\""+user+"\",\"password\":\""+password+"\"}"
        sock.send(msg)
        result = sock.recv(bufsize)
        print result
        if result == "true":
            self.ContactPanel = ContactWindow.ContactFrame(sock)
            self.ContactPanel.Show()
            self.Close()
        else:
            dlg = wx.MessageDialog(self.panel, "密码错误！",
                                   "提示",wx.OK | wx.ICON_INFORMATION)
            dlg.ShowModal()
            dlg.Destroy()

    def OnExit(self, evt):
        self.Close(True)
        wx.Exit()
