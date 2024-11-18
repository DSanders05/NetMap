from enum import auto
import tkinter as tk
from tkinter import ttk
from turtle import back, clear
import tksvg



#### Frame Styles ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class App():
    root = tk.Tk()
    root.title("NetMap Tool")
    root.geometry("800x400+2800+200")
    root.resizable(width=False,height=False)
    root.grid_rowconfigure(0,weight=1)
    root.grid_columnconfigure(0,weight=1)
    

    nm_style = ttk.Style()

    #### PAGES ####
    nm_style.configure(style="InputPage.TFrame",background=BACKGND)
    init_page = ttk.Frame(master=root,style='InputPage.TFrame')
    init_page.grid_columnconfigure(0,weight=1)
    init_page.grid_rowconfigure(0,weight=1)
    init_page.grid_rowconfigure(1,weight=3)
    # init_page.grid(row=0,column=0,sticky="nsew")

    nm_style.configure(style="SelectPage.TFrame",background=BACKGND,anchor="ew")
    select_page = ttk.Frame(master=root,style="SelectPage.TFrame")
    select_page.grid_rowconfigure(0,weight=1)
    select_page.grid_rowconfigure(1,weight=4)
    select_page.grid_columnconfigure(0,minsize=200)
    select_page.grid_columnconfigure(1,minsize=200)
    # select_page.grid(row=0,column=0,sticky="nswe")

    nm_style.configure(style="AutoPage.TFrame",background=BACKGND)
    auto_page = ttk.Frame(master=root,style="AutoPage.TFrame")
    auto_page.grid_columnconfigure(0,weight=1)
    auto_page.grid_columnconfigure(1,weight=1)
    auto_page.grid_rowconfigure(0,weight=1)
    auto_page.grid_rowconfigure(1,weight=15)
    # auto_page.grid(row=0,column=0,sticky="nswe")

    nm_style.configure(style="ManPage.TFrame",background=BACKGND)
    man_page = ttk.Frame(master=root,style="ManPage.TFrame")
    man_page.grid_columnconfigure(0,weight=1)
    man_page.grid_columnconfigure(1,weight=1)
    man_page.grid_rowconfigure(0,weight=1)
    man_page.grid_rowconfigure(1,weight=15)
    man_page.grid(row=0,column=0,sticky="nswe")
    

    #### INIT PAGE MEMBERS ####
    nm_style.configure(style="InitLabel.TLabel", background=BACKGND,foreground=WHITE,anchor="center",borderwidth=10,relief="solid")
    init_frame_label = ttk.Label(master=init_page,text="NetMap",font=("Deja Vu Sans", 40,"bold"),style="InitLabel.TLabel")
    # init_frame_label.grid(column=0,row=0,sticky="nswe")

    nm_style.configure(style="LogoLabel.TLabel",borderwidth=10,anchor="nswe",relief="solid")
    logo_label = ttk.Label(master=init_page,image=tksvg.SvgImage(file="~/NetMap/user_interface/ncpa_logo.svg"),style="LogoLabel.TLabel")
    # logo_label.grid(column=0,row=1,sticky="nswe")

    # #### ROVER SELECT FRAME MEMBERS ####
    def on_button_press(self, value):
        current_text = self.entry_var.get()
        self.entry_var.set(current_text + value)

    def submit_entry(self):
        print("Entered: ", self.entry_var.get())

    def clear_entry(self):
        self.entry_var.set("")

    nm_style.configure(style="RoverLabel.TLabel",background=BACKGND,anchor="center",foreground=WHITE)
    rov_select_lbl = ttk.Label(master=select_page, style="RoverLabel.TLabel",text="Enter number of rovers deployed:",font=('Deja Vu Sans',30,"bold"))
    rov_select_lbl.grid(row=0,column=0,sticky="nwes",columnspan=2)
    
    nm_style.configure(style="NumPad.TFrame",background=BACKGND)
    num_pad = ttk.Frame(master=select_page,style="NumPad.TFrame")
    num_pad.grid(row=1,column=0,sticky="nsew")

    for i in range(0,3):
        num_pad.grid_columnconfigure(i,weight=1)

    for i in range(0,6):
        num_pad.grid_rowconfigure(i,weight=1)

    nm_style.configure(style="NumPadBtn.TButton",font=("Deja Vu Sans", 10),)
    num0 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="0",command=on_button_press)
    num0.grid(row=4,column=0,sticky="nswe",padx=(10,0))

    num7 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="7",command=on_button_press)
    num7.grid(row=1,column=0,sticky="nswe",padx=(10,0))

    num8 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="8",command=on_button_press)
    num8.grid(row=1,column=1,sticky="nswe")

    num9 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="9",command=on_button_press)
    num9.grid(row=1,column=2,sticky="nswe",padx=(0,10))

    num4 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="4",command=on_button_press)
    num4.grid(row=2,column=0,sticky="nswe",padx=(10,0))

    num5 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="5",command=on_button_press)
    num5.grid(row=2,column=1,sticky="nswe")

    num6 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="6",command=on_button_press)
    num6.grid(row=2,column=2,sticky="nswe",padx=(0,10))

    num1 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="1",command=on_button_press)
    num1.grid(row=3,column=0,sticky="nswe",padx=(10,0))

    num2 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="2",command=on_button_press)
    num2.grid(row=3,column=1,sticky="nswe")

    num3 = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="3",command=on_button_press)
    num3.grid(row=3,column=2,sticky="nswe",padx=(0,10))

    enter_button = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="ENTER",command=submit_entry)
    enter_button.grid(row=4,rowspan=2,column=1,columnspan=2,sticky="nswe",padx=(0,10),pady=(0,10))

    clear_button = ttk.Button(master=num_pad,style="NumPadBtn.TButton",text="CLR",command=on_button_press)
    clear_button.grid(row=5,column=0,sticky="nswe",padx=(10,0),pady=(0,10))

    entry_var = tk.StringVar()
    nm_style.configure(style="RoverEntry.TEntry",foreground=WHITE,anchor="center")
    num_entry = ttk.Entry(master=select_page,style="RoverEntry.TEntry",textvariable=entry_var,width=25,font=("Deja Vu Sans",20),takefocus=False)
    num_entry.grid(row=1,column=1,sticky="n")

    # #### AUTO FRAME MEMBERS ####
    def list_rovers():
        pass

    nm_style.configure(style="AutoLabel.TLabel",foreground=WHITE,background=BACKGND,anchor="center",borderwidth=10,relief="solid")
    auto_mode_lbl = ttk.Label(master=auto_page,style="AutoLabel.TLabel",text="AUTO MODE",font=("Deja Vu Sans",30,"bold"))
    auto_mode_lbl.grid(row=0,column=0,columnspan=2,sticky="new")

    nm_style.configure(style="AutoListFrame.TFrame",background=WHITE,borderwidth=10,relief="solid",anchor="center",width=300)
    list_frame = ttk.Frame(master=auto_page,style="AutoListFrame.TFrame")
    list_frame.grid(row=1,column=0,columnspan=2,sticky="ns")

    # #### MANUAL FRAME MEMBERS ####
    nm_style.configure(style="ManLabel.TLabel",foreground=WHITE,background=BACKGND,anchor="center",borderwidth=10,relief="solid")
    man_mode_lbl = ttk.Label(master=man_page,style="ManLabel.TLabel",text="MANUAL MODE",font=("Deja Vu Sans",30,"bold"))
    man_mode_lbl.grid(row=0,column=0,columnspan=2,sticky="new")

    # selection frame can be reused from rover selection  