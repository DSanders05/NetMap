from concurrent.futures import thread
import sys
import os
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
import threading
sys.path.append("/home/ech0/NetMap/build/bindings")

# Imports pybind bindings
import manager_bindings

# Creates a Manager instance for C++ functions
manager = manager_bindings.Manager(["192.168.2.22"],8080)

class NetMapApp(ttk.Window):
    def __init__(self):
        super().__init__(title="NetMap Monitoring Tool", size=(800, 400), themename="superhero")

        # Vars for page frame list, motor thread, and thread running flag (bool)
        self.frames = {}
        self.motor_thread = None
        self.motor_running = threading.Event()

        # Create page frames
        for PageClass in (InitPage, AutoModePage, ManualPage):
            page = PageClass(self)
            self.frames[PageClass.__name__] = page
            print("PageClass.__name__ : ", PageClass.__name__)
            page.place(relwidth=1, relheight=1)

        # Show the initialization page
        print("Showing first page with show_frame")
        self.show_frame("InitPage")

    # Swaps page frames
    def show_frame(self, page_name):
        print("In show_frame")
        frame = self.frames[page_name]
        frame.tkraise()
        print(f"Called frame.tkraise({page_name}) in show_frame",frame)

    # Starts thread to run the motor in to keep from blocking interface
    def start_motor(self):
        if not self.motor_thread or not self.motor_thread.is_alive():
            self.motor_running.set()
            self.motor_thread = threading.Thread(target=self.run_motor)
            self.motor_thread.start()

    # Start Manager objects auto_mode
    def run_motor(self):
        try:
            manager.start_auto_mode()
        except Exception as e:
            print(f"Error starting auto mode: {e}")

    # Exits the Managers auto_mode loop
    def stop_motor(self):
        """Stop stepper motor"""
        if self.motor_thread and self.motor_thread.is_alive():
            self.motor_running.clear()
            manager.stop_auto_mode()
            self.motor_thread.join()

class InitPage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Banner
        banner = ttk.Label(self, text="NetMap", font=("Arial", 40, "bold"), anchor="center")
        banner.pack(pady=(100, 10))

        # Start button for AUTO Mode
        start_button = ttk.Button(self, text="Start Auto Scan", command=lambda: self.start_scan(parent))
        start_button.pack(pady=(60,0))

    def start_scan(self,parent):
        print("About to show_frame AutoModePage")
        parent.show_frame("AutoModePage")
        print("About to start_motor")
        parent.start_motor()


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
        option_frame = ttk.Frame(content_frame)
        option_frame.pack(side=RIGHT,expand=True,fill=BOTH)

        connect_button = ttk.Button(option_frame, text="Connect", command=lambda: (parent.show_frame("ManualPage"),parent.stop_motor()))
        connect_button.pack(fill=X,pady=100)


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

        button_frame = ttk.Frame(content_frame)
        button_frame.pack(side=RIGHT,fill=BOTH,expand=True,padx=10)

        return_button = ttk.Button(button_frame,text="Return to Auto Mode",command=lambda:{parent.show_frame("AutoModePage")})
        return_button.pack(anchor=CENTER,pady=100)

def start_ui():
    app = NetMapApp()
    app.mainloop()

if __name__ == "__main__":
    start_ui()
