import tkinter as tk
from tkinter import ttk

#### Frame Style Colors ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class AutoPage(tk.Frame):
    def __init__(self,parent):
        super().__init__(master=parent)

        self.grid_columnconfigure(0,weight=1)
        self.grid_columnconfigure(1,weight=1)

        self.grid_rowconfigure(0,weight=1)
        self.grid_rowconfigure(1,weight=15)

        # self.controller = controller

        self.style = ttk.Style()

        self.rovers = []                    # list of rovers to display to list frame

        self.style.configure(style="AutoLabel.TLabel",foreground=WHITE,background=BACKGND,anchor="center",borderwidth=10,relief="solid")
        self.auto_lbl = ttk.Label(master=self,style="AutoLabel.TLabel",text="AUTO MODE",font=("Deja Vu Sans",30,"bold"))
        self.auto_lbl.grid(row=0,column=0,columnspan=2,sticky="new")


        self.style.configure(style="ListFrame.TFrame",background=BACKGND,anchor="center",borderwidth=10,relief="solid",width=300)
        self.list_frame = ttk.Frame(master=self,style="ListFrame.TFrame")

    def list_rovers(self):
        pass

    def update_rover_list(self):
        pass