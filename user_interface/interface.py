from concurrent.futures import thread
import sys
import os
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
import threading
sys.path.append("/home/ncpa/NetMap/build/bindings")

# Imports pybind bindings
from manager_bindings import Manager, is_queue_empty, get_from_queue

# Creates a Manager instance for C++ functions
manager = Manager(["127.0.0.1"],8080)

frames = {}
rover_values = {}

class NetMapApp(ttk.Window):
    def __init__(self):
        super().__init__(title="NetMap Monitoring Tool", size=(800, 400), themename="superhero")

        # Vars for page frame list, motor thread, and thread running flag (bool)
        # self.frames = {}
        self.frame
        # self.rover_values

        # Create page frames
        for PageClass in (InitPage, AutoModePage, ManualPage):
            page = PageClass(self)
            # self.frames[PageClass.__name__] = page
            frames[PageClass.__name__] = page
            page.place(relwidth=1, relheight=1)

        # Start button for AUTO Mode
        start_button = ttk.Button(frames["InitPage"], text="Start Auto Scan", command=lambda: self.start_scan())
        start_button.pack(pady=(60,0))

        connect_button = ttk.Button(frames["AutoModePage"].option_frame, text="Connect", command=lambda: (self.stop_motor(), frames["AutoModePage"].target_rover(), frames["ManualPage"].update_labels(), self.show_frame("ManualPage"), manager.turn_to_target(frames["ManualPage"].heading)))
        connect_button.pack(fill=X,pady=100)

        return_button = ttk.Button(frames["ManualPage"].button_frame,text="Return to Auto Mode",command=lambda:{self.show_frame("AutoModePage"),self.start_scan()})
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
            threading.Thread(target=manager.start_thread,daemon=True).start()
            # manager.start_thread()
        except Exception as e:
            print(f"Error starting motor control loop: {e}")

    # Stop the auto_mode thread
    def stop_motor(self):
        manager.stop_auto_mode()

    def on_close(self):
        self.stop_motor()
        self.destroy()

class InitPage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Banner
        banner = ttk.Label(self, text="NetMap", font=("Arial", 40, "bold"), anchor="center")
        banner.pack(pady=(100, 10))

class AutoModePage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        self.parent = parent

        # Auto Scan Banner
        banner = ttk.Label(self, text="AUTO SCAN", font=("Arial", 30, "bold"), anchor="center")
        banner.pack()

        # Columns layout
        content_frame = ttk.Frame(self)
        content_frame.pack()

        # Connect button Frame
        self.option_frame = ttk.Frame(content_frame)
        self.option_frame.pack()

        # Left column List of Rovers
        rovers_frame = ttk.Labelframe(content_frame, text="Rovers")
        rovers_frame.pack()

        blank_frame = ttk.Frame(content_frame)
        blank_frame.pack()
        blank_frame2 = ttk.Frame(content_frame)
        blank_frame2.pack()


        columns = ("Rover", "Rover Ip", "Location")
        self.rovers_table = ttk.Treeview(rovers_frame, columns=columns, show="headings", height=10)
        for col in columns:
            self.rovers_table.heading(col, text=col.capitalize())
        self.rovers_table.pack()


        self.count = 0
        self.process_queue()

    def process_queue(self):
        while not is_queue_empty():
            rover_ip, heading = get_from_queue()
            if rover_ip:
               self.add_rover(self.count,rover_ip,heading)
               self.count += 1
        self.after(200,self.process_queue)

    def add_rover(self,rover_num,rover_ip,heading):
        self.rovers_table.insert("","end",values=(f"Rover {rover_num}",rover_ip,heading))

    def target_rover(self):
        selected_rover = self.rovers_table.focus()
        if selected_rover:
            # self.parent.rover_values = self.rovers_table.item(selected_rover,"values")
            rover_values = self.rovers_table.item(selected_rover,"values")
            return rover_values
        return None



class ManualPage(ttk.Frame):
    def __init__(self,parent):
        super().__init__(parent)

        self.parent = parent
        self.rover = 0
        self.ip = ""
        self.heading = 0
        # selected_values = self.parent.rover_values
        selected_values = rover_values
        # rover, ip, heading = ("","","")
        if selected_values:
            self.rover, self.ip, self.heading = selected_values
        
        # Manual Mode Banner
        banner = ttk.Label(self, text="Manual Mode", font=("Arial", 30, "bold"), anchor="center")
        banner.pack(pady=20)

        content_frame = ttk.Frame(self)
        content_frame.pack(expand=True,fill=BOTH,padx=20,pady=20)

        self.connection_frame = ttk.Labelframe(content_frame,text=f"Rover {self.rover}")
        self.connection_frame.pack(side=LEFT,fill=BOTH,expand=True,padx=10)

        ip_label = ttk.Label(self.connection_frame,anchor=W,text="Rover IP:")
        ip_label.grid(row=1,column=1,pady=(50,0),padx=(30,0))

        self.ip_value = ttk.Label(self.connection_frame,text= f"{self.ip}")
        self.ip_value.grid(row=1,column=2,pady=(50,0),padx=(30,0))

        self.loc_label = ttk.Label(self.connection_frame,anchor=W,text="Angular Location")
        self.loc_label.grid(row=2,column=1,pady=(50,0),padx=(50,0))

        self.loc_value = ttk.Label(self.connection_frame,text=f"{self.heading}")
        self.loc_value.grid(row=2,column=2,pady=(50,0),padx=(50,0))

        self.button_frame = ttk.Frame(content_frame)
        self.button_frame.pack(side=RIGHT,fill=BOTH,expand=True,padx=10)

    def update_labels(self):
        selected_values = rover_values
        self.rover = 0
        self.ip = ""
        self.heading=0
        if selected_values:
            self.rover, self.ip, self.heading = selected_values
        self.connection_frame.config(text=f"Rover {self.rover}")
        self.ip_value.config(text = f"{self.ip}")
        self.loc_value.config(text = f"{self.heading}")


def start_ui():
    app = NetMapApp()
    app.protocol("WM_DELETE_WINDOW",app.on_close)
    app.mainloop()

if __name__ == "__main__":
    start_ui()
