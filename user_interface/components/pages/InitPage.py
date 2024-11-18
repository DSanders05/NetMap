import tkinter as tk
from tkinter import ttk

#### Frame Style Colors ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class InitPage(ttk.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent)
        self.controller = controller        # Main App will be the "controller" of this page

        self.grid_columnconfigure(0,weight=1)
        self.grid_rowconfigure(0,weight=1)
        self.grid_rowconfigure(1,weight=10)
    
        #Style Object for Init Page
        style = ttk.Style()

        style.configure(style="NmLabel.TLabel",background=BACKGND,foreground=WHITE,anchor="center",borderwidth=10,relief="solid")
        ncpa_lbl = ttk.Label(master=self,style="NmLabel.TLabel",text="NetMap",font=("Deja Vu Sans",40,"bold"))
        ncpa_lbl.grid(column=0,row=0,sticky="nswe")


        style.configure(style="LogoLbl.TLabel",background=BACKGND,foreground=WHITE,anchor="nswe")
        ncpa_logo = ttk.Label(master=self,image="",style="LogoLbl.TLabel")
        ncpa_logo.grid(column=0,row=1,sticky="nswe")