import tkinter as tk
from tkinter import ttk
from user_interface.components.pages.InitPage import InitPage
from user_interface.components.pages.RoverSelect import SelectPage
from user_interface.components.pages.AutoPage import AutoPage
from user_interface.components.pages.ManPage import ManualPage

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

        #### PAGES ####
        self.style.configure(style="SelectPage.TFrame",background=BACKGND,anchor="ew")
        select_page = ttk.Frame(master=root,style="SelectPage.TFrame")


        self.style.configure(style="AutoPage.TFrame",background=BACKGND)
        auto_page = ttk.Frame(master=root,style="AutoPage.TFrame")
        auto_page.grid_columnconfigure(0,weight=1)
        auto_page.grid_columnconfigure(1,weight=1)
        auto_page.grid_rowconfigure(0,weight=1)
        auto_page.grid_rowconfigure(1,weight=15)
        # auto_page.grid(row=0,column=0,sticky="nswe")

        self.style.configure(style="ManPage.TFrame",background=BACKGND)
        man_page = ttk.Frame(master=root,style="ManPage.TFrame")
        man_page.grid_columnconfigure(0,weight=1)
        man_page.grid_columnconfigure(1,weight=1)
        man_page.grid_rowconfigure(0,weight=1)
        man_page.grid_rowconfigure(1,weight=15)
        man_page.grid(row=0,column=0,sticky="nswe")



        # #### AUTO FRAME MEMBERS ####
        def list_rovers():
            pass

        self.style.configure(style="AutoLabel.TLabel",foreground=WHITE,background=BACKGND,anchor="center",borderwidth=10,relief="solid")
        auto_mode_lbl = ttk.Label(master=auto_page,style="AutoLabel.TLabel",text="AUTO MODE",font=("Deja Vu Sans",30,"bold"))
        auto_mode_lbl.grid(row=0,column=0,columnspan=2,sticky="new")

        self.style.configure(style="AutoListFrame.TFrame",background=WHITE,borderwidth=10,relief="solid",anchor="center",width=300)
        list_frame = ttk.Frame(master=auto_page,style="AutoListFrame.TFrame")
        list_frame.grid(row=1,column=0,columnspan=2,sticky="ns")

        # #### MANUAL FRAME MEMBERS ####
        self.style.configure(style="ManLabel.TLabel",foreground=WHITE,background=BACKGND,anchor="center",borderwidth=10,relief="solid")
        man_mode_lbl = ttk.Label(master=man_page,style="ManLabel.TLabel",text="MANUAL MODE",font=("Deja Vu Sans",30,"bold"))
        man_mode_lbl.grid(row=0,column=0,columnspan=2,sticky="new")

        # selection frame can be reused from rover selection  