[![Linux](https://github.com/Mizux/rftg/actions/workflows/linux.yml/badge.svg)](https://github.com/Mizux/rftg/actions/workflows/linux.yml)
[![Linux](https://github.com/Mizux/rftg/actions/workflows/macos.yml/badge.svg)](https://github.com/Mizux/rftg/actions/workflows/macos.yml)
[![Linux](https://github.com/Mizux/rftg/actions/workflows/windows.yml/badge.svg)](https://github.com/Mizux/rftg/actions/workflows/windows.yml)


# Introduction
This is a program to play Race for the Galaxy against AI players.

## Authors
This program was created by Keldon Jones <keldon@keldon.net>.
Many useful improvements, especially to the GUI, were made by B. Nordli.

## Dependencies
* CMAKE >= 2.LICENSE8
* MYSQL
* GTK2

## Compilation

```sh
cmake -S. -Bbuild
cmake --build build
```

## Running
Run with `cd asset; ../build/gui/gui`.  
You may specify number of players, expansion level, etc with some command line options:
```
-n <name>      -- Set the name of the human player
-s <savegame>  -- Load a savegame when starting the program
-r <num>       -- A seed to pick when initializing the random pool
-p <num>       -- Number of players (including yourself)
-a             -- Play a two-player advanced game
-e <expansion> -- Expansion level to play:
			0: Base game only
			1: The Gathering Storm
			2: Rebel vs Imperium
			3: The Brink of War
			4: Alien Artifacts
-g, -nog       -- Enable or disable goals
-t, -not       -- Enable or disable takeovers
```
You may also change these setting once the game is running with the
*Select Parameters* option under the Game menu.

## Interface
Cards in your hand are displayed across the bottom of the window.  Your
active cards are just above, in the blue-shaded area.  Your opponents
active cards will be displayed in the top colored areas.

You may move your pointer over any card to see a full-sized version in
the upper-left.

In between your hand and active area is a prompt asking for your next
play.  Typically this is a request to choose an action, choose a card
to play or cards to discard, etc.  Select an action (or two actions if
playing the two-player advanced game) by using the action buttons.
Select cards to play or discard by clicking on them in your hand area.
When you are satisfied, click the "Done" button at the far right of the
prompt area.  This button will not be clickable if your current
selection is not legal.

You can right-click a card to select all other cards (for example, when
Exploring).

## Keyboard Shortcuts
        F1:            Explore: +5
        Shift+F1:      Explore: +1, +1
        F2:            Develop
        Shift+F2:      Second Develop (in advanced game)
        F3:            Settle
        Shift+F3:      Second Settle (in advanced game)
        F4:            Consume-Trade
        Shift+F4:      Consume-x2
        F5:            Produce
        F6:            Search (The Brink of War)
        F7:            Prestige action (The Brink of War)

        F1-F9 and Shift+F1-Shift+F9:
                       Activate selectable cards in tableaux and hand
        F12/Shift+F12:
                       Select/deselect all selectable cards in hand

        Shift+Enter:   'Done' button
        Shift+Up/Down: Change selection in drop down
        F12:           Open selection drop down

## Bugs
If you encounter a bug, especially an error in the rules implementation,
please report it to keldon@keldon.net .

## Legal
The source code is copyrighted and is placed under the GPL.  For details,
see the file [LICENSE](LICENSE).

The original game of Race for the Galaxy was designed by Tom Lehmann and
published by Rio Grande Games.  Permission to distribute the card and
goal images has been granted by Rio Grande Games.
