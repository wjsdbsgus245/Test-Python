import tkinter
from tkinter import messagebox

maxWidth = 640
maxHight = 400

window = tkinter.Tk()


window.title("Python Program")
window.geometry(str(maxWidth) + "x" + str(maxHight) + "+100+100")
window.resizable(False, False)

frame = tkinter.Frame(window)

window.mainloop() 