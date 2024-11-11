import tkinter as tk
from tkinter import ttk

#### Frame Styles ####
BACKGND = '#' # RGB(19 33 66 1) Background needs to be Ole Miss blue
HILIGHT = '#' # RGB(0 111 186 1)Hilight should be red/white?
WHITE = '#' # RGB(255 255 255 1)

class App(tk.Tk):
    # Initialization Method for App class
    def __init__(self, screenName = None, baseName = None, className = "Tk", useTk = True, sync = False, use = None):
        super().__init__(screenName, baseName, className, useTk, sync, use)
        self.title("NetMap Visualization Tool")
        self.geometry("800x480")
        self.resizable(False,False)

        #### Frame ####

        #### Style ####

    def run_app(self):
        self.mainloop()

    def change_frame(self):
        # Define function to change between frames
        # - Initialization Page
        # - Scan Page
        # - ...
        pass



if __name__ == "__main__":
    net_map_app = App()
    net_map_app.run_app()
