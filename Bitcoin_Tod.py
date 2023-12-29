from bs4 import BeautifulSoup
import lxml.html as html
import os
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import time
import tkinter as tk
from tkinter import *
import requests
from svglib.svglib import svg2rlg
from reportlab.graphics import renderPM

def cls():
   os.system('cls' if os.name == 'nt' else 'clear')

options = Options()
options.headless = True
options.add_experimental_option('excludeSwitches', ['enable-logging'])


driver = webdriver.Chrome(executable_path='.\chromedriver.exe',options = options)
url = 'https://coinmarketcap.com/'

loading = 0
def Loading(): 
    cls()
    global loading
    cls()
    t = '.'
    for i in range(loading):
        t += '.'
    print("Loading" + t)
    loading += 1

cls()

#Scroll

try:
    Loading()
    driver.get(url=url)
    driver.execute_script('window.scrollTo(0, 2600);')
    time.sleep(1)
    page = driver.page_source
    with open('\index.html', 'w', encoding='utf-8') as file:
        file.write(page)

        
finally:
    Loading()
    driver.close()
    driver.quit()
    cls()

Loading()
with open('\index.html', 'r', encoding='utf-8') as file:
    src = file.read()
soup = BeautifulSoup(src, 'lxml')

Loading()
cls()

# Parsing

nameCoin = []
priceCoin = []
capCoin = []
ImgCoin = []

AllnameCoin = soup.find_all('div', class_='sc-16r8icm-0 sc-1teo54s-0 dBKWCw')
for i in (AllnameCoin):
    if len(nameCoin) != 25:
        nameCoin.append(i.find('p', class_='sc-1eb5slv-0 iworPT').text)


AllpriceCoin = soup.find_all('div', class_='sc-131di3y-0 cLgOOr')
for i in (AllpriceCoin):
    if i.find('span') is not None:
        if len(priceCoin) != 25:
            priceCoin.append(i.find('span').text)


AllcapCoin = soup.find_all('p', class_='sc-1eb5slv-0 hykWbK')
for i in (AllcapCoin):
    if i.find('span', class_='sc-1ow4cwt-0 iosgXe') is not None:
        if len(capCoin) != 25:
            capCoin.append(i.find('span', class_='sc-1ow4cwt-0 iosgXe').text)


AllimgCoin = soup.find_all('a', class_='cmc-link')
for i in (AllimgCoin):
    if i.find('img', class_='h7vnx2-0 bCltOL') is not None:
        if len(ImgCoin) != 25:
            atribute = i.find('img', class_='h7vnx2-0 bCltOL')
            img = atribute.get('src')
            ImgCoin.append(img)


#Interface

startlist = 0
endlist = 5

def ShowList():
    for i in range(len(nameCoin)):
        if i >= startlist and i < endlist:
            textStr[i].grid(column = 1, row = i + 1)
        else:
            textStr[i].grid_forget()

def Next():
    global endlist
    global startlist
    if endlist + 5 <= len(nameCoin):
        startlist+=5
        endlist+=5
    ShowList()

def Back():
    global endlist
    global startlist
    if startlist - 5 >= 0:
        startlist-=5
        endlist-=5
    ShowList()

def Open(button):
    global draw
    global lbl
    lbl = Label(window, text = f'[{nameCoin[button]}] [{capCoin[button]}] [{priceCoin[button]}]', width=351, height=55, image=px, compound="c", bg = 'WHITE', fg = 'BLACK')  
    lbl.place(x=120, y=5)
    if draw == True:
        p = requests.get(ImgCoin[button])
        out = open("img.svg", "wb")
        out.write(p.content)
        out.close()
        drawing = svg2rlg('img.svg')
        renderPM.drawToFile(drawing, 'img.png', fmt='PNG')
        img = PhotoImage(file=f'img.png')
        panel = Label(window, image = img)
        panel.place(x=425, y=5)

def Enter():
    name = EnterTxt.get()
    find = False
    for i in range(len(nameCoin)):
        if name.lower() == nameCoin[i].lower():
            Open(i)
            find = True
    if find == False:
        lbl = Label(window, text= 'Not found', width=351, height=55, image=px, compound="c", bg = 'WHITE', fg = 'BLACK')  
        lbl.place(x=120, y=5)
        img = PhotoImage(file=f'null.png')
        panel = Label(window, image = img)
        panel.place(x=425, y=5)
           

window = Tk()
lbl = Label()
window.geometry('620x140')
window.title("TodorovCrypt")
window["bg"] = "WHITE"
px = PhotoImage(width=1, height=1)


ButtonBack = Button(window, text = '<Back', font='Arial 10 bold',command=Back, width=100, height=20, image=px, compound="c", bg = '#5294ff', fg = 'WHITE');
ButtonBack.place(x=135, y=80)


ButtonNext = Button(window, text = 'Next>', font='Arial 10 bold', command=Next, width=100, height=20, image=px, compound="c", bg = '#5294ff', fg = 'WHITE');
ButtonNext.place(x=250, y=80)

EnterTxt = Entry(window,width=20)  
EnterTxt.place(x=365, y=80)  

EnterButton = Button(window, text = 'Enter', font='Arial 10 bold', command=Enter, width=100, height=20, image=px, compound="c", bg = '#5294ff', fg = 'WHITE');
EnterButton.place(x=480, y=80)

textStr = []
draw = False
for i in range(len(nameCoin)):
    textStr.append(Button(window, text = f'{i+1}.  {nameCoin[i]}', font='Arial 8 bold', command=Open(i), width=100, height=20, image=px, compound="c", bg = '#5294ff', fg = 'WHITE'))
    textStr[i].bind("<Button-1>",lambda event, button = i: Open(button))
    lbl = Label(window, width=351, height=55, image=px, compound="c", bg = 'WHITE')
    lbl.place(x=120, y=5)
draw = True
ShowList()  
window.mainloop()