import tkinter
from tkinter import ttk
import ttkbootstrap as boot
from .InitPage import InitPage
from .AutoPage import AutoPage

class App():
    def __init__(self):
        self.window = boot.Window(title="NetMap Tool",
                                  themename="superhero",
                                  size=(800,400),
                                  resizable=(False,False))
        
        self.window.grid_rowconfigure(0,weight=1)
        self.window.grid_columnconfigure(0,weight=1)
        self.window.place_window_center()

        self.init_page = InitPage(self.window,self)
        # self.init_page.grid(row=0,column=0,sticky="nwse")

        self.auto_page = AutoPage(self.window,self)
        self.auto_page.grid(row=0,column=0,sticky="nswe")