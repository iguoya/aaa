#!/usr/bin/env python
# -*- coding: utf-8 -*-
#

import wx

class Frame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, parent = None, id = -1, pos = wx.DefaultPosition,size=(800, 600), title = '聊天窗口')
        panel = wx.Panel(self, -1)
        panel.SetAutoLayout(True)
        txt_chatView = wx.TextCtrl(panel, -1, "",
                size = (600, 400), style = wx.TE_MULTILINE | wx.TE_RICH2 | wx.TE_READONLY)


        sizer_font = wx.GridSizer(rows = 1, cols = 8, vgap = 3, hgap = 5)

        btn_setFont = wx.Button(panel, -1, "字体")
        self.Bind(wx.EVT_BUTTON, self.OnSelectFont, btn_setFont)
        btn_setColor = wx.Button(panel, -1, "颜色")
        self.Bind(wx.EVT_BUTTON, self.OnSelectColor, btn_setColor)

        sizer_font.Add(btn_setFont)
        sizer_font.Add(btn_setColor)


        txt_chatView.SetFont(wx.Font(14, wx.DEFAULT, wx.NORMAL, wx.NORMAL, 0, ""))

        #chat input
        txt_chatInput = wx.TextCtrl(panel, -1, "",
                size = (600, 50), style = wx.TE_MULTILINE | wx.TE_RICH2)

        txt_chatInput.SetFont(wx.Font(14, wx.DEFAULT, wx.NORMAL, wx.NORMAL, 0, ""))


        #        txt_chatInput.curFont =  txt_chatInput.GetFont()
        #        print txt_chatInput.GetFont()
        self.txt_chatInput = txt_chatInput

        btn_sendfile = wx.Button(panel, -1, "发送文件")
        btn_history = wx.Button(panel, -1, "聊天记录")
        btn_sendmsg = wx.Button(panel, -1, "发送")
        btn_exit = wx.Button(panel, -1, "退出")
        self.Bind(wx.EVT_BUTTON, self.OnExit, btn_exit)

        sizer_send = wx.GridSizer(rows = 1, cols = 4, vgap = 3, hgap = 5)
        sizer_send.Add(btn_sendfile, 0, wx.ALIGN_CENTER)
        sizer_send.Add(btn_history, 0, wx.ALIGN_CENTER)
        sizer_send.Add(btn_sendmsg, 0, wx.ALIGN_CENTER)
        sizer_send.Add(btn_exit, 0, wx.ALIGN_CENTER)

        space = 10
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(txt_chatView, 0, wx.GROW | wx.ALL, space)
        sizer.Add(sizer_font, 0, wx.GROW | wx.ALL, space)
        sizer.Add(txt_chatInput, 0, wx.GROW | wx.ALL, space)
        sizer.Add(sizer_send, 0, wx.GROW | wx.ALL, space)

        panel.SetSizer(sizer)


    def OnSelectFont(self, evt):
        data = wx.FontData()
        data.EnableEffects(True)
        #        data.SetInitialFont(self.txt_chatInput.curFont)
        dlg = wx.FontDialog(self, data)
        if dlg.ShowModal() == wx.ID_OK:
            data = dlg.GetFontData()
            font = data.GetChosenFont()

            print('You selected: "%s", %d points\n' %
            (font.GetFaceName(), font.GetPointSize()))
            self.txt_chatInput.SetFont(wx.Font(font.GetPointSize(), wx.DEFAULT, wx.NORMAL, wx.NORMAL, 0, ""))
        dlg.Destroy()

    def OnSelectColor(self, evt):
        dlg = wx.ColourDialog(self)
        dlg.GetColourData().SetChooseFull(True)

        if dlg.ShowModal() == wx.ID_OK:
            data = dlg.GetColourData()
            #            wx.TextAttr(colText, colBack=wx.NullColor, font=wx.NullFont)
            #            self.txt_chatInput.SetStyle(68, 82, 
            #            self.txt_chatInput.textAttr.SetTextColour(data.GetColour())
            #          attr.SetTextColour(colour)
            attr = wx.TextAttr(data.GetColour())
            self.txt_chatInput.SetStyle(r, attr)

            #            print('You selected: %s\n' % str(data.GetColour().Get()))

        dlg.Destroy()


    def OnExit(self, evt):
        self.Close(True)

class ChatWindow(wx.App):
    def OnInit(self):
        self.frame = Frame()
        self.frame.Show()
        self.SetTopWindow(self.frame)
        return True


if __name__=='__main__':
    app = ChatWindow()
    app.MainLoop()
