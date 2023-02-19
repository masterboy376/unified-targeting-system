# importing necessary libraries
import tkinter
import tkinter.messagebox
import customtkinter

# configuring themes
customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("dark-blue")

# using OOPs
class App(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        # configure window
        self.w=1000
        self.h=600
        self.title("Unified Targeting System(UTS)")
        self.geometry(f"{self.w}x{self.h}")
        self.minsize(self.w, self.h)
        self.maxsize(self.w, self.h)

        # create sidebar frame with widgets
        self.sidebar_frame = customtkinter.CTkFrame(self , corner_radius=0)
        self.sidebar_frame.pack(side="left" , fill="y")
        # widget for adding enemy
        self.add_enemy_label = customtkinter.CTkLabel(self.sidebar_frame, text="Add Enemy", font=customtkinter.CTkFont(size=14, weight="bold"))
        self.add_enemy_label.pack(padx=20, pady=(10, 0))
        self.x_enemy_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="X")
        self.x_enemy_entry.pack(padx=20, pady=(10, 0))
        self.y_enemy_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="Y")
        self.y_enemy_entry.pack(padx=20, pady=(10, 0))
        self.z_enemy_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="Z")
        self.z_enemy_entry.pack(padx=20, pady=(10, 0))
        self.range_enemy_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="Range")
        self.range_enemy_entry.pack(padx=20, pady=(10, 0))
        self.isAvailable_enemy_checkbox = customtkinter.CTkCheckBox(master=self.sidebar_frame, text="is available")
        self.isAvailable_enemy_checkbox.pack(pady=(10, 0), padx=20)
        self.add_enemy_button = customtkinter.CTkButton(self.sidebar_frame, text="Add Enemy")
        self.add_enemy_button.pack(padx=20, pady=10)
        # widget for adding enemy
        self.add_comrad_label = customtkinter.CTkLabel(self.sidebar_frame, text="Add Comrad", font=customtkinter.CTkFont(size=14, weight="bold"))
        self.add_comrad_label.pack(padx=20, pady=(10, 0))
        self.x_comrad_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="X")
        self.x_comrad_entry.pack(padx=20, pady=(10, 0))
        self.y_comrad_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="Y")
        self.y_comrad_entry.pack(padx=20, pady=(10, 0))
        self.z_comrad_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="Z")
        self.z_comrad_entry.pack(padx=20, pady=(10, 0))
        self.range_comrad_entry = customtkinter.CTkEntry(self.sidebar_frame, placeholder_text="Range")
        self.range_comrad_entry.pack(padx=20, pady=(10, 0))
        self.isAvailable_comrad_checkbox = customtkinter.CTkCheckBox(master=self.sidebar_frame, text="is available")
        self.isAvailable_comrad_checkbox.pack(pady=(10, 0), padx=20)
        self.role_comrad_optionmenu = customtkinter.CTkOptionMenu(self.sidebar_frame, dynamic_resizing=False,
                                                        values=["attack", "surveillance", "defence"])
        self.role_comrad_optionmenu.pack(padx=20, pady=(10, 0))
        self.add_comrad_button = customtkinter.CTkButton(self.sidebar_frame, text="Add Comrad")
        self.add_comrad_button.pack(padx=20, pady=10)

        # # create main frame
        # self.main_frame = customtkinter.CTkFrame(self , corner_radius=0)
        # self.main_frame.pack(side="right" , fill="y")

        # create textbox
        self.result_textbox = customtkinter.CTkTextbox(self, height=self.h-50)
        self.result_textbox.pack(padx=10, pady=10, fill="x")

        # create botttom status bar
        self.statusbar = customtkinter.CTkFrame(self)
        self.statusbar.pack(side="bottom", fill="x")
        self.status = customtkinter.CTkLabel(self.statusbar, text="Running...")
        self.status.grid(row=0, column=0)


# main executions
if __name__ == "__main__":
    app = App()
    app.mainloop()