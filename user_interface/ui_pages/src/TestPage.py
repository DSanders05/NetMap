import tkinter as tk
from tkinter import ttk

#### Frame Styles ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class TestPage(ttk.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent)
        # Store the controller for frame switching
        self.controller = controller

        # Create the banner label
        banner_label = ttk.Label(
            self, text="AUTO MODE", style="Banner.TLabel", anchor="center"
        )
        banner_label.grid(row=0, column=0, columnspan=2, sticky="ew", pady=(0, 10))

        # Define a custom style for the banner label
        style = ttk.Style(self)
        style.configure("Banner.TLabel", font=("Deja Vu Sans", 25, "bold"), background=BACKGND,foreground=WHITE)

        # Configure column weights
        self.columnconfigure(0, weight=1)
        self.columnconfigure(1, weight=1)
        self.rowconfigure(1, weight=1)

        # Create the left frame for rover objects
        left_frame = ttk.Frame(self, padding="10", relief="solid")
        left_frame.grid(row=1, column=0, sticky="nsew", padx=(0, 10))

        # Add a sample listbox to the left frame
        rover_listbox = tk.Listbox(left_frame)
        rover_listbox.pack(fill="both", expand=True)

        # Add some dummy rover objects
        for i in range(10):
            rover_listbox.insert(tk.END, f"Rover {i + 1}")

        # Create the right frame for buttons
        right_frame = ttk.Frame(self, padding="10", relief="solid")
        right_frame.grid(row=1, column=1, sticky="nsew", padx=(10, 0))

        # Add buttons to the right frame
        for i in range(3):
            button_text = f"Option {i + 1}"
            button = ttk.Button(
                master=right_frame,
                text=button_text,
                command=lambda opt=i: self.handle_option(opt),
            )
            button.pack(pady=10, expand=True)

    def handle_option(self, option):
        if option == 0:  # Option 1 selected
            self.controller.show_frame("ManualPage")