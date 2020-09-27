#Introduction of game of Hex#
The game of Hex has been invented in 1942 by Piet Hein, reinvented in 1948 by John Nash, got its name in 1952 from a commercial distribution by Parker Brothers
and has been popularized by Martin Gardner in 1957. It is similar to tic-tac-toe on a hexagonal 11x11 board.

                 B - B - B - . - . - . - . - . - . - . - .
                  \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                   B - R - . - . - . - . - . - . - . - . - .
                    \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                     . - . - . - . - . - . - . - . - . - . - .
                      \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                       . - . - . - . - . - . - . - . - R - . - .
                        \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                         . - . - . - . - . - . - . - . - . - . - .
                          \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                           . - . - . - . - . - . - . - . - . - . - .
                            \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                             . - . - . - . - . - . - . - . - . - . - .
                              \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                               R - . - R - . - . - . - . - . - . - . - .
                                \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                                 . - . - . - . - . - . - . - . - . - . - .
                                  \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                                   . - . - . - . - . - . - . - . - . - . - .
                                    \ / \ / \ / \ / \ / \ / \ / \ / \ / \ / \
                                     . - . - . - . - . - . - . - . - . - . - .

The blue player must make a connected set of blue hexagons from east to west. The red player must do the same from north to south. At each turn a player chooses
an unoccupied hexagon and gives it their color. Unlike tic-tac-toe the game cannot end in a draw. Indeed it can be proven that by best play the first player wins.
(John Nash). However there is no known optimal strategy.

This is a code for implementing the game of Hex. Bascially, this programme can draw a HEX board and determining a legal position and a winning position. Furthermore,
I have added an AI that can play Hex as well. This AI is inspired from the Monte Carlo process, which help the AI to choose the best move and finally exceed human ability.

The player is  able to interact with the program and choose its “color” with blue going first. The program  has a convenient interface for entering a move, 
displaying the board, and then making its own move. The program can also determine when the game is over and announce the winner.

The AI will evaluate a position using a Monte Carlo selection of moves until the board is filled up. Then determining who won. The program takes turns. It inputs the human 
(or machine opponent if playing against another program) move. When it is the “AI”’s turn, it is to evaluate all legal available next moves and select a “best” move. Each 
legal move will be evaluated using ~1000 or more trials. Each trial winds the game forward by randomly selecting successive moves until there is a winner. The trial is counted 
as a win or loss. The ratio: wins/trials are the AI’s metric for picking which next move to make.
