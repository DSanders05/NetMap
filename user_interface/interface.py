import sys
import os
import ttkbootstrap as ttk
from ttkbootstrap.constants import *

sys.path.append("../build/app_manager/python_bindings")

import manager_bindings

manager = manager_bindings.Manager()

class NetMapApp(ttk.Window):
    def __init__(self):
        super().__init__(title="NetMap Monitoring Tool", size=(800, 400), themename="superhero")

        self.frames = {}

        # Create page frames
        for PageClass in (InitPage, AutoModePage):
            page = PageClass(self)
            self.frames[PageClass.__name__] = page
            page.place(relwidth=1, relheight=1)

        # Show the initialization page
        self.show_frame("InitPage")

    def show_frame(self, page_name):
        frame = self.frames[page_name]
        frame.tkraise()
        

class InitPage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Banner
        banner = ttk.Label(self, text="NetMap", font=("Arial", 40, "bold"), anchor="center")
        banner.pack(pady=(100, 10))

        # # Image frame 
        # image_frame = ttk.Frame(self)
        # image_frame.pack(pady=20)
        # image_label = ttk.Label(image_frame, text="[Image Placeholder]", anchor="center", relief="solid")
        # image_label.pack(padx=10, pady=10, ipadx=100, ipady=50)

        # Start button
        start_button = ttk.Button(self, text="Start Auto Scan", command=lambda: self.start_scan(parent))
        start_button.pack(pady=(60,0))

    def start_scan(self,parent):
        parent.show_frame("AutoModePage")
        # try:
        #     manager.start_auto_mode() # Call C++ function to start the auto mode scan
        # except Exception as e:
        #     print(f"Error in start_auto_mode function: {e}")


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

        columns = ("rover", "rover_id", "location")
        self.rovers_table = ttk.Treeview(rovers_frame, columns=columns, show="headings", height=10)
        for col in columns:
            self.rovers_table.heading(col, text=col.capitalize())
        self.rovers_table.pack(fill=BOTH, expand=True, padx=10, pady=10)

        # Example data
        sample_data = [
            ("Rover 1", "01", "100"),
            ("Rover 2", "02", "270"),
        ]
        
        for entry in sample_data:
            self.rovers_table.insert("", END, values=entry)

def start_ui():
    app = NetMapApp()
    app.mainloop()

if __name__ == "__main__":
    start_ui()
