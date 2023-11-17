# Welcome to My Mastermind
***

## Task
The task is to implement a simple cli version of the classic Mastermind game.
The complexity of this task lies in reading user input from the command line, handling multiple program options
implementing logic to evaluate user guesses and provide useful feedback.

## Description
The user can provide a secret code and the number of attempts when starting the program. If no secret code is provided,
a pseudo random code will be generated. If no number of attempts is provided the default of 10 is assumed. The secret code must consist of
character digits from '0' to '8' and is of length 4.
A game loop will indicate to the player which round they're in and ask them to provide a guess. After reading the guess
from stdin, the program evaluates the guess in comparison with the secret code and displays the number of correctly placed
and misplaced digits. The game ends when the user successfully guesses the secret code or the number of attempts is used up.

## Installation
my_mastermind can be compiled by running make

## Usage
```
./my_mastermind [OPTIONS] [PARAMS]
./my_mastermind -c [CODE]
./my_mastermind -t [ATTEMPTS]
```

### The Core Team
anderhu_m

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
