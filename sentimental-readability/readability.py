# TODO
def main():
    text = input("Text: ")
    count_of_letters = count_letters(text)
    count_of_words = count_words(text)
    count_of_sentences = count_sentences(text)

    l = 100 * (count_of_letters / count_of_words)
    s = 100 * (count_of_sentences / count_of_words)

    index = round(0.0588 * l - 0.296 * s - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    count = 0
    for c in text:
        if c.isalpha():
            count += 1
    return count


def count_words(text):
    count = 0
    for c in text:
        if c == " ":
            count += 1
    return count + 1


def count_sentences(text):
    count = 0
    for c in text:
        if c == "!" or c == "?" or c == ".":
            count += 1
    return count


main()
