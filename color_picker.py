import tkinter as tk
from tkinter import ttk
from tkinter.colorchooser import askcolor
import serial
import time

arduino = serial.Serial(port='COM9', baudrate=9600)
time.sleep(5)

root = tk.Tk()
root.title('Tkinter Color Chooser')
root.geometry('300x150')


def change_color():
    colors = askcolor(title="Tkinter Color Chooser")
    print(colors[1])
    arduino.write(colors[1].encode())
    root.configure(bg=colors[1])


ttk.Button(
    root,
    text='Select a Color',
    command=change_color).pack(expand=True)


root.mainloop()
