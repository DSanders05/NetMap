import ttkbootstrap as ttk
from ttkbootstrap.constants import *

class NetMapApp(ttk.Window):
    def __init__(self):
        super().__init__(title="NetMap UI", size=(800, 400), themename="superhero")

        self.frames = {}
        self.selected_rover = ttk.StringVar(value="None")
        self.connection_status = ttk.StringVar(value="Not Connected")
        self.target_value = ttk.StringVar()

        # Create pages
        for PageClass in (InitPage, AutoModePage):
            page = PageClass(self)
            self.frames[PageClass.__name__] = page
            page.place(relwidth=1, relheight=1)

        # Show the initialization page
        self.show_frame("InitPage")

    def show_frame(self, page_name):
        frame = self.frames[page_name]
        frame.tkraise()

    def submit_target(self):
        print(f"Target submitted: {self.target_value.get()}")


class InitPage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Banner
        banner = ttk.Label(self, text="NetMap", font=("Arial", 24, "bold"), anchor="center")
        banner.pack(pady=20)

        # Placeholder for image
        image_frame = ttk.Frame(self)
        image_frame.pack(pady=20)
        image_label = ttk.Label(image_frame, text="[Image Placeholder]", anchor="center", relief="solid")
        image_label.pack(padx=10, pady=10, ipadx=100, ipady=50)

        # Start button
        start_button = ttk.Button(self, text="Start", command=lambda: parent.show_frame("AutoModePage"))
        start_button.pack(pady=20)


class AutoModePage(ttk.Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Banner
        banner = ttk.Label(self, text="AUTO MODE", font=("Arial", 24, "bold"), anchor="center")
        banner.pack(pady=20)

        # Columns layout
        content_frame = ttk.Frame(self)
        content_frame.pack(expand=True, fill=BOTH, padx=20, pady=20)

        # Left column (List of Rovers)
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

    def dummy_action(self):
        print("Option button clicked.")


if __name__ == "__main__":
    app = NetMapApp()
    app.mainloop()
