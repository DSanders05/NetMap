import tkinter as tk
from tkinter import ttk
import ttkbootstrap as boot

class AutoPage(boot.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent,padding=10)
        self.controller = controller
        self.page_style = boot.Style()
        self.page_style.configure('MenuButton.TButton',font=("Helvetica",18,"bold"),anchor="center")
        

        self.grid_rowconfigure(0,weight=1)
        self.grid_rowconfigure(1,weight=12)

        self.grid_columnconfigure(0,weight=1)
        self.grid_columnconfigure(1,weight=1)

        self.banner = boot.Label(master=self,
                                 text="AUTO MODE",
                                 anchor="s",
                                 padding=(5),
                                 font=("",30,"bold"))
        self.banner.grid(row=0,
                         column=0,
                         columnspan=2,
                         sticky="nwse")
        
        self.left_frame = boot.Frame(master=self,
                                     padding=10)
        self.left_frame.grid(row=1,
                             column=0,
                             sticky="nswe")
        self.left_frame.grid_rowconfigure(0,weight=1)
        self.left_frame.grid_columnconfigure(0,weight=1)
        
        self.list_box = tk.Listbox(master=self.left_frame,
                                   background="#ffffff")
        self.list_box.grid(row=0,column=0,columnspan=1,sticky="nsew")

        self.vert_divider = boot.Separator(master=self,
                                           orient='vertical',
                                           bootstyle='success')
        # self.vert_divider.grid(row=1,column=1,sticky="ns")


        self.right_frame = boot.Frame(master=self,
                                    padding=10)
        self.right_frame.grid(row=1,
                              column=1,
                              sticky="nswe")
        self.right_frame.grid_rowconfigure(0,weight=1)
        self.right_frame.grid_columnconfigure(0,weight=1)
        
        self.menu_frame = boot.Frame(master=self.right_frame,bootstyle="light")
        self.menu_frame.grid(row=0,column=0,sticky="nswe")
        # self.menu_frame.grid_rowconfigure(0,weight=1)
        # self.menu_frame.grid_columnconfigure(0,weight=1)

        self.mode_button = boot.Button(master=self.menu_frame,
                                       bootstyle="dark",
                                       text="Manual Mode",
                                       width=12,
                                       padding=(0,5),
                                       style="MenuButton.TButton").place(anchor='center',rely=.25,relx=.5)
        
        self.stop_button = boot.Button(master=self.menu_frame,
                                       bootstyle="success",
                                       text="STOP",
                                       width=12,
                                       padding=(0,5),
                                       style="MenuButton.TButton").place(anchor='center',rely=.5,relx=.5)
        
        self.optional_button = boot.Button(master=self.menu_frame,
                                           text="OPT BUTTON",
                                           width=12,padding=(0,5),
                                           style="MenuButton.TButton").place(anchor="center",rely=.75,relx=.5)

    def list_items():
        pass