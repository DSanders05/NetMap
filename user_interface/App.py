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
    root.resizable((False,False))

    main_frame = ttk.Frame(master=root,padding="3 3 10 10")
    main_frame.grid()

    list_frame = ttk.Frame(master=root,padding = "3 3 5 5",height=500,width=250)



        #### Style ####

    def import_rover_list():
        pass

    def run_app(self):
        self.mainloop()

    def change_frame(self):
        pass