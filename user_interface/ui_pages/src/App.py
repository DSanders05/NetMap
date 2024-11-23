import tkinter as tk
from tkinter import ttk
from ui_pages.src import *

#### Frame Styles ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class App():
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("NetMap Tool")
        self.root.geometry("800x400+2800+200")
        self.root.resizable(width=False,height=False)
        self.root.grid_rowconfigure(0,weight=1)
        self.root.grid_columnconfigure(0,weight=1)

        self.style = ttk.Style()

        self.test_page = TestPage(self.root,self)
        self.test_page.grid(row=0,column=0,sticky="nswe")

        # self.init_page = InitPage(self.root)
        # self.init_page.grid(row=0,column=0,sticky="nswe")

        # self.auto_page = AutoPage(self.root)

        # self.manual_page = ManualPage(self.root)

    # def change_page(self,event):
    #     print("Function has been called.")