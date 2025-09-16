from cs50 import get_string
import re

def main():
    text = get_string("Text: ")
    letters = GetLetters(text)
    words = GetWords(text)
    sentences = GetSentence(text)

    # Расчет Среднего кол-ва букв на 100 слов в тексте
    L = letters / words * 100.00
    #print(f"Среднее кол-во букв на 100 слов в тексте: {L}")

    # Расчет Среднего кол-ва предложений на 100 слов в тексте
    S = sentences / words * 100.00
    #print(f"Среднее кол-во предложений на 100 слов в тексте: {S}")

    index = 0.0588 * L - 0.296 * S - 15.8

    # Вывод сообщения об уровне чтения
    if index < 1:
        print("Before Grade 1")
    elif index >= 1 and index <= 16:
        print(f"Grade: {round(index)}")
    elif index > 16:
        print("Grade 16+")

# Функция подсчета букв в тексте
def GetLetters(text):

    # Счетчик букв в тексте
    letters = 0
    for i in text:
        if i.isalpha():
            #print(i)
            letters += 1

    #print(f"Количество букв: {letters}")
    return letters


# Функция подсчета слов в тексте
def GetWords(text):

    # Счетчик слов в тексте
    words = 0
    word = text.split(' ')
    #print(word)
    for i in word:
        #print(i)
        words += 1

    #print(f"Количество слов: {words}")
    return words


# Функция подсчета слов в тексте
def GetSentence(text):

    # Счетчик предложений в тексте
    sentences = 0
    sentence = re.split(r'[.!?...] ', text)
    #print(sentence)
    for i in sentence:
        #print(i)
        sentences += 1

    #print(f"Количество предложений: {sentences}")
    return sentences

main()
