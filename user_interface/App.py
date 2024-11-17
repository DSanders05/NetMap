from enum import auto
import tkinter as tk
from tkinter import ttk
import tksvg
from tkinter import font



#### Frame Styles ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class App():
    root = tk.Tk()
    root.title("NetMap Tool")
    root.geometry("800x400")
    root.resizable(width=False,height=False)

    #### TOPLEVELS ####
    init_page = tk.Frame(master=root,background=BACKGND)
    # init_page.grid(row=0,column=0,padx=5,pady=5)

    rover_input_page = tk.Frame(master=root,background=BACKGND)
    # rover_input_page.grid(row=0,column=0)

    auto_page = tk.Frame(master=root,background=BACKGND)
    # auto_page.grid(row=0,column=0)

    manual_page = tk.Frame(master=root,background=BACKGND)
    manual_page.grid(row=0,column=0,sticky='we')



    #### Styles ####

    # Create style for ttk.Button

    init_frame_style = ttk.Style()
    rover_selec_style = ttk.Style()
    auto_frame_style = ttk.Style()
    manual_frame_style = ttk.Style()



    #### INIT TOPLVL MEMBERS ####
    init_frame_label = ttk.Label(master=init_page,text="NetMap",font="DejaVuSans 40",padding="100 30",background=BACKGND,foreground=WHITE)                               # This label holds the text NetMap
    init_frame_label.grid(column=0,row=0)

    logo_label = tk.Label(master=init_page,image=tksvg.SvgImage(file="~/NetMap/user_interface/ncpa_logo.svg"),anchor='w',height=300,width=800,background=BACKGND)
    logo_label.grid(column=0,row=2,rowspan=2)



    # #### ROVER SELECT FRAME MEMBERS ####
    rover_pg_label = ttk.Label(master=rover_input_page,text="Enter number of rovers deployed:",font="DejaVuSans 20",background=BACKGND,foreground=WHITE,padding="0 15")
    rover_pg_label.grid(column=0,row=1)

    rover_entry = ttk.Entry(master=rover_input_page,width=10,font='DejaVuSans 20')
    rover_entry.grid(column=1,row=1)

    num_pad = ttk.Frame(master=rover_input_page,width=280)
    num_pad.grid(column=0,row=2)

    num0 = ttk.Button(master=num_pad, text="0",width=30)
    num0.grid(row=3,column=0)

    num1 = ttk.Button(master=num_pad, text="1",width=30)
    num1.grid(row=0,column=0)

    num2 = ttk.Button(master=num_pad, text="2",width=30)
    num2.grid(row=0,column=1)

    num3 = ttk.Button(master=num_pad, text="3",width=30)
    num3.grid(row=0,column=2)

    num4 = ttk.Button(master=num_pad, text="4",width=30)
    num4.grid(row=1,column=0)

    num5 = ttk.Button(master=num_pad, text="5",width=30)
    num5.grid(row=1,column=1)

    num6 = ttk.Button(master=num_pad, text="6",width=30)
    num6.grid(row=1,column=2)

    num7 = ttk.Button(master=num_pad, text="7",width=30)
    num7.grid(row=2,column=0)

    num8 = ttk.Button(master=num_pad, text="8",width=30)
    num8.grid(row=2,column=1)

    num9 = ttk.Button(master=num_pad, text="9",width=30)
    num9.grid(row=2,column=2)

    enter_button = ttk.Button(master=num_pad, text="ENTER",width=30)
    enter_button.grid(row=3,column=1,columnspan=1,sticky='e')

    clear_button = ttk.Button(master=num_pad, text="CLEAR",width=30)
    clear_button.grid(row=3,column=2,columnspan=1)


    # #### AUTO FRAME MEMBERS ####
    mode_label = ttk.Label(master=auto_page)
    list_frame = ttk.Frame(master=auto_page)
    menu_frame = ttk.Frame(master=auto_page)


    # #### MANUAL FRAME MEMBERS ####
    mode_label = ttk.Label(master=manual_page,text="MANUAL MODE ENABLED",font='DejaVuSans 20',padding="5 5",background=BACKGND,foreground=WHITE)
    mode_label.grid(column=0,row=0,columnspan=4,sticky='we')

    target_label = ttk.Label(master=manual_page,text="TARGET: ",font='DejaVuSans 20',padding='5 5',foreground=WHITE,background=BACKGND)
    target_label.grid(column=0,row=1,sticky='we')

    current_heading_lbl = ttk.Label(master=manual_page,text="CURR. HEADING: ",font='DejaVuSans 20',padding='5 5',foreground=WHITE,background=BACKGND)
    current_heading_lbl.grid(column=0,row=2,sticky='we')

    connection_label = ttk.Label(master=manual_page,text="Connected: ",font='DejaVuSans 20',padding='5 5',foreground=WHITE,background=BACKGND)
    connection_label.grid(column=0,row=3,rowspan=2,sticky='we')

    # selection frame can be reused from rover selection  


    def show_top_lvl(page:tk.Toplevel):
        page.lift()