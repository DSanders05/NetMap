import tkinter as tk
from tkinter import ttk

#### Frame Style Colors ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class ManualPage(tk.Frame):
    def __init__(self,parent):
        super().__init__(master=parent)
        self.grid_columnconfigure(0,weight=1)
        self.grid_columnconfigure(1,weight=1)

        self.grid_rowconfigure(0,weight=1)
        self.grid_rowconfigure(1,weight=15)

        # self.controller=controller

        self.style = ttk.Style()
        self.style.configure(style="ManPage.TFrame",background=BACKGND)

        self.style.configure(style="ManLbl.TLabel",background=BACKGND,foreground=WHITE,anchor="center",borderwidth=10,relief="solid")
        self.man_lbl = ttk.Label(master=self,style="ManLbl.TLabel",text="MANUAL MODE",font=("Deja Vu Sans",30,"bold"))
        self.man_lbl.grid(row=0,column=0,columnspan=2,sticky="new")