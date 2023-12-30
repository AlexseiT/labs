# -*- coding: utf-8 -*-
import random
from random import randint
from PIL import Image, ImageDraw
 
x1 = 0
y1 = 0
x2 = 0
y2 = 0
x3 = 0
y3 = 0

color1 = 0
color2 = 0

#color3
R = 0
G = 0
B = 0

width = 0
def random_color():
    return random.randint(0,0x1000000)

def RandCoordinates():
    global x1
    global x2
    global x3
    global y1
    global y2
    global y3
    global width
    x1 = randint(0, 256)
    x2 = randint(0, 256)
    x3 = randint(0, 256)
    y1 = randint(0, 256)
    y2 = randint(0, 256)
    y3 = randint(0, 256)
    width = randint(2, 5)

def RandColor():
    global R
    global G
    global B
    global color1
    global color2
    R = randint(0, 255)
    G = randint(0, 255)
    B = randint(0, 255)
    color1 = '{:06x}'.format(random_color())
    color2 = '{:06x}'.format(random_color())
#?????
def DistanceCheck():
    if (abs(x1 - x2) < 25): return False
    elif (abs(x1 - x3) < 25): return False
    elif (abs(x2 - x3) < 25): return False
    return True

c = input('1 - Triangle, 2 - Ellipse, 3 - Rectangle:  ')
n = input('Quantity:  ')

#Triangle Generate
if (c == '1'):
    for i in range(int(n)):
       # print(i)
        RandCoordinates()
        RandColor()

        #while(DistanceCheck() == False):
          #  print(i)
          #  RandCoordinates()

        rand = randint(0, 1)
        if (rand == 0): im = Image.new('RGB', (256, 256), (R, G, B))
        if (rand == 1): im = Image.new('RGB', (256, 256), (255, 255, 255))

        draw = ImageDraw.Draw(im)

        rand = randint(0, 2)
        if (rand == 0): draw.polygon([(x1,y1), (x2, y2), (x3,y3)], fill = ('#'+ color1), outline=('#'+ color2), width=width)
        if (rand == 1): draw.polygon([(x1,y1), (x2, y2), (x3,y3)], fill = ('#'+ color1), width=width)
        if (rand == 2): draw.polygon([(x1,y1), (x2, y2), (x3,y3)], outline=('#'+ color2), width=width)
        name = 'triangle'+ str(i) +'.png'
        im.save(name)

#Ellipse Generate
if (c == '2'):
    for i in range(int(n)):
        RandCoordinates()
        RandColor()
        #print(str(i) + ' => ' + str(x1) + ' ' + str(y1) + ' ' + str(x2) + ' ' + str(y2) + ' ')
        rand = randint(0, 1)
        if (rand == 0): im = Image.new('RGB', (256, 256), (R, G, B))
        if (rand == 1): im = Image.new('RGB', (256, 256), (255, 255, 255))

        draw = ImageDraw.Draw(im)

        rand = randint(0, 2)
        if (rand == 0): draw.ellipse((x1, y1, x2, y2), fill = ('#'+ color1), outline=('#'+ color2), width=width)
        if (rand == 1): draw.ellipse((x1, y1, x2, y2), fill = ('#'+ color1), width=width)
        if (rand == 2): draw.ellipse((x1, y1, x2, y2), outline=('#'+ color2), width=width)

        name = 'ellipse'+ str(i) +'.png'

        im.save(name)

#Rectangle Generate
if (c == '3'):
    for i in range(int(n)):
        RandCoordinates()
        RandColor()
       # print(str(i) + ' => ' + str(x1) + ' ' + str(y1) + ' ' + str(x2) + ' ' + str(y2) + ' ')
        rand = randint(0, 1)
        if (rand == 0): im = Image.new('RGB', (256, 256), (R, G, B))
        if (rand == 1): im = Image.new('RGB', (256, 256), (255, 255, 255))

        draw = ImageDraw.Draw(im)

        rand = randint(0, 2)
        if (rand == 0): draw.rectangle((x1, y1, x2, y2), fill = ('#'+ color1), outline=('#'+ color2), width=width)
        if (rand == 1): draw.rectangle((x1, y1, x2, y2), fill = ('#'+ color1), width=width)
        if (rand == 2): draw.rectangle((x1, y1, x2, y2), outline=('#'+ color2), width=width)

        name = 'rectangle'+ str(i) +'.png'

        im.save(name)
