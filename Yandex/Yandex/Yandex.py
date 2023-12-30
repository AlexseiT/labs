import telebot
from telebot import types

bot = telebot.TeleBot('5903911615:AAHIcVF4bLz1bt81gC4CDi09l_remTPXbhU')

class Dice():
    def __init__(self):
        1
    def RandDice(self):
        1

@bot.message_handler(commands = ['start'])
def URL(message):
    markup = types.ReplyKeyboardMarkup()
    buttonDice = types.KeyboardButton(text='🎲 Кинуть кубик d6')
    buttonCard = types.KeyboardButton(text='🃏 Случайная карта')
    
    markup.add(buttonDice, buttonCard)

    bot.send_message(message.from_user.id, "ℹ️ Это крутой бот рандомайзер\n\n✅ Выбери интересующую категорию\n\n🙃 И Развлекайся\n\n❓ Если чтото не понятно ➡️ /help ", reply_markup = markup)

@bot.message_handler(content_types=['text'])
def Change(message):
    if(message.text == '🎲 Кинуть кубик d6'):
        bot.send_message(message.chat.id, text="Кинул кубик")
    elif(message.text == '🃏 Случайная карта'):
        bot.send_message(message.chat.id, text="Вытянул карту")
    else:
        bot.send_message(message.chat.id, text="Попробуй еще раз")

def main(): 
    bot.polling()

if __name__ == "__main__": 
    main() 