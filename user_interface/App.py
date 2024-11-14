from enum import auto
import tkinter as tk
from tkinter import ttk


#### Frame Styles ####
BACKGND = '#132142' # RGB(19 33 66 1) Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class App():
    root = tk.Tk()
    root.title("NetMap Tool")
    root.geometry("800x400")
    root.resizable(width=False,height=False)

    #### FRAMES ####
    init_frame = ttk.Frame(master=root,padding="3 3 5 5",height=800,width=400)

    rover_selection_frame = ttk.Frame(master=root, padding='3 3 5 5',height=800,width=400)

    auto_frame = ttk.Frame(master=root,padding = "3 3 5 5",height=800,width=400)

    manual_frame = ttk.Frame(master=root, padding= "3 3 5 5", height=800, width=400)

    #### Styles ####
    init_frame_style = ttk.Style()
    rover_selec_style = ttk.Style()
    auto_frame_style = ttk.Style()
    manual_frame_style = ttk.Style()

    #### INIT FRAME MEMBERS ####
    init_frame_label = ttk.Label(master=init_frame)                               # This label holds the text NetMap
    init_frame_label.grid(column=1,row=1)

    ncpa_logo = ttk.Label(master=init_frame)                                       # This label holds the NCPA logo
    ncpa_logo.grid(column=1,row=2)

    #### ROVER SELECT FRAME MEMBERS ####
    frame_label = ttk.Label(master=rover_selection_frame,text="Enter number of rovers deployed: ")    # Request number of rovers to list
    frame_label.grid(column=1,rowspan=2)

    entry_frame = ttk.Frame(master=rover_selection_frame)                                                               # Send input number of rovers to auto page
    entry_frame.grid(column=1, rowspan=6)

    num_pad = ttk.Frame(master=rover_selection_frame)

    num0 = ttk.Button(master=num_pad, text="0")
    num1 = ttk.Button(master=num_pad, text="1")
    num2 = ttk.Button(master=num_pad, text="2")
    num3 = ttk.Button(master=num_pad, text="3")
    num4 = ttk.Button(master=num_pad, text="4")
    num5 = ttk.Button(master=num_pad, text="5")
    num6 = ttk.Button(master=num_pad, text="6")
    num7 = ttk.Button(master=num_pad, text="7")
    num8 = ttk.Button(master=num_pad, text="8")
    num9 = ttk.Button(master=num_pad, text="9")
    enter_button = ttk.Button(master=entry_frame, text="ENTER")
    clear_button = ttk.Button(master=entry_frame, text="CLEAR")

    #### AUTO FRAME MEMBERS ####
    mode_label = ttk.Label(master=auto_frame)                                   # This label should display AUTO mode
    list_frame = ttk.Frame(master=auto_frame)                                     # This frame will hold the listing of each rover
    menu_frame = ttk.Frame(master=auto_frame)                                # This frame will hold the options for stopping auto scan and switching to manual


    #### MANUAL FRAME MEMBERS ####
    mode_label = ttk.Label(master=manual_frame)                              # Displays MANUAL mode
    target_label = ttk.Label(master=manual_frame)                              # Displays target heading to move to
    current_heading_lbl = ttk.Label(master=manual_frame)                 # Displays the current heading (changes throughout movement)
    connection_label = ttk.Label(master=manual_frame)                     # Displays if connected to rover at target location or not
    # selection frame can be reused from rover selection  