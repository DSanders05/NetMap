import tkinter as tk
from tkinter import ttk
import ttkbootstrap as boot

class ManualPage(boot.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent)
        self.controller = controller

        self.grid_rowconfigure(0,weight=1)
        self.grid_rowconfigure(1,weight=12)

        self.grid_columnconfigure(0,weight=1)
        self.grid_columnconfigure(1,weight=1)

        self.banner = boot.Label(master=self,
                                 text="MANUAL MODE",
                                 anchor="center",
                                 padding=(5),
                                 font=("",30,"bold"),relief="solid")
        self.banner.grid(row=0,
                         column=0,
                         columnspan=2,
                         sticky="nwe")
        
        self.left_frame = boot.Frame(master=self,
                                     )
        self.left_frame.grid(row=1,column=0,sticky="nwse")
        
        self.right_frame = boot.Frame(master=self,
                                      )
        self.right_frame.grid(row=1,column=1,sticky="nwse")

        self.mode_button = boot.Button(master=self.right_frame,
                                       command="",
                                       text="AUTO MODE",padding=5)
        
        self.button2 = boot.Button(master=self.right_frame,
                                   text="Option 2",
                                   command="")