import tkinter as tk
from tkinter import ttk
from user_interface.components.NumPad import NumPad

#### Frame Style Colors ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class SelectPage(tk.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent)

        self.grid_rowconfigure(0,weight=1)
        self.grid_rowconfigure(1,weight=4)

        self.grid_columnconfigure(0,minsize=200)
        self.grid_columnconfigure(1,minsize=200)

        self.controller=controller

        self.text = tk.StringVar()

        self.style = ttk.Style()             # Style object for page

        self.style.configure(style="RovPageLbl.TLabel",background=BACKGND,foreground=WHITE,anchor="center")
        self.page_lbl = ttk.Label(master=self,text="Enter number of rovers deployed:",font=("Deja Vu Sans",30,"bold"))
        self.page_lbl.grid(row=0,column=0,sticky="nwes",columnspan=2)

        self.num_pad = NumPad(self,self)
        self.num_pad.grid(row=1,column=0)

        self.style.configure(style="RoverEntry.TEntry",foreground=WHITE,anchor="center")
        self.entry = ttk.Entry(master=self,style="RoverEntry.TEntry",textvariable=self.text,width=20,font=("Deja Vu Sans",20),takefocus=False)
        self.entry.grid(row=1,column=1,sticky="n")

    def on_button_press():
        pass

    def submit_entry():
        pass

    def clear_entry():    
        pass