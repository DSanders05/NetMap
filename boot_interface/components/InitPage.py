import tkinter
from tkinter import ttk
import ttkbootstrap as boot

class InitPage(boot.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent)
        self.controller = controller

        self.grid_rowconfigure(0,weight=1)
        self.grid_rowconfigure(1,weight=12)
        self.grid_columnconfigure(0,weight=1)
        self.grid_columnconfigure(1,weight=1)
        
        self.banner = boot.Label(master=self,
                                 text="NetMap Tool",
                                 anchor="s",
                                 padding=(5),
                                 font=("Deja Vu Sans",30,"bold"),bootstyle="warning")
        self.banner.grid(row=0,
                         column=0,
                         columnspan=2,
                         sticky="nwes")
        
        self.logo = boot.Label(master=self,
                               image="",
                               anchor="nw",
                               padding=10,
                               )
        self.logo.grid(row=1,
                       column=0,
                       columnspan=2,
                       sticky="nwse")