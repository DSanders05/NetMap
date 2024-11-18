import tkinter as tk
from tkinter import ttk

#### Frame Styles ####
BACKGND = '#132142' # RGB(19 33 66 1)           Background needs to be Ole Miss blue
HILIGHT = '#006fba' # RGB(0 111 186 1)          Hilight should be red/white?
WHITE   = '#ffffff' # RGB(255 255 255 1)
RED     = '#cc2128' # RGB(204, 33, 40, 1)

class NumPad(ttk.Frame):
    def __init__(self,parent,controller):
        super().__init__(master=parent)
        self.controller = controller
        
        for i in range(0,3):
            self.grid_columnconfigure(0,weight=1)

        for i in range(0,6):
            self.grid_rowconfigure(0,weight=1)

        self.text = tk.StringVar(master=self)

        self.style = ttk.Style()


        self.style.configure(style="NumPadBtn.TButton",font=("Deja Vu Sans",10))
        self.num0 = ttk.Button(master=self,style="NumPadBtn.TButton",text="0",command=self.on_button_press)
        self.num0.grid(row=4,column=0,sticky="nswe",padx=(10,0))

        self.num1 = ttk.Button(master=self,style="NumPadBtn.TButton",text="1",command=self.on_button_press)
        self.num1.grid(row=3,column=0,sticky="nswe",padx=(10,0))

        self.num2 = ttk.Button(master=self,style="NumPadBtn.TButton",text="2",command=self.on_button_press)
        self.num2.grid(row=3,column=1,sticky="nswe")

        self.num3 = ttk.Button(master=self,style="NumPadBtn.TButton",text="3",command=self.on_button_press)
        self.num3.grid(row=3,column=2,sticky="nswe",padx=(0,10))

        self.num4 = ttk.Button(master=self,style="NumPadBtn.TButton",text="4",command=self.on_button_press)
        self.num4.grid(row=2,column=0,sticky="nswe",padx=(10,0))

        self.num5 = ttk.Button(master=self,style="NumPadBtn.TButton",text="5",command=self.on_button_press)
        self.num5.grid(row=2,column=1,sticky="nswe")

        self.num6 = ttk.Button(master=self,style="NumPadBtn.TButton",text="6",command=self.on_button_press)
        self.num6.grid(row=2,column=2,sticky="nswe",padx=(0,10))

        self.num7 = ttk.Button(master=self,style="NumPadBtn.TButton",text="7",command=self.on_button_press)
        self.num7.grid(row=1,column=0,sticky="nswe",padx=(10,0))

        self.num8 = ttk.Button(master=self,style="NumPadBtn.TButton",text="8",command=self.on_button_press)
        self.num8.grid(row=1,column=1,sticky="nswe")

        self.num9 = ttk.Button(master=self,style="NumPadBtn.TButton",text="9",command=self.on_button_press)
        self.num9.grid(row=1,column=2,sticky="nswe",padx=(0,10))

        self.enter_btn = ttk.Button(master=self,style="NumPadBtn.TButton",text="ENTER",command=self.submit_entry)
        self.enter_btn.grid(row=4,rowspan=2,column=1,columnspan=2,sticky="nswe",padx=(0,10),pady=(0,10))

        self.clear_btn = ttk.Button(master=self,style="NumPadBtn.TButton",text="CLR",command=self.clear_entry)
        self.clear_btn.grid(row=5,column=0,sticky="nswe",padx=(10,0),pady=(0,10))
    
    def on_button_press(self,value):
        current_text = self.text.get()
        self.text.set(current_text + value)

    def submit_entry(self):
        print("Entered:",self.text.get())

    def clear_entry():
        pass