from concurrent.futures import thread
import sys
import os
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
import threading
sys.path.append("/home/ech024/NetMap/build/bindings")

# Imports pybind bindings
import manager_bindings

# Creates a Manager instance for C++ functions
manager = manager_bindings.Manager(["192.168.3.23","192.168.3.33"],8080)

frames = {}

class NetMapApp(ttk.Window):
    def __init__(self):
        super().__init__(title="NetMap Monitoring Tool", size=(800, 400), themename="superhero")

        # Vars for page frame list, motor thread, and thread running flag (bool)
        # self.frames = {}
        self.frame
        self.motor_thread = None
        self.motor_running = threading.Event()

        # Create page frames
        for PageClass in (InitPage, AutoModePage, ManualPage):
            page = PageClass(self)
            # self.frames[PageClass.__name__] = page
            frames[PageClass.__name__] = page
            page.place(relwidth=1, relheight=1)

        # Start button for AUTO Mode
        start_button = ttk.Button(frames["InitPage"], text="Start Auto Scan", command=lambda: self.start_scan())
        start_button.pack(pady=(60,0))

        connect_button = ttk.Button(frames["AutoModePage"].option_frame, text="Connect", command=lambda: (self.show_frame("ManualPage"),self.stop_motor()))
        connect_button.pack(fill=X,pady=100)

        return_button = ttk.Button(frames["ManualPage"].button_frame,text="Return to Auto Mode",command=lambda:{self.show_frame("AutoModePage")})
        return_button.pack(anchor=CENTER,pady=100)

        # Show the initialization page
        self.show_frame("InitPage")

    # Swaps page frames
    def show_frame(self, page_name):
        # frame = self.frames[page_name]
        self.frame = frames[page_name]
        self.frame.tkraise()

    def start_scan(self):
        self.show_frame("AutoModePage")
        self.start_motor()

    # Starts thread to run the motor in to keep from blocking interface
    def start_motor(self):
        # Starting auto mode in separate thread
        try:
            print("Starting motor in separate thread.")
            manager.start_thread()
            print("Motor thread started.")
        except Exception as e:
            print(f"Error starting motor control loop: {e}")

    # Start Manager objects auto_mode
    # def run_motor(self):
    #     try:
    #         manager.start_auto_mode()
    #     except Exception as e:
    #         print(f"Error starting auto mode: {e}")

    # Stop the auto_mode thread
    def stop_motor(self):
        manager.stop_auto_mode()

class InitPage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Banner
        banner = ttk.Label(self, text="NetMap", font=("Arial", 40, "bold"), anchor="center")
        banner.pack(pady=(100, 10))

class AutoModePage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Auto Scan Banner
        banner = ttk.Label(self, text="AUTO SCAN", font=("Arial", 30, "bold"), anchor="center")
        banner.pack(pady=20)

        # Columns layout
        content_frame = ttk.Frame(self)
        content_frame.pack(expand=True, fill=BOTH, padx=20, pady=20)

        # Left column List of Rovers
        rovers_frame = ttk.Labelframe(content_frame, text="Rovers")
        rovers_frame.pack(side=LEFT, fill=BOTH, expand=True, padx=10)

        columns = ("Rover", "Rover Ip", "Location")
        self.rovers_table = ttk.Treeview(rovers_frame, columns=columns, show="headings", height=10)
        for col in columns:
            self.rovers_table.heading(col, text=col.capitalize())
        self.rovers_table.pack(fill=BOTH, expand=True, padx=10, pady=10)

        # Connect button Frame
        self.option_frame = ttk.Frame(content_frame)
        self.option_frame.pack(side=RIGHT,expand=True,fill=BOTH)




class ManualPage(ttk.Frame):
    def __init__(self,parent):
        super().__init__(parent)
        
        # Manual Mode Banner
        banner = ttk.Label(self, text="Manual Mode", font=("Arial", 30, "bold"), anchor="center")
        banner.pack(pady=20)

        content_frame = ttk.Frame(self)
        content_frame.pack(expand=True,fill=BOTH,padx=20,pady=20)

        connection_frame = ttk.Labelframe(content_frame,text="Connection Status")
        connection_frame.pack(side=LEFT,fill=BOTH,expand=True,padx=10)

        ip_label = ttk.Label(connection_frame,anchor=W,text="Rover IP:")
        ip_label.grid(row=1,column=1,pady=(50,0),padx=(30,0))

        ip_value = ttk.Label(connection_frame,text= "Dummy Value")
        ip_value.grid(row=1,column=2,pady=(50,0),padx=(30,0))

        loc_label = ttk.Label(connection_frame,anchor=W,text="Angular Location")
        loc_label.grid(row=2,column=1,pady=(50,0),padx=(50,0))

        loc_value = ttk.Label(connection_frame,text="56")
        loc_value.grid(row=2,column=2,pady=(50,0),padx=(50,0))

        self.button_frame = ttk.Frame(content_frame)
        self.button_frame.pack(side=RIGHT,fill=BOTH,expand=True,padx=10)


def start_ui():
    app = NetMapApp()
    app.mainloop()

if __name__ == "__main__":
    start_ui()
