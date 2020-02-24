import string


def getAvailableLetters(lettersGuessed):
    '''
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters that represents what letters have not
      yet been guessed.
    '''
    fullstring = string.ascii_lowercase
    lettersLeft = ''
    for letter in fullstring:
        if letter not in lettersGuessed:
            lettersLeft = lettersLeft + letter
    return lettersLeft


def getGuessedWord(secretWord, lettersGuessed):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters and underscores that represents
      what letters in secretWord have been guessed so far.
    '''
    wordGuessed = ''
    for letter in secretWord:
        if letter in lettersGuessed:
            wordGuessed = wordGuessed + letter
        else:
            wordGuessed = wordGuessed + '_ '
    return wordGuessed


def isWordGuessed(secretWord, lettersGuessed):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: boolean, True if all the letters of secretWord are in lettersGuessed;
      False otherwise
    '''
    numCorrect = 0
    for letter in secretWord:
        if letter in lettersGuessed:
            numCorrect += 1
        else:
            return False
    return True


def hangman(secretWord):
    guessesLeft = 8
    lettersGuessed = []

    print('Welcome to the game Hangman!')
    print('I am thinking of a word that is ' + str(len(secretWord)) + ' letters long.')
    print('-----------')

    while guessesLeft > 0:
        if isWordGuessed(secretWord, lettersGuessed):
            return print('Congratulations, you won!')
        print('You have ' + str(guessesLeft) + ' guesses left.')
        print('Available Letters: ' + getAvailableLetters(lettersGuessed))
        user_input = input('Please guess a letter: ')
        user_input = str(user_input)
        user_input = user_input.lower()
        if user_input not in lettersGuessed:
            lettersGuessed.append(user_input)
            if user_input in secretWord:
                print("Good guess: " + getGuessedWord(secretWord, lettersGuessed))
                print('-----------')
            else:
                print("Oops! That letter is not in my word: " + getGuessedWord(secretWord, lettersGuessed))
                print('-----------')
                guessesLeft -= 1
        else:
            print("Oops! You've already guessed that letter: " + getGuessedWord(secretWord, lettersGuessed))
            print('-----------')

    return print("Sorry, you ran out of guesses. The word was " + str(secretWord))


hangman('elvin')
