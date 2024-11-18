import tkinter as tk
from tkinter import ttk
from user_interface.components.ListFrame import ListFrame

#### Frame Style Colors ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class AutoPage(tk.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent)

        self.controller = controller

        self.style = ttk.Style()

        self.style.configure(style="AutoLabel.TLabel",foreground=WHITE,background=BACKGND,anchor="center",borderwidth=10,relief="solid")
        self.auto_lbl = ttk.Label(master=self,style="AutoLabel.TLabel",text="AUTO MODE",font=("Deja Vu Sans",30,"bold"))
        self.auto_lbl.grid(row=0,column=0,columnspan=2,sticky="new")

        self.list_frame = ListFrame()

    def list_rovers(self):
        pass