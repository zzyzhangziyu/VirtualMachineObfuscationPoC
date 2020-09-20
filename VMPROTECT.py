#!/usr/bin/python3

import Editor.main as editor

from tkinter import *
from tkinter import messagebox
from tkinter import filedialog

print("""\
 _   ____  _______________ _____ _____ _____ _____ _____ 
| | | |  \/  || ___ \ ___ \  _  |_   _|  ___/  __ \_   _|
| | | | .  . || |_/ / |_/ / | | | | | | |__ | /  \/ | |  
| | | | |\/| ||  __/|    /| | | | | | |  __|| |     | |  
\ \_/ / |  | || |   | |\ \\ \_/ / | | | |___| \__/\ | |  
 \___/\_|  |_/\_|   \_| \_|\___/  \_/ \____/ \____/ \_/  
""")
print("ver 0.1.200920.1741-dev")

# Creating TK Container
root = Tk()
# Passing Root to Editor Class
editor.Editor(root)
# Root Window Looping
root.mainloop()