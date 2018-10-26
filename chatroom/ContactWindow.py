#!/usr/bin/env python
# -*- coding: utf-8 -*-

import wx
import ChatWindow
import wx.lib.scrolledpanel as scrolled
import simplejson as json
from simplejson import OrderedDict

class ContactFrame(wx.Frame):
    def __init__(self, sock):
        wx.Frame.__init__(self, None, -1,
                          "聊天列表",
                          size=(200,600))
        self.sock = sock
        #        self.Bind(wx.EVT_WINDOW_CREATE, self.GetUserList)

        self.panel = scrolled.ScrolledPanel(self, -1,
                                       size=(200, 1800),
                                       style = wx.TAB_TRAVERSAL | wx.SUNKEN_BORDER)


        self.timer = wx.Timer(self)
        self.timer.Start(4000)
        self.SetUserList()
        #        wx.EVT_WINDOW_CREATE,
        self.Bind(wx.EVT_TIMER, self.SetUserList, self.timer)

    def SetUserList(self, evt = ""):
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add((10, 10))
        il = wx.ImageList(32,32, True)#创建图像列表
        il_max = 0
        for x in range(1,12):
            if x < 10:
                x = "0"+str(x)
            name = "bmp_source/LB"+str(x)+".png"
            bmp = wx.Bitmap(name, wx.BITMAP_TYPE_PNG)
            il.Add(bmp)
            il_max = il_max + 1

        self.list = wx.ListCtrl(self.panel, -1,
                           style=wx.LC_ICON | wx.LC_AUTOARRANGE)
        self.list.AssignImageList(il, wx.IMAGE_LIST_NORMAL)
        #获取用户列表
        msg = "{\"action\": \"get_users\"}"
        bufsize = 100000
        self.sock.send(msg)
        UserList = self.sock.recv(bufsize)
        UserList = json.loads(UserList)
        print UserList
        #显示用户列表
        num = 0
        for x in UserList['users']:
            img = num % il_max
            self.list.InsertImageStringItem(num,x, img)
            num = num + 1
        self.currentItem = ""
        self.list.Bind(wx.EVT_LEFT_DCLICK, self.OnChat)
        self.Bind(wx.EVT_LIST_ITEM_SELECTED, self.OnItemSelected, self.list)

        sizer.Add(self.list, 1, wx.EXPAND)

        self.panel.SetSizer(sizer)
        self.panel.SetAutoLayout(True)
        self.panel.SetupScrolling()
    def OnItemSelected(self, evt):
        self.currentItem = evt.m_itemIndex
        self.list.SetItemState(self.currentItem, 0, wx.LIST_STATE_SELECTED)
        print self.currentItem
    def OnChat(self, evt):
        print   self.list.GetItemText(self.currentItem)
        self.chatWindow = ChatWindow.Frame()
        self.chatWindow.Show()
        
        print "cccc"



    def OnExit(self, evt):
        self.sock.close()
        self.Close(True)
        wx.ExitMainLoop()


# if __name__ == '__main__':
#     app = wx.PySimpleApp()
#     frame = DemoFrame()
#     frame.Show()
#     app.MainLoop()
