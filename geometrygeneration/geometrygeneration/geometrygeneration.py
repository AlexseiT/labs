# -*- coding: utf-8 -*-
from tkinter import Tk, Canvas
import random
from random import randint
import PIL.Image
from PIL import ImageGrab

window = Tk()
window.title('canvas')
canvas = Canvas(window,width=256,height=256,bg="white", cursor="pencil")
canvas.pack()
canvas.postscript(file="my_dram.eps", colormode="color")
x1 = 0
y1 = 0
x2 = 0
y2 = 0
x3 = 0
y3 = 0
color1 = 0
color2 = 0

def random_color():
    return random.randint(0,0x1000000)

def RandRectangle():
    global x1
    global x2
    global x3
    global y1
    global y2
    global y3
    global color1
    global color2
    x1 = randint(0, 256)
    x2 = randint(0, 256)
    x3 = randint(0, 256)
    y1 = randint(0, 256)
    y2 = randint(0, 256)
    y3 = randint(0, 256)
    color1 = '{:06x}'.format(random_color())
    color2 = '{:06x}'.format(random_color())

def save_widget_as_image(widget, file_name):
    ImageGrab.grab(bbox=(
        widget.winfo_rootx(),
        widget.winfo_rooty(),
        widget.winfo_rootx() + widget.winfo_width(),
        widget.winfo_rooty() + widget.winfo_height()
    )).save(file_name)

RandRectangle()
points = [x1, y1, x2, y2, x3, y3]

rand = randint(0, 2)

if (rand == 0): canvas.create_polygon(points, outline=('#'+ color1), fill= ('#'+ color2), width=2)

if (rand == 1): canvas.create_polygon(points, fill= ('#'+ color2), width=2)

if (rand == 2): canvas.create_polygon(points, outline=('#'+ color1), fill= ('white'), width=2)

canvas.update()

#fp = open("my_dram.eps","rb")

#img = PIL.Image.open(fp)

#img.save("my_dram.png", "png")

window.mainloop()

